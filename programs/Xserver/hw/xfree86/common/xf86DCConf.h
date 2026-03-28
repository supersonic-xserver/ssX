/* $XFree86$ */
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


#include "xf86.h"
#include "xf86_Config.h"
#include "xf86_Option.h"

#ifndef DCConfig
extern
#endif
int DCpushToken;

#ifndef DCConfig
extern
#endif
LexRec DCval;

#ifndef DCConfig
extern
int xf86DCGetToken(
#if NeedFunctionPrototypes
char *,
SymTabRec [],
SymTabRec []
#endif
);
OFlagSet *xf86DCGetOption(
#if NeedFunctionPrototypes
char* Pointer,
OptFlagRec []
#endif
);
void xf86DCConfigError(
#if NeedFunctionPrototypes
char *
#endif
);
#endif
