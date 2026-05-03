/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XAGSRV_H_
#define _XAGSRV_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

extern void XagConnectionInfo(
    ClientPtr			/* client */,
    xConnSetupPrefix**		/* conn_prefix */,
    char**			/* conn_info */,
    int*			/* num_screens */
);

extern VisualID XagRootVisual(
    ClientPtr			/* client */
);

extern Colormap XagDefaultColormap(
    ClientPtr			/* client */
);

extern ClientPtr XagLeader(
    ClientPtr			/* client */
);

extern void XagCallClientStateChange(
    ClientPtr			/* client */
);

extern Bool XagIsControlledRoot (
    ClientPtr			/* client */,
    WindowPtr			/* pParent */
);

extern XID XagId (
    ClientPtr			/* client */
);

extern void XagGetDeltaInfo (
    ClientPtr			/* client */,
    CARD32*			/* buf */
);

_XFUNCPROTOEND

#endif /* _XAGSRV_H_ */

