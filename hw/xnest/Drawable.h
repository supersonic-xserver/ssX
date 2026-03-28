/*
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


Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
/* $XFree86: xc/programs/Xserver/hw/xnest/Drawable.h,v 1.4 2006/01/09 15:00:30 dawes Exp $ */

#ifndef XNESTDRAWABLE_H
#define XNESTDRAWABLE_H

#include "XNWindow.h"
#include "XNPixmap.h"

#define xnestDrawable(pDrawable) \
  ((pDrawable)->type == DRAWABLE_WINDOW ? \
   xnestWindow((WindowPtr)pDrawable) : \
   xnestPixmap((PixmapPtr)pDrawable))

#endif /* XNESTDRAWABLE_H */
