/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _MITMISCSTR_H_
#define _MITMISCSTR_H_

#include <X11/extensions/MITMisc.h>

#define MITMISCNAME "MIT-SUNDRY-NONSTANDARD"

typedef struct _SetBugMode {
    CARD8	reqType;	/* always MITReqCode */
    CARD8	mitReqType;	/* always X_MITSetBugMode */
    CARD16	length B16;
    BOOL	onOff;
    BYTE	pad0;
    CARD16	pad1;
} xMITSetBugModeReq;
#define sz_xMITSetBugModeReq	8

typedef struct _GetBugMode {
    CARD8	reqType;	/* always MITReqCode */
    CARD8	mitReqType;	/* always X_MITGetBugMode */
    CARD16	length B16;
} xMITGetBugModeReq;
#define sz_xMITGetBugModeReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	onOff;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
} xMITGetBugModeReply;
#define sz_xMITGetBugModeReply	32

#endif /* _MITMISCSTR_H_ */
