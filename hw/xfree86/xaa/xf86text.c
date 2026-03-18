/* $XFree86$ */

/*
 * Copyright 1996  The XFree86 Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 * HARM HANEMAAYER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 * 
 * Written by Harm Hanemaayer (H.Hanemaayer@inter.nl.net).
 */

#include	"X.h"
#include	"Xmd.h"
#include	"Xproto.h"
/* PSZ doesn't matter. */
#define PSZ 8
#include	"cfb.h"
#include	"fontstruct.h"
#include	"dixfontstr.h"
#include	"gcstruct.h"
#include	"windowstr.h"
#include	"scrnintstr.h"
#include	"pixmapstr.h"
#include	"regionstr.h"

#include "xf86.h"
#include "xf86xaa.h"
#include "xf86local.h"
#include "xf86expblt.h"

/*
 * These functions check for clipping, and only dispatch to the
 * hardware accelerated function if the text string is not clipped.
 *
 * A nice improvement would be to determine which substring of
 * characters fall within a clipping region and call the accelerated
 * text functions for these substrings. This doesn't seem to hard
 * to do.
 *
 * Note that fall-back functions (usually cfb) are called for the
 * clipped case.
 *
 * When a font-cache is implemented (which is not necessarily the fastest
 * way to draw text), you would probably be clipping each character.
 */

