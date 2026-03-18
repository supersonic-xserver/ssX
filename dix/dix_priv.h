/*
 * dix_priv.h - Private DIX functions and definitions
 * 
 * This header provides access to internal DIX functions that were
 * previously in XFree86's private headers.
 */

#ifndef _DIX_PRIV_H
#define _DIX_PRIV_H

#include "include/dix.h"
#include "include/privates.h"

/* Resource allocation - moved from dispatch.c */
typedef unsigned long XID;

typedef struct _Resource *ResourcePtr;

extern _X_EXPORT int dixCreateWindow(WindowPtr pWin, WindowPtr pParent, 
                                     int x, int y, unsigned int w, unsigned int h,
                                     unsigned int bw, unsigned int class, 
                                     VisualPtr pVisual, unsigned long mask,
                                     XID *pWindowId, ClientPtr client);

/* Private data management */
extern _X_EXPORT PrivatePtr dixAllocatePrivate(Private **privates, int keyIndex);
extern _X_EXPORT void dixFreePrivates(Private *privates);

/* Screen access */
extern _X_EXPORT ScreenPtr dixGetScreenPtr(int index);

/* Event handling */
extern _X_EXPORT void mieqEnqueue(DeviceIntPtr pDev, InternalEvent *e);

/* Device private data */
typedef struct _DeviceIntRec *DeviceIntPtr;
extern _X_EXPORT void *dixLookupPrivate(Private *privates, int key);

/* Client private data */
typedef struct _ClientRec *ClientPtr;
extern _X_EXPORT void *dixLookupClientPrivate(ClientPtr client, int key);

/* Callback support - moved from callback.c */
typedef void (*CallbackProcPtr)(void *ptr, void *data);
typedef struct _Callback {
    struct _Callback *next;
    CallbackProcPtr proc;
    void *data;
} CallbackRec, *CallbackPtr;

extern _X_EXPORT void AddCallback(CallbackPtr *head, CallbackProcPtr proc, void *data);
extern _X_EXPORT void DeleteCallback(CallbackPtr *head, CallbackProcPtr proc, void *data);
extern _X_EXPORT void CallCallbacks(CallbackPtr *head, void *call_data);

/* Callback list types */
typedef struct _CallbackList {
    CallbackPtr list;
    int disabled;
} CallbackList;

#define CALLBACK_NIL { NULL, 0 }

/* Main callback lists */
extern _X_EXPORT CallbackList DeviceInitializeCallback;
extern _X_EXPORT CallbackList DeviceResetCallback;
extern _X_EXPORT CallbackList DeviceCloseCallback;

/* Connection callbacks */
extern _X_EXPORT CallbackList ClientStateCallback;

/* Selection callbacks */
typedef struct {
    WindowPtr window;
    Atom selection;
} SelectionInfoRec;

extern _X_EXPORT CallbackList SelectionCallback;

#endif /* _DIX_PRIV_H */
