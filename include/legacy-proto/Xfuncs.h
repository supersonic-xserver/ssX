/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XFUNCS_H_
#define _XFUNCS_H_

#include <X11/Xosdefs.h>

/* the old Xfuncs.h, for pre-R6 */
#if !(defined(XFree86LOADER) && defined(IN_MODULE))

#ifdef X_USEBFUNCS
void bcopy();
void bzero();
int bcmp();
#else
#if defined(SYSV) && !defined(__SCO__)
#include <memory.h>
void bcopy();
#define bzero(b,len) memset(b, 0, len)
#define bcmp(b1,b2,len) memcmp(b1, b2, len)
#else
#include <string.h>
#ifdef __SCO__
#include <strings.h>
#endif
#define _XFUNCS_H_INCLUDED_STRING_H
#define bcopy(b1,b2,len) memmove(b2, b1, (size_t)(len))
#define bzero(b,len) memset(b, 0, (size_t)(len))
#define bcmp(b1,b2,len) memcmp(b1, b2, (size_t)(len))
#endif
#endif /* X_USEBFUNCS */

/* the new Xfuncs.h */

#if !defined(X_NOT_STDC_ENV) && (!defined(sun) || defined(SVR4))
/* the ANSI C way */
#ifndef _XFUNCS_H_INCLUDED_STRING_H
#include <string.h>
#endif
#undef bzero
#define bzero(b,len) memset(b,0,len)
#else /* else X_NOT_STDC_ENV or SunOS 4 */
#if defined(SYSV) || defined(luna) || defined(sun) || defined(__sxg__)
#include <memory.h>
#define memmove(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#if defined(SYSV) && defined(_XBCOPYFUNC)
#undef memmove
#define memmove(dst,src,len) _XBCOPYFUNC((char *)(src),(char *)(dst),(int)(len))
#define _XNEEDBCOPYFUNC
#endif
#else /* else vanilla BSD */
#define memmove(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#define memcpy(dst,src,len) bcopy((char *)(src),(char *)(dst),(int)(len))
#define memcmp(b1,b2,len) bcmp((char *)(b1),(char *)(b2),(int)(len))
#endif /* SYSV else */
#endif /* ! X_NOT_STDC_ENV else */

#if defined(X_NOT_STDC_ENV) || (defined(sun) && !defined(SVR4))
#define atexit(f) on_exit(f, 0)
#endif

#endif /* !(defined(XFree86LOADER) && defined(IN_MODULE)) */

#endif /* _XFUNCS_H_ */
