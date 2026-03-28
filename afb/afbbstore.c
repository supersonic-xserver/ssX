/* $XFree86: xc/programs/Xserver/afb/afbbstore.c,v 3.2 2005/10/14 15:16:17 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/* Combined Purdue/PurduePlus patches, level 2.0, 1/17/89 */
/*

Copyright (c) 1987  X Consortium

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR
OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall
not be used in advertising or otherwise to promote the sale, use or
other dealings in this Software without prior written authorization
from the X Consortium.

*/

#include	"afb.h"
#include	<X11/X.h>
#include	"mibstore.h"
#include	"regionstr.h"
#include	"scrnintstr.h"
#include	"pixmapstr.h"
#include	"windowstr.h"

/*
 *-----------------------------------------------------------------------
 * afbSaveAreas --
 *		Function called by miSaveAreas to actually fetch the areas to be
 *		saved into the backing pixmap. This is very simple to do, since
 *		afbDoBitblt is designed for this very thing. The region to save is
 *		already destination-relative and we're given the offset to the
 *		window origin, so we have only to create an array of points of the
 *		u.l. corners of the boxes in the region translated to the screen
 *		coordinate system and fetch the screen pixmap out of its devPrivate
 *		field....
 *
 * Results:
 *		None.
 *
 * Side Effects:
 *		Data are copied from the screen into the pixmap.
 *
 *-----------------------------------------------------------------------
 */
void
afbSaveAreas(PixmapPtr pPixmap, RegionPtr prgnSave, int xorg, int yorg,
	     WindowPtr pWin)
{
	DDXPointPtr	pPt;
	DDXPointPtr	pPtsInit;
	BoxPtr		pBox;
	int		numRects;

	numRects = REGION_NUM_RECTS(prgnSave);
	pPtsInit = (DDXPointPtr)ALLOCATE_LOCAL(numRects * sizeof(DDXPointRec));
	if (!pPtsInit)
		return;

	pBox = REGION_RECTS(prgnSave);
	pPt = pPtsInit;
	while (numRects--) {
		pPt->x = pBox->x1 + xorg;
 		pPt->y = pBox->y1 + yorg;
 		pPt++;
 		pBox++;
	}

	afbDoBitblt((DrawablePtr)pPixmap->drawable.pScreen->devPrivates[afbScreenPrivateIndex].ptr,
				(DrawablePtr)pPixmap,
				GXcopy,
				prgnSave,
				pPtsInit, wBackingBitPlanes (pWin));

	DEALLOCATE_LOCAL(pPtsInit);
}

/*
 *-----------------------------------------------------------------------
 * afbRestoreAreas --
 *		Function called by miRestoreAreas to actually fetch the areas to be
 *		restored from the backing pixmap. This is very simple to do, since
 *		afbDoBitblt is designed for this very thing. The region to restore is
 *		already destination-relative and we're given the offset to the
 *		window origin, so we have only to create an array of points of the
 *		u.l. corners of the boxes in the region translated to the pixmap
 *		coordinate system and fetch the screen pixmap out of its devPrivate
 *		field....
 *
 * Results:
 *		None.
 *
 * Side Effects:
 *		Data are copied from the pixmap into the screen.
 *
 *-----------------------------------------------------------------------
 */
void
afbRestoreAreas(PixmapPtr pPixmap, RegionPtr prgnRestore, int xorg, int yorg,
		WindowPtr pWin)
{
	DDXPointPtr	pPt;
	DDXPointPtr	pPtsInit;
	BoxPtr		pBox;
	int		numRects;

	numRects = REGION_NUM_RECTS(prgnRestore);
	pPtsInit = (DDXPointPtr)ALLOCATE_LOCAL(numRects*sizeof(DDXPointRec));
	if (!pPtsInit)
		return;

	pBox = REGION_RECTS(prgnRestore);
	pPt = pPtsInit;
	while (numRects--) {
		pPt->x = pBox->x1 - xorg;
 		pPt->y = pBox->y1 - yorg;
 		pPt++;
 		pBox++;
	}

	afbDoBitblt((DrawablePtr)pPixmap,
				(DrawablePtr)pPixmap->drawable.pScreen->devPrivates[afbScreenPrivateIndex].ptr,
				GXcopy,
				prgnRestore,
				pPtsInit, wBackingBitPlanes (pWin));

	DEALLOCATE_LOCAL(pPtsInit);
}
