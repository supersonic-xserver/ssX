/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/shared/xf86Axp.h,v 1.3 2001/02/15 19:46:03 eich Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XF86_AXP_H_
#define _XF86_AXP_H_

typedef enum {
  SYS_NONE,
  TSUNAMI,
  LCA,
  APECS,
  T2,
  T2_GAMMA,
  CIA,
  MCPCIA,
  JENSEN,
  POLARIS,
  PYXIS,
  PYXIS_CIA,
  IRONGATE
} axpDevice;
  
typedef struct {
  axpDevice id;
  unsigned long hae_thresh;
  unsigned long hae_mask;
  unsigned long size;
} axpParams;

extern axpParams xf86AXPParams[];

#endif

