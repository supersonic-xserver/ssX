/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/*
 * ET4/6K acceleration interface.
 *
 * Uses Harm Hanemaayer's generic acceleration interface (XAA).
 *
 * Author: Koen Gadeyne
 *
 * Much of the acceleration code is based on the XF86_W32 server code from
 * Glenn Lai.
 *
 */

/* $XFree86$ */

#include "vga256.h"
#include "xf86.h"
#include "vga.h"
#include "tseng.h"
#include "tseng_acl.h"

#include "xf86xaa.h"

#include "miline.h"

void TsengSync();
void TsengSetupForFillRectSolid();
void TsengSubsequentFillRectSolid();

void TsengSetupForScreenToScreenCopy();
void TsengSubsequentScreenToScreenCopy();

void TsengSetupForScanlineScreenToScreenColorExpand();
void TsengSubsequentScanlineScreenToScreenColorExpand();

void TsengSubsequentBresenhamLine();
void TsengSubsequentTwoPointLine();

int bytesperpixel;
int tseng_line_width;

/* These will hold the ping-pong registers.
 * Note that ping-pong registers might not be needed when using
 * BACKGROUND_OPERATIONS (because of the WAIT()-ing involved)
 */

LongP MemFg;
long Fg;

LongP MemBg;
long Bg;

LongP MemPat;
long Pat;



/*
 * The following function sets up the supported acceleration. Call it
 * from the FbInit() function in the SVGA driver.
 */
void TsengAccelInit() {
    /*
     * If you want to disable acceleration, just don't modify anything in
     * the AccelInfoRec.
     */

    /*
     * Set up the main acceleration flags.
     */
    xf86AccelInfoRec.Flags = BACKGROUND_OPERATIONS | 
       PIXMAP_CACHE | COP_FRAMEBUFFER_CONCURRENCY;

    /*
     * The following line installs a "Sync" function, that waits for
     * all coprocessor operations to complete.
     */
    xf86AccelInfoRec.Sync = TsengSync;

    /*
     * We want to set up the FillRectSolid primitive for filling a solid
     * rectangle.
     */
#if 1
    xf86GCInfoRec.PolyFillRectSolidFlags = NO_PLANEMASK;

    xf86AccelInfoRec.SetupForFillRectSolid = TsengSetupForFillRectSolid;
    xf86AccelInfoRec.SubsequentFillRectSolid = TsengSubsequentFillRectSolid;
#endif

    /*
     * We also want to set up the ScreenToScreenCopy (BitBLT) primitive for
     * copying a rectangular area from one location on the screen to
     * another. First we set up the restrictions. In this case, we
     * don't handle transparency color compare nor planemasks.
     */
    xf86GCInfoRec.CopyAreaFlags = NO_TRANSPARENCY | NO_PLANEMASK;
    
    xf86AccelInfoRec.SetupForScreenToScreenCopy =
        TsengSetupForScreenToScreenCopy;
    xf86AccelInfoRec.SubsequentScreenToScreenCopy =
        TsengSubsequentScreenToScreenCopy;

    /*
     * Setup hardware-line-drawing code.
     * -- currently disabled because of major bugs...
     */

#if 0
    xf86AccelInfoRec.SubsequentBresenhamLine =
        TsengSubsequentBresenhamLine;
    xf86AccelInfoRec.ErrorTermBits = 11;
#endif

#if 0
    xf86AccelInfoRec.SubsequentTwoPointLine =
        TsengSubsequentTwoPointLine;
#endif

    xf86GCInfoRec.PolyLineSolidZeroWidthFlags = NO_TRANSPARENCY | NO_PLANEMASK;
    xf86GCInfoRec.PolySegmentSolidZeroWidthFlags = NO_TRANSPARENCY | NO_PLANEMASK;

    /*
     * Color expansion primitives.
     * Since the ET6000 doesn't support CPU-to-screen color expansion,
     * we revert to scanline-screen-to-screen color expansion instead.
     * This is a less performant solution.
     */

#if 0
    xf86AccelInfoRec.ColorExpandFlags =
        VIDEO_SOURCE_GRANULARITY_PIXEL | BIT_ORDER_IN_BYTE_LSBFIRST |
        NO_TRANSPARENCY | NO_PLANEMASK;
    xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand =
        TsengSetupForScanlineScreenToScreenColorExpand;
    xf86AccelInfoRec.SubsequentScanlineScreenToScreenColorExpand =
        TsengSubsequentScanlineScreenToScreenColorExpand;
    xf86AccelInfoRec.ScratchBufferAddr = (long) W32Mix;
    xf86AccelInfoRec.ScratchBufferSize = vga256InfoRec.videoRam * 1024 - (long) W32Mix;
    ErrorF("ColorExpand ScratchBuf: Base = %d ; Size = %d\n",
           xf86AccelInfoRec.ScratchBufferAddr, xf86AccelInfoRec.ScratchBufferSize);
#endif
    
    /*
     * Finally, we set up the video memory space available to the pixmap
     * cache. In this case, all memory from the end of the virtual screen
     * to the end of video memory minus 1K, can be used.
     */
    xf86InitPixmapCache(
        &vga256InfoRec,
        vga256InfoRec.virtualY * vga256InfoRec.displayWidth *
            vga256InfoRec.bitsPerPixel / 8,
        vga256InfoRec.videoRam * 1024 - 1024
    );
    
    /*
     * For Tseng, we set up some often-used values
     */
     bytesperpixel = (vga256InfoRec.bitsPerPixel/8);
     tseng_line_width = vga256InfoRec.displayWidth*bytesperpixel;
     
     /*
      * Init ping-pong registers.
      * This might be obsoleted by the BACKGROUND_OPERATIONS flag.
      */
     MemFg = MemW32ForegroundPing;
     Fg = W32ForegroundPing;
     MemBg = MemW32BackgroundPing;
     Bg = W32BackgroundPing;
     MemPat = MemW32PatternPing;
     Pat = W32PatternPing;
}

