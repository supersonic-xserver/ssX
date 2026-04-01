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
 * Copyright 1996 by Alan Hourihane, Wigan, England.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Alan Hourihane not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Alan Hourihane makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * ALAN HOURIHANE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL ALAN HOURIHANE BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Alan Hourihane, alanh@fairlite.demon.co.uk
 * 
 * Trident TGUI accelerated options.
 */

#include "vga256.h"
#include "xf86.h"
#include "vga.h"
#include "miline.h"
#include "compiler.h"

#include "xf86xaa.h"

extern unsigned char *tguiMMIOBase;
extern int TVGAchipset;
#include "t89_driver.h"
#include "tgui_ger.h"

int TGUIRops[16] = {
	TGUIROP_0,
	TGUIROP_AND,
	TGUIROP_SRC_AND_NOT_DST,
	TGUIROP_SRC,
	TGUIROP_NOT_SRC_AND_DST,
	TGUIROP_DST,
	TGUIROP_XOR,
	TGUIROP_OR,
	TGUIROP_NOR,
	TGUIROP_XNOR,
	TGUIROP_NOT_DST,
	TGUIROP_SRC_OR_NOT_DST,
	TGUIROP_NOT_SRC,
	TGUIROP_NOT_SRC_OR_DST,
	TGUIROP_NAND,
	TGUIROP_1
};

void TGUISync();
void TGUIMMIOSync();
void TGUISetupForFillRectSolid();
void TGUISubsequentFillRectSolid();
void TGUIMMIOSetupForFillRectSolid();
void TGUIMMIOSubsequentFillRectSolid();
void TGUISetupForScreenToScreenCopy();
void TGUISubsequentScreenToScreenCopy();
void TGUIMMIOSetupForScreenToScreenCopy();
void TGUIMMIOSubsequentScreenToScreenCopy();
void TGUISubsequentBresenhamLine();
void TGUISetupForCPUToScreenColorExpand();
void TGUISubsequentCPUToScreenColorExpand();
void TGUISetupForScreenToScreenColorExpand();
void TGUISubsequentScreenToScreenColorExpand();
void TGUISetupForFill8x8Pattern();
void TGUISubsequentFill8x8Pattern();

/*
 * The following function sets up the supported acceleration. Call it
 * from the FbInit() function in the SVGA driver.
 */
