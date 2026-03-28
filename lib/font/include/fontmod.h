/* $XFree86: xc/lib/font/include/fontmod.h,v 1.3 1998/12/13 05:32:33 dawes Exp $ */
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


#ifndef _FONTMOD_H_
#define _FONTMOD_H_

typedef void (*InitFont)(void);

typedef struct {
    InitFont	initFunc;
    char *	name;
    pointer	module;
} FontModule;

extern FontModule *FontModuleList;

#endif /* _FONTMOD_H_ */
