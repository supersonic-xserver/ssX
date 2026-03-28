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
 * New-style acceleration for chips with BitBLT engine:
 *
 *					DWORD
 *				Solid	Align	Left		Transp.	Vert.
 *			Auto	Fill /	Color	Edge	32bpp	Color   Pattern
 *		MMIO	Start	24bpp	Exp	Clip	Support	Compare Alignm.
 * CL-GD5426							Yes
 * CL-GD5428							Yes
 * CL-GD5429	Yes				Yes			Yes
 * CL-GD5430/40	Yes				Yes			Yes
 * CL-GD5434	Yes					Yes (1)
 * CL-GD5436	Yes	Yes	Yes	Yes	Yes	Yes	?	Yes
 * CL-GD5446	Yes	Yes	Yes?	Yes?	?	?	?	?
 * CL-GD7543							Yes
 * CL-GD7548	Yes	Yes					Yes
 * CL-GD7555	Yes	Yes	?	?	?	?	?	?
 *
 * (1) 8x8 non-color expand pattern fill not supported at 32bpp.
 *
 * In the case of the 7548, I wonder if it shares some of the other newer
 * BitBLT features such as clipping for color expansion. The databook doesn't
 * mention this.
 *
 * Also, it's unclear whether the CL-GD5436 has transparency color compare
 * (maybe it was a late feature).
 *
 * I have made the assumption that it is OK on all chips with MMIO to write
 * a 32-bit word to the MMIO address 0x18:
 *
 * 0x18		BLT Mode
 * 0x19		Undefined
 * 0x1A		Raster OP
 * 0x1B         BLT Mode Extensions (GD5436/46 only)
 */

#include "vga256.h"
#include "xf86.h"
#include "vga.h"

#include "xf86xaa.h"

#include "cir_driver.h"
#include "cirBlitMM.h"


#define CHIPHASPACKED24FILL() \
    (cirrusChip == CLGD5436 || cirrusChip == CLGD5446)

#define CHIPHASAUTOSTART() \
    (cirrusChip == CLGD5436 || cirrusChip == CLGD5446 || \
    cirrusChip == CLGD7548)

#define CHIPHASSOLIDCOLORFILL() \
    (cirrusChip == CLGD5436 || cirrusChip == CLGD5446)
    
#define CHIPHASTRANSPARENCYCOMPARE() \
    (cirrusChip == CLGD5426 || cirrusChip == CLGD5428 || \
    cirrusChip == CLGD7543 || cirrusChip == CLGD7548)

/* "Write Mask" is used for left-edge clipping. */
#define CHIPHASWRITEMASK() \
    (cirrusChip == CLGD5430 || cirrusChip == CLGD5436 || \
    cirrusChip == CLGD5446)

#define CHIPHASDWORDCOLOREXPANSIONSCANLINEPAD() \
    (cirrusChip == CLGD5436 || cirrusChip == CLGD5446)

#define WAITEMPTY()

#define BPPADJUST(x) \
    vga256InfoRec.bitsPerPixel == 8 ? x : \
    vga256InfoRec.bitsPerPixel == 16 ? x * 2 : \
    vga256InfoRec.bitsPerPixel == 24 ? x * 3 : x * 4

#ifndef MMIO    

int cirrusUseAutoStart = FALSE;
int cirrusUseSolidColorFill = FALSE;

#else

extern int cirrusUseAutoStart, cirrusUseSolidColorFill;

#define MMIONAME(x) #define x x##MMIO

#define MMIONAME(CirrusAccelInit)
#define MMIONAME(CirrusSetupForFillRectSolid)
#define MMIONAME(Cirrus8SubsequentFillRectSolid)
#define MMIONAME(Cirrus16SubsequentFillRectSolid)
#define MMIONAME(Cirrus24SubsequentFillRectSolid)
#define MMIONAME(Cirrus32SubsequentFillRectSolid)

#endif

