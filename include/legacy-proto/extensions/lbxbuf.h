/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _BUFFER_H_
#define _BUFFER_H_

#define INBUFFER_SIZE		(1 << 13)	/* 8K */
#define OUTBUFFER_SIZE		(1 << 12)	/* 4K */

#ifndef TRUE
#define TRUE    1
#endif
#ifndef FALSE
#define FALSE   0
#endif

typedef struct _zlibbuffer  *ZlibBufferPtr;

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

extern int  InitZlibBuffer(ZlibBufferPtr b, int size);
extern void FreeZlibBuffer(ZlibBufferPtr b);
extern char *ReserveOutBuf(ZlibBufferPtr outbuf, int outlen);

_XFUNCPROTOEND

#endif	/* _BUFFER_H_ */
