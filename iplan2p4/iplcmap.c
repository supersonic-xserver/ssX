/* $XFree86: xc/programs/Xserver/iplan2p4/iplcmap.c,v 3.3 2006/01/09 15:00:35 dawes Exp $ */
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

/* Modified nov 94 by Martin Schaller (Martin_Schaller@maus.r.de) for use with
interleaved planes */

#include <X11/X.h>
#include <X11/Xproto.h>
#include "scrnintstr.h"
#include "colormapst.h"
#include "resource.h"
#include "micmap.h"

int
iplListInstalledColormaps(pScreen, pmaps)
    ScreenPtr	pScreen;
    Colormap	*pmaps;
{
    return miListInstalledColormaps(pScreen, pmaps);
}


void
iplInstallColormap(pmap)
    ColormapPtr	pmap;
{
    miInstallColormap(pmap);
}

void
iplUninstallColormap(pmap)
    ColormapPtr	pmap;
{
    miUninstallColormap(pmap);
}

void
iplResolveColor(pred, pgreen, pblue, pVisual)
    unsigned short	*pred, *pgreen, *pblue;
    register VisualPtr	pVisual;
{
    miResolveColor(pred, pgreen, pblue, pVisual);
}

Bool
iplInitializeColormap(pmap)
    register ColormapPtr	pmap;
{
    return miInitializeColormap(pmap);
}

int
iplExpandDirectColors (pmap, ndef, indefs, outdefs)
    ColormapPtr	pmap;
    int		ndef;
    xColorItem	*indefs, *outdefs;
{
    return miExpandDirectColors(pmap, ndef, indefs, outdefs);
}

Bool
iplCreateDefColormap(pScreen)
    ScreenPtr pScreen;
{
    return miCreateDefColormap(pScreen);
}

Bool
iplSetVisualTypes (depth, visuals, bitsPerRGB)
    int	    depth;
    int	    visuals;
{
    return miSetVisualTypes(depth, visuals, bitsPerRGB, -1);
}

/*
 * Given a list of formats for a screen, create a list
 * of visuals and depths for the screen which coorespond to
 * the set which can be used with this version of ipl.
 */

Bool
iplInitVisuals (visualp, depthp, nvisualp, ndepthp, rootDepthp, defaultVisp, sizes, bitsPerRGB)
    VisualPtr	*visualp;
    DepthPtr	*depthp;
    int		*nvisualp, *ndepthp;
    int		*rootDepthp;
    VisualID	*defaultVisp;
    unsigned long   sizes;
    int		bitsPerRGB;
{
    return miInitVisuals(visualp, depthp, nvisualp, ndepthp, rootDepthp,
			 defaultVisp, sizes, bitsPerRGB, -1);
}
