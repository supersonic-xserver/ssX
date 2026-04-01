/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FONTCACHESTR_H_
#define _FONTCACHESTR_H_

#include <X11/extensions/fontcache.h>

#define FONTCACHENAME		"FontCache"

#define FONTCACHE_MAJOR_VERSION	0	/* current version numbers */
#define FONTCACHE_MINOR_VERSION	1

typedef struct _FontCacheQueryVersion {
    CARD8	reqType;		/* always FontCacheReqCode */
    CARD8	fontcacheReqType;	/* always X_FontCacheQueryVersion */
    CARD16	length B16;
} xFontCacheQueryVersionReq;
#define sz_xFontCacheQueryVersionReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD16	majorVersion B16;	/* major version of Font-Cache */
    CARD16	minorVersion B16;	/* minor version of Font-Cache */
    CARD32	pad2 B32;
    CARD32	pad3 B32;
    CARD32	pad4 B32;
    CARD32	pad5 B32;
    CARD32	pad6 B32;
} xFontCacheQueryVersionReply;
#define sz_xFontCacheQueryVersionReply	32

typedef struct _FontCacheGetCacheSettings {
    CARD8	reqType;		/* always FontCacheReqCode */
    CARD8	fontcacheReqType;	/* always X_FontCacheGetCacheSettings */
    CARD16	length B16;
} xFontCacheGetCacheSettingsReq;
#define sz_xFontCacheGetCacheSettingsReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	himark B32;
    CARD32	lowmark B32;
    CARD32	balance B32;
    CARD32	reserve0 B32;
    CARD32	reserve1 B32;
    CARD32	reserve2 B32;
} xFontCacheGetCacheSettingsReply;
#define sz_xFontCacheGetCacheSettingsReply	32

typedef struct _FontCacheChangeCacheSettings {
    CARD8	reqType;		/* always FontCacheReqCode */
    CARD8	fontcacheReqType;	/* always X_FontCacheChangeCacheSettings */
    CARD16	length B16;
    CARD32	himark B32;
    CARD32	lowmark B32;
    CARD32	balance B32;
    CARD32	reserve0 B32;
    CARD32	reserve1 B32;
    CARD32	reserve2 B32;
    CARD32	reserve3 B32;
} xFontCacheChangeCacheSettingsReq;
#define sz_xFontCacheChangeCacheSettingsReq	32

typedef struct _FontCacheGetCacheStatistics {
    CARD8	reqType;		/* always FontCacheReqCode */
    CARD8	fontcacheReqType;	/* always X_FontCacheGetCacheStatistics */
    CARD16	length B16;
} xFontCacheGetCacheStatisticsReq;
#define sz_xFontCacheGetCacheStatisticsReq	4

typedef struct {
    BYTE	type;			/* X_Reply */
    BOOL	pad1;
    CARD16	sequenceNumber B16;
    CARD32	length B32;
    CARD32	purge_runs B32;
    CARD32	purge_stat B32;
    CARD32	balance B32;
    CARD32	reserve0 B32;
    CARD32	f_hits B32;
    CARD32	f_misshits B32;
    CARD32	f_purged B32;
    CARD32	f_usage B32;
    CARD32	f_reserve0 B32;
    CARD32	v_hits B32;
    CARD32	v_misshits B32;
    CARD32	v_purged B32;
    CARD32	v_usage B32;
    CARD32	v_reserve0 B32;
} xFontCacheGetCacheStatisticsReply;
#define sz_xFontCacheGetCacheStatisticsReply	64

#endif /* _FONTCACHESTR_H_ */
