/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/hwcursor.h,v 1.4 1999/11/19 13:54:45 hohndel Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * file hwcursor.h
 */

#ifndef __HWCURSOR_H__
#define __HWCURSOR_H__

/*
 * functions prototypes
 */

void RenditionHWCursorPreInit(ScrnInfoPtr pScreenInfo);
Bool RenditionHWCursorInit(int scrnIndex, ScreenPtr pScreen);
void RenditionHWCursorRelease (ScrnInfoPtr pScreenInfo);

#define HC_SIZE  (64*64*2)/8  /* 1024 */

/* end of __HWCURSOR_H__ */
#endif 

/*
 * end of file hwcursor.h
 */

