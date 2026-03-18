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

/*
 * These functions are compiled seperately for:
 * cfb8
 * cfb16
 * cfb32
 * vga256 (banked 8bpp)
 *
 * They are called from xf86ValidateGC.
 *
 * Contents:
 *     xf86GCNewFillPolygon(GCPtr, new_cfb_line);
 *     xf86GCNewRectangle(GCPtr, new_cfb_line);
 *     xf86GCNewLine(GCPtr, DrawablePtr, new_cfb_line);
 *     xf86GCNewText(GCPtr, cfb_new_text);
 *     xf86GCNewFillSpans(GCPtr, cfb_new_fillspans);
 *     xf86GCNewFillArea(GCPtr, cfb_new_fillarea);
 *     xf86GCNewCopyArea(GCPtr);
 */

#include "gcstruct.h"
#include "fontstruct.h"
#include "dixfontstr.h"
#include "mi.h"

#ifdef VGA256
/*
 * VGA256 is a special case. We don't use cfb for non-accelerated
 * functions, but instead use their vga256 equivalents.
 */
#include "vga256.h"
#include "vga256map.h"
#else
#include "cfb.h"
#include "cfbmskbits.h"
#endif

#include "xf86.h"
#include "xf86xaa.h"
#include "xf86gcmap.h"
#include "xf86maploc.h"
#include "xf86local.h"


#if PSZ == 8
# define useTEGlyphBlt  cfbTEGlyphBlt8
#else
# ifdef WriteBitGroup
#  define useTEGlyphBlt	cfbImageGlyphBlt8
# else
#  define useTEGlyphBlt	cfbTEGlyphBlt
# endif
#endif

#define CHECKPLANEMASK(flag) \
    (!(flag & NO_PLANEMASK) || (pGC->planemask & PMSK) == PMSK)
#define CHECKROP(flag) \
    (!(flag & GXCOPY_ONLY) || devPriv->rop == GXcopy)
#define CHECKRGBEQUAL(flag) \
    (!(flag & RGB_EQUAL) || ((pGC->fgPixel & 0xFF) == ((pGC->fgPixel \
    & 0xFF00) >> 8) && (pGC->fgPixel & 0xFF) == ((pGC->fgPixel \
    & 0xFF0000) >> 16)))


void xf86GCNewFillPolygon(pGC, new_cfb_line)
    GCPtr pGC;
    Bool new_cfb_line;
{
    void (*FillPolygonFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);
    if (new_cfb_line)
        FillPolygonFunc = miFillPolygon;
    else
        FillPolygonFunc = pGC->ops->FillPolygon;
#ifdef NO_ONE_RECT
    if (new_cfb_line && pGC->fillStyle == FillSolid)
    {
	switch (devPriv->rop) {
	case GXcopy:
            FillPolygonFunc = cfbFillPoly1RectCopy;
	    break;
	default:
	    FillPolygonFunc = cfbFillPoly1RectGeneral;
	    break;
	}
    }
#else
    /*
     * For acceleration purposes, assume that ONE_RECT detection
     * is defined.
     */
    if (devPriv->oneRect && pGC->fillStyle == FillSolid)
    {
        if (new_cfb_line)
	    switch (devPriv->rop) {
	    case GXcopy:
	        FillPolygonFunc = cfbFillPoly1RectCopy;
	        break;
	    default:
	        FillPolygonFunc = cfbFillPoly1RectGeneral;
	        break;
	    }
	if (xf86GCInfoRec.FillPolygonSolid &&
            CHECKPLANEMASK(xf86GCInfoRec.FillPolygonSolidFlags) &&
            CHECKROP(xf86GCInfoRec.FillPolygonSolidFlags) &&
            CHECKRGBEQUAL(xf86GCInfoRec.FillPolygonSolidFlags))
            FillPolygonFunc = xf86GCInfoRec.FillPolygonSolid;
    }
#endif
    pGC->ops->FillPolygon = FillPolygonFunc;
}