void CirrusSync();
void CirrusSetupForFillRectSolid();
void Cirrus8SubsequentFillRectSolid();
void Cirrus16SubsequentFillRectSolid();
void Cirrus24SubsequentFillRectSolid();
void Cirrus32SubsequentFillRectSolid();
void CirrusSetupForScreenToScreenCopy();
void Cirrus8SubsequentScreenToScreenCopy();
void Cirrus16SubsequentScreenToScreenCopy();
void Cirrus24SubsequentScreenToScreenCopy();
void Cirrus32SubsequentScreenToScreenCopy();
void CirrusSetupForCPUToScreenColorExpand();
void CirrusSubsequentCPUToScreenColorExpand();
void CirrusSetupForScreenToScreenColorExpand();
void CirrusSubsequentScreenToScreenColorExpand();
void CirrusSetupForScanlineScreenToScreenColorExpand();
void CirrusSubsequentScanlineScreenToScreenColorExpand();
void CirrusSetupFor8x8PatternFill();
void CirrusSubsequent8x8PatternFill();
void CirrusSetupFor8x8PatternColorExpand();
void CirrusSubsequent8x8PatternColorExpand();

void CirrusAccelInit() {
    /* Initialization for chips with MMIO. */
    xf86AccelInfoRec.Flags = BACKGROUND_OPERATIONS | PIXMAP_CACHE
        | ONLY_TWO_BITBLT_DIRECTIONS | HARDWARE_PATTERN_ALIGN_64;
    xf86AccelInfoRec.Sync = CirrusSync;
    xf86GCInfoRec.PolyFillRectSolidFlags |= NO_PLANEMASK;
    if (vga256InfoRec.bitsPerPixel == 24 && !CHIPHASPACKED24FILL())
        xf86GCInfoRec.PolyFillRectSolidFlags |= RGB_EQUAL;
    xf86AccelInfoRec.SetupForFillRectSolid = CirrusSetupForFillRectSolid;
    switch (vgaBitsPerPixel) {
    case 8 :
        xf86AccelInfoRec.SubsequentFillRectSolid = Cirrus8SubsequentFillRectSolid;
        break;
    case 16 :
        xf86AccelInfoRec.SubsequentFillRectSolid = Cirrus16SubsequentFillRectSolid;
        break;
    case 24 :
        xf86AccelInfoRec.SubsequentFillRectSolid = Cirrus24SubsequentFillRectSolid;
        break;
    case 32 :
        xf86AccelInfoRec.SubsequentFillRectSolid = Cirrus32SubsequentFillRectSolid;
        break;
    }
    xf86GCInfoRec.CopyAreaFlags |= NO_PLANEMASK;
    if (!CHIPHASTRANSPARENCYCOMPARE())
        xf86GCInfoRec.CopyAreaFlags |= NO_TRANSPARENCY;
    xf86AccelInfoRec.SetupForScreenToScreenCopy = CirrusSetupForScreenToScreenCopy;
    switch (vgaBitsPerPixel) {
    case 8 :
        xf86AccelInfoRec.SubsequentScreenToScreenCopy = Cirrus8SubsequentScreenToScreenCopy;
        break;
    case 16 :
        xf86AccelInfoRec.SubsequentScreenToScreenCopy = Cirrus16SubsequentScreenToScreenCopy;
        break;
    case 24 :
        xf86AccelInfoRec.SubsequentScreenToScreenCopy = Cirrus24SubsequentScreenToScreenCopy;
        break;
    case 32 :
        xf86AccelInfoRec.SubsequentScreenToScreenCopy = Cirrus32SubsequentScreenToScreenCopy;
        break;
    }
#if 0
    xf86AccelInfoRec.SetupForFill8x8Pattern = CirrusSetupFor8x8PatternFill;
    xf86AccelInfoRec.SubsequentFill8x8Pattern = CirrusSubsequent8x8PatternFill;
#endif
    /* Color expansion. */
    if (vga256InfoRec.bitsPerPixel != 24 || CHIPHASPACKED24FILL()) {
        xf86AccelInfoRec.ColorExpandFlags =
            CPU_TRANSFER_PAD_DWORD |
            BIT_ORDER_IN_BYTE_MSBFIRST | VIDEO_SOURCE_GRANULARITY_DWORD;
        if (CHIPHASDWORDCOLOREXPANSIONSCANLINEPAD())
            xf86AccelInfoRec.ColorExpandFlags |= SCANLINE_PAD_DWORD;
        else
            xf86AccelInfoRec.ColorExpandFlags |= SCANLINE_PAD_BYTE;
        if (vga256InfoRec.bitsPerPixel == 24)
            /*
             * The 5436 (and 46?), which support 24bpp color expansion,
             * only support it with transparency.
             */
            xf86AccelInfoRec.ColorExpandFlags |= ONLY_TRANSPARENCY_SUPPORTED;
#if 0
        xf86AccelInfoRec.SetupFor8x8PatternColorExpand =
            CirrusSetupFor8x8PatternColorExpand;
        xf86AccelInfoRec.Subsequent8x8PatternColorExpand =
            CirrusSubsequent8x8PatternColorExpand;
#endif
	if (CHIPHASDWORDCOLOREXPANSIONSCANLINEPAD()) {
            if (CHIPHASWRITEMASK())
                xf86AccelInfoRec.ColorExpandFlags |= LEFT_EDGE_CLIPPING;
            xf86AccelInfoRec.SetupForCPUToScreenColorExpand =
                CirrusSetupForCPUToScreenColorExpand;
            xf86AccelInfoRec.SubsequentCPUToScreenColorExpand =
                CirrusSubsequentCPUToScreenColorExpand;
            xf86AccelInfoRec.SetupForScreenToScreenColorExpand =
                CirrusSetupForScreenToScreenColorExpand;
            xf86AccelInfoRec.SubsequentScreenToScreenColorExpand =
                CirrusSubsequentScreenToScreenColorExpand;
        }
        else {
            /*
             * CPU-to-screen color expansion with BYTE padding doesn't
             * work yet, so we have to use the indirect method (which
             * isn't particularly fast because there's no coprocessor/
             * CPU framebuffer concurrency.
             */
            xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand =
                CirrusSetupForScanlineScreenToScreenColorExpand;
            xf86AccelInfoRec.SubsequentScanlineScreenToScreenColorExpand =
                CirrusSubsequentScanlineScreenToScreenColorExpand;
            xf86AccelInfoRec.ScratchBufferAddr = cirrusBufferSpaceAddr;
            xf86AccelInfoRec.ScratchBufferSize = cirrusBufferSpaceSize;
        }
    }
    if (CHIPHASAUTOSTART())
        cirrusUseAutoStart = TRUE;
    if (CHIPHASSOLIDCOLORFILL())
        cirrusUseSolidColorFill = TRUE;
    xf86InitPixmapCache(&vga256InfoRec, vga256InfoRec.virtualY *
        vga256InfoRec.displayWidth * vga256InfoRec.bitsPerPixel / 8,
        vga256InfoRec.videoRam * 1024 - 1024 - cirrusBufferSpaceSize);
}