/*
 * This is the implementation of the Sync() function.
 *
 * To avoid pipeline/cache/buffer flushing in the PCI subsystem and the VGA
 * controller, we might replace this read-intensive code with a dummy
 * accelerator operation that causes a hardware-blocking (wait-states) until
 * the running operation is done.
 */
void TsengSync() {
    WAIT_ACL;
}

/*
 * This is the implementation of the SetupForFillRectSolid function
 * that sets up the coprocessor for a subsequent batch for solid
 * rectangle fills.
 */
void TsengSetupForFillRectSolid(color, rop, planemask)
    int color, rop;
    unsigned planemask;
{
    /*
     * all registers are queued in the Tseng chips, except of course for the
     * stuff we want to store in off-screen memory. So we have to use a
     * ping-pong method for those if we want to avoid having to wait for the
     * accelerator when we want to write to these.
     */
     
/*    ErrorF("S:0x%x 0x%x ", rop, color);*/

    if (planemask != -1) ErrorF("S:planemask = 0x%x\n", planemask);

    PINGPONG;

    *ACL_FOREGROUND_RASTER_OPERATION = W32OpTable[rop];
    *ACL_DESTINATION_Y_OFFSET        = tseng_line_width-1;
    *ACL_SOURCE_ADDRESS              = Fg;

    switch (bytesperpixel)
    {
      case 1:
        color &= 0xFF;
        color = (color << 24) | (color << 16) | (color << 8) | color;
        break;
      case 2:
        color &= 0xFFFF;
        color = (color << 16) | color;
        break;
    }
    *MemFg = color;

    if (et4000_type <= TYPE_ET4000W32I)
    {
        /* The W32i only supports 8bpp acceleration */
        *(LongP)(MemFg + 4)             = color;
        *ACL_SOURCE_WRAP                = 0x12;
        *ACL_SOURCE_Y_OFFSET            = 0x3;
    }
    else /* w32p */
    {
      /*
       * only the ET6000 has 24bpp capabilities, and the init code
       * should make sure 3 bytes per pixel can never happen at this point.
       */

      if (bytesperpixel == 3)
        *ACL_SOURCE_WRAP                = 0x0A;  /* 3x1 wrap for 24bpp */
      else
        *ACL_SOURCE_WRAP                = 0x02;  /* 4x1 wrap */
    }

    if (et4000_type>=TYPE_ET6000)
        *ACL_MIX_CONTROL                = 0x33;
    else
        *ACL_ROUTING_CONTROL            = 0x00;

}

/*
 * This is the implementation of the SubsequentForFillRectSolid function
 * that sends commands to the coprocessor to fill a solid rectangle of
 * the specified location and size, with the parameters from the SetUp
 * call.
 */
void TsengSubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    int destaddr;
    destaddr = y * tseng_line_width + x * bytesperpixel;

    /*
     * On Tseng chips, all "queued registers" are blocking until the current
     * accelerated operation has finished. Thus, we don't need a WAIT here,
     * since the chip will block the writing (with hardware-wait-states)
     * until the accelerator has finished.
     */

    *ACL_XY_DIRECTION = 0; /* if this is not reset here, drawing a line
                            * in between blitting, with the same ROP, color, etc
                            * will not cause a call to SetupFor..., and thus
                            * the direction register will have been changed by
                            * the last LineDraw operation.
                            */
    SET_XY(w, h);
    START_ACL(destaddr);
}

/*
 * This is the implementation of the SetupForScreenToScreenCopy function
 * that sets up the coprocessor for a subsequent batch of
 * screen-to-screen copies. Remember, we don't handle transparency,
 * so the transparency color is ignored.
 */
static int blitxdir, blitydir;
 
void TsengSetupForScreenToScreenCopy(xdir, ydir, rop, planemask,
transparency_color)
    int xdir, ydir;
    int rop;
    unsigned planemask;
    int transparency_color;
{
    /*
     * xdir can be either 1 (left-to-right) or -1 (right-to-left).
     * ydir can be either 1 (top-to-bottom) or -1 (bottom-to-top).
     */

    int i;

    blitxdir = xdir;
    blitydir = ydir;
    
/*    ErrorF("C"); */

    *ACL_SOURCE_WRAP    = 0x77;
    *ACL_FOREGROUND_RASTER_OPERATION = W32OpTable[rop];

    i = 0;
    if (xdir == -1) i |= 0x1;
    if (ydir == -1) i |= 0x2;
    *ACL_XY_DIRECTION                   = i;
    *ACL_DESTINATION_Y_OFFSET           = tseng_line_width-1;
    *ACL_SOURCE_Y_OFFSET                = tseng_line_width-1;
    if (et4000_type >= TYPE_ET6000)
        *ACL_MIX_CONTROL                = 0x33;
    else
        *ACL_ROUTING_CONTROL            = 0x00;
}

/*
 * This is the implementation of the SubsequentForScreenToScreenCopy
 * that sends commands to the coprocessor to perform a screen-to-screen
 * copy of the specified areas, with the parameters from the SetUp call.
 * In this sample implementation, the direction must be taken into
 * account when calculating the addresses (with coordinates, it might be
 * a little easier).
 */
void TsengSubsequentScreenToScreenCopy(x1, y1, x2, y2, w, h)
    int x1, y1, x2, y2, w, h;
{
    int srcaddr, destaddr;
    
    /* tseng chips want x-sizes in bytes, not pixels */
    x1 *= bytesperpixel;
    x2 *= bytesperpixel;
    
    /*
     * If the direction is "decreasing", the chip wants the addresses
     * to be at the other end, so we must be aware of that in our
     * calculations.
     */
    if (blitydir == -1) {
        srcaddr = (y1 + h - 1) * tseng_line_width;
	destaddr = (y2 + h - 1) * tseng_line_width;
    } else {
        srcaddr = y1 * tseng_line_width;
        destaddr = y2 * tseng_line_width;
    }
    if (blitxdir == -1) {
        /* Accelerator start address must point to first byte to be processed.
         * Depending on the direction, this is the first or the last byte
         * in the multi-byte pixel.
         */
	srcaddr += x1 + w * bytesperpixel - 1;
	destaddr += x2 + w * bytesperpixel - 1;
    } else {
	srcaddr += x1;
	destaddr += x2;
    }

    SET_XY(w, h);
    *(ACL_SOURCE_ADDRESS) = srcaddr;
    START_ACL(destaddr);

}

static int ColorExpandDst;

