/* $XFree86: xc/programs/Xserver/afb/afbcmap.c,v 3.3 2005/10/14 15:16:17 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/************************************************************
Copyright 1987 by Sun Microsystems, Inc. Mountain View, CA.

                    All Rights Reserved

Permission  to  use,  copy,  modify,  and  distribute   this
software  and  its documentation for any purpose and without
fee is hereby granted, provided that the above copyright no-
tice  appear  in all copies and that both that copyright no-
tice and this permission notice appear in  supporting  docu-
mentation,  and  that the names of Sun or X Consortium
not be used in advertising or publicity pertaining to
distribution  of  the software  without specific prior
written permission. Sun and X Consortium make no
representations about the suitability of this software for
any purpose. It is provided "as is" without any express or
implied warranty.

SUN DISCLAIMS ALL WARRANTIES WITH REGARD TO  THIS  SOFTWARE,
INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FIT-
NESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SUN BE  LI-
ABLE  FOR  ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,  DATA  OR
PROFITS,  WHETHER  IN  AN  ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
THE USE OR PERFORMANCE OF THIS SOFTWARE.

********************************************************/

#include <X11/X.h>
#include <X11/Xproto.h>
#include "scrnintstr.h"
#include "colormapst.h"
#include "resource.h"
#include "micmap.h"
#include "afb.h"

int
afbListInstalledColormaps(ScreenPtr pScreen, Colormap *pmaps)
{
	return miListInstalledColormaps(pScreen, pmaps);
}


void
afbInstallColormap(ColormapPtr pmap)
{
	miInstallColormap(pmap);
}

void
afbUninstallColormap(ColormapPtr pmap)
{
	miUninstallColormap(pmap);
}

void
afbResolveColor(unsigned short *pred, unsigned short *pgreen,
		unsigned short *pblue, VisualPtr pVisual)
{
	miResolveColor(pred, pgreen, pblue, pVisual);
}

Bool
afbInitializeColormap(ColormapPtr pmap)
{
	return miInitializeColormap(pmap);
}

int
afbExpandDirectColors(ColormapPtr pmap, int ndef, xColorItem *indefs,
		      xColorItem *outdefs)
{
	return miExpandDirectColors(pmap, ndef, indefs, outdefs);
}

Bool
afbCreateDefColormap(ScreenPtr pScreen)
{
	return miCreateDefColormap(pScreen);
}

Bool
afbSetVisualTypes(int depth, int visuals, int bitsPerRGB)
{
	return miSetVisualTypes(depth, visuals, bitsPerRGB, -1);
}

/*
 * Given a list of formats for a screen, create a list
 * of visuals and depths for the screen which correspond to
 * the set which can be used with this version of afb.
 */

Bool
afbInitVisuals(VisualPtr *visualp, DepthPtr *depthp, int *nvisualp,
	       int *ndepthp, int *rootDepthp, VisualID *defaultVisp,
	       unsigned long sizes, int bitsPerRGB)
{
	return miInitVisuals(visualp, depthp, nvisualp, ndepthp, rootDepthp,
				defaultVisp, sizes, bitsPerRGB, -1);
}
