/* $XFree86: xc/programs/Xserver/Xext/xvmod.c,v 1.3 2005/10/14 15:16:12 tsi Exp $ */
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


#include <X11/X.h>
#include "misc.h"
#include "scrnintstr.h"
#include "gc.h"
#include <X11/extensions/Xv.h>
#include <X11/extensions/Xvproto.h>
#include "xvdix.h"
#include "xvmodproc.h"

void
XvRegister()
{
    XvScreenInitProc = XvScreenInit;
    XvGetScreenIndexProc = XvGetScreenIndex;
    XvGetRTPortProc = XvGetRTPort;
    XvMCScreenInitProc = XvMCScreenInit;
}