void CirrusInitializeBitBLTEngine() {
   int bytewidth;
   bytewidth = vga256InfoRec.displayWidth * vga256InfoRec.bitsPerPixel / 8;
   SETSRCPITCH(bytewidth);
   SETDESTPITCH(bytewidth);
   if (CHIPHASTRANSPARENCYCOMPARE())
       SETTRANSPARENCYCOLORMASK16(0);
   if (CHIPHASDWORDCOLOREXPANSIONSCANLINEPAD())
       SETBLTMODEEXT(SOURCEDWORDGRANULARITY);
}

void CirrusSync() {
    WAITUNTILFINISHED();
#if 0
    /*
     * This is not necessary, as long as in every operation the
     * BLTMODEEXT is also written by using a SETBLTMODEANDROP command.
     */
    if (cirrusUseSolidColorFill)
        SETBLTMODEEXT(0);
#endif
}

void CirrusSetupForFillRectSolid(color, rop, planemask)
    int color, rop, planemask;
{
    int bltmode;
    if (vga256InfoRec.bitsPerPixel >= 24 &&
    (vga256InfoRec.bitsPerPixel != 24 || CHIPHASPACKED24FILL())) {
        if (!cirrusUseSolidColorFill) {
            SETBACKGROUNDCOLOR32(color);
        }
        SETFOREGROUNDCOLOR32(color);
    }
    else {
        if (!cirrusUseSolidColorFill) {
            SETBACKGROUNDCOLOR16(color);
        }
        SETFOREGROUNDCOLOR16(color);
    }
#if 0
    if (!cirrusUseSolidColorFill)
#endif
        SETSRCADDR(0);
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        bltmode = COLOREXPAND | PATTERNCOPY;
        break;
    case 16 :
        bltmode = COLOREXPAND | PATTERNCOPY | PIXELWIDTH16;
        break;
    case 24 :
        if (CHIPHASPACKED24FILL()) {
            bltmode = COLOREXPAND | PATTERNCOPY | PIXELWIDTH24;
        }
        else {
            bltmode = COLOREXPAND | PATTERNCOPY;
        }
        break;
    default : /* 32 */
        bltmode = COLOREXPAND | PATTERNCOPY | PIXELWIDTH32;
        break;
    }
    if (cirrusUseSolidColorFill) {
        SETBLTMODEANDROP(bltmode, SOLIDCOLORFILL, cirrus_rop[rop]);
    }
    else {
        SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
    }
}

