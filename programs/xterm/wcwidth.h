/* $XFree86: xc/programs/xterm/wcwidth.h,v 1.4 2002/09/30 00:39:07 dickey Exp $ */
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


#ifndef	included_wcwidth_h
#define	included_wcwidth_h 1

#include <stddef.h>

extern int mk_wcswidth(const wchar_t * pwcs, size_t n);
extern int mk_wcswidth_cjk(const wchar_t * pwcs, size_t n);
extern int mk_wcwidth(wchar_t ucs);
extern int mk_wcwidth_cjk(wchar_t ucs);
extern int wcswidth(const wchar_t * pwcs, size_t n);
extern int wcswidth_cjk(const wchar_t * pwcs, size_t n);

#endif /* included_wcwidth_h */
