/* $XFree86: xc/programs/Xserver/hw/xfree86/xaa/xf86line.c,v 3.1 1997/01/18 06:57:23 dawes Exp $ */

/***********************************************************

Copyright (c) 1987  X Consortium

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
X CONSORTIUM BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of the X Consortium shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from the X Consortium.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

******************************************************************/
/* $XConsortium: cfbline.c,v 1.24 94/07/28 14:33:33 dpw Exp $ */
/* $XFree86: xc/programs/Xserver/hw/xfree86/xaa/xf86line.c,v 3.1 1997/01/18 06:57:23 dawes Exp $ */

/*
 * Accelerated dashed lines.
 * Adapted from xf86line.c by Mark Vojkovich (mvojkovi@ucsd.edu).
 *
 * The xf86AccelInfoRec.Flags HARDWARE_CLIP_LINE flag indicates that
 * lines are clipped by the hardware. In that case, SetClippingRectangle
 * must be defined.
 *
 * At the moment, when software clipping is used the Bresenham error term
 * gets to large, at which point it is scaled. The precision is taken
 * from xf86AccelInfoRec.ErrorTermBits.
 */


#include "X.h"
#include "Xmd.h"

#include "gcstruct.h"
#include "windowstr.h"
#include "pixmapstr.h"
#include "regionstr.h"
#include "scrnintstr.h"
#include "mistruct.h"
/* PSZ doesn't matter. */
#define PSZ 8
#include "cfb.h"
#include "miline.h"

#include "xf86.h"
#include "xf86xaa.h"
#include "xf86local.h"


void
#ifdef POLYSEGMENT
xf86PolyStippledSegment(pDrawable, pGC, nseg, pSeg)
    DrawablePtr	pDrawable;
    GCPtr	pGC;
    int		nseg;
    register xSegment	*pSeg;
#else
xf86PolyStippledLine(pDrawable, pGC, mode, npt, pptInit)
    DrawablePtr pDrawable;
    GCPtr	pGC;
    int		mode;		/* Origin or Previous */
    int		npt;		/* number of points */
    DDXPointPtr pptInit;
