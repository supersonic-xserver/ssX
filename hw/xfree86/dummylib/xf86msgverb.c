/* $XFree86: xc/programs/Xserver/hw/xfree86/dummylib/xf86msgverb.c,v 1.3 2005/10/14 15:16:50 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#include <X11/X.h>
#include "os.h"
#include "xf86.h"
#include "xf86Priv.h"

/*
 * Utility functions required by libxf86_os. 
 */

void
xf86MsgVerb(MessageType type, int verb, const char *format, ...)
{
    va_list ap;

    va_start(ap, format);
    LogVWrite(verb, format, ap);
    va_end(ap);
}

