/* $XFree86$ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * New-style acceleration for the Laguna-family (CL-GD5462/5464).
 */

#include "vga256.h"
#include "xf86.h"
#include "vga.h"

#include "../../vgainit/xf86gc.h"

#include "cir_driver.h"
#include "cirBlitLG.h"

void LagunaSync();
void LagunaSetupForFillRectSolid();
void LagunaSubsequentFillRectSolid();
void LagunaSetupForScreenToScreenCopy();
void LagunaSubsequentScreenToScreenCopy();
void LagunaSetupForCPUToScreenColorExpand();
void LagunaSubsequentCPUToScreenColorExpand();
void LagunaSetupForScreenToScreenColorExpand();
void LagunaSubsequentScreenToScreenColorExpand();

void LagunaAccelInit() {
    xf86AccelInfoRec.Flags = BACKGROUND_OPERATIONS | PIXMAP_CACHE
        | ONLY_LEFT_TO_RIGHT_BITBLT;
    xf86AccelInfoRec.Sync = LagunaSync;
    xf86GCInfoRec.PolyFillRectSolidFlags |= NO_PLANEMASK;
    xf86AccelInfoRec.SetupForFillRectSolid = LagunaSetupForFillRectSolid;
    xf86AccelInfoRec.SubsequentFillRectSolid = LagunaSubsequentFillRectSolid;
    xf86GCInfoRec.CopyAreaFlags |= NO_PLANEMASK | NO_TRANSPARENCY;
    xf86AccelInfoRec.SetupForScreenToScreenCopy =
        LagunaSetupForScreenToScreenCopy;
    xf86AccelInfoRec.SubsequentScreenToScreenCopy =
        LagunaSubsequentScreenToScreenCopy;
#if 0
    /*
     * I took the liberty of guessing what kind of color expansion
     * the Laguna chips handle:
     *
     * Transfer DWORDS to HOSTDATA. HOSTDATA has a 1024 byte range.
     * Scanlines are padded to DWORD boundaries.
     * The bit order within a byte is MSB-First.
     * 24bpp color expansion is supported, but only with transparency.
     *
     * Screen-to-screen color expansion is not yet implemented.
     */
    xf86AccelInfoRec.ColorExpandFlags =
        SCANLINE_PAD_DWORD | CPU_TRANSFER_PAD_DWORD |
        BIT_ORDER_IN_BYTE_MSBFIRST | VIDEO_SOURCE_GRANULARITY_DWORD;
    if (vga256InfoRec.bitsPerPixel == 24)
        xf86AccelInfoRec.ColorExpandFlags |= ONLY_TRANSPARENCY_SUPPORTED;
    xf86AccelInfoRec.SetupForCPUToScreenColorExpand =
        LagunaSetupForCPUToScreenColorExpand;
    xf86AccelInfoRec.SubsequentCPUToScreenColorExpand =
        LagunaSubsequentCPUToScreenColorExpand;
    xf86AccelInfoRec.CPUToScreenColorExpandBase =
        cirrusMMIOBase + HOSTDATA;
    xf86AccelInfoRec.CPUToScreenColorExpandRange = 1024;
#endif
    xf86InitPixmapCache(&vga256InfoRec, vga256InfoRec.virtualY *
        vga256InfoRec.displayWidth * vga256InfoRec.bitsPerPixel / 8,
        vga256InfoRec.videoRam * 1024 - 1024);
}

void LagunaSync() {
    while (!LgReady());
}

void LagunaSetupForFillRectSolid(color, rop, planemask)
    int color, rop, planemask;
{
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        color & = 0xFF;
        color |= (color << 8) | (color << 16) | (color << 24);
        break;
    /* Why isn't this necessary for 16bpp? */
    default :
        break;
    }
    /*
     * Does RDRAM have any special support for solid filling that
     * we might enable here?
     */
    LgSETBACKGROUND(color);
    LgSETROP(lgCirrusRop[rop]);
    LgSETMODE(SCR2SCR | COLORFILL);
}

void LagunaSubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    /*
     * As long as we are waiting to here, that large PCI write buffer
     * on the motherboard will get flushed again and again. Querying
     * for the number of free FIFO slots (and doing that as little as
     * possible by keeping track of the number of free slots) will
     * help, but is still a bottleneck. It would be best to not
     * do any querying at all.
     */
    LagunaSync();
    LgSETDSTXY(x, y);
    LgSETEXTENTS(w, h);
}

static int blitxdir, blitydir;
 
void LagunaSetupForScreenToScreenCopy(xdir, ydir, rop, planemask,
transparency_color)
    int xdir, ydir;
    int rop;
    unsigned planemask;
    int transparency_color;
{
    int bltmode;
    LagunaSync();
    /* There's no support for transparency color compare. */
    blitxdir = xdir;
    blitydir = ydir;
    bltmode = 0;
    if (ydir < 0)
	bltmode |= BLITUP;
    LgSETROP(lgCirrusRop[rop]);
    LgSETMODE(SCR2SCR | COLORSRC | bltmode);
}

void LagunaSubsequentScreenToScreenCopy(x1, y1, x2, y2, w, h)
    int x1, y1, x2, y2, w, h;
{
    int srcaddr, destaddr;
    /*
     * We have set the flag indicating that xdir must be one,
     * so we can assume that here.
     */
    if (blitydir == -1) {
        y1 += h - 1;
        y2 += h - 1;
    }
    LagunaSync();
    LgSETSRCXY(x1, y1);
    LgSETDSTXY(x2, y2);
    LgSETEXTENTS(w, h);
}

/*
 * CPU-to-screen color expansion.
 */
 
void LagunaSetupForCPUToScreenColorExpand(bg, fg, rop, planemask)
    int bg, fg, rop;
    unsigned int planemask;
{
    int load;
    loadbg = FALSE;
    if (bg != -1)
        loadbg = TRUE;
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        /* Is this required? */
        fg & = 0xFF;
        fg |= (fg << 8) | (fg << 16) | (fg << 24);
        if (bg != -1) {
            bg & = 0xFF;
            bg |= (bg << 8) | (bg << 16) | (bg << 24);
        }
        break;
    /* Why isn't this necessary for 16bpp? */
    default :
        break;
    }
    /*
     * With solid filling, the background color was the fill color.
     * Does this mean the colors need be reversed?
     */
    if (loadbg) {
        LgSETBACKGROUND(bg);
    }
    LgSETFOREGROUND(fg);
    LgSETROP(lgCirrusRop[rop]);
    LgSETMODE(HOST2SCR | MONOSRC);
}

void LagunaSubsequentCPUToScreenColorExpand(x, y, w, h, skipleft)
    int x, y, w, h, skipleft;
{
    /*
     * I assume the higher level code has called Sync(), which is
     * a reasonable assumption since it transferred the CPU data.
     */
    LgSETSRCXY(x, y);
    LgSETEXTENTS(w, h);
}