#endif
{
    int nboxInit;
    register int nbox;
    BoxPtr pboxInit;
    register BoxPtr pbox;
#ifndef POLYSEGMENT
    register DDXPointPtr ppt;	/* pointer to list of translated points */
#endif

    unsigned int oc1;		/* outcode of point 1 */
    unsigned int oc2;		/* outcode of point 2 */

    int xorg, yorg;		/* origin of window */

    int adx;		/* abs values of dx and dy */
    int ady;
    int e, e1, e2;		/* bresenham error and increments */
    int len;			/* length of segment */
    unsigned int bias = miGetZeroLineBias(pDrawable->pScreen);
    Bool EvenDash = TRUE;
    int signdx, signdy, octant;

				/* a bunch of temporaries */
    int tmp;
    register int y1, y2;
    register int x1, x2;
    RegionPtr cclip;
    cfbPrivGCPtr    devPriv;
    int PatternLength = 0;
    int PatternOffset = pGC->dashOffset;

    if(pGC->numInDashList & 0x01)
	EvenDash = FALSE;

    {
	register int num = pGC->numInDashList;
	register unsigned char *list = (unsigned char*)pGC->dash;

        while(num--) 
      	    PatternLength += *(list++);

	if(!EvenDash)
	    PatternLength <<= 1;
    }


    /* determine if we can use this function */
    if(PatternLength > xf86AccelInfoRec.LinePatternMaxLength) {
	mi routines
	return;
    }

    PatternOffset %= PatternLength;

    /* convert dash pattern to a color expand pattern */
    {
	register unsigned long* PatPtr = 
		(unsigned long*)xf86AccelInfoRec.LinePatternAddr;
	register unsigned char value;
	unsigned char* DashPtr = (unsigned char*)pGC->dash; 
	register int bits = 0;
	int count;
	Bool set = TRUE;

	count = (EvenDash) ? PatternLength : (PatternLength >> 1); 
      
CONCATENATE:	

	while(count) {
	    value = *(DashPtr++);

	    if(set) {
		count -= value;
		while(value--) {
		   *PatPtr = (*PatPtr << 1) | 0x01;
		    if((++bits) & 32) {
			PatPtr++;
			bits = 0;
		    }
		}
		set = FALSE;
	    } else {
		count -= value;
		while(value--) {
		    *PatPtr <<= 1;
		    if((++bits) & 32) { 
			PatPtr++;
			bits = 0;
		    }
		}
		set = TRUE;
	    }
	}
	
	if(!EvenDash) {
	    EvenDash = TRUE;
	    DashPtr = (unsigned char*)pGC->dash;
	    count = PatternLength >> 1;
	    goto CONCATENATE;
	}

	if(bits) 
	   *PatPtr <<= (31 - bits);	
    }        
    

    devPriv = cfbGetGCPrivate(pGC);
    cclip = devPriv->pCompositeClip;
    pboxInit = REGION_RECTS(cclip);
    nboxInit = REGION_NUM_RECTS(cclip);


    xf86AccelInfoRec.SetupForStippledLine(pGC->fgPixel, 
		(pGC->lineStyle == LineDoubleDash) ? pGC->bgPixel : -1,
		pGC->alu, pGC->planemask, PatternLength);


    xorg = pDrawable->x;
    yorg = pDrawable->y;
#ifdef POLYSEGMENT
    while (nseg--)
#else
    ppt = pptInit;
    x2 = ppt->x + xorg;
    y2 = ppt->y + yorg;
    while(--npt)
#endif
    {
	nbox = nboxInit;
	pbox = pboxInit;

#ifdef POLYSEGMENT
	x1 = pSeg->x1 + xorg;
	y1 = pSeg->y1 + yorg;
	x2 = pSeg->x2 + xorg;
	y2 = pSeg->y2 + yorg;
	pSeg++;
#else
	x1 = x2;
	y1 = y2;
	++ppt;
	if (mode == CoordModePrevious)
	{
	    xorg = x1;
	    yorg = y1;
	}
	x2 = ppt->x + xorg;
	y2 = ppt->y + yorg;
#endif

	CalcLineDeltas(x1, y1, x2, y2, adx, ady, signdx, signdy,
			       1, 1, octant);

	if(!(adx | ady)) continue;

	if (adx > ady)
	{
		e1 = ady << 1;
		e2 = e1 - (adx << 1);
		e = e1 - adx;
 	}
	else
	{
		e1 = adx << 1;
		e2 = e1 - (ady << 1);
		e = e1 - ady;
		SetYMajorOctant(octant);
	}

	FIXUP_ERROR(e, octant, bias);

	    /* we have bresenham parameters and two points.
	       all we have to do now is clip and draw.
	    */

	while(nbox--)
	{
		oc1 = 0;
		oc2 = 0;
		OUTCODES(oc1, x1, y1, pbox);
		OUTCODES(oc2, x2, y2, pbox);
		if ((oc1 | oc2) == 0)
		{
		    if (!(octant & YMAJOR))
			len = adx;
		    else
			len = ady;
#ifdef POLYSEGMENT
		    if (pGC->capStyle != CapNotLast)
			len++;
#endif
		    xf86AccelInfoRec.SubsequentStippledBresenhamLine(x1, y1,
		        octant, e, e1, e2, len, PatternOffset);

#ifndef POLYSEGMENT
		PatternOffset += len;
		PatternOffset %= PatternLength;
#endif
		    break;
		}
		else if (oc1 & oc2)
		{
		    pbox++;
		}
		else if (xf86AccelInfoRec.Flags & HARDWARE_CLIP_LINE) {
		    xf86AccelInfoRec.SetClippingRectangle(
		        pbox->x1, pbox->y1, pbox->x2 - 1, pbox->y2 - 1);
		    if (!(octant & YMAJOR))
			    len = adx;
		    else
			    len = ady;
#ifdef POLYSEGMENT
		    if (pGC->capStyle != CapNotLast)
			   len++;
#endif
		    xf86AccelInfoRec.SubsequentStippledBresenhamLine(x1, y1,
		            octant, e, e1, e2, len, PatternOffset);

#ifndef POLYSEGMENT
		    PatternOffset += len;
		    PatternOffset %= PatternLength;
#endif
		    pbox++;
		}
		else
		{
		    int new_x1 = x1, new_y1 = y1, new_x2 = x2, new_y2 = y2;
		    int clip1 = 0, clip2 = 0;
		    int clipdx, clipdy;
		    int err;

		    /*
		     * If we were to support software clipping with
		     * two point lines, we would have to use
		     * CalculateLineDeltas() now.
		     */
		    if (miZeroClipLine(pbox->x1, pbox->y1, pbox->x2-1,
				       pbox->y2-1,
				       &new_x1, &new_y1, &new_x2, &new_y2,
				       adx, ady, &clip1, &clip2,
				       octant, bias, oc1, oc2) == -1)
		    {
			pbox++;
			continue;
		    }

		    if (!(octant & YMAJOR))
			len = abs(new_x2 - new_x1);
		    else
			len = abs(new_y2 - new_y1);
#ifdef POLYSEGMENT
		    if (clip2 != 0 || pGC->capStyle != CapNotLast)
			len++;
#else
		    len += (clip2 != 0);
#endif
		    if (len)
		    {
			int offset;

			/* unwind bresenham error term to first point */
			if (clip1)
			{
			    int range;
			    clipdx = abs(new_x1 - x1);
			    clipdy = abs(new_y1 - y1);
			    /*
			     * XXX This new error term is probably
			     * too big to be handled.
			     */
			    if (!(octant & YMAJOR))
				err = e+((clipdy*e2) + ((clipdx-clipdy)*e1));
			    else
				err = e+((clipdx*e2) + ((clipdy-clipdx)*e1));
			    /*
			     * Rescale the error terms.
			     */
#define nbits xf86AccelInfoRec.ErrorTermBits
			    range = 1 << nbits;
                            if (abs(err) >= range
                            || abs(e1) >= range || abs(e2) >= range) {
			        int div;
			        if (abs(err) > abs(e1))
			            div = (abs(err) > abs(e2)) ?
			                (abs(err) + range - 1) >> nbits :
			                (abs(e2) + range - 1) >> nbits;
			        else
			            div = (abs(e1) > abs(e2)) ?
			                 (abs(e1) + range - 1) >> nbits :
			                 (abs(e2) + range - 1) >> nbits;
			        err /= div;
			        e1 /= div;
			        e2 /= div;
			    }
			}
			else
			    err = e;
			    
			if(octant & YMAJOR)
			    offset = abs(new_y1 - y1);
			else 
			    offset = abs(new_x1 - x1);

			offset += PatternOffset;
			offset %= PatternLength;
	
		        xf86AccelInfoRec.SubsequentStippledBresenhamLine(
		       	      	new_x1, new_y1, octant, err, e1, e2,
			   	len, offset);

#ifndef POLYSEGMENT
		    	PatternOffset += len;
		    	PatternOffset %= PatternLength;
#endif
	
		    }
		    pbox++;
		}
          } /* while (nbox--) */
    } /* while (nline--) */

#ifndef POLYSEGMENT
    /* paint the last point if the end style isn't CapNotLast.
       (Assume that a projecting, butt, or round cap that is one
        pixel wide is the same as the single pixel of the endpoint.)
    */

    if ((pGC->capStyle != CapNotLast) &&
	((ppt->x + xorg != pptInit->x + pDrawable->x) ||
	 (ppt->y + yorg != pptInit->y + pDrawable->y) ||
	 (ppt == pptInit + 1)))
    {
	nbox = nboxInit;
	pbox = pboxInit;
	while (nbox--)
	{
	    if ((x2 >= pbox->x1) &&
		(y2 >= pbox->y1) &&
		(x2 <  pbox->x2) &&
		(y2 <  pbox->y2))
	    {
		xf86AccelInfoRec.SubsequentStippledBresenhamLine(
		     x2, y2, YMAJOR, -1, 0, -2, 1, PatternOffset);
		break;
	    }
	    else
		pbox++;
	}
    }
#endif

    if (xf86AccelInfoRec.Flags & BACKGROUND_OPERATIONS)
        xf86AccelInfoRec.Sync();
}

