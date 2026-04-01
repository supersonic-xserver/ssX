/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _EVENTCONVERT_H_
#include <X11/X.h>
#include <X11/extensions/XIproto.h>
#include "input.h"
#include "events.h"

#define FP1616(integral, frac) ((integral) * (1 << 16) + (frac) * (1 << 16))

_X_EXPORT int EventToCore(InternalEvent *event, xEvent *core);
_X_EXPORT int EventToXI(InternalEvent *ev, xEvent **xi, int *count);
_X_EXPORT int EventToXI2(InternalEvent *ev, xEvent **xi);
_X_INTERNAL int GetCoreType(InternalEvent* ev);
_X_INTERNAL int GetXIType(InternalEvent* ev);
_X_INTERNAL int GetXI2Type(InternalEvent* ev);

#endif /* _EVENTCONVERT_H_ */