void TsengSetupForScanlineScreenToScreenColorExpand(x, y, w, h, bg, fg, rop, planemask)
    int x, y, w, h, bg, fg, rop, planemask;
{

/*    ErrorF("C");*/

    PINGPONG;

    ColorExpandDst = y * tseng_line_width + x * bytesperpixel;

    *ACL_FOREGROUND_RASTER_OPERATION 	= W32OpTable[rop];
    *ACL_BACKGROUND_RASTER_OPERATION	= W32PatternOpTable[rop];
    if (et4000_type == TYPE_ET6000)
      *ACL_MIX_CONTROL			= 0x32;
    else
      *ACL_ROUTING_CONTROL		= 0x02;

    *ACL_XY_DIRECTION			= 0;

    *ACL_DESTINATION_Y_OFFSET		= tseng_line_width-1;

    switch (bytesperpixel)
    {
      case 1:
        fg &= 0xFF;
        fg = (fg << 24) | (fg << 16) | (fg << 8) | fg;
        bg &= 0xFF;
        bg = (bg << 24) | (bg << 16) | (bg << 8) | bg;
        break;
      case 2:
        fg &= 0xFFFF;
        fg = (fg << 16) | fg;
        bg &= 0xFFFF;
        bg = (bg << 16) | bg;
        break;
    }

    *ACL_SOURCE_WRAP			= 0x02;
    *ACL_SOURCE_Y_OFFSET		= 0x3;
    *ACL_SOURCE_ADDRESS                 = Fg;
    *MemFg                              = fg;

    *ACL_PATTERN_WRAP			= 0x02;
    *ACL_PATTERN_Y_OFFSET		= 0x3;
    *ACL_PATTERN_ADDRESS		= Pat;
    *MemPat		 		= bg;

    *ACL_MIX_Y_OFFSET 			= 31;

    *ACL_XY_DIRECTION                   = 0;

    SET_XY(w, 1);
}

void TsengSubsequentScanlineScreenToScreenColorExpand(srcaddr)
    int srcaddr;
{
/*    WAIT_XY;*/  /* this should not be needed -- but it is */
    *ACL_MIX_ADDRESS = srcaddr;
    START_ACL(ColorExpandDst);
    ColorExpandDst += tseng_line_width;
}

/*
 * W32p/ET6000 hardware linedraw code. 
 *
 * Actually, the Tseng engines are rather slow line-drawing machines.
 * On 350-pixel long lines, the _raw_ accelerator performance is about
 * 24400 lines per second. And that is "only" about 8.5 Million pixels
 * per second.
 * The break-even point is a Pentium-133, which does line-drawing as fast as
 * the ET6000, including X-overhead.
 * Of course, there's the issue of hardware parallellism that makes a difference.
 *
 * TsengSetupForFillRectSolid() is used as a setup function
 */


void TsengSubsequentBresenhamLine(x1, y1, octant, err, e1, e2, length)
   int x1, y1, octant, err, e1, e2, length;
{
   int algrthm=0, direction=0;
   int destaddr;

   destaddr = y1 * tseng_line_width + x1 * bytesperpixel;
   
   direction = W32BresTable[octant];

   if (octant & XDECREASING)
     destaddr += bytesperpixel-1;

   if (!(octant & YDECREASING))
     algrthm = 16;
   
   if (!(octant & YMAJOR))
   {
       SET_XY_RAW(length * bytesperpixel - 1, 0xFFF);
   }
   else
   {
       SET_XY_RAW(0xFFF, length -1);
   }

   SET_DELTA(e1>>1, length);
   
   *ACL_XY_DIRECTION = 0x80 | algrthm | direction;
   
   START_ACL(destaddr);
}

/*
 * Two-point lines
 */

void TsengSubsequentTwoPointLine(x1, y1, x2, y2, bias)
   int x1, y1, x2, y2, bias;
{
   int dx, dy, xdir, ydir, adir, destaddr;

   ErrorF("L");
   dx = x2-x1;
   if (dx==0) ErrorF("%d,%d-%d ", x1, y1, y2);
   if (dx<0)
     {
       xdir = 1;
       dx = -dx;
     }
   else
     {
       xdir = 0;
     }

   dy = y2-y1;
   if (dy<0)
     {
       ydir = 1;
       dy = -dy;
     }
   else
     {
       ydir = 0;
     }

   if (dx >= dy)  /* X is major axis */
   {
     adir = 1;
     SET_XY_RAW(dx * bytesperpixel - 1, 0xFFF);
     SET_DELTA(dy, dx);
   }
   else           /* Y is major axis */
   {
     adir = 0;
     SET_XY_RAW(0xFFF, dy - 1);
     SET_DELTA(dx, dy);
   }

   *ACL_XY_DIRECTION = 0x80 | (((!ydir) & 1) << 4) | (adir << 2) | (ydir << 1) | xdir;

   destaddr = y1 * tseng_line_width + x1 * bytesperpixel;
   if (xdir == 1)
   {
     /* destaddr must point to highest addressed byte in the pixel when drawing
      * right-to-left
      */
     destaddr += bytesperpixel-1;
   }
   
   START_ACL(destaddr);
}

