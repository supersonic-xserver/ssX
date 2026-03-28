/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/vboard.h,v 1.6 2000/03/31 20:13:26 dawes Exp $ */
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


/*
 * vboard.h
 *
 * functions to interact with a Verite board
 */

#ifndef __VBOARD_H__
#define __VBOARD_H__


/*
 * includes
 */

#include "rendition.h"
#include "vtypes.h"

/*
 * function prototypes
 */

int verite_initboard(ScrnInfoPtr pScreenInfo);
int verite_resetboard(ScrnInfoPtr pScreenInfo);
int verite_getmemorysize(ScrnInfoPtr pScreenInfo);

void verite_check_csucode(ScrnInfoPtr pScreenInfo);


#endif /* __VBOARD_H__ */

/*
 * end of file vboard.h
 */