void xf86GCNewRectangle(pGC, new_cfb_line)
    GCPtr pGC;
    Bool new_cfb_line;
{
    void (*PolyRectangleFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);
    if (new_cfb_line)
        PolyRectangleFunc = miPolyRectangle;
    else
        PolyRectangleFunc = pGC->ops->PolyRectangle;
    if (xf86GCInfoRec.PolyRectangleSolidZeroWidth &&
        pGC->lineStyle == LineSolid &&
        pGC->fillStyle == FillSolid &&
        pGC->lineWidth == 0 &&
        CHECKPLANEMASK(xf86GCInfoRec.PolyRectangleSolidZeroWidthFlags) &&
        CHECKROP(xf86GCInfoRec.PolyRectangleSolidZeroWidthFlags) &&
        CHECKRGBEQUAL(xf86GCInfoRec.PolyRectangleSolidZeroWidthFlags))
        PolyRectangleFunc = xf86GCInfoRec.PolyRectangleSolidZeroWidth;
    pGC->ops->PolyRectangle = PolyRectangleFunc;
}

void xf86GCNewLine(pGC, pDrawable, new_cfb_line)
    GCPtr pGC;
    DrawablePtr pDrawable;
    Bool new_cfb_line;
{
    void (*PolyLineFunc)();
    void (*PolySegmentFunc)();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);

    if (!new_cfb_line) {
        PolyLineFunc = pGC->ops->Polylines;
        PolySegmentFunc = pGC->ops->PolySegment;
    }
    else {
	if (pGC->lineWidth == 0)
	{
#ifdef PIXEL_ADDR
	    if ((pGC->lineStyle == LineSolid) && (pGC->fillStyle == FillSolid))
	    {
		switch (devPriv->rop)
		{
		case GXxor:
		    pGC->ops->PolyArc = cfbZeroPolyArcSS8Xor;
		    break;
		case GXcopy:
		    pGC->ops->PolyArc = cfbZeroPolyArcSS8Copy;
		    break;
		default:
		    pGC->ops->PolyArc = cfbZeroPolyArcSS8General;
		    break;
		}
	    }
	    else
#endif
		pGC->ops->PolyArc = miZeroPolyArc;
	}
	else
	    pGC->ops->PolyArc = miPolyArc;
	PolySegmentFunc = miPolySegment;
	switch (pGC->lineStyle)
	{
	case LineSolid:
	    if(pGC->lineWidth == 0)
	    {
		if (pGC->fillStyle == FillSolid)
		{
#if defined(PIXEL_ADDR) && !defined(NO_ONE_RECT)
		    if (devPriv->oneRect &&
			((pDrawable->x >= pGC->pScreen->width - 32768) &&
			 (pDrawable->y >= pGC->pScreen->height - 32768)))
		    {
			PolyLineFunc = cfb8LineSS1Rect;
			PolySegmentFunc = cfb8SegmentSS1Rect;
		    } else
#endif
#ifdef NO_ONE_RECT
		    {
			PolyLineFunc = cfb8LineSS1Rect;
			PolySegmentFunc = cfb8SegmentSS1Rect;
		    }
#else
		    {
		    	PolyLineFunc = cfbLineSS;
		    	PolySegmentFunc = cfbSegmentSS;
		    }
#endif
		}
 		else
		    PolyLineFunc = miZeroLine;
	    }
	    else
		PolyLineFunc = miWideLine;
	    break;
	case LineOnOffDash:
	case LineDoubleDash:
	    if (pGC->lineWidth == 0 && pGC->fillStyle == FillSolid)
	    {
		PolyLineFunc = cfbLineSD;
		PolySegmentFunc = cfbSegmentSD;
	    } else
		PolyLineFunc = miWideDash;
	    break;
	}
    } /* endif new_cfb_line */
    if (xf86GCInfoRec.PolyLineSolidZeroWidth &&
        pGC->lineStyle == LineSolid &&
        pGC->lineWidth == 0 &&
#if !defined(NO_ONE_RECT)
	(!(xf86GCInfoRec.PolyLineSolidZeroWidthFlags & ONE_RECT_CLIPPING)
	|| devPriv->oneRect) &&
#endif
        CHECKPLANEMASK(xf86GCInfoRec.PolyLineSolidZeroWidthFlags) &&
        CHECKROP(xf86GCInfoRec.PolyLineSolidZeroWidthFlags) &&
        CHECKRGBEQUAL(xf86GCInfoRec.PolyLineSolidZeroWidthFlags))
        PolyLineFunc = xf86GCInfoRec.PolyLineSolidZeroWidth;
    if (xf86GCInfoRec.PolySegmentSolidZeroWidth &&
        pGC->lineStyle == LineSolid &&
        pGC->lineWidth == 0 &&
#if !defined(NO_ONE_RECT)
	(!(xf86GCInfoRec.PolyLineSolidZeroWidthFlags & ONE_RECT_CLIPPING)
	|| devPriv->oneRect) &&
#endif
        CHECKPLANEMASK(xf86GCInfoRec.PolySegmentSolidZeroWidthFlags) &&
        CHECKROP(xf86GCInfoRec.PolySegmentSolidZeroWidthFlags) &&
        CHECKRGBEQUAL(xf86GCInfoRec.PolySegmentSolidZeroWidthFlags) &&
        (pGC->capStyle != CapNotLast || 
        !(xf86GCInfoRec.PolySegmentSolidZeroWidthFlags & NO_CAP_NOT_LAST)))
        PolySegmentFunc = xf86GCInfoRec.PolySegmentSolidZeroWidth;
    pGC->ops->Polylines = PolyLineFunc;
    pGC->ops->PolySegment = PolySegmentFunc;
}

