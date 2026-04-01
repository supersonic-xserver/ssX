/* $XFree86: xc/programs/Xserver/hw/xfree86/dummylib/xf86addrestolist.c,v 1.3 2002/12/24 15:50:43 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#include "xf86.h"

resPtr
xf86AddResToList(resPtr rlist, resRange *Range, int entityIndex)
{
    return rlist;
}

void
xf86FreeResList(resPtr rlist)
{
    return;
}

resPtr
xf86DupResList(const resPtr rlist)
{
    return rlist;
}
