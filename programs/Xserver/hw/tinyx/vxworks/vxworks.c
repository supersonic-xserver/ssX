/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


 * Copyright © 1999 Network Computing Devices, Inc.  All rights reserved.
 *
 * Author: Keith Packard
 */

#include "tinyx.h"
#include <X11/keysym.h>

int
VxWorksInit (void)
{
    return 1;
}

void
VxWorksEnable (void)
{
}

Bool
VxWorksSpecialKey (KeySym sym)
{
    switch (sym) {
    case XK_Sys_Req:
	download(1, "setup", 0);
	return TRUE;
    case XK_Break:
	download(1, "launcher", 0);
	return TRUE;
    case XK_Delete:
	dispatchException |= DE_REBOOT;
	return TRUE;
    case XK_BackSpace:
	dispatchException |= DE_RESET;
	return TRUE;
    }
    return FALSE;
}

void
VxWorksDisable (void)
{
}

void
VxWorksFini (void)
{
}

KdOsFuncs   VxWorksFuncs = {
    VxWorksInit,
    VxWorksEnable,
    VxWorksSpecialKey,
    VxWorksDisable,
    VxWorksFini,
};

void
OsVendorPreInit (void)
{
}

void
OsVendorInit (void)
{
    KdOsInit (&VxWorksFuncs);
}
