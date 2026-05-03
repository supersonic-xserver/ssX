/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _BUFFERSTR_H_
#define _BUFFERSTR_H_

#include <X11/extensions/lbxbuf.h>

/*
 * ZLIB Input/Output buffer
 */
typedef struct _zlibbuffer {
	char 	*bufbase;
	char	*bufend;
	char	*bufptr;
	int  	bufcnt;
} ZlibBuffer;

#define BYTES_AVAIL(inbuf, len)	\
	(((inbuf)->bufcnt >= (len)) ? (inbuf)->bufptr : NULL)

#endif	/* _BUFFERSTR_H_ */