void
xf86ImageGlyphBltTE(pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GCPtr pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    int widthGlyph;
    int h;
    int x, y;
    BoxRec bbox;		       /* for clipping */
    int glyphWidth;		       /* Character width in pixels. */

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);

    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;
    bbox.x1 = x;
    bbox.x2 = x + (glyphWidth * nglyph);
    bbox.y1 = y;
    bbox.y2 = y + h;

    switch (RECT_IN_REGION(pGC->pScreen, cfbGetCompositeClip(pGC), &bbox)) {
    case rgnPART:
        (*(xf86GCInfoRec.ImageGlyphBltFallBack))(
	    pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
    case rgnOUT:
	return;
    }

    (*(xf86AccelInfoRec.ImageTextTE))(
        pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
}


/*
 * Non-Terminal emulator fonts (any font).
 */

void
xf86ImageGlyphBltNonTE(pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    int widthGlyph;
    int h;
    int x, y;
    BoxRec bbox;		       /* for clipping */
    int glyphWidth, width;
    int i;

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);

    if ((h | glyphWidth) == 0)
	return;

    width = 0;
    for (i = 0; i < nglyph; i++)
    	width += GLYPHWIDTHPIXELS(ppci[i]);

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;
    bbox.x1 = x;
    bbox.x2 = x + width;
    bbox.y1 = y;
    bbox.y2 = y + h;

    switch (RECT_IN_REGION(pGC->pScreen, cfbGetCompositeClip(pGC), &bbox)) {
    case rgnPART:
        (*(xf86GCInfoRec.ImageGlyphBltFallBack))(
	    pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
    case rgnOUT:
	return;
    }

    (*(xf86AccelInfoRec.ImageTextNonTE))(pDrawable, pGC, xInit, yInit,
        nglyph, ppci, pglyphBase);
}


void
xf86PolyGlyphBltTE(pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int h;
    int x, y;
    BoxRec bbox;		       /* for clipping */

    int glyphWidth;		       /* Character width in pixels. */

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);

    h = FONTASCENT(pfont) + FONTDESCENT(pfont);
    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;
    bbox.x1 = x;
    bbox.x2 = x + (glyphWidth * nglyph);
    bbox.y1 = y;
    bbox.y2 = y + h;

    switch (RECT_IN_REGION(pGC->pScreen, cfbGetCompositeClip(pGC), &bbox)) {
    case rgnPART:
	(*(xf86GCInfoRec.PolyGlyphBltFallBack))(
	    pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
    case rgnOUT:
	return;
    }

    (*(xf86AccelInfoRec.PolyTextTE))(pDrawable, pGC, xInit, yInit,
        nglyph, ppci, pglyphBase);
}


void
xf86PolyGlyphBltNonTE(pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int h;
    int x, y;
    BoxRec bbox;		       /* for clipping */
    int width, i;

    int glyphWidth;		       /* Character width in pixels. */

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);

    h = FONTASCENT(pfont) + FONTDESCENT(pfont);
    if ((h | glyphWidth) == 0)
	return;

    width = 0;
    for (i = 0; i < nglyph; i++)
    	width += GLYPHWIDTHPIXELS(ppci[i]);

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;
    bbox.x1 = x;
    bbox.x2 = x + (glyphWidth * nglyph);
    bbox.y1 = y;
    bbox.y2 = y + h;

    switch (RECT_IN_REGION(pGC->pScreen, cfbGetCompositeClip(pGC), &bbox)) {
    case rgnPART:
	(*(xf86GCInfoRec.PolyGlyphBltFallBack))(
	    pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
    case rgnOUT:
	return;
    }

    (*(xf86AccelInfoRec.PolyTextNonTE))(pDrawable, pGC, xInit, yInit,
        nglyph, ppci, pglyphBase);
}


/*
 * The folowing functions implement non-clipped text drawing
 * using hardware bitmap color expansion.
 */

static void DrawTextTECPUToScreenColorExpand(
#if NeedFunctionPrototypes
    int nglyph,
    int h,
    unsigned int **glyphp,
    int glyphwidth
#endif
);

static void DrawTextTEScreenToScreenColorExpand(
#if NeedFunctionPrototypes
    int nglyph,
    int w,
    int h,
    unsigned int **glyphp,
    int glyphwidth
#endif
);

/* 
 * This function collects pointers to the character bitmaps.
 */

static void
CollectCharacters(glyphp, nglyph, pglyphBase, ppci)
    unsigned int **glyphp;
    unsigned int nglyph;
    unsigned char *pglyphBase;
    CharInfoPtr *ppci;
{
    int i;

    for (i = 0; i < nglyph; i++) {
        glyphp[i] = (unsigned int *)FONTGLYPHBITS(pglyphBase,
	    *ppci++);
    }
}

/* 
 * This function collects glyph info for Non-TE text strings.
 */

static void
CollectCharacterInfo(glyphinfop, nglyph, pglyphBase, ppci, maxascent)
    NonTEGlyphInfo *glyphinfop;
    unsigned int nglyph;
    unsigned char *pglyphBase;
    CharInfoPtr *ppci;
    int maxascent;
{
    int i;

    for (i = 0; i < nglyph; i++) {
	glyphinfop[i].bitsp = (unsigned int *)FONTGLYPHBITS(
	    pglyphBase, ppci[i]);
	glyphinfop[i].width = GLYPHWIDTHPIXELS(ppci[i]);
	glyphinfop[i].firstline = maxascent - ppci[i]->metrics.ascent;
	glyphinfop[i].lastline = maxascent + ppci[i]->metrics.descent;
	ppci++;
    }
}

void
xf86ImageTextTECPUToScreenColorExpand(pDrawable, pGC, xInit, yInit,
nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int w, h;
    int x, y;

    int glyphWidth;		       /* Character width in pixels. */
    int glyphWidthBytes;	       /* Character width in bytes (padded). */
    int i;

    /* Characters are padded to 4 bytes. */
    unsigned int **glyphp;
    int destaddr, blitwidth;

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    glyphWidthBytes = GLYPHWIDTHBYTESPADDED(*ppci);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);

    /*
     * Check for non-standard glyphs, glyphs that are too wide.
     */
    if (glyphWidthBytes != 4 || glyphWidth > 32) {
        xf86GCInfoRec.ImageGlyphBltFallBack(
            pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
	return;
    }

    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;
    w = nglyph * glyphWidth;

    /*
     * If only color expansion with transparency is supported, then
     * do it in two steps -- first do the background with a solid fill,
     * then draw the text with transparency.
     */
    if (xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED) {
        /* First fill-in the background. */
        xf86AccelInfoRec.SetupForFillRectSolid(pGC->bgPixel, pGC->alu,
            pGC->planemask);
        xf86AccelInfoRec.SubsequentFillRectSolid(x, y, w, h);
    }

    /* Allocate list of pointers to glyph bitmaps. */
    glyphp = (unsigned int **)ALLOCATE_LOCAL(nglyph * sizeof(unsigned int *));

    CollectCharacters(glyphp, nglyph, pglyphBase, ppci);

    if (xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED) {
        if (xf86AccelInfoRec.Flags & BACKGROUND_OPERATIONS)
            xf86AccelInfoRec.Sync();
        xf86AccelInfoRec.SetupForCPUToScreenColorExpand(
            -1, pGC->fgPixel, pGC->alu, pGC->planemask);
    }
    else
        xf86AccelInfoRec.SetupForCPUToScreenColorExpand(
            pGC->bgPixel, pGC->fgPixel, pGC->alu, pGC->planemask);

    xf86AccelInfoRec.SubsequentCPUToScreenColorExpand(
        x, y, w, h, 0);

#if 0
    if (xf86AccelInfoRec.ColorExpandFlags & CPU_SCANLINE_PAD_BYTE)
        DrawTextTECPUToScreenColorExpandBytePadded(
            nglyph, w, h, glyphp, glyphwidth);
    else
#endif
        DrawTextTECPUToScreenColorExpand(nglyph, h, glyphp, glyphWidth);

    DEALLOCATE_LOCAL(glyphp);
}


void
xf86ImageTextTEScreenToScreenColorExpand(pDrawable, pGC, xInit, yInit,
nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int w, h;
    int x, y;

    int glyphWidth;		       /* Character width in pixels. */
    int glyphWidthBytes;	       /* Character width in bytes (padded). */
    int i;

    /* Characters are padded to 4 bytes. */
    unsigned int **glyphp;
    int destaddr, blitwidth;

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    glyphWidthBytes = GLYPHWIDTHBYTESPADDED(*ppci);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);
    w = glyphWidth * nglyph;

    /*
     * Check for non-standard glyphs, glyphs that are too wide,
     * and for strings whose scanlines are too large to fit in the
     * bitmap buffer in video memory.
     */
    if (glyphWidthBytes != 4 || glyphWidth > 32 || ((w + 31)
    & ~31) / 8 * 2 > xf86AccelInfoRec.ScratchBufferSize) {
        xf86GCInfoRec.ImageGlyphBltFallBack(
            pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
	return;
    }

    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;

    if (xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED) {
        /* First fill-in the background. */
        xf86AccelInfoRec.SetupForFillRectSolid(pGC->bgPixel, pGC->alu,
            pGC->planemask);
        xf86AccelInfoRec.SubsequentFillRectSolid(x, y, w, h);
    }

    /* Allocate list of pointers to glyph bitmaps. */
    glyphp = (unsigned int **)ALLOCATE_LOCAL(nglyph * sizeof(unsigned int *));

    CollectCharacters(glyphp, nglyph, pglyphBase, ppci);

    if (xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED) {
        if (xf86AccelInfoRec.Flags & BACKGROUND_OPERATIONS)
            xf86AccelInfoRec.Sync();
        xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand(
            x, y, w, h, -1, pGC->fgPixel, pGC->alu, pGC->planemask);
    }
    else
        xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand(
            x, y, w, h, pGC->bgPixel, pGC->fgPixel, pGC->alu, pGC->planemask);

    DrawTextTEScreenToScreenColorExpand(nglyph, w, h, glyphp, glyphWidth);

    DEALLOCATE_LOCAL(glyphp);
}


void
xf86PolyTextTECPUToScreenColorExpand(pDrawable, pGC, xInit, yInit,
nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int h;
    int x, y;

    int glyphWidth;		       /* Character width in pixels. */
    int glyphWidthBytes;	       /* Character width in bytes (padded). */
    int i;

    /* Characters are padded to 4 bytes. */
    unsigned int **glyphp;
    int destaddr, blitwidth;

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    glyphWidthBytes = GLYPHWIDTHBYTESPADDED(*ppci);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);

    /*
     * Check for non-standard glyphs, glyphs that are too wide.
     */
    if (glyphWidthBytes != 4 || glyphWidth > 32) {
        xf86GCInfoRec.PolyGlyphBltFallBack(
            pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
	return;
    }

    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;

    /* Allocate list of pointers to glyph bitmaps. */
    glyphp = (unsigned int **)ALLOCATE_LOCAL(nglyph * sizeof(unsigned int *));

    CollectCharacters(glyphp, nglyph, pglyphBase, ppci);
    
    xf86AccelInfoRec.SetupForCPUToScreenColorExpand(
        -1, pGC->fgPixel, pGC->alu, pGC->planemask);

    xf86AccelInfoRec.SubsequentCPUToScreenColorExpand(
        x, y, nglyph * glyphWidth, h, 0);

#if 0
    if (xf86AccelInfoRec.ColorExpandFlags & CPU_SCANLINE_PAD_BYTE)
        DrawTextTECPUToScreenColorExpandBytePadded(
            nglyph, w, h, glyphp, glyphwidth);
    else
#endif
        DrawTextTECPUToScreenColorExpand(nglyph, h, glyphp, glyphWidth);

    DEALLOCATE_LOCAL(glyphp);
}

void
xf86PolyTextTEScreenToScreenColorExpand(pDrawable, pGC, xInit, yInit,
nglyph, ppci, pglyphBase)
    DrawablePtr pDrawable;
    GC *pGC;
    int xInit, yInit;
    int nglyph;
    CharInfoPtr *ppci;		       /* array of character info */
    unsigned char *pglyphBase;	       /* start of array of glyphs */
{
    FontPtr pfont = pGC->font;
    unsigned int *pdstBase;
    int widthDst;
    int widthGlyph;
    int w, h;
    int x, y;

    int glyphWidth;		       /* Character width in pixels. */
    int glyphWidthBytes;	       /* Character width in bytes (padded). */
    int i;

    /* Characters are padded to 4 bytes. */
    unsigned int **glyphp;
    int destaddr, blitwidth;

    glyphWidth = FONTMAXBOUNDS(pfont, characterWidth);
    glyphWidthBytes = GLYPHWIDTHBYTESPADDED(*ppci);
    h = FONTASCENT(pfont) + FONTDESCENT(pfont);
    w = glyphWidth * nglyph;

    /*
     * Check for non-standard glyphs, glyphs that are too wide,
     * and for strings whose scanlines are too large to fit in the
     * bitmap buffer in video memory.
     */
    if (glyphWidthBytes != 4 || glyphWidth > 32 || ((w + 31)
    & ~31) / 8 * 2 > xf86AccelInfoRec.ScratchBufferSize) {
        xf86GCInfoRec.PolyGlyphBltFallBack(
            pDrawable, pGC, xInit, yInit, nglyph, ppci, pglyphBase);
	return;
    }

    if ((h | glyphWidth) == 0)
	return;

    x = xInit + FONTMAXBOUNDS(pfont, leftSideBearing) + pDrawable->x;
    y = yInit - FONTASCENT(pfont) + pDrawable->y;

    /* Allocate list of pointers to glyph bitmaps. */
    glyphp = (unsigned int **)ALLOCATE_LOCAL(nglyph * sizeof(unsigned int *));

    CollectCharacters(glyphp, nglyph, pglyphBase, ppci);

    xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand(
        x, y, w, h, -1, pGC->fgPixel, pGC->alu, pGC->planemask);

    DrawTextTEScreenToScreenColorExpand(nglyph, w, h, glyphp, glyphWidth);

    DEALLOCATE_LOCAL(glyphp);
}



/*
 * The following are lower-level function that transfer the text
 * bitmap from the CPU to the screen to be color expanded.
 *
 */
 
/*
 * This function is used for Imagetext/Polytext with TE font with
 * CPU-to-screen color expansion (DWORD padding at the end of scanlines).
 */

static void DrawTextTECPUToScreenColorExpand(nglyph, h, glyphp, glyphwidth)
    int nglyph;
    int h;
    unsigned int **glyphp;
    int glyphwidth;
{
    int bitmapwidth;
    int line;
    unsigned char *base;
    unsigned int *(*DrawTextScanlineFunc)(
#if NeedNestedPrototypes
        unsigned int *base,
        unsigned int **glyphp,
        int line,
        int nglyph,
        int glyphwidth
#endif
    );

    if (xf86AccelInfoRec.ColorExpandFlags & BIT_ORDER_IN_BYTE_MSBFIRST)
        if (xf86AccelInfoRec.ColorExpandFlags & TRIPLE_BITS_24BPP)
            DrawTextScanlineFunc = xf86DrawTextScanline3MSBFirst;
        else
            DrawTextScanlineFunc = xf86DrawTextScanlineMSBFirst;
    else
        if (xf86AccelInfoRec.ColorExpandFlags & TRIPLE_BITS_24BPP)
            DrawTextScanlineFunc = xf86DrawTextScanline3;
        else
            DrawTextScanlineFunc = xf86DrawTextScanline;

    base = (unsigned char *)xf86AccelInfoRec.CPUToScreenColorExpandBase;

    line = 0;
    while (line < h) {
	base = (unsigned char *)(*DrawTextScanlineFunc)(
	    (unsigned int *)base, glyphp, line, nglyph, glyphwidth);
        if (base >=
        (unsigned char *)xf86AccelInfoRec.CPUToScreenColorExpandEndMarker)
            base = (unsigned char *)xf86AccelInfoRec.CPUToScreenColorExpandBase;
	line++;
    }

    if (xf86AccelInfoRec.ColorExpandFlags & CPU_TRANSFER_PAD_QWORD)
        if (((int)base - (int)xf86AccelInfoRec.CPUToScreenColorExpandBase) & 4)
            *(unsigned int *)base = 0;

    xf86AccelInfoRec.Sync();
}

#if 0

/*
 * Used for Imagetext/Polytext with TE font with CPU-to-screen
 * color expansion (BYTE padding at the end of scanlines).
 *
 * This is not yet implemented. The ASM function in the cirrus driver
 * could be used.
 */

static void DrawTextTECPUToScreenColorExpandBytePadded(nglyph, h, glyphp,
glyphwidth)
    int nglyph;
    int h;
    unsigned int **glyphp;
    int glyphwidth;
{
    int bitmapwidth;
    int line;
    unsigned char *base;
    ScanlineReturn sr;

    base = xf86AccelInfoRec.CPUToScreenColorExpandBase;

    /* Calculate the non-expanded bitmap width rounded up to 32-bit words, */
    /* in units of pixels. */
    bitmapwidth = (w + 31) & ~31;

    line = 0;
    while (line < h) {
	sr = xf86DrawTextScanlineMSBFirstBytePadded(
	    base, glyphp, line, nglyph, glyphWidth);
        if (base >= xf86AccelInfoRec.CPUToScreenColorExpandEndMarker)
            base = xf86AccelInfoRec.CPUToScreenColorExpandBase;
	line++;
    }

    if (xf86AccelInfoRec.ColorExpandFlags & CPU_TRANSFER_PAD_QWORD)
        if ((base - xf86AccelInfoRec.CPUToScreenColorExpandBase) & 4)
            *(unsigned int *)base = 0;

    xf86AccelInfoRec.Sync();
}

#endif


/*
 * The following function is used for Imagetext/Polytext with TE font with
 * buffered screen-to-screen color expansion. Each scanline is first
 * transferred from the CPU to a scratch buffer in off-screen video memory,
 * and then color expanded to the on-screen destination.
 */

static void DrawTextTEScreenToScreenColorExpand(nglyph, w, h, glyphp, glyphwidth)
    int nglyph;
    int w;
    int h;
    unsigned int **glyphp;
    int glyphwidth;
{
    int bitmapwidth;
    int line;

    /* Calculate the non-expanded bitmap width rounded up to 32-bit words, */
    /* in units of pixels. */
    bitmapwidth = (w + 31) & ~31;

    line = 0;
    while (line < h) {
        int base;
	base = xf86AccelInfoRec.ScratchBufferAddr;
        if (line & 1)
            /*
             * There are two buffers -- while the first one is being
             * blitted, the other one is initialized. Then the other
             * way around, and so on.
             */
	    base += bitmapwidth / 8;
	if (!(xf86AccelInfoRec.Flags & COP_FRAMEBUFFER_CONCURRENCY))
	    xf86AccelInfoRec.Sync();
        if (xf86AccelInfoRec.ColorExpandFlags & BIT_ORDER_IN_BYTE_MSBFIRST)
	    xf86DrawTextScanlineMSBFirst((unsigned int *)
	        (xf86AccelInfoRec.FramebufferBase + base),
	        glyphp, line, nglyph, glyphwidth);
        else
	    xf86DrawTextScanline((unsigned int *)
	        (xf86AccelInfoRec.FramebufferBase + base),
	        glyphp, line, nglyph, glyphwidth);
	xf86AccelInfoRec.SubsequentScanlineScreenToScreenColorExpand(
	    base * 8);
	line++;
    }

    if (xf86AccelInfoRec.Flags & BACKGROUND_OPERATIONS)
        xf86AccelInfoRec.Sync();
}
