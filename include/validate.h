/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef VALIDATE_H
#define VALIDATE_H

#include "miscstruct.h"
#include "regionstr.h"

typedef enum { VTOther, VTStack, VTMove, VTUnmap, VTMap, VTBroken } VTKind;

/* union _Validate is now device dependent; see mivalidate.h for an example */
typedef union _Validate *ValidatePtr;

#define UnmapValData ((ValidatePtr)1)

#endif /* VALIDATE_H */
