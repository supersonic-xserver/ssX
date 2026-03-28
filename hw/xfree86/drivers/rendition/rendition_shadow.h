/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


 * file rendition_shadow.h
 *
 * headfile for rendition_shadow.c
 */
/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/rendition_shadow.h,v 1.1 2000/03/01 00:25:25 dawes Exp $ */

#ifndef __RENDITION_SHADOW_H__
#define __RENDITION_SHADOW_H__

void renditionRefreshArea(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
void renditionRefreshArea8(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
void renditionRefreshArea16(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
void renditionRefreshArea24(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
void renditionRefreshArea32(ScrnInfoPtr pScrn, int num, BoxPtr pbox);
void renditionPointerMoved(int index, int x, int y);


#endif 

/*
 * end of file rendition_shadow.h
 */
