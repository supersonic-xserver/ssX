/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _ZLIB_H_
#define _ZLIB_H_

#define ZLIB_STRCOMP_OPT	"XC-ZLIB"
#define ZLIB_STRCOMP_OPT_LEN	7

#define ZLIB_PACKET_HDRLEN	2
#define ZLIB_MAX_DATALEN	0xfff
#define ZLIB_MAX_PLAIN		270
#define ZLIB_MAX_OUTLEN		(ZLIB_MAX_PLAIN << 1)

#define ZLIB_COMPRESS_FLAG	0x80
#define ZLIB_DATALEN_MASK	0x0f

#define ZLIB_PUT_PKTHDR(p, len, compflag) \
    { \
	(p)[0] = ((unsigned)(len)) >> 8 | ((compflag) ? ZLIB_COMPRESS_FLAG : 0);\
	(p)[1] = (len) & 0xff; \
    }

#define ZLIB_GET_DATALEN(p) \
	((((unsigned)((p)[0] & ZLIB_DATALEN_MASK)) << 8) | (unsigned)(p)[1])

#define ZLIB_COMPRESSED(p) ((p)[0] & ZLIB_COMPRESS_FLAG)

struct ZlibInfo;

extern void * ZlibInit ( int fd, int level );
extern void ZlibFree ( struct ZlibInfo *comp );
extern int ZlibFlush ( int fd );
extern int ZlibStuffInput ( int fd, unsigned char *buffer, int buflen );
extern void ZlibCompressOn ( int fd );
extern void ZlibCompressOff ( int fd );
extern int ZlibWrite ( int fd, unsigned char *buffer, int buflen );
extern int ZlibWriteV ( int fd, struct iovec *iov, int iovcnt );
extern int ZlibRead ( int fd, unsigned char *buffer, int buflen );
extern int ZlibInputAvail ( int fd );


#endif /* _ZLIB_H_ */
