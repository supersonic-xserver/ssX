/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#ifndef CALLBACK_H
#define CALLBACK_H

#include <X11/X.h>      /* for GContext, Mask */
#include <X11/Xdefs.h>  /* for Bool */
#include <X11/Xproto.h>
#include <X11/Xfuncproto.h>

/*
 *  callback manager stuff
 */

#ifndef _XTYPEDEF_CALLBACKLISTPTR
typedef struct _CallbackList *CallbackListPtr; /* also in misc.h */
#define _XTYPEDEF_CALLBACKLISTPTR
#endif

typedef void (*CallbackProcPtr) (
    CallbackListPtr *, pointer, pointer);

/*
 * CallbackFuncsRec - vtable for a callback list implementation.
 * Allows different callback list types to provide their own
 * CallCallbacks and DeleteCallbackList operations.
 */
typedef void (*CallCallbacksProcPtr)(
    CallbackListPtr * /*pcbl*/,
    pointer           /*call_data*/);

typedef void (*DeleteCallbackListProcPtr)(
    CallbackListPtr * /*pcbl*/);

typedef struct _CallbackFuncs {
    CallCallbacksProcPtr        callCallbacks;
    DeleteCallbackListProcPtr   deleteCallbackList;
} CallbackFuncsRec, *CallbackFuncsPtr;

/* Compatibility: legacy code expects these member names - add as additional members */
typedef struct _CallbackFuncsLegacy {
    CallCallbacksProcPtr        AddCallback;
    DeleteCallbackListProcPtr   DeleteCallback;
    CallCallbacksProcPtr        CallCallbacks;
    DeleteCallbackListProcPtr   DeleteCallbackList;
} CallbackFuncsLegacyRec, *CallbackFuncsLegacyPtr;

/* Union to allow both old and new code to work */
typedef union _CallbackFuncsUnion {
    CallbackFuncsRec newStyle;
    CallbackFuncsLegacyRec oldStyle;
} CallbackFuncsUnion;

extern _X_EXPORT Bool AddCallback(
    CallbackListPtr * /*pcbl*/,
    CallbackProcPtr /*callback*/,
    pointer /*data*/);

extern _X_EXPORT Bool DeleteCallback(
    CallbackListPtr * /*pcbl*/,
    CallbackProcPtr /*callback*/,
    pointer /*data*/);

extern _X_EXPORT void CallCallbacks(
    CallbackListPtr * /*pcbl*/,
    pointer /*call_data*/);

extern _X_EXPORT void DeleteCallbackList(
    CallbackListPtr * /*pcbl*/);

extern _X_EXPORT void InitCallbackManager(void);

#endif /* CALLBACK_H *//*/
 */