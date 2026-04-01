/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XCMISCSTR_H_
#define _XCMISCSTR_H_

#define X_XCMiscGetVersion	0
#define X_XCMiscGetXIDRange	1
#define X_XCMiscGetXIDList	2

#define XCMiscNumberEvents	0

#define XCMiscNumberErrors	0

#define XCMiscMajorVersion	1
#define XCMiscMinorVersion	1

#define XCMiscExtensionName	"XC-MISC"

typedef struct {
    CARD8	reqType;	/* always XCMiscCode */
    CARD8	miscReqType;	/* always X_XCMiscGetVersion */
    CARD16	length B16;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
} xXCMiscGetVersionReq;
#define sz_xXCMiscGetVersionReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;
    CARD16	minorVersion B16;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xXCMiscGetVersionReply;
#define sz_xXCMiscGetVersionReply 32

typedef struct {
    CARD8	reqType;	/* always XCMiscCode */
    CARD8	miscReqType;	/* always X_XCMiscGetXIDRange */
    CARD16	length B16;
} xXCMiscGetXIDRangeReq;
#define sz_xXCMiscGetXIDRangeReq 4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	start_id B32;
    CARD32	count B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xXCMiscGetXIDRangeReply;
#define sz_xXCMiscGetXIDRangeReply 32

typedef struct {
    CARD8	reqType;	/* always XCMiscCode */
    CARD8	miscReqType;	/* always X_XCMiscGetXIDList */
    CARD16	length B16;
    CARD32	count B32;	/* number of IDs requested */
} xXCMiscGetXIDListReq;
#define sz_xXCMiscGetXIDListReq 8

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8	pad0;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	count B32;	/* number of IDs requested */
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xXCMiscGetXIDListReply;
#define sz_xXCMiscGetXIDListReply 32

#endif /* _XCMISCSTR_H_ */
