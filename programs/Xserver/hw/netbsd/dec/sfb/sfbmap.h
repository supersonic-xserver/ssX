/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



#if PSZ == 8
#elif PSZ == 32

#define decSfbValidateGC	decSfb32ValidateGC
#define decSfbMatchCommon	decSfb32MatchCommon
#define decSfbCreateGC		decSfb32CreateGC

#define decSfbCopyArea		decSfb32CopyArea
#define decSfbCopyWindow	decSfb32CopyWindow
#define decSfbDoBitblt		decSfb32DoBitblt
#define decSfbDoBitbltCopy	decSfb32DoBitbltCopy
#define decSfbDoBitbltSimple	decSfb32DoBitbltSimple

#define decSfbGCFuncs		decSfb32GCFuncs
#define decSfbTEOps1Rect	decSfb32TEOps1Rect
#define decSfbNonTEOps1Rect	decSfb32NonTEOps1Rect
#define decSfbTEOps		decSfb32TEOps
#define decSfbNonTEOps		decSfb32NonTEOps

#else
#error Unsupported PSZ
#endif
