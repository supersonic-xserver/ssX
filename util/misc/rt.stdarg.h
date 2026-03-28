/* $Xorg: rt.stdarg.h,v 1.3 2000/08/17 19:55:21 cpqbld Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _STDARG_H
#define _STDARG_H
typedef int *va_list;
#define va_start(ap, arg)       ap = ((int *)&arg) + ((sizeof(arg) + 3) / 4)
#define va_end(ap)
#define va_arg(ap, type)        ((type *)(ap += (sizeof(type)+3)/4))[-1]
#endif
