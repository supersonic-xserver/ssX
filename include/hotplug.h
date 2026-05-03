/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef HOTPLUG_H
#define HOTPLUG_H 1

/*
 * Stub definitions for legacy build mode
 * Hotplug support is disabled in XFree86 4.8.0
 * HAVE_HOTPLUG is defined as 0 in legacy build mode
 */

/* 
 * DeviceIntPtr is defined in input.h - do not redefine here
 * IDevPtr is a stub for legacy compatibility
 */
typedef void *IDevPtr;

#endif /* HOTPLUG_H */
