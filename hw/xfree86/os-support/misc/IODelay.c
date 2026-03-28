/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/misc/IODelay.c,v 1.5 2006/01/09 15:00:22 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


 
/*******************************************************************************
  Stub for Alpha Linux
*******************************************************************************/

#include <X11/X.h>
#include "xf86.h"
#include "xf86Priv.h"
#include "xf86_OSlib.h"

/* 
 *   All we really need is a delay of about 40ns for I/O recovery for just
 *   about any occasion, but we'll be more conservative here:  On a
 *   100-MHz CPU, produce at least a delay of 1,000ns.
 */ 
void
xf86IODelay()
{
	xf86UDelay(1);
}