void
xf86GCNewText(pGC, new_cfb_text)
    GCPtr pGC;
    Bool new_cfb_text;
{
    void (*PolyGlyphBltFunc) ();
    void (*ImageGlyphBltFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);

    if (!new_cfb_text) {
        PolyGlyphBltFunc = pGC->ops->PolyGlyphBlt;
        ImageGlyphBltFunc = pGC->ops->ImageGlyphBlt;
    	goto no_new_cfb_text;
    }

    if (FONTMAXBOUNDS(pGC->font, rightSideBearing) -
	FONTMINBOUNDS(pGC->font, leftSideBearing) > 32 ||
	FONTMINBOUNDS(pGC->font, characterWidth) < 0) {
	PolyGlyphBltFunc = miPolyGlyphBlt;
	ImageGlyphBltFunc = miImageGlyphBlt;
    } else {
	/* Start with the non-accelerated defaults. */
#ifdef WriteBitGroup
	if (pGC->fillStyle == FillSolid) {
	    if (devPriv->rop == GXcopy)
		PolyGlyphBltFunc = cfbPolyGlyphBlt8;
	    else
#ifdef FOUR_BIT_CODE
		PolyGlyphBltFunc = cfbPolyGlyphRop8;
#else
		PolyGlyphBltFunc = miPolyGlyphBlt;
#endif
	} else
#endif
	    PolyGlyphBltFunc = miPolyGlyphBlt;
	/* special case ImageGlyphBlt for terminal emulator fonts */
#if !defined(WriteBitGroup) || PSZ == 8
	if (TERMINALFONT(pGC->font) &&
	    (pGC->planemask & PMSK) == PMSK
#ifdef FOUR_BIT_CODE
	    && FONTMAXBOUNDS(pGC->font, characterWidth) >= PGSZB
#endif
	    ) {
	    ImageGlyphBltFunc = useTEGlyphBlt;
	} else
#endif
	{
#ifdef WriteBitGroup
	    if (devPriv->rop == GXcopy &&
		pGC->fillStyle == FillSolid &&
		(pGC->planemask & PMSK) == PMSK)
		ImageGlyphBltFunc = cfbImageGlyphBlt8;
	    else
#endif
		ImageGlyphBltFunc = miImageGlyphBlt;
	}
    }
no_new_cfb_text:
    xf86GCInfoRec.ImageGlyphBltFallBack = ImageGlyphBltFunc;
    xf86GCInfoRec.PolyGlyphBltFallBack = PolyGlyphBltFunc;

    /* Replace with accelerated functions if possible. */
    if (!TERMINALFONT(pGC->font)) {
	if (xf86GCInfoRec.PolyGlyphBltNonTE
	    && pGC->fillStyle == FillSolid
	    && CHECKPLANEMASK(xf86GCInfoRec.PolyGlyphBltNonTEFlags)
	    && CHECKROP(xf86GCInfoRec.PolyGlyphBltNonTEFlags))
	    PolyGlyphBltFunc = xf86GCInfoRec.PolyGlyphBltNonTE;
	if (xf86GCInfoRec.ImageGlyphBltNonTE
	    && pGC->fillStyle == FillSolid
	    && CHECKPLANEMASK(xf86GCInfoRec.ImageGlyphBltNonTEFlags)
	    && CHECKROP(xf86GCInfoRec.ImageGlyphBltNonTEFlags))
	    ImageGlyphBltFunc = xf86GCInfoRec.ImageGlyphBltNonTE;
    } else {	/* TERMINALFONT(pGC->font) */
	if (xf86GCInfoRec.PolyGlyphBltTE
	    && pGC->fillStyle == FillSolid
	    && CHECKPLANEMASK(xf86GCInfoRec.PolyGlyphBltTEFlags)
	    && CHECKROP(xf86GCInfoRec.PolyGlyphBltTEFlags))
	    PolyGlyphBltFunc = xf86GCInfoRec.PolyGlyphBltTE;
	if (xf86GCInfoRec.ImageGlyphBltTE
	    && CHECKPLANEMASK(xf86GCInfoRec.ImageGlyphBltTEFlags)
	    && CHECKROP(xf86GCInfoRec.ImageGlyphBltTEFlags))
	    ImageGlyphBltFunc = xf86GCInfoRec.ImageGlyphBltTE;
    }
    pGC->ops->ImageGlyphBlt = ImageGlyphBltFunc;
    pGC->ops->PolyGlyphBlt = PolyGlyphBltFunc;
}


