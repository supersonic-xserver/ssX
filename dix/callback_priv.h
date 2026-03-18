/*
 * callback_priv.h - Private callback support for DIX
 * 
 * This header provides internal callback types and functions.
 */

#ifndef _CALLBACK_PRIV_H
#define _CALLBACK_PRIV_H

#include "include/callback.h"

/* Callback procedure type */
typedef void (*CallbackProcPtr)(void *ptr, void *data);

/* Callback list entry */
typedef struct _Callback {
    struct _Callback *next;
    CallbackProcPtr proc;
    void *data;
} CallbackRec, *CallbackPtr;

/* Callback list structure */
typedef struct _CallbackList {
    CallbackPtr list;
    int disabled;
} CallbackList;

#define CALLBACK_NIL { NULL, 0 }

/* Callback functions */
extern _X_EXPORT void AddCallback(CallbackPtr *head, CallbackProcPtr proc, void *data);
extern _X_EXPORT void DeleteCallback(CallbackPtr *head, CallbackProcPtr proc, void *data);
extern _X_EXPORT void CallCallbacks(CallbackPtr *head, void *call_data);

/* Pre-defined callback lists */
extern _X_EXPORT CallbackList DeviceInitializeCallback;
extern _X_EXPORT CallbackList DeviceResetCallback;
extern _X_EXPORT CallbackList DeviceCloseCallback;
extern _X_EXPORT CallbackList ClientStateCallback;
extern _X_EXPORT CallbackList SelectionCallback;

#endif /* _CALLBACK_PRIV_H */
