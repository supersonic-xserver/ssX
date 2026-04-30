/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef INPUTUTILS_H
#define INPUTUTILS_H

#include "input.h"

struct _ValuatorMask {
    int8_t      last_bit; /* highest bit set in mask */
    uint8_t     mask[(MAX_VALUATORS + 7)/8];
    int         valuators[MAX_VALUATORS]; /* valuator data */
};

#endif
