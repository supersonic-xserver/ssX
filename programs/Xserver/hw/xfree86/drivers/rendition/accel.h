/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */
/* file accel.h
 *
 * header file for accel.c
 */
/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/accel.h,v 1.3 1999/11/19 13:54:44 hohndel Exp $ */

#ifndef __ACCEL_H__
#define __ACCEL_H__
 


/*
 * includes
 */

#include "vtypes.h"



/*
 * function prototypes
 */

void RENDITIONAccelPreInit(ScrnInfoPtr pScreenInfo);
void RENDITIONAccelXAAInit(ScreenPtr pScreen);
void RENDITIONAccelNone(ScrnInfoPtr pScreenInfo);
int RENDITIONInitUcode(ScrnInfoPtr pScreenInfo);
int RENDITIONLoadUcode(ScrnInfoPtr pScreenInfo);

void RENDITIONDumpUcode(ScrnInfoPtr pScreenInfo);
void RENDITIONDrawSomething(ScrnInfoPtr pScreenInfo);



#endif /* #ifdef __ACCEL_H__ */

/*
 * end of file accel.h
 */