void Cirrus8SubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    int destaddr;
    destaddr = y * vga256InfoRec.displayWidth + x;
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTH(w);				/* 8 */
    SETHEIGHT(h);
#if 0
    if (!cirrusUseSolidColorFill)
        SETSRCADDR(0);				/* 20 */
#endif
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

void Cirrus16SubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    int destaddr;
    destaddr = (y * vga256InfoRec.displayWidth + x) * 2;
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTH(w * 2);
    SETHEIGHT(h);				/* 10 */
#if 0
    if (!cirrusUseSolidColorFill)
        SETSRCADDR(0);				/* 20 */
#endif
    SETDESTADDR(destaddr);			/* 10 */
    if (!cirrusUseAutoStart)
        STARTBLT();
}

void Cirrus24SubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    int destaddr;
    destaddr = (y * vga256InfoRec.displayWidth + x) * 3;
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTH(w * 3);				/* 8 */
    SETHEIGHT(h);				/* 10 */
#if 0
    if (!cirrusUseSolidColorFill)
        SETSRCADDR(0);				/* 20 */
#endif
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

void Cirrus32SubsequentFillRectSolid(x, y, w, h)
    int x, y, w, h;
{
    int destaddr;
    destaddr = (y * vga256InfoRec.displayWidth + x) * 4;
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTH(w * 4);				/* 8 */
    SETHEIGHT(h);				/* 10 */
#if 0
    if (!cirrusUseSolidColorFill)
        SETSRCADDR(0);				/* 20 */
#endif
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

/*
 * Screen-to-screen BitBLT.
 *
 * Any raster-op is supported.
 * Planemask is supported in all modes except 24bpp.
 */

static int blitxdir, blitydir;
 
void CirrusSetupForScreenToScreenCopy(xdir, ydir, rop, planemask,
transparency_color)
    int xdir, ydir;
    int rop;
    unsigned planemask;
    int transparency_color;
{
    int bltmode;
    bltmode = 0;
    /* Set up optional transparency compare. */
    if (transparency_color != -1) {
        /*
         * As far as I'm aware, the only chips that support transparency
         * color compare only support it with 8/16bpp.
         */
        if (vga256InfoRec.bitsPerPixel == 8) {
            transparency_color &= 0xFF;
            transparency_color |= transparency_color << 8;
        }
        SETTRANSPARENCYCOLOR16(transparency_color);
        bltmode |= TRANSPARENCYCOMPARE;
    }
#if 0
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        SETSRCPITCH(vga256InfoRec.displayWidth);
        break;
    case 16 :
        SETSRCPITCH(vga256InfoRec.displayWidth * 2);
        break;
    case 24 :
        SETSRCPITCH(vga256InfoRec.displayWidth * 3);
        break;
    default : /* case 32 */
        SETSRCPITCH(vga256InfoRec.displayWidth * 4);
        break;
    }
#endif
    /* Set up the blit direction. */
    blitxdir = xdir;
    blitydir = ydir;
    if (ydir < 0)
	bltmode |= BACKWARDS;
    SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
}

