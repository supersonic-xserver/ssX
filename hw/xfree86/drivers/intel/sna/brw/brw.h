/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include "brw_eu.h"

bool brw_sf_kernel__nomask(struct brw_compile *p);
bool brw_sf_kernel__mask(struct brw_compile *p);

bool brw_wm_kernel__affine(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__affine_mask(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__affine_mask_ca(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__affine_mask_sa(struct brw_compile *p, int dispatch_width);

bool brw_wm_kernel__projective(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__projective_mask(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__projective_mask_ca(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__projective_mask_sa(struct brw_compile *p, int dispatch_width);

bool brw_wm_kernel__affine_opacity(struct brw_compile *p, int dispatch_width);
bool brw_wm_kernel__projective_opacity(struct brw_compile *p, int dispatch_width);
