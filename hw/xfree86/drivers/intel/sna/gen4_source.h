/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef GEN4_SOURCE_H
#define GEN4_SOURCE_H

#include "compiler.h"

#include "sna.h"
#include "sna_render.h"

bool
gen4_channel_init_solid(struct sna *sna,
			struct sna_composite_channel *channel,
			uint32_t color);

bool
gen4_channel_init_linear(struct sna *sna,
			 PicturePtr picture,
			 struct sna_composite_channel *channel,
			 int x, int y,
			 int w, int h,
			 int dst_x, int dst_y);

#endif /* GEN4_SOURCE_H */