void TGUIAccelInit() {

    xf86AccelInfoRec.Flags = BACKGROUND_OPERATIONS | 
				HARDWARE_PATTERN_TRANSPARENCY |
				HARDWARE_PATTERN_ALIGN_64 |
				PIXMAP_CACHE;

#if 0
    /* TGUI 96xx series have hardware clipping */
    if (TVGAchipset == TGUI96xx) xf86AccelInfoRec.Flags |= HARDWARE_CLIP_LINE;
#endif

    if (OFLG_ISSET(OPTION_MMIO, &vga256InfoRec.options))
	xf86AccelInfoRec.Sync = TGUIMMIOSync;
    else
	xf86AccelInfoRec.Sync = TGUISync;

#if 0
    xf86GCInfoRec.PolyFillRectSolidFlags = NO_PLANEMASK;

    if (OFLG_ISSET(OPTION_MMIO, &vga256InfoRec.options))
    {
    xf86AccelInfoRec.SetupForFillRectSolid = TGUIMMIOSetupForFillRectSolid;
    xf86AccelInfoRec.SubsequentFillRectSolid = TGUIMMIOSubsequentFillRectSolid;
    }
    else
    {
    xf86AccelInfoRec.SetupForFillRectSolid = TGUISetupForFillRectSolid;
    xf86AccelInfoRec.SubsequentFillRectSolid = TGUISubsequentFillRectSolid;
    }
#endif

    xf86GCInfoRec.CopyAreaFlags = NO_PLANEMASK;

    if (OFLG_ISSET(OPTION_MMIO, &vga256InfoRec.options))
    {
	xf86AccelInfoRec.SetupForScreenToScreenCopy =
       		TGUIMMIOSetupForScreenToScreenCopy;
	xf86AccelInfoRec.SubsequentScreenToScreenCopy =
        	TGUIMMIOSubsequentScreenToScreenCopy;
    } 
    else
    {
	xf86AccelInfoRec.SetupForScreenToScreenCopy =
       		TGUISetupForScreenToScreenCopy;
	xf86AccelInfoRec.SubsequentScreenToScreenCopy =
	       	TGUISubsequentScreenToScreenCopy;
    }

#if 0
    /* Bresenham Lines */
    xf86AccelInfoRec.SubsequentBresenhamLine = TGUISubsequentBresenhamLine;
#endif

if (OFLG_ISSET(OPTION_MMIO, &vga256InfoRec.options))
{
}
else
{
    xf86AccelInfoRec.SetupForFill8x8Pattern = TGUISetupForFill8x8Pattern;
    xf86AccelInfoRec.SubsequentFill8x8Pattern = TGUISubsequentFill8x8Pattern;
}

    /* Color Expansion */
    xf86AccelInfoRec.ColorExpandFlags = VIDEO_SOURCE_GRANULARITY_PIXEL;
#if 0
    xf86AccelInfoRec.SetupForCPUToScreenColorExpand = 
	TGUISetupForCPUToScreenColorExpand;
    xf86AccelInfoRec.SubsequentCPUToScreenColorExpand = 
	TGUISubsequentCPUToScreenColorExpand;
#endif
    xf86AccelInfoRec.SetupForScreenToScreenColorExpand = 
	TGUISetupForScreenToScreenColorExpand;
    xf86AccelInfoRec.SubsequentScreenToScreenColorExpand = 
	TGUISubsequentScreenToScreenColorExpand;

    xf86InitPixmapCache(
        &vga256InfoRec,
        vga256InfoRec.virtualY * vga256InfoRec.displayWidth *
            vga256InfoRec.bitsPerPixel / 8,
        vga256InfoRec.videoRam * 1024 - 1024
    );
}

/*
 * This is the implementation of the Sync() function.
 */
void TGUISync() {
	while (inb(0x2100+GER_STATUS) & GE_BUSY);
}

void TGUIMMIOSync() {
	while ( (*(unsigned char *)(tguiMMIOBase+GER_STATUS)) & GE_BUSY);
}

/*
 * This is the implementation of the SetupForFillRectSolid function
 * that sets up the coprocessor for a subsequent batch for solid
 * rectangle fills.
 */
void TGUISetupForFillRectSolid(color, rop, planemask)
    int color, rop;
    unsigned planemask;
{
	outl(0x2100+GER_FCOLOUR, color);
	outl(0x2100+GER_BCOLOUR, color);
	outb(0x2100+GER_FMIX, TGUIRops[rop]);
	outl(0x2100+GER_DRAWFLAG, SOLIDFILL | PAT2SCR | SRCMONO | SCR2SCR);
}

void TGUIMMIOSetupForFillRectSolid(color, rop, planemask)
    int color, rop;
    unsigned planemask;
{
	TGUI_BCOLOUR(color);
	TGUI_FMIX(TGUIRops[rop]);
}
/*
 * This is the implementation of the SubsequentForFillRectSolid function
 * that sends commands to the coprocessor to fill a solid rectangle of
 * the specified location and size, with the parameters from the SetUp
 * call.
 */
void TGUISubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
	TGUISync();
	outl(0x2100+GER_DIM_XY, ((h-1) << 16) | (w-1));
	outl(0x2100+GER_DEST_XY, (y << 16) | x);
	outb(0x2100+GER_COMMAND, GE_BLT);
}

void TGUIMMIOSubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
	TGUIMMIOSync();
	TGUI_DRAWFLAG(SOLIDFILL | SCR2SCR);
	TGUI_DIM_XY(w,h);
	TGUI_DEST_XY(x,y);
	TGUI_COMMAND(GE_BLT);
}

/*
 * This is the implementation of the SetupForScreenToScreenCopy function
 * that sets up the coprocessor for a subsequent batch for solid
 * screen-to-screen copies. Remember, we don't handle transparency,
 * so the transparency color is ignored.
 */
static int blitxdir, blitydir;
 
void TGUISetupForScreenToScreenCopy(xdir, ydir, rop, planemask,
transparency_color)
    int xdir, ydir;
    int rop;
    unsigned planemask;
    int transparency_color;
{
    int direction = 0;

    if (xdir < 0) direction |= XNEG;
    if (ydir < 0) direction |= YNEG;
    if (transparency_color != -1)
    {
	outl(0x2100+GER_FCOLOUR, transparency_color);
	direction |= TRANS_ENABLE;
    }
    outl(0x2100+GER_DRAWFLAG, direction | SCR2SCR);
    outb(0x2100+GER_FMIX, TGUIRops[rop]);
    blitxdir = xdir;
    blitydir = ydir;
}

void TGUIMMIOSetupForScreenToScreenCopy(xdir, ydir, rop, planemask,
transparency_color)
    int xdir, ydir;
    int rop;
    unsigned planemask;
    int transparency_color;
{
    int direction = 0;

    if (xdir < 0) direction |= XNEG;
    if (ydir < 0) direction |= YNEG;
    if (transparency_color != -1)
    {
	TGUI_FCOLOUR(transparency_color);
	direction |= TRANS_ENABLE;
    }
    TGUI_DRAWFLAG(direction | SCR2SCR);
    TGUI_FMIX(TGUIRops[rop]);
    blitxdir = xdir;
    blitydir = ydir;
}
/*
 * This is the implementation of the SubsequentForScreenToScreenCopy
 * that sends commands to the coprocessor to perform a screen-to-screen
 * copy of the specified areas, with the parameters from the SetUp call.
 * In this sample implementation, the direction must be taken into
 * account when calculating the addresses (with coordinates, it might be
 * a little easier).
 */
void TGUISubsequentScreenToScreenCopy(x1, y1, x2, y2, w, h)
    int x1, y1, x2, y2, w, h;
{
    if (blitydir < 0) {
        y1 = y1 + h - 1;
	y2 = y2 + h - 1;
    }
    if (blitxdir < 0) {
	x1 = x1 + w - 1;
	x2 = x2 + w - 1;
    }
    TGUISync();
    outl(0x2100+GER_SRC_XY, (y1 << 16) | x1);
    outl(0x2100+GER_DEST_XY, (y2 << 16) | x2);
    outl(0x2100+GER_DIM_XY, ((h-1) << 16) | (w-1));
    outb(0x2100+GER_COMMAND, GE_BLT);
}

void TGUIMMIOSubsequentScreenToScreenCopy(x1, y1, x2, y2, w, h)
    int x1, y1, x2, y2, w, h;
{
    if (blitydir < 0) {
        y1 = y1 + h - 1;
	y2 = y2 + h - 1;
    }
    if (blitxdir < 0) {
	x1 = x1 + w - 1;
	x2 = x2 + w - 1;
    }
    TGUIMMIOSync();
    TGUI_SRC_XY(x1,y1);
    TGUI_DEST_XY(x2,y2);
    TGUI_DIM_XY(w,h);
    TGUI_COMMAND(GE_BLT);
}
void TGUISubsequentBresenhamLine(x1, y1, octant, err, e1, e2, length)
    int x1, y1, octant, err, e1, e2, length;
{
	int direction = 0;

	if (octant & YMAJOR)      direction |= YMAJ;
	if (octant & XDECREASING) direction |= XNEG;
	if (octant & YDECREASING) direction |= YNEG;
	TGUISync();
	outl(0x2100+GER_SRC_XY, (e1 << 16) | e2);
	outl(0x2100+GER_DEST_XY, (y1 << 16) | x1);
	outl(0x2100+GER_DIM_XY, (length << 16) | err);
	outl(0x2100+GER_DRAWFLAG, STENCIL | SRCMONO | PAT2SCR | SCR2SCR | direction);
	outb(0x2100+GER_COMMAND, GE_BRESLINE);
}

