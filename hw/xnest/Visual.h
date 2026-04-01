/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
/* $XFree86: xc/programs/Xserver/hw/xnest/Visual.h,v 1.3 2006/01/09 15:00:30 dawes Exp $ */

#ifndef XNESTVISUAL_H
#define XNESTVISUAL_H

Visual *xnestVisual(VisualPtr pVisual);
Visual *xnestVisualFromID(ScreenPtr pScreen, VisualID visual);
Colormap xnestDefaultVisualColormap(Visual *visual);

#define xnestDefaultVisual(pScreen) \
  xnestVisualFromID((pScreen), (pScreen)->rootVisual)

#endif /* XNESTVISUAL_H */
