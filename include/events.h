/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef EVENTS_H
#define EVENTS_H
typedef struct _DeviceEvent DeviceEvent;
typedef struct _DeviceChangedEvent DeviceChangedEvent;
#ifdef XFreeXDGA
typedef struct _DGAEvent DGAEvent;
#endif
typedef struct _RawDeviceEvent RawDeviceEvent;
#ifdef XQUARTZ
typedef struct _XQuartzEvent XQuartzEvent;
#endif
typedef union _InternalEvent InternalEvent;

#endif
