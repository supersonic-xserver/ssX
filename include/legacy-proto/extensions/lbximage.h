/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _LBX_IMAGE_H_
#define _LBX_IMAGE_H_

#include <X11/Xfuncproto.h>

_XFUNCPROTOBEGIN

typedef struct _LbxBitmapCompMethod {

    char *methodName;
    int inited;
    int methodOpCode;	/* to be filled on reply from server */

    int (*compInit)(
	void
    );

    int (*compFunc)(
	unsigned char *		/* inbuf */,
	unsigned char *		/* outbuf */,
	int			/* outbufSize */,
	int			/* image_bytes */,
	int			/* pixels_per_line */,
	int			/* padded_bytes_per_scanline */,
	int			/* reverse_bits */,
	int *			/* bytesCompressed */
    );

    int (*decompFunc)(
	unsigned char *		/* inbuf */,
	unsigned char *		/* outbuf */,
	int			/* image_bytes */,
	int			/* pixels_per_line */,
	int			/* padded_bytes_per_scanline */,
	int			/* reverse_bits */
    );

} LbxBitmapCompMethod;


#define LBX_MAX_DEPTHS 5

typedef struct _LbxPixmapCompMethod {

    char *methodName;
    unsigned formatMask;
    int depthCount;
    int depths[LBX_MAX_DEPTHS];
    int inited;
    int methodOpCode;	/* to be filled on reply from server */

    int (*compInit)(
	void
    );

    int (*compFunc)(
	char *			/* inbuf */,
	char *			/* outbuf */,
	int			/* outbufSize */,
	int			/* format */,
	int			/* depth */,
	int			/* num_scan_lines */,
	int			/* scan_line_size */,
	int *			/* bytesCompressed */
    );

    int (*decompFunc)(
	char *			/* inbuf */,
	char *			/* outbuf */,
	int			/* num_scan_lines */,
	int			/* scan_line_size */
    );

} LbxPixmapCompMethod;


extern int LbxImageEncodePackBits (
char *			/* inbuf */,
char *			/* outbuf */,
int			/* outbufSize */,
int			/* format */,
int			/* depth */,
int			/* num_scan_lines */,
int			/* scan_line_size */,
int *			/* bytesCompressed */
);

extern int LbxImageEncodeFaxG42D (
unsigned char *		/* inbuf */,
unsigned char *		/* outbuf */,
int			/* outbufSize */,
int			/* image_bytes */,
int			/* pixels_per_line */,
int			/* padded_bytes_per_scanline */,
int			/* reverse_bits */,
int *			/* bytesCompressed */
);

extern int LbxImageDecodePackBits (
char *			/* inbuf */,
char *			/* outbuf */,
int			/* num_scan_lines */,
int			/* scan_line_size */
);

extern int LbxImageDecodeFaxG42D (
unsigned char *		/* inbuf */,
unsigned char *		/* outbuf */,
int			/* image_bytes */,
int			/* pixels_per_line */,
int			/* padded_bytes_per_scanline */,
int			/* reverse_bits */
);

_XFUNCPROTOEND

#define LBX_IMAGE_COMPRESS_SUCCESS		0
#define LBX_IMAGE_COMPRESS_NO_SUPPORT		1
#define LBX_IMAGE_COMPRESS_BAD_MALLOC		2
#define LBX_IMAGE_COMPRESS_NOT_WORTH_IT		3

#endif /* _LBX_IMAGE_H_ */
