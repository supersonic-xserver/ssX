/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/misc/xf86_IlHack.c,v 3.6 2006/01/09 15:00:22 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * This file is an incredible crock to get the normally-inline functions
 * built into the server so that things can be debugged properly.
 *
 * Note: this doesn't work when using a compiler other than GCC.
 */

#define static /**/
#define __inline__ /**/
#undef NO_INLINE
#define DO_PROTOTYPES
#include "compiler.h"
