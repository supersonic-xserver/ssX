/* $XFree86: xc/programs/Xserver/hw/xfree86/ramdac/xf86RamDacPriv.h,v 1.4 1999/07/18 03:27:02 dawes Exp $ */
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


#include "xf86RamDac.h"
#include "xf86cmap.h"

void RamDacGetRecPrivate(void);
Bool RamDacGetRec(ScrnInfoPtr pScrn);
int  RamDacGetScreenIndex(void);
void RamDacLoadPalette(ScrnInfoPtr pScrn, int numColors, int *indices,
    			LOCO *colors, VisualPtr pVisual);