void
xf86GCNewFillSpans(pGC, new_cfb_spans)
    GCPtr pGC;
{
    void (*FillSpansFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);

    /* Non-accelerated defaults. */
    if (!new_cfb_spans)
        FillSpansFunc = pGC->ops->FillSpans;
    else
    switch (pGC->fillStyle) {
    case FillSolid:
	switch (devPriv->rop) {
	case GXcopy:
	    FillSpansFunc = cfbSolidSpansCopy;
	    break;
	case GXxor:
	    FillSpansFunc = cfbSolidSpansXor;
	    break;
	default:
	    FillSpansFunc = cfbSolidSpansGeneral;
	    break;
	}
	break;
    case FillTiled:
	if (devPriv->pRotatedPixmap) {
	    if (pGC->alu == GXcopy && (pGC->planemask & PMSK) == PMSK)
		FillSpansFunc = cfbTile32FSCopy;
	    else
		FillSpansFunc = cfbTile32FSGeneral;
	} else
	    FillSpansFunc = cfbUnnaturalTileFS;
	break;
    case FillStippled:
#ifdef FOUR_BIT_CODE
	if (devPriv->pRotatedPixmap)
	    FillSpansFunc = cfb8Stipple32FS;
	else
#endif
	    FillSpansFunc = cfbUnnaturalStippleFS;
	break;
    case FillOpaqueStippled:
#ifdef FOUR_BIT_CODE
	if (devPriv->pRotatedPixmap)
	    FillSpansFunc = cfb8OpaqueStipple32FS;
	else
#endif
	    FillSpansFunc = cfbUnnaturalStippleFS;
	break;
    default:
	FatalError("xf86ValidateGC: illegal fillStyle\n");
    }
    xf86GCInfoRec.FillSpansFallBack = FillSpansFunc;

    /* Replace with accelerated functions if possible. */
    switch (pGC->fillStyle) {
    case FillSolid:
        if (xf86GCInfoRec.FillSpansSolid &&
	    CHECKPLANEMASK(xf86GCInfoRec.FillSpansSolidFlags) &&
	    CHECKROP(xf86GCInfoRec.FillSpansSolidFlags) &&
	    CHECKRGBEQUAL(xf86GCInfoRec.FillSpansSolidFlags))
	    FillSpansFunc = xf86GCInfoRec.FillSpansSolid;
	break;
    case FillTiled:
        if (!xf86GCInfoRec.FillSpansTiled)
            break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.FillSpansTiledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.FillSpansTiledFlags))
	    break;
	FillSpansFunc = xf86GCInfoRec.FillSpansTiled;
	break;
    case FillStippled:
        if (!xf86GCInfoRec.FillSpansStippled)
            break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.FillSpansStippledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.FillSpansStippledFlags))
	    break;
	FillSpansFunc = xf86GCInfoRec.FillSpansStippled;
	break;
    case FillOpaqueStippled:
        if (!xf86GCInfoRec.FillSpansOpaqueStippled)
            break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.FillSpansOpaqueStippledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.FillSpansOpaqueStippledFlags))
	    break;
	FillSpansFunc = xf86GCInfoRec.FillSpansOpaqueStippled;
	break;
    }
    pGC->ops->FillSpans = FillSpansFunc;
}


