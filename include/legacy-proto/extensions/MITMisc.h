/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XMITMISC_H_
#define _XMITMISC_H_

#include <X11/Xfuncproto.h>

#define X_MITSetBugMode			0
#define X_MITGetBugMode			1

#define MITMiscNumberEvents		0

#define MITMiscNumberErrors		0

#ifndef _MITMISC_SERVER_

_XFUNCPROTOBEGIN

Bool XMITMiscQueryExtension(
    Display*		/* dpy */,
    int*		/* event_basep */,
    int*		/* error_basep */
);

Status XMITMiscSetBugMode(
    Display*		/* dpy */,
    Bool		/* onOff */
);

Bool XMITMiscGetBugMode(
    Display*		/* dpy */
);

_XFUNCPROTOEND

#endif

#endif
