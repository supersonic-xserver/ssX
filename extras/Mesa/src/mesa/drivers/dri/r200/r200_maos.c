/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */




/* Currently, can only use arrays, verts are not implemented, though
 * verts are suspected to be faster.
 * To get an idea how the verts path works, look at the radeon implementation.
 */
#include <string.h>
 
#include "r200_context.h"
#define R200_MAOS_VERTS 0
#if (R200_MAOS_VERTS)
#include "r200_maos_verts.c"
#else
#include "r200_maos_arrays.c"
#endif