/* This a bit ugly but I don't feel like duplicating the code this time. */

#define MAPSubsequentScreenToScreenCopy(bpp) \
void Cirrus##bpp##SubsequentScreenToScreenCopy(x1, y1, x2, y2, w, h) \
    int x1, y1, x2, y2, w, h; \
{ \
    int srcaddr, destaddr; \
    /* \
     * We have set the flag indicating that xdir and ydir must be equal, \
     * so we can assume that here. \
     */ \
    if (blitydir == -1) { \
        srcaddr = (y1 + h - 1) * vga256InfoRec.displayWidth * (bpp / 8); \
	destaddr = (y2 + h - 1) * vga256InfoRec.displayWidth * (bpp / 8); \
    } else { \
        srcaddr = y1 * vga256InfoRec.displayWidth * (bpp / 8); \
        destaddr = y2 * vga256InfoRec.displayWidth * (bpp / 8); \
    } \
    if (blitxdir == -1) { \
	srcaddr += (x1 + w) * (bpp / 8) - 1; \
	destaddr += (x2 + w) * (bpp / 8) - 1; \
    } else { \
	srcaddr += x1 * (bpp / 8); \
	destaddr += x2 * (bpp / 8); \
    } \
    if (cirrusUseAutoStart) \
        WAITEMPTY(); \
    else \
        WAITUNTILFINISHED(); \
    SETSRCADDR(srcaddr); \
    w *= (bpp / 8); \
    SETWIDTHANDHEIGHT(w, h); \
    SETDESTADDR(destaddr); \
    if (!cirrusUseAutoStart) \
        STARTBLT(); \
}

MAPSubsequentScreenToScreenCopy(8)
MAPSubsequentScreenToScreenCopy(16)
MAPSubsequentScreenToScreenCopy(24)
MAPSubsequentScreenToScreenCopy(32)

/*
 * CPU-to-screen color expansion.
 */
 
void CirrusSetupForCPUToScreenColorExpand(bg, fg, rop, planemask)
    int bg, fg, rop;
    unsigned int planemask;
{
    int bltmode, loadbg;
    bltmode = 0;
    if (bg == -1)
        bltmode = TRANSPARENCYCOMPARE;
    /*
     * There are three different types of chip regarding color expansion
     * with transparency:
     *
     * - The CL-GD5426/28/7543/7548, which have a transparency compare
     *   color. The background color and the 16-bit transparency color
     *   (doubled at 8bpp) must both be loaded with the same unique value.
     * - The CL-GD5434. It requires requires the 32-bit background color
     *   to be set to the logical inverse of the foreground color, with both
     *   loaded with 32 bits worth of pixels for 8bpp and 16bpp.
     * - The CL-GD5429/30/40, which do not require any additional
     *   colors to be loaded.
     * - I have no up-to-date data for the CL-GD5436/46. I assume they
     *   are compatible with the 5430 (at least the Jan 1995 databook
     *   implies this for the 5436). I suspect they do have a
     *   transparency color though.
     */
    loadbg = (bg != -1);
    if (bg == -1 && (cirrusChip == CLGD5434 || CHIPHASTRANSPARENCYCOMPARE())) {
        switch (vga256InfoRec.bitsPerPixel) {
        case 8 :
            bg = (~fg) & 0xFF;
            bg |= (bg << 8) | (bg << 16) | (bg << 24);
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 16 :
            bg = (~fg) & 0xFFFF;
            bg |= bg << 16;
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 32 :
            bg = ~fg;
            break;
        }
        if (CHIPHASTRANSPARENCYCOMPARE()) {
            SETTRANSPARENCYCOLOR16(bg);
        }
        loadbg = TRUE;
    }
    if (cirrusChip == CLGD5434 || vga256InfoRec.bitsPerPixel == 32 ||
    (vga256InfoRec.bitsPerPixel == 24 || CHIPHASPACKED24FILL())) {
        if (loadbg) {
            SETBACKGROUNDCOLOR32(bg);
        }
        SETFOREGROUNDCOLOR32(fg);
    }
    else {
        if (loadbg) {
            SETBACKGROUNDCOLOR16(bg);
        }
        SETFOREGROUNDCOLOR16(fg);
    }
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        bltmode |= COLOREXPAND | SYSTEMSRC;
        break;
    case 16 :
        bltmode |= COLOREXPAND | SYSTEMSRC | PIXELWIDTH16;
        break;
    case 24 :
        if (CHIPHASPACKED24FILL()) {
            bltmode |= COLOREXPAND | SYSTEMSRC | PIXELWIDTH24;
        }
        else {
            bltmode |= COLOREXPAND | SYSTEMSRC;
        }
        break;
    default : /* 32 */
        bltmode |= COLOREXPAND | SYSTEMSRC | PIXELWIDTH32;
        break;
    }
    if (CHIPHASDWORDCOLOREXPANSIONSCANLINEPAD()) {
        SETBLTMODEANDROP(bltmode, SOURCEDWORDGRANULARITY, cirrus_rop[rop]);
    }
    else {
        SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
    }
}

