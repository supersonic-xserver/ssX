/* $XFree86: xc/programs/Xserver/mi/mioverlay.h,v 3.4 2001/04/14 21:15:26 mvojkovi Exp $ */
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


#ifndef __MIOVERLAY_H
#define __MIOVERLAY_H

typedef void (*miOverlayTransFunc)(ScreenPtr, int, BoxPtr);
typedef Bool (*miOverlayInOverlayFunc)(WindowPtr);

Bool
miInitOverlay(
   ScreenPtr pScreen, 
   miOverlayInOverlayFunc inOverlay,
   miOverlayTransFunc trans
);

Bool
miOverlayGetPrivateClips(
    WindowPtr pWin,
    RegionPtr *borderClip,
    RegionPtr *clipList
);

Bool miOverlayCollectUnderlayRegions(WindowPtr, RegionPtr*);
void miOverlayComputeCompositeClip(GCPtr, WindowPtr);
Bool miOverlayCopyUnderlay(ScreenPtr);
void miOverlaySetTransFunction(ScreenPtr, miOverlayTransFunc);
void miOverlaySetRootClip(ScreenPtr, Bool);

#endif /* __MIOVERLAY_H */
