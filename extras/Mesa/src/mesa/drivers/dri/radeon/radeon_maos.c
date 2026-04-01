/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */




/* If using new packets, can choose either verts or arrays.
 * Otherwise, must use verts.
 */
#include "radeon_context.h"
#define RADEON_MAOS_VERTS 1
#if (RADEON_MAOS_VERTS) || (RADEON_OLD_PACKETS)
#include "radeon_maos_verts.c"
#else
#include "radeon_maos_arrays.c"
#endif