void CirrusSubsequentCPUToScreenColorExpand(x, y, w, h, skipleft)
    int x, y, w, h, skipleft;
{
    int destaddr;
    /*
     * I assume the higher level code has called Sync(), which is
     * a reasonable assumption since it transferred the CPU data.
     */
    w = BPPADJUST(w);
    SETWIDTHANDHEIGHT(w, h);
    if (CHIPHASWRITEMASK()) {
        /*
         * Apart from setting the write mask, this also satisfies the
         * requirement of writing to GR2C for the 5430/40.
         */
        SETSRCADDR(skipleft << 24);
    }
    destaddr = y * vga256InfoRec.displayWidth + x;
    destaddr = BPPADJUST(destaddr);
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

/* Screen-to-screen color expansion. */

void CirrusSetupForScreenToScreenColorExpand(bg, fg, rop, planemask)
    int bg, fg, rop;
    unsigned int planemask;
{
    int bltmode, loadbg;
    bltmode = 0;
    if (bg == -1)
        bltmode = TRANSPARENCYCOMPARE;
    loadbg = (bg != -1);
    if (bg == -1 && (cirrusChip == CLGD5434 || CHIPHASTRANSPARENCYCOMPARE())) {
        switch (vga256InfoRec.bitsPerPixel) {
        case 8 :
            bg = (~fg) & 0xFF;
            bg |= (bg << 8) | (bg << 16) | (bg << 24);
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 16 :
            bg = (~fg) & 0xFFFF;
            bg |= bg << 16;
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 32 :
            bg = ~fg;
            break;
        }
        if (CHIPHASTRANSPARENCYCOMPARE()) {
            SETTRANSPARENCYCOLOR16(bg);
        }
        loadbg = TRUE;
    }
    if (cirrusChip == CLGD5434 || vga256InfoRec.bitsPerPixel == 32 ||
    (vga256InfoRec.bitsPerPixel == 24 || CHIPHASPACKED24FILL())) {
        if (loadbg) {
            SETBACKGROUNDCOLOR32(bg);
        }
        SETFOREGROUNDCOLOR32(fg);
    }
    else {
        if (loadbg) {
            SETBACKGROUNDCOLOR16(bg);
        }
        SETFOREGROUNDCOLOR16(fg);
    }
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        bltmode |= COLOREXPAND;
        break;
    case 16 :
        bltmode |= COLOREXPAND | PIXELWIDTH16;
        break;
    case 24 :
        if (CHIPHASPACKED24FILL()) {
            bltmode |= COLOREXPAND | PIXELWIDTH24;
        }
        else {
            bltmode |= COLOREXPAND;
        }
        break;
    default : /* 32 */
        bltmode |= COLOREXPAND | PIXELWIDTH32;
        break;
    }
    SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
}

