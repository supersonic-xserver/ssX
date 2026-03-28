/* $XFree86: xc/lib/X11/Xresinternal.h,v 1.1 2003/04/13 19:22:19 dawes Exp $ */
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


#ifndef _XRESINTERNAL_H_
#define _XRESINTERNAL_H_

/* type defines */
typedef unsigned long Signature;

/* prototypes */
extern XrmQuark _XrmInternalStringToQuark(
    register _Xconst char *name, register int len, register Signature sig,
    Bool permstring);

#endif /* _XRESOURCEINTERNAL_H_ */
/* DON'T ADD STUFF AFTER THIS #endif */
