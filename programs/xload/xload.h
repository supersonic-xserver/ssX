/* $XFree86: xc/programs/xload/xload.h,v 1.2 2001/08/28 17:10:39 tsi Exp $ */
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


#ifndef _XLOAD_H_
#define _XLOAD_H_

#include <X11/Intrinsic.h>

extern void InitLoadPoint(void);
extern void GetLoadPoint(Widget w, XtPointer closure, XtPointer call_data);
extern void GetRLoadPoint(Widget w, XtPointer closure, XtPointer call_data);

#endif
