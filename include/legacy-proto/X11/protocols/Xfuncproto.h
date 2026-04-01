/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XFUNCPROTO_H_
#define _XFUNCPROTO_H_

#ifndef NeedFunctionPrototypes
#define NeedFunctionPrototypes 1
#endif /* NeedFunctionPrototypes */

#ifndef NeedVarargsPrototypes
#define NeedVarargsPrototypes 1
#endif /* NeedVarargsPrototypes */

#if NeedFunctionPrototypes

#ifndef NeedNestedPrototypes
#define NeedNestedPrototypes 1
#endif /* NeedNestedPrototypes */

#ifndef _Xconst
#define _Xconst const
#endif /* _Xconst */

#ifndef NeedWidePrototypes
#ifdef NARROWPROTO
#define NeedWidePrototypes 0
#else
#define NeedWidePrototypes 1		/* default to make interropt. easier */
#endif
#endif /* NeedWidePrototypes */

#endif /* NeedFunctionPrototypes */

#ifndef _XFUNCPROTOBEGIN
#if defined(__cplusplus) || defined(c_plusplus) /* for C++ V2.0 */
#define _XFUNCPROTOBEGIN extern "C" {	/* do not leave open across includes */
#define _XFUNCPROTOEND }
#else
#define _XFUNCPROTOBEGIN
#define _XFUNCPROTOEND
#endif
#endif /* _XFUNCPROTOBEGIN */

#endif /* _XFUNCPROTO_H_ */
