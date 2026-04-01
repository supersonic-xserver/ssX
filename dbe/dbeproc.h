/* $XFree86: xc/programs/Xserver/dbe/dbeproc.h,v 1.3 2007/01/04 02:48:12 tsi Exp $ */
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


#ifndef DBEPROC_H
#define DBEPROC_H 1

#include "extnsionst.h"

#ifndef DBE_EXT_INIT_ONLY

#include "dbestruct.h"

typedef Bool (*DbeInitFuncPtr)(ScreenPtr pScreen,
			       DbeScreenPrivPtr pDbeScreenPriv);

/* DbeValidateBuffer declaration moved to dix.h */

void DbeRegisterFunction(ScreenPtr pScreen, DbeInitFuncPtr funct);

#endif /* DBE_EXT_INIT_ONLY */

void DbeExtensionInit(INITARGS);

#endif /* DBEPROC_H */
