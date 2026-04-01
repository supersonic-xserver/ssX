/* $XFree86: xc/lib/misc/snprintf.h,v 3.2 1999/04/28 15:04:51 dawes Exp $ */
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


#ifndef SNPRINTF_H
#define SNPRINTF_H

#ifdef HAS_SNPRINTF
#ifdef LIBXT
#define _XtSnprintf snprintf
#define _XtVsnprintf vsnprintf
#endif
#ifdef LIBX11
#define _XSnprintf snprintf
#define _XVsnprintf vsnprintf
#endif
#else /* !HAS_SNPRINTF */

#ifdef LIBXT
#define snprintf _XtSnprintf
#define vsnprintf _XtVsnprintf
#endif
#ifdef LIBX11
#define snprintf _XSnprintf
#define vsnprintf _XVsnprintf
#endif

extern int snprintf (char *str, size_t count, const char *fmt, ...);
extern int vsnprintf (char *str, size_t count, const char *fmt, va_list arg);

#endif /* HAS_SNPRINTF */

#endif /* SNPRINTF_H */
