/* $XFree86: xc/programs/Xserver/Xext/appgroup.h,v 1.2 2004/06/25 15:44:42 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#ifndef APPGROUP_H
#define APPGROUP_H 1

void XagClientStateChange(
    CallbackListPtr* pcbl,
    pointer nulldata,
    pointer calldata);
int ProcXagCreate (
    register ClientPtr client);
int ProcXagDestroy(
    register ClientPtr client);

#endif
