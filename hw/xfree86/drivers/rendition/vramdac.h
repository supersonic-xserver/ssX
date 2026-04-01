/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/vramdac.h,v 1.6 2002/04/04 14:05:45 eich Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * file vramdac.h
 *
 * headfile for vramdac.c
 */

#ifndef __VRAMDAC_H__
#define __VRAMDAC_H__

/*
 * includes
 */

#include "vtypes.h"

/*
 * defines
 */

#define VERITE_NOCURSOR  0
#define VERITE_2COLORS   1
#define VERITE_3COLORS   2
#define VERITE_XCURSOR   3

#define VERITE_CURSOR32  0
#define VERITE_CURSOR64  1

/*
 * function prototypes
 */

void verite_savedac (ScrnInfoPtr pScreenInfo);
void verite_restoredac (ScrnInfoPtr pScreenInfo, RenditionRegPtr reg);
int verite_initdac(ScrnInfoPtr pScreenInfo, vu8 bpp, vu8 doubleclock);
void verite_enablecursor(ScrnInfoPtr pScreenInfo, int type, int size);
void verite_movecursor(ScrnInfoPtr pScreenInfo, vu16 x, vu16 y, vu8 xo, vu8 yo);
void verite_setcursorcolor(ScrnInfoPtr pScreenInfo, vu32 bg, vu32 fg);
void verite_loadcursor(ScrnInfoPtr pScreenInfo, vu8 type, vu8 *cursorimage);
void verite_setpalette(ScrnInfoPtr pScreenInfo, int numColors, int *indices,
		  LOCO *colors, VisualPtr pVisual);

#endif /* #ifndef _VRAMDAC_H_ */

/*
 * end of file vramdac.h
 */
