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

#include "servermd.h"
#include "windowstr.h"
#include "gcstruct.h"
#include "regionstr.h"
#include "mi.h"

#include "xf86.h"
#include "xf86xaa.h"
#include "xf86gcmap.h"
#include "xf86local.h"
#include "xf86pcache.h"

/*
 * This is just for the messages, it's about the only thing that
 * prevents a server that doesn't use vga256 from using the XAA code.
 */
extern ScrnInfoRec vga256InfoRec;
#include "xf86_Config.h"

#ifdef PIXPRIV
/*
 * This is a convenient place to declare this variable (this file is only
 * compiled once).
 */
int xf86PixmapIndex;
#endif

void
xf86InitializeAcceleration(pScreen)
    ScreenPtr pScreen;
{
    int SimpleFillRectSolid = FALSE;
    int SimpleScreenToScreenCopy = FALSE;
    int CPUToScreenColorExpand = FALSE;
    int ScreenToScreenColorExpand = FALSE;
    int ScanlineScreenToScreenColorExpand = FALSE;
 
    ErrorF("%s %s: Using XAA (XFree86 Acceleration Architecture)\n",
        XCONFIG_PROBED, vga256InfoRec.name);

#if 1
    xf86AccelInfoRec.Flags &= ~PIXMAP_CACHE;
    ErrorF("%s %s: Sorry, pixmap cache is broken (disabled)\n",
        XCONFIG_PROBED, vga256InfoRec.name);
#endif

    /*
     * Probe the low-level accelerated functions supported.
     */

    if (xf86AccelInfoRec.SetupForFillRectSolid &&
    xf86AccelInfoRec.SubsequentFillRectSolid) {
        SimpleFillRectSolid = TRUE;
        ErrorF("%s %s: accel: Solid filled rectangles\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupForScreenToScreenCopy &&
    xf86AccelInfoRec.SubsequentScreenToScreenCopy) {
        SimpleScreenToScreenCopy = TRUE;
        ErrorF("%s %s: accel: Screen-to-screen copy\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupForCPUToScreenColorExpand &&
    xf86AccelInfoRec.SubsequentCPUToScreenColorExpand) {
        CPUToScreenColorExpand = TRUE;
        ErrorF("%s %s: accel: CPU-to-screen color expand\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupForScreenToScreenColorExpand &&
    xf86AccelInfoRec.SubsequentScreenToScreenColorExpand) {
        ScreenToScreenColorExpand = TRUE;
        ErrorF("%s %s: accel: Screen-to-screen color expand\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupForScanlineScreenToScreenColorExpand &&
    xf86AccelInfoRec.SubsequentScanlineScreenToScreenColorExpand) {
        ScanlineScreenToScreenColorExpand = TRUE;
        ErrorF("%s %s: accel: Scanline screen-to-screen color expand\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupForFill8x8Pattern &&
    xf86AccelInfoRec.SubsequentFill8x8Pattern) {
        ErrorF("%s %s: accel: 8x8 pattern fill\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }
    if (xf86AccelInfoRec.SetupFor8x8PatternColorExpand &&
    xf86AccelInfoRec.Subsequent8x8PatternColorExpand) {
        ErrorF("%s %s: accel: 8x8 color expand pattern fill\n",
            XCONFIG_PROBED, vga256InfoRec.name);
    }

    /*
     * Set up the higher-level accelerated functions to make use of
     * the available lower-level functions.
     */

    /* Solid filled rectangles. */
    if (SimpleFillRectSolid && !xf86AccelInfoRec.FillRectSolid)
        xf86AccelInfoRec.FillRectSolid = xf86SimpleFillRectSolid;
    if (xf86AccelInfoRec.FillRectSolid && !xf86GCInfoRec.PolyFillRectSolid)
        xf86GCInfoRec.PolyFillRectSolid = xf86PolyFillRect;

    /* Various solid fills. */
    if (SimpleFillRectSolid) {
        if (!xf86GCInfoRec.FillSpansSolid) {
            xf86GCInfoRec.FillSpansSolid = xf86FillSpansAsRects;
            xf86GCInfoRec.FillSpansSolidFlags =
                 xf86GCInfoRec.PolyFillRectSolidFlags;
        }
        /* Solid filled arcs. */
        if (!xf86GCInfoRec.PolyFillArcSolid) {
            xf86GCInfoRec.PolyFillArcSolid = xf86PolyFillArcSolid;
            xf86GCInfoRec.PolyFillArcSolidFlags =
                xf86GCInfoRec.PolyFillRectSolidFlags;
        }
        /* Solid filled polygons. */
        if (!xf86GCInfoRec.FillPolygonSolid) {
            xf86GCInfoRec.FillPolygonSolid = xf86FillPolygonSolid1Rect;
            xf86GCInfoRec.FillPolygonSolidFlags =
                xf86GCInfoRec.PolyFillRectSolidFlags | ONE_RECT_CLIPPING;
        }
        /* Line rectangles. */
        if (!xf86GCInfoRec.PolyRectangleSolidZeroWidth) {
            xf86GCInfoRec.PolyRectangleSolidZeroWidth =
                xf86PolyRectangleSolidZeroWidth;
            xf86GCInfoRec.PolyRectangleSolidZeroWidthFlags =
                xf86GCInfoRec.PolyFillRectSolidFlags;
	}
    }

    /* Tile and stipple filled rectangles (non-cached). */
    if (xf86AccelInfoRec.FillRectTiled && !xf86GCInfoRec.PolyFillRectTiled)
        xf86GCInfoRec.PolyFillRectTiled = xf86PolyFillRect;
    if (xf86AccelInfoRec.FillRectStippled
    && !xf86GCInfoRec.PolyFillRectStippled)
        xf86GCInfoRec.PolyFillRectStippled = xf86PolyFillRect;
    if (xf86AccelInfoRec.FillRectOpaqueStippled
    && !xf86GCInfoRec.PolyFillRectOpaqueStippled)
        xf86GCInfoRec.PolyFillRectOpaqueStippled = xf86PolyFillRect;

    /* Screen-to-screen BitBLT. */
    if (SimpleScreenToScreenCopy && !xf86AccelInfoRec.ScreenToScreenBitBlt)
        xf86AccelInfoRec.ScreenToScreenBitBlt = xf86ScreenToScreenBitBlt;
    if (xf86AccelInfoRec.ScreenToScreenBitBlt && !xf86GCInfoRec.CopyArea) {
        xf86GCInfoRec.CopyArea = xf86CopyArea;
    }

    /* Color expansion. */
    
    /*
     * Make decisions based on the specified range for CPU-to-screen
     * color expansion. We need at least a scanline worth of range.
     * The EndMarker is defined as the highest possible base address
     * where there's still space for a complete scanline within the
     * allowed range.
     */
    if (CPUToScreenColorExpand) {
        if (!xf86AccelInfoRec.CPUToScreenColorExpandBase)
            /* No base specified, assume start of framebuffer. */
            xf86AccelInfoRec.CPUToScreenColorExpandBase =
                (unsigned int *)xf86AccelInfoRec.FramebufferBase;
        if (!xf86AccelInfoRec.CPUToScreenColorExpandRange) {
            /* No range specified, assume a 64K range. */
            xf86AccelInfoRec.CPUToScreenColorExpandRange = 65536;
            xf86AccelInfoRec.CPUToScreenColorExpandEndMarker = (unsigned int *)
                ((unsigned char *)xf86AccelInfoRec.CPUToScreenColorExpandBase
                + 65536 - ((xf86AccelInfoRec.FramebufferWidth + 31) & ~31) / 8);
        }
        else {
            if (xf86AccelInfoRec.CPUToScreenColorExpandRange >=
            ((xf86AccelInfoRec.FramebufferWidth + 31) & ~31) / 8)
                /*
                 * OK, the range is large enough for a scanline, so we can
                 * use color expansion.
                 */
                xf86AccelInfoRec.CPUToScreenColorExpandEndMarker =
                    (unsigned int *)((unsigned char *)
                    xf86AccelInfoRec.CPUToScreenColorExpandBase +
                    xf86AccelInfoRec.CPUToScreenColorExpandRange
                    - ((xf86AccelInfoRec.FramebufferWidth + 31) & ~31) / 8);
            else
                /* Alas, not a large enough range. */
                xf86AccelInfoRec.ColorExpandFlags |= CPU_TRANSFER_BASE_FIXED;
        }
    }

    if (CPUToScreenColorExpand
    && (xf86AccelInfoRec.ColorExpandFlags & (SCANLINE_PAD_DWORD
        | SCANLINE_PAD_BYTE))
    && !(xf86AccelInfoRec.ColorExpandFlags & CPU_TRANSFER_BASE_FIXED)
    && !((xf86AccelInfoRec.ColorExpandFlags & SCANLINE_PAD_BYTE)
        && !(xf86AccelInfoRec.ColorExpandFlags & BIT_ORDER_IN_BYTE_MSBFIRST))
    ) {
        if (!(xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED)
        || SimpleFillRectSolid)
            xf86AccelInfoRec.WriteBitmap =
                xf86WriteBitmapCPUToScreenColorExpand;
        ErrorF("%s %s: accel: CPU to screen color expansion (bitmap",
	    XCONFIG_PROBED, vga256InfoRec.name);
        if (!xf86AccelInfoRec.ImageTextTE && !xf86GCInfoRec.ImageGlyphBltTE &&
        (!(xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED)
        || SimpleFillRectSolid)
        && (xf86AccelInfoRec.ColorExpandFlags & SCANLINE_PAD_DWORD)) {
            xf86AccelInfoRec.ImageTextTE =
                xf86ImageTextTECPUToScreenColorExpand;
            xf86GCInfoRec.ImageGlyphBltTEFlags =
                xf86AccelInfoRec.ColorExpandFlags;
            ErrorF(", imagetext");
        }
        if (!xf86AccelInfoRec.PolyTextTE && !xf86GCInfoRec.PolyGlyphBltTE
        && !(xf86AccelInfoRec.ColorExpandFlags & NO_TRANSPARENCY)
        && (xf86AccelInfoRec.ColorExpandFlags & SCANLINE_PAD_DWORD)) {
            xf86AccelInfoRec.PolyTextTE =
                xf86PolyTextTECPUToScreenColorExpand;
            xf86GCInfoRec.PolyGlyphBltTEFlags =
                xf86AccelInfoRec.ColorExpandFlags;
            ErrorF(", polytext");
        }
        ErrorF(")\n");
    }
    else
    if (ScanlineScreenToScreenColorExpand
    && xf86AccelInfoRec.ScratchBufferAddr
    && xf86AccelInfoRec.FramebufferBase) {
        ErrorF("%s %s: accel: Indirect CPU to screen color expansion "
            "(", XCONFIG_PROBED, vga256InfoRec.name);
        if ((xf86AccelInfoRec.ColorExpandFlags &
        VIDEO_SOURCE_GRANULARITY_PIXEL) &&
        (!(xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED)
        || SimpleFillRectSolid)) {
            xf86AccelInfoRec.WriteBitmap =
                xf86WriteBitmapScreenToScreenColorExpand;
            ErrorF("bitmap");
        }
        if (!xf86AccelInfoRec.ImageTextTE && !xf86GCInfoRec.ImageGlyphBltTE &&
        (!(xf86AccelInfoRec.ColorExpandFlags & ONLY_TRANSPARENCY_SUPPORTED)
        || SimpleFillRectSolid)) {
            xf86AccelInfoRec.ImageTextTE =
                xf86ImageTextTEScreenToScreenColorExpand;
            xf86GCInfoRec.ImageGlyphBltTEFlags =
                xf86AccelInfoRec.ColorExpandFlags;
            ErrorF(", imagetext");
        }
        if (!xf86AccelInfoRec.PolyTextTE && !xf86GCInfoRec.PolyGlyphBltTE &&
        !(xf86AccelInfoRec.ColorExpandFlags & NO_TRANSPARENCY)) {
            xf86AccelInfoRec.PolyTextTE =
                xf86PolyTextTEScreenToScreenColorExpand;
            xf86GCInfoRec.PolyGlyphBltTEFlags =
                xf86AccelInfoRec.ColorExpandFlags;
            ErrorF(", polytext");
        }
        ErrorF(")\n");
    }

    /*
     * Text. Has a dependency on color expansion.
     * This part just installs the high level hooks that check
     * for clipping, if lower-level hooks that don't check for clipping
     * exist.
     */
    if (!xf86GCInfoRec.ImageGlyphBltTE && xf86AccelInfoRec.ImageTextTE)
        xf86GCInfoRec.ImageGlyphBltTE = xf86ImageGlyphBltTE;
    if (!xf86GCInfoRec.ImageGlyphBltNonTE && xf86AccelInfoRec.ImageTextNonTE)
        xf86GCInfoRec.ImageGlyphBltNonTE = xf86ImageGlyphBltNonTE;
    if (!xf86GCInfoRec.PolyGlyphBltTE && xf86AccelInfoRec.PolyTextTE)
        xf86GCInfoRec.PolyGlyphBltTE = xf86PolyGlyphBltTE;
    if (!xf86GCInfoRec.PolyGlyphBltNonTE && xf86AccelInfoRec.PolyTextNonTE)
        xf86GCInfoRec.PolyGlyphBltNonTE = xf86PolyGlyphBltNonTE;

    /* Pixmap caching. */
    if ((xf86AccelInfoRec.Flags & PIXMAP_CACHE) && SimpleScreenToScreenCopy) {
        ErrorF("%s %s: accel: Caching tiles ",
	    XCONFIG_PROBED, vga256InfoRec.name);
        xf86GCInfoRec.PolyFillRectTiled = xf86PolyFillRect;
        xf86GCInfoRec.PolyFillRectTiledFlags = xf86GCInfoRec.CopyAreaFlags;
        if (!xf86GCInfoRec.FillSpansTiled) {
            xf86GCInfoRec.FillSpansTiled = xf86FillSpansTiled;
            xf86GCInfoRec.FillSpansTiledFlags = xf86GCInfoRec.CopyAreaFlags;
        }
        /* Caching of stipples requires WriteBitmap or WriteBitmapFallBack. */
        if (xf86AccelInfoRec.WriteBitmap
        || xf86AccelInfoRec.WriteBitmapFallBack) {
            xf86GCInfoRec.PolyFillRectOpaqueStippled = xf86PolyFillRect;
            xf86GCInfoRec.PolyFillRectOpaqueStippledFlags =
                xf86GCInfoRec.CopyAreaFlags;
            if (!xf86GCInfoRec.FillSpansOpaqueStippled) {
                xf86GCInfoRec.FillSpansOpaqueStippled = xf86FillSpansStippled;
                xf86GCInfoRec.FillSpansOpaqueStippledFlags =
                    xf86GCInfoRec.CopyAreaFlags;
            }
            /*
             * Caching of transparent stipples requires screen-to-screen
             * copy with transparency color compare.
             */
            if (!(xf86GCInfoRec.CopyAreaFlags & NO_TRANSPARENCY)) {
                xf86GCInfoRec.PolyFillRectStippled = xf86PolyFillRect;
                xf86GCInfoRec.PolyFillRectStippledFlags =
                    xf86GCInfoRec.CopyAreaFlags;
                if (!xf86GCInfoRec.FillSpansStippled) {
                    xf86GCInfoRec.FillSpansStippled =
                        xf86FillSpansStippled;
                    xf86GCInfoRec.FillSpansStippledFlags =
                        xf86GCInfoRec.CopyAreaFlags;
                }
                ErrorF("and stipples\n");
            }
            else
                ErrorF("and non-transparent stipples\n");
        }
        else {
            /*
             * If we cache tiles but not stipples we must set
             * this flag, since stipples may be routed to
             * xf86PolyFillRect because of other types of
             * acceleration.
             */
            xf86AccelInfoRec.Flags |= DO_NOT_CACHE_STIPPLES;
            ErrorF("\n");
        }
    }

    /*
     * General lines. At the moment, hardware clipping of lines
     * is a requirement for TwoPointLine.
     * For BresenhamLine, we can do software clipping if ErrorTermBits
     * is defined.
     * If no general lines are available, a function is used that
     * that speeds up horizontal and vertical lines using FillRectSolid,
     * and also takes advantage of any TwoPointLine for vertical and
     * non-clipped lines.
     */
        if ((xf86AccelInfoRec.SubsequentBresenhamLine
        && ((xf86AccelInfoRec.Flags & HARDWARE_CLIP_LINE) ||
        xf86AccelInfoRec.ErrorTermBits))
        || (xf86AccelInfoRec.SubsequentTwoPointLine
        && (xf86AccelInfoRec.Flags & HARDWARE_CLIP_LINE))) {
            if (!xf86GCInfoRec.PolyLineSolidZeroWidth)
                xf86GCInfoRec.PolyLineSolidZeroWidth = xf86PolyLine;
            if (!xf86GCInfoRec.PolySegmentSolidZeroWidth)
                xf86GCInfoRec.PolySegmentSolidZeroWidth = xf86PolySegment;
            if (xf86AccelInfoRec.SubsequentTwoPointLine)
                xf86AccelInfoRec.Flags |= USE_TWO_POINT_LINE;
            if (!xf86AccelInfoRec.SubsequentBresenhamLine &&
            !(xf86AccelInfoRec.Flags & TWO_POINT_LINE_NOT_LAST))
                /*
                 * If there's only TwoPointLine, and it doesn't support
                 * skipping of the last pixel, then PolySegment cannot
                 * be supported with the CapNotLast line style.
                 */
                xf86GCInfoRec.PolySegmentSolidZeroWidthFlags |=
                    NO_CAP_NOT_LAST;
            ErrorF("%s %s: accel: General lines and segments\n",
	        XCONFIG_PROBED, vga256InfoRec.name);
        }
        else
        if (SimpleFillRectSolid) {
            /* This one will make use of any available TwoPointLine. */
            if (!xf86GCInfoRec.PolyLineSolidZeroWidth)
                xf86GCInfoRec.PolyLineSolidZeroWidth = xf86PolyLine2;
            if (!xf86GCInfoRec.PolySegmentSolidZeroWidth)
                xf86GCInfoRec.PolySegmentSolidZeroWidth = xf86PolySegment2;
            if (xf86AccelInfoRec.SubsequentTwoPointLine)
                ErrorF("%s %s: accel: Non-clipped general lines and segments\n",
                    XCONFIG_PROBED, vga256InfoRec.name);
            else
                ErrorF("%s %s: accel: Horizontal and vertical lines and segments\n",
                    XCONFIG_PROBED, vga256InfoRec.name);
        }

    /*
     * If there is a replacement for screen-to-screen BitBlt, then we
     * want to use it for CopyWindow.
     */
    if (SimpleScreenToScreenCopy) {
        pScreen->CopyWindow = xf86CopyWindow;
    }
    /*
     * For PaintWindow, just use the mi version, which does everything
     * with GC ops, which will automatically use the most efficient
     * functions.
     */
    pScreen->PaintWindowBackground = miPaintWindow;
    pScreen->PaintWindowBorder = miPaintWindow;
}
