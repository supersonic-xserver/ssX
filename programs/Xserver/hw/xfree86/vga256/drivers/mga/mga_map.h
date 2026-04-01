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


#if (defined(__STDC__) && !defined(UNIXCPP)) || defined(ANSICPP)
#define CATNAME(prefix,subname) prefix##subname
#else
#define CATNAME(prefix,subname) prefix/**/subname
#endif

#if PSZ == 8
#define MGANAME(subname) CATNAME(Mga8,subname)
#elif PSZ == 16
#define MGANAME(subname) CATNAME(Mga16,subname)
#elif PSZ == 24
#define MGANAME(subname) CATNAME(Mga24,subname)
#elif PSZ == 32
#define MGANAME(subname) CATNAME(Mga32,subname)
#endif
