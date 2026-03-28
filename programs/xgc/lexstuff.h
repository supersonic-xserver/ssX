/* $XFree86: xc/programs/xgc/lexstuff.h,v 1.2 2005/03/28 02:51:14 dawes Exp $ */
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


#ifdef NEED_YYIN
extern FILE *yyin;
#endif

extern void yyerror(const char *);
#if !defined(YYBISON) && !(defined(YYBYACC) && defined(__NetBSD__))
extern int yyparse(void);
#endif
extern int yylex(void);

