/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef GEN8_VERTEX_H
#define GEN8_VERTEX_H

#include "compiler.h"

#include "sna.h"
#include "sna_render.h"

void gen8_vertex_align(struct sna *sna, const struct sna_composite_op *op);
void gen8_vertex_flush(struct sna *sna);
int gen8_vertex_finish(struct sna *sna);
void gen8_vertex_close(struct sna *sna);

#endif /* GEN8_VERTEX_H */
