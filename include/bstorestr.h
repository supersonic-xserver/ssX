/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _BSTORESTR_H_
#define _BSTORESTR_H_

#include "gc.h"
#include "pixmap.h"
#include "region.h"
#include "window.h"

typedef    void (* BackingStoreSaveAreasProcPtr)(
	PixmapPtr /*pBackingPixmap*/,
	RegionPtr /*pObscured*/,
	int /*x*/,
	int /*y*/,
	WindowPtr /*pWin*/);

typedef    void (* BackingStoreRestoreAreasProcPtr)(
	PixmapPtr /*pBackingPixmap*/,
	RegionPtr /*pExposed*/,
	int /*x*/,
	int /*y*/,
	WindowPtr /*pWin*/);

typedef    void (* BackingStoreSetClipmaskRgnProcPtr)(
	GCPtr /*pBackingGC*/,
	RegionPtr /*pbackingCompositeClip*/);

typedef    PixmapPtr (* BackingStoreGetImagePixmapProcPtr)(void);

typedef    PixmapPtr (* BackingStoreGetSpansPixmapProcPtr)(void);

typedef struct _BSFuncs {

	BackingStoreSaveAreasProcPtr SaveAreas;
	BackingStoreRestoreAreasProcPtr RestoreAreas;
	BackingStoreSetClipmaskRgnProcPtr SetClipmaskRgn;
	BackingStoreGetImagePixmapProcPtr GetImagePixmap;
	BackingStoreGetSpansPixmapProcPtr GetSpansPixmap;

} BSFuncRec, *BSFuncPtr;

#endif /* _BSTORESTR_H_ */