void CirrusSubsequentScreenToScreenColorExpand(srcx, srcy, x, y, w, h)
    int srcx, srcy, x, y, w, h;
{
    int srcaddr, destaddr;
    w = BPPADJUST(w);
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTHANDHEIGHT(w, h);
    srcaddr = srcy * vga256InfoRec.displayWidth;
    srcaddr = BPPADJUST(srcaddr);
    /*
     * srcx is in monochrome pixel units; actually we only support
     * units of 32 (DWORD alignmnent).
     */
    srcaddr += srcx / 8;
    SETSRCADDR(srcaddr);
    destaddr = y * vga256InfoRec.displayWidth + x;
    destaddr = BPPADJUST(destaddr);
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

/* Scanline-by-scanline screen-to-screen color expansion. */

static int scanline_destaddr;
static int scanline_width;

void CirrusSetupForScanlineScreenToScreenColorExpand(x, y, w, h, bg, fg, 
rop, planemask)
    int x, y, w, h;
    int bg, fg, rop;
    unsigned int planemask;
{
    int bltmode, loadbg;
    bltmode = 0;
    if (bg == -1)
        bltmode = TRANSPARENCYCOMPARE;
    loadbg = (bg != -1);
    if (bg == -1 && (cirrusChip == CLGD5434 || CHIPHASTRANSPARENCYCOMPARE())) {
        switch (vga256InfoRec.bitsPerPixel) {
        case 8 :
            bg = (~fg) & 0xFF;
            bg |= (bg << 8) | (bg << 16) | (bg << 24);
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 16 :
            bg = (~fg) & 0xFFFF;
            bg |= bg << 16;
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 32 :
            bg = ~fg;
            break;
        }
        if (CHIPHASTRANSPARENCYCOMPARE()) {
            SETTRANSPARENCYCOLOR16(bg);
        }
        loadbg = TRUE;
    }
    if (cirrusChip == CLGD5434 || vga256InfoRec.bitsPerPixel == 32 ||
    (vga256InfoRec.bitsPerPixel == 24 || CHIPHASPACKED24FILL())) {
        if (loadbg) {
            SETBACKGROUNDCOLOR32(bg);
        }
        SETFOREGROUNDCOLOR32(fg);
    }
    else {
        if (loadbg) {
            SETBACKGROUNDCOLOR16(bg);
        }
        SETFOREGROUNDCOLOR16(fg);
    }
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        bltmode |= COLOREXPAND;
        break;
    case 16 :
        bltmode |= COLOREXPAND | PIXELWIDTH16;
        break;
    case 24 :
        if (CHIPHASPACKED24FILL()) {
            bltmode |= COLOREXPAND | PIXELWIDTH24;
        }
        else {
            bltmode |= COLOREXPAND;
        }
        break;
    default : /* 32 */
        bltmode |= COLOREXPAND | PIXELWIDTH32;
        break;
    }
    SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
    scanline_width = BPPADJUST(w);
    scanline_destaddr = y * vga256InfoRec.displayWidth + x;
    scanline_destaddr = BPPADJUST(scanline_destaddr);
}

