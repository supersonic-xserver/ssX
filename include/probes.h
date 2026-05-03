/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef XORG_PROBES_H
#define XORG_PROBES_H

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

/* definitions needed to include Dtrace probes in a source file */

#if XSERVER_DTRACE
#include <sys/types.h>
typedef const char *string;
typedef const uint8_t *const_uint8_p;
typedef const double *const_double_p;
#include "../dix/Xserver-dtrace.h"
#endif

#endif /* XORG_PROBES_H */
