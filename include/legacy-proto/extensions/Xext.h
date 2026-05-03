/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XEXT_H_
#define _XEXT_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

typedef int (*XExtensionErrorHandler)(Display *, _Xconst char *,
				      _Xconst char *);

extern XExtensionErrorHandler XSetExtensionErrorHandler(
	XExtensionErrorHandler handler
);

extern int XMissingExtension(
    Display*		/* dpy */,
    _Xconst char*	/* ext_name */
);

_XFUNCPROTOEND

#define X_EXTENSION_UNKNOWN "unknown"
#define X_EXTENSION_MISSING "missing"

#endif /* _XEXT_H_ */