void CirrusSubsequentScanlineScreenToScreenColorExpand(srcaddr)
    int srcaddr;
{
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    srcaddr /= 8;
    SETWIDTHANDHEIGHT(scanline_width, 1);
    SETSRCADDR(srcaddr);
    SETDESTADDR(scanline_destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
    scanline_destaddr +=
        vga256InfoRec.displayWidth * vga256InfoRec.bitsPerPixel / 8;
}

void CirrusSetupFor8x8PatternFill(patternx, patterny, rop, planemask,
transparency_color)
    int patternx, patterny, rop, planemask, transparency_color;
{
    int bltmode;
    bltmode = 0;
    /* Set up optional transparency compare. */
    if (transparency_color != -1) {
        /*
         * As far as I'm aware, the only chips that support transparency
         * color compare only support it with 8/16bpp.
         */
        if (vga256InfoRec.bitsPerPixel == 8) {
            transparency_color &= 0xFF;
            transparency_color |= transparency_color << 8;
        }
        SETTRANSPARENCYCOLOR16(transparency_color);
        bltmode |= TRANSPARENCYCOMPARE;
    }
    SETBLTMODEANDROP(PATTERNCOPY | bltmode, 0, cirrus_rop[rop]);
}

void CirrusSubsequent8x8PatternFill(patternx, patterny, x, y, w, h)
    int patternx, patterny, x, y, w, h;
{
    int srcaddr, destaddr;
    srcaddr = patterny * vga256InfoRec.displayWidth + patternx;
    destaddr = y * vga256InfoRec.displayWidth + x;
    srcaddr = BPPADJUST(srcaddr);
    destaddr = BPPADJUST(destaddr);
    w = BPPADJUST(w);
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTHANDHEIGHT(w, h);
    SETSRCADDR(srcaddr);
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}

void CirrusSetupFor8x8PatternColorExpand(patternx, patterny, bg, fg, rop,
planemask)
    int patternx, patterny, bg, fg, rop, planemask;
{
    int bltmode, loadbg;
    /* Ignore patternx and patterny. */
    bltmode = 0;
    if (bg == -1)
        bltmode = TRANSPARENCYCOMPARE;
    loadbg = (bg != -1);
    if (bg == -1 && (cirrusChip == CLGD5434 || CHIPHASTRANSPARENCYCOMPARE())) {
        switch (vga256InfoRec.bitsPerPixel) {
        case 8 :
            bg = (~fg) & 0xFF;
            bg |= (bg << 8) | (bg << 16) | (bg << 24);
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 16 :
            bg = (~fg) & 0xFFFF;
            bg |= bg << 16;
            if (cirrusChip == CLGD5434) {
                fg = ~bg;
            }
            break;
        case 32 :
            bg = ~fg;
            break;
        }
        if (CHIPHASTRANSPARENCYCOMPARE()) {
            SETTRANSPARENCYCOLOR16(bg);
        }
        loadbg = TRUE;
    }
    if (cirrusChip == CLGD5434 || vga256InfoRec.bitsPerPixel == 32 ||
    (vga256InfoRec.bitsPerPixel == 24 || CHIPHASPACKED24FILL())) {
        if (loadbg) {
            SETBACKGROUNDCOLOR32(bg);
        }
        SETFOREGROUNDCOLOR32(fg);
    }
    else {
        if (loadbg) {
            SETBACKGROUNDCOLOR16(bg);
        }
        SETFOREGROUNDCOLOR16(fg);
    }
    switch (vga256InfoRec.bitsPerPixel) {
    case 8 :
        bltmode |= COLOREXPAND | PATTERNCOPY;
        break;
    case 16 :
        bltmode |= COLOREXPAND | PIXELWIDTH16 | PATTERNCOPY;
        break;
    case 24 :
        if (CHIPHASPACKED24FILL()) {
            bltmode |= COLOREXPAND | PIXELWIDTH24 | PATTERNCOPY;
        }
        else {
            bltmode |= COLOREXPAND | PATTERNCOPY;
        }
        break;
    default : /* 32 */
        bltmode |= COLOREXPAND | PIXELWIDTH32 | PATTERNCOPY;
        break;
    }
    SETBLTMODEANDROP(bltmode, 0, cirrus_rop[rop]);
}

void CirrusSubsequent8x8PatternColorExpand(patternx, patterny, x, y, w, h)
    int patternx, patterny, x, y, w, h;
{
    int srcaddr, destaddr;
    srcaddr = patterny * vga256InfoRec.displayWidth;
    destaddr = y * vga256InfoRec.displayWidth + x;
    srcaddr = BPPADJUST(srcaddr);
    destaddr = BPPADJUST(destaddr);
    w = BPPADJUST(w);
    /* The pattern x-coordinate is in "bit" units. */
    srcaddr += patternx / 8;
    if (cirrusUseAutoStart)
        WAITEMPTY();
    else
        WAITUNTILFINISHED();
    SETWIDTHANDHEIGHT(w, h);
    SETSRCADDR(srcaddr);
    SETDESTADDR(destaddr);
    if (!cirrusUseAutoStart)
        STARTBLT();
}