void SetClippingRectangle(x1, y1, x2, y2)
    int x1, y1, x2, y2;
{
	/* Used for 96xx based cards (12bit registers) */
	outw(GER_SRCCLIP_X, x1);
	outw(GER_SRCCLIP_Y, y1);
	outw(GER_DSTCLIP_X, x2);
	outw(GER_DSTCLIP_Y, y2);
}

void TGUISetupForCPUToScreenColorExpand(bg, fg, rop, planemask)
    int bg, fg, rop;
    unsigned planemask;
{
	int drawflag = 0;

	outl(0x2100+GER_FCOLOUR, fg);
        if (bg == -1)
		drawflag |= TRANS_ENABLE;
	outl(0x2100+GER_BCOLOUR, bg);
	outl(0x2100+GER_DRAWFLAG, SRCMONO | drawflag);
	outb(0x2100+GER_FMIX, TGUIRops[rop]);
}

void TGUISubsequentCPUToScreenColorExpand(x, y, w, h, skipleft)
    int x, y, w, h, skipleft;
{
	TGUISync();
	outl(0x2100+GER_DEST_XY, (y << 16) | x);
	outl(0x2100+GER_DIM_XY, ((h-1) << 16) | (w-1));
	outb(0x2100+GER_COMMAND, GE_BLT);
}

void TGUISetupForFill8x8Pattern(patternx, patterny, rop, planemask,
transparency_color)
    int patternx, patterny, rop;
    unsigned planemask;
    int transparency_color;
{
	int drawflag = 0;

	if (transparency_color != -1)
	{
		outl(0x2100+GER_FCOLOUR, transparency_color);
		drawflag |= TRANS_ENABLE;
	}
	outb(0x2100+GER_FMIX, TGUIRops[rop]); /* ROP */
	outl(0x2100+GER_DRAWFLAG, drawflag | PAT2SCR | SCR2SCR);
}

void TGUISubsequentFill8x8Pattern(patternx, patterny, x, y, w, h)
    int patternx, patterny;
    int x, y, w, h;
{
	TGUISync();
	outw(0x2100+GER_PATLOC, (patterny * vga256InfoRec.displayWidth + patternx));
	outl(0x2100+GER_DEST_XY, (y << 16) | x);
	outl(0x2100+GER_DIM_XY, ((w-1) << 16) | (h-1));
	outb(0x2100+GER_COMMAND, GE_BLT);
}

void TGUISetupForScreenToScreenColorExpand(bg, fg, rop, planemask)
    int bg, fg, rop;
    unsigned planemask;
{
	int drawflag = 0;

	outl(0x2100+GER_FCOLOUR, fg);
        if (bg == -1)
		drawflag |= TRANS_ENABLE;
	outl(0x2100+GER_BCOLOUR, bg);
	outl(0x2100+GER_DRAWFLAG, SCR2SCR | SRCMONO | drawflag);
	outb(0x2100+GER_FMIX, TGUIRops[rop]);
}

void TGUISubsequentScreenToScreenColorExpand(srcx, srcy, x, y, w, h)
    int srcx, srcy, x, y, w, h;
{
	TGUISync();
	outl(0x2100+GER_SRC_XY, (srcy << 16) | srcx);
	outl(0x2100+GER_DEST_XY, (y << 16) | x);
	outl(0x2100+GER_DIM_XY, ((h-1) << 16) | (w-1));
	outb(0x2100+GER_COMMAND, GE_BLT);
}
