/* $XFree86: xc/lib/font/stubs/xpstubs.c,v 1.1 1999/01/11 05:13:22 dawes Exp $ */
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


/*
  stub for XpClient* functions.
*/

#include "stubs.h"

Bool
XpClientIsBitmapClient(ClientPtr client)
{
    return True;
}

Bool
XpClientIsPrintClient(ClientPtr client, FontPathElementPtr fpe)
{
    return False;
}

/* end of file */