void
xf86GCNewFillArea(pGC, new_cfb_fillarea)
    GCPtr pGC;
    Bool new_cfb_fillarea;
{
    void (*PolyFillRectFunc) ();
    void (*PolyFillArcFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);

    if (!new_cfb_fillarea)
        PolyFillRectFunc = pGC->ops->PolyFillRect;
    else {
        /* Non-accelerated defaults for PolyFillRect. */
#ifdef FOUR_BIT_CODE
        /* 8bpp */
        PolyFillRectFunc = cfbPolyFillRect;
#else
        /* > 8bpp */
        PolyFillRectFunc = miPolyFillRect;
        if (pGC->fillStyle == FillSolid || pGC->fillStyle == FillTiled) {
            PolyFillRectFunc = cfbPolyFillRect;
        }
#endif
    }

    /* Now check if we can replace the operation. */
    switch (pGC->fillStyle) {
    case FillSolid:
        if (!xf86GCInfoRec.PolyFillRectSolid)
            break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.PolyFillRectSolidFlags))
	    break;
        if (!CHECKROP(xf86GCInfoRec.PolyFillRectSolidFlags))
	    break;
	if (!CHECKRGBEQUAL(xf86GCInfoRec.PolyFillRectSolidFlags))
	    break;
	/* There is a replacement for PolyFillRect, with this rop. */
	PolyFillRectFunc = xf86GCInfoRec.PolyFillRectSolid;
	break;
    case FillTiled:
    	if (!xf86GCInfoRec.PolyFillRectTiled)
    	    break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.PolyFillRectTiledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.PolyFillRectTiledFlags))
	    break;
	PolyFillRectFunc = xf86GCInfoRec.PolyFillRectTiled;
	/* We need to set fall backs also. */
	if (!devPriv->pRotatedPixmap)
	    xf86AccelInfoRec.FillRectTiledFallBack = cfbFillRectTileOdd;
	else {
	    if (pGC->alu == GXcopy && (pGC->planemask & PMSK) == PMSK)
		xf86AccelInfoRec.FillRectTiledFallBack = cfbFillRectTile32Copy;
	    else
		xf86AccelInfoRec.FillRectTiledFallBack =
		    cfbFillRectTile32General;
	}
	break;
    case FillStippled:
    	if (!xf86GCInfoRec.PolyFillRectStippled)
    	    break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.PolyFillRectStippledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.PolyFillRectStippledFlags))
	    break;
	PolyFillRectFunc = xf86GCInfoRec.PolyFillRectStippled;
	/* We need to set fall backs also. */
