/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/tdfx/tdfx_dripriv.h,v 1.2 1999/12/14 01:33:50 robin Exp $ */
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


#ifndef _TDFX_DRIPRIV_H_
#define _TDFX_DRIPRIV_H_

#define TDFX_MAX_DRAWABLES 256

extern void GlxSetVisualConfigs(
    int nconfigs,
    __GLXvisualConfig *configs,
    void **configprivs
);

typedef struct {
  /* Nothing here yet */
  int dummy;
} TDFXConfigPrivRec, *TDFXConfigPrivPtr;

typedef struct {
  /* Nothing here yet */
  int dummy;
} TDFXDRIContextRec, *TDFXDRIContextPtr;

#endif
