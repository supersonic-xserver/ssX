/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _EVISTR_H_
#define _EVISTR_H_

#include <X11/extensions/XEVI.h>

#define VisualID CARD32
#define EVINAME "Extended-Visual-Information"
#define XEVI_MAJOR_VERSION	1	/* current version numbers */
#define XEVI_MINOR_VERSION	0

typedef CARD32 VisualID32;
#define sz_VisualID32 4

typedef struct _xExtendedVisualInfo {
    VisualID	core_visual_id B32;
    INT8	screen;
    INT8	level;
    CARD8	transparency_type;
    CARD8	pad0;
    CARD32	transparency_value B32;
    CARD8	min_hw_colormaps;
    CARD8	max_hw_colormaps;
    CARD16	num_colormap_conflicts B16;
} xExtendedVisualInfo;
#define sz_xExtendedVisualInfo 16

typedef struct _XEVIQueryVersion {
    CARD8	reqType;		/* always XEVIReqCode */
    CARD8	xeviReqType;		/* always X_EVIQueryVersion */
    CARD16	length B16;
} xEVIQueryVersionReq;
#define sz_xEVIQueryVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    CARD8 	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;	/* major version of EVI protocol */
    CARD16	minorVersion B16;	/* minor version of EVI protocol */
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
} xEVIQueryVersionReply;
#define sz_xEVIQueryVersionReply	32

typedef struct _XEVIGetVisualInfoReq {
    CARD8	reqType;	/* always XEVIReqCode */
    CARD8	xeviReqType;	/* always X_EVIGetVisualInfo */
    CARD16      length B16;
    CARD32 	n_visual B32;
} xEVIGetVisualInfoReq;
#define sz_xEVIGetVisualInfoReq	8

typedef struct _XEVIGetVisualInfoReply {
    BYTE	type;  /* X_Reply */
    CARD8	unused;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	n_info B32;
    CARD32	n_conflicts B32;
    CARD32	pad0 B32;
    CARD32	pad1 B32;
    CARD32	pad2 B32;
    CARD32	pad3 B32;
} xEVIGetVisualInfoReply;
#define sz_xEVIGetVisualInfoReply	32

#undef VisualID

#endif /* _EVISTR_H_ */
