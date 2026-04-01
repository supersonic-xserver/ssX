/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _EXT_FONTCACHE_H_
#define _EXT_FONTCACHE_H_

#define X_FontCacheQueryVersion		0
#define X_FontCacheGetCacheSettings	1
#define X_FontCacheChangeCacheSettings	2
#define X_FontCacheGetCacheStatistics	3

#define FontCacheNumberEvents		0

#define FontCacheBadProtocol		0
#define FontCacheCannotAllocMemory	1
#define FontCacheNumberErrors		(FontCacheCannotAllocMemory + 1)

typedef struct {
    long	himark;
    long	lowmark;
    long	balance;
} FontCacheSettings, *FontCacheSettingsPtr;

struct cacheinfo {
    long	hits;
    long	misshits;
    long	purged;
    long	usage;
};

typedef struct {
    long		purge_runs;
    long		purge_stat;
    long		balance;
    struct cacheinfo	f;
    struct cacheinfo	v;
} FontCacheStatistics, *FontCacheStatisticsPtr;

#ifndef _FONTCACHE_SERVER_

#include <X11/Xlib.h>

_XFUNCPROTOBEGIN

Bool FontCacheQueryVersion(
    Display*		/* dpy */,
    int* 		/* majorVersion */,
    int* 		/* minorVersion */
);

Bool FontCacheQueryExtension(
    Display*		/* dpy */,
    int*		/* event_base */,
    int*		/* error_base */
);

Status FontCacheGetCacheSettings(
    Display*			/* dpy */,
    FontCacheSettings*		/* cache info */
);

Status FontCacheChangeCacheSettings(
    Display*			/* dpy */,
    FontCacheSettings*		/* cache info */
);

Status FontCacheGetCacheStatistics(
    Display*			/* dpy */,
    FontCacheStatistics*	/* cache statistics info */
);

_XFUNCPROTOEND

#endif /* !_FONTCACHE_SERVER_ */

#endif /* _EXT_FONTCACHE_H_ */
