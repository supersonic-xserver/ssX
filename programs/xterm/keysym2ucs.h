/* $XFree86: xc/programs/xterm/keysym2ucs.h,v 1.1 1999/06/12 15:37:18 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * This module converts keysym values into the corresponding ISO 10646-1
 * (UCS, Unicode) values.
 */

#include <X11/X.h>

long keysym2ucs(KeySym keysym);
