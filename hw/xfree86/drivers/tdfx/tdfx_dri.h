/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/tdfx/tdfx_dri.h,v 1.6 2004/12/10 16:07:03 alanh Exp $ */
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


#ifndef _TDFX_DRI_
#define _TDFX_DRI_

#include "xf86drm.h"

typedef struct {
  drm_handle_t regs;
  drmSize regsSize;
  drmAddress regsMap;
  int deviceID;
  int width;
  int height;
  int mem;
  int cpp;
  int stride;
  int fifoOffset;
  int fifoSize;
  int fbOffset;
  int backOffset;
  int depthOffset;
  int textureOffset;
  int textureSize;
  unsigned int sarea_priv_offset;
} TDFXDRIRec, *TDFXDRIPtr;

#endif
