/* $XFree86: xc/programs/Xserver/hw/xfree86/dummylib/fatalerror.c,v 1.1 2000/02/13 03:06:38 dawes Exp $ */
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


#include "X.h"
#include "os.h"
#include "xf86.h"
#include "xf86Priv.h"

/*
 * Utility functions required by libxf86_os. 
 */

void
FatalError(const char *f, ...)
{
    va_list args;

    va_start(args, f);
    fprintf(stderr, "Fatal Error:\n");
    vfprintf(stderr, f, args);
    va_end(args);
    exit(1);
}