#if PSZ == 8
	if (!devPriv->pRotatedPixmap)
	    xf86AccelInfoRec.FillRectStippledFallBack =
	        cfb8FillRectStippledUnnatural;
	else
	    xf86AccelInfoRec.FillRectStippledFallBack =
	        cfb8FillRectTransparentStippled32;
#else
	xf86AccelInfoRec.FillRectStippledFallBack =
	    xf86miFillRectStippledFallBack;
#endif
	break;
    case FillOpaqueStippled:
    	if (!xf86GCInfoRec.PolyFillRectOpaqueStippled)
    	    break;
	if (!CHECKPLANEMASK(xf86GCInfoRec.PolyFillRectOpaqueStippledFlags))
	    break;
	if (!CHECKROP(xf86GCInfoRec.PolyFillRectOpaqueStippledFlags))
	    break;
	PolyFillRectFunc = xf86GCInfoRec.PolyFillRectOpaqueStippled;
	/* We need to set fall backs also. */
#if PSZ == 8
	if (!devPriv->pRotatedPixmap)
	    xf86AccelInfoRec.FillRectOpaqueStippledFallBack =
	        cfb8FillRectStippledUnnatural;
	else
	    xf86AccelInfoRec.FillRectOpaqueStippledFallBack =
	        cfb8FillRectOpaqueStippled32;
#else
	xf86AccelInfoRec.FillRectOpaqueStippledFallBack =
	    xf86miFillRectStippledFallBack;
#endif
	break;
    }
    pGC->ops->PolyFillRect = PolyFillRectFunc;

#ifdef FOUR_BIT_CODE
    if (new_cfb_fillarea) {
        pGC->ops->PushPixels = mfbPushPixels;
        if (pGC->fillStyle == FillSolid && devPriv->rop == GXcopy)
	    pGC->ops->PushPixels = cfbPushPixels8;
    }
#endif

    if (!new_cfb_fillarea)
        PolyFillArcFunc = pGC->ops->PolyFillArc;
    else
        PolyFillArcFunc = miPolyFillArc;
    if (pGC->fillStyle == FillSolid) {
        if (new_cfb_fillarea)
	    switch (devPriv->rop) {
	    case GXcopy:
	        PolyFillArcFunc = cfbPolyFillArcSolidCopy;
	        break;
	    default:
	        PolyFillArcFunc = cfbPolyFillArcSolidGeneral;
	        break;
	    }
        if (xf86GCInfoRec.PolyFillArcSolid &&
            CHECKPLANEMASK(xf86GCInfoRec.PolyFillArcSolidFlags) &&
            CHECKROP(xf86GCInfoRec.PolyFillArcSolidFlags) &&
            CHECKRGBEQUAL(xf86GCInfoRec.PolyFillArcSolidFlags))
	    PolyFillArcFunc = xf86GCInfoRec.PolyFillArcSolid;
    }
    pGC->ops->PolyFillArc = PolyFillArcFunc;
}


void
xf86GCNewCopyArea(pGC)
    GCPtr pGC;
{
    RegionPtr (*CopyAreaFunc) ();
    cfbPrivGCPtr devPriv;

    devPriv = cfbGetGCPrivate(pGC);

    /* Default is cfb. */
    CopyAreaFunc = cfbCopyArea;
    if (xf86GCInfoRec.CopyArea &&
	CHECKPLANEMASK(xf86GCInfoRec.CopyAreaFlags) &&
	CHECKROP(xf86GCInfoRec.CopyAreaFlags))
	CopyAreaFunc = xf86GCInfoRec.CopyArea;
    pGC->ops->CopyArea = CopyAreaFunc;
}
