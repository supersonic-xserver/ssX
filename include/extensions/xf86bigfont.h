/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XF86BIGFONT_H_
#define _XF86BIGFONT_H_

#include <X11/Xfuncproto.h>

#define X_XF86BigfontQueryVersion	0
#define X_XF86BigfontQueryFont		1

#define XF86BigfontNumberEvents		0

#define XF86BigfontNumberErrors		0

#ifdef _XF86BIGFONT_SERVER_

_XFUNCPROTOBEGIN

#include "font.h"

extern void XFree86BigfontExtensionInit(void);
extern void XF86BigfontFreeFontShm(FontPtr);
extern void XF86BigfontCleanup(void);

_XFUNCPROTOEND

#endif /* _XF86BIGFONT_SERVER_ */

#endif /* _XF86BIGFONT_H_ */
