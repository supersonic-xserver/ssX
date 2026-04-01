/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



#if PSZ == 8
#elif PSZ == 32

#define alphaTgaValidateGC	alphaTga32ValidateGC
#define alphaTgaMatchCommon	alphaTga32MatchCommon
#define alphaTgaCreateGC	alphaTga32CreateGC

#define alphaTgaCopyArea	alphaTga32CopyArea
#define alphaTgaCopyWindow	alphaTga32CopyWindow
#define alphaTgaDoBitblt	alphaTga32DoBitblt
#define alphaTgaDoBitbltCopy	alphaTga32DoBitbltCopy
#define alphaTgaDoBitbltSimple	alphaTga32DoBitbltSimple

#define alphaTgaGCFuncs		alphaTga32GCFuncs
#define alphaTgaTEOps1Rect	alphaTga32TEOps1Rect
#define alphaTgaNonTEOps1Rect	alphaTga32NonTEOps1Rect
#define alphaTgaTEOps		alphaTga32TEOps
#define alphaTgaNonTEOps	alphaTga32NonTEOps

#else
#error Unsupported PSZ
#endif
