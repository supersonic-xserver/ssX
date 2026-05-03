/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XCUPSTR_H_ /* { */
#define _XCUPSTR_H_

#include <X11/extensions/Xcup.h>

#define XCUPNAME "TOG-CUP"

#define XCUP_MAJOR_VERSION	1	/* current version numbers */
#define XCUP_MINOR_VERSION	0

typedef struct _XcupQueryVersion {
    CARD8	reqType;	/* always XcupReqCode */
    CARD8	xcupReqType;	/* always X_XcupQueryVersion */
    CARD16	length B16;
    CARD16	client_major_version B16;
    CARD16	client_minor_version B16;
} xXcupQueryVersionReq;
#define sz_xXcupQueryVersionReq		8

typedef struct {
    BYTE	type;		/* X_Reply */
    BOOL	pad1;
    CARD16	sequence_number B16;
    CARD32	length B32;
    CARD16	server_major_version B16;
    CARD16	server_minor_version B16;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xXcupQueryVersionReply;
#define sz_xXcupQueryVersionReply	32

typedef struct _XcupGetReservedColormapEntries {
    CARD8	reqType;	/* always XcupReqCode */
    CARD8	xcupReqType;	/* always X_XcupGetReservedColormapEntries */
    CARD16	length B16;
    CARD32	screen B32;
} xXcupGetReservedColormapEntriesReq;
#define sz_xXcupGetReservedColormapEntriesReq 8

typedef struct {
    BYTE	type;		/* X_Reply */
    BOOL	pad1;
    CARD16	sequence_number B16;
    CARD32	length B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
    CARD32	pad7 B32;
} xXcupGetReservedColormapEntriesReply;
#define sz_xXcupGetReservedColormapEntriesReply		32

typedef struct _XcupStoreColors {
    CARD8	reqType;	/* always XcupReqCode */
    CARD8	xcupReqType;	/* always X_XcupStoreColors */
    CARD16	length B16;
    CARD32	cmap B32;
} xXcupStoreColorsReq;
#define sz_xXcupStoreColorsReq		8

typedef struct {
    BYTE	type;		/* X_Reply */
    BOOL	pad1;
    CARD16	sequence_number B16;
    CARD32	length B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
    CARD32	pad7 B32;
} xXcupStoreColorsReply;
#define sz_xXcupStoreColorsReply	32

#endif /* } _XCUPSTR_H_ */

