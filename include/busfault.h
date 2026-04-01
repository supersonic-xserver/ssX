/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _BUSFAULT_H_
#define _BUSFAULT_H_

#include <dix-config.h>

#ifdef BUSFAULT

#include <sys/types.h>

typedef void (*busfault_notify_ptr) (void *context);

struct busfault *
busfault_register_mmap(void *addr, size_t size, busfault_notify_ptr notify, void *context);

void
busfault_unregister(struct busfault *busfault);

void
busfault_check(void);

Bool
busfault_init(void);

#endif

#endif /* _BUSFAULT_H_ */
