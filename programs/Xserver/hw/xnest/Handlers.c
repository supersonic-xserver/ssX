/* $Xorg: Handlers.c,v 1.3 2000/08/17 19:53:28 cpqbld Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
/* $XFree86: xc/programs/Xserver/hw/xnest/Handlers.c,v 1.3 2003/11/16 05:05:20 dawes Exp $ */

#include "X.h"
#include "Xproto.h"
#include "screenint.h"
#include "input.h"
#include "misc.h"
#include "scrnintstr.h"
#include "windowstr.h"
#include "servermd.h"

#include "Xnest.h"

#include "Display.h"
#include "Events.h"
#include "Handlers.h"

void
xnestBlockHandler(pointer blockData, OSTimePtr pTimeout, pointer pReadMask)
{
  xnestCollectExposures();
  XFlush(xnestDisplay);
}

void
xnestWakeupHandler(pointer blockData, int result, pointer pReadMask)
{
  xnestCollectEvents();
}
