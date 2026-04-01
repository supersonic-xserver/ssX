/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XCUP_H_
#define _XCUP_H_

#include <X11/Xfuncproto.h>

#define X_XcupQueryVersion			0
#define X_XcupGetReservedColormapEntries	1
#define X_XcupStoreColors			2

#define XcupNumberErrors			0

#ifndef _XCUP_SERVER_

_XFUNCPROTOBEGIN

Bool XcupQueryVersion(
    Display*			/* dpy */,
    int*			/* major_version */,
    int*			/* minor_version */
);

Status XcupGetReservedColormapEntries(
    Display*			/* dpy */,
    int				/* screen */,
    XColor**			/* colors_out */,
    int*			/* ncolors */
);

Status XcupStoreColors(
    Display*			/* dpy */,
    Colormap			/* colormap */,
    XColor*			/* colors */,
    int				/* ncolors */
);

_XFUNCPROTOEND

#endif /* _XCUP_SERVER_ */

#endif /* _XCUP_H_ */

