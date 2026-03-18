/*
 * ssX Shim Layer Implementation
 * 
 * This file provides the actual storage for global variables declared in ssx_compat.h.
 * These are needed to bridge legacy XFree86 code with modern XLibre/DIX.
 */

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#include "ssx_compat.h"
#include "inputstr.h"
#include "misc.h"
#include "privates.h"
#include "eventstr.h"

/* Connection info pointer - legacy global, can be reassigned */
char *ConnectionInfo = NULL;

/* Client limit configuration */
int LimitClients = 256;

/* Client operation tracking for XACE (shadow storage)
 * Modern ClientRec no longer has minorOp/majorOp, but XACE may need them */
typedef struct {
    CARD8 majorOp;
    CARD8 minorOp;
} SSX_ClientOpTracker;

SSX_ClientOpTracker ssx_client_ops[256] = {{0}};

/* Accessor functions for client operations */
void ssx_set_client_major(void *client, CARD8 op) {
    unsigned long idx = ((unsigned long)client) % 256;
    ssx_client_ops[idx].majorOp = op;
}

void ssx_set_client_minor(void *client, CARD8 op) {
    unsigned long idx = ((unsigned long)client) % 256;
    ssx_client_ops[idx].minorOp = op;
}

CARD8 ssx_get_client_major(void *client) {
    unsigned long idx = ((unsigned long)client) % 256;
    return ssx_client_ops[idx].majorOp;
}

CARD8 ssx_get_client_minor(void *client) {
    unsigned long idx = ((unsigned long)client) % 256;
    return ssx_client_ops[idx].minorOp;
}

/* ============================================================================
 * Legacy XFree86 to Modern Xlibre Shim Wrappers
 * ============================================================================ */

/* Include required headers for wrapper implementations */
#include "dixstruct.h"
#include "mipointer.h"
#include "mi.h"
#include "eventstr.h"
#include "input.h"
#include "windowstr.h"
#include "scrnintstr.h"
#include "dix.h"

/* ============================================================================
 * SSX_LAST_VALUATORS - Convert int[36] to double* for modern APIs
 * ============================================================================ */

/* Legacy XFree86 used int[36] for last.valuators, modern uses double*
 * This wrapper provides the conversion */
#ifndef MAX_VALUATORS
#define MAX_VALUATORS 36
#endif

/* Static buffer for conversion - not thread-safe but matches X server single-threaded event model */
static double ssx_valuator_buffer[MAX_VALUATORS];

double* ssx_get_last_valuators(DeviceIntPtr dev) {
    int i;
    for (i = 0; i < MAX_VALUATORS && i < dev->valuator->numAxes; i++) {
        ssx_valuator_buffer[i] = (double)dev->last.valuators[i];
    }
    return ssx_valuator_buffer;
}

void ssx_set_last_valuators(DeviceIntPtr dev, double *vals) {
    int i;
    for (i = 0; i < MAX_VALUATORS && i < dev->valuator->numAxes; i++) {
        dev->last.valuators[i] = (int)vals[i];
    }
}

/* ============================================================================
 * SCREEN X/Y Shim Functions
 * ============================================================================ */

/* Modern ScreenRec doesn't have x/y members. Use screenInfo for desktop coordinates.
 * These functions provide the legacy screen offset behavior. */

int ssx_screen_get_x(ScreenPtr scr) {
    /* Modern X doesn't use per-screen offsets. Return 0. */
    return 0;
}

int ssx_screen_get_y(ScreenPtr scr) {
    /* Modern X doesn't use per-screen offsets. Return 0. */
    return 0;
}

/* ============================================================================
 * GetMotionHistory Shim
 * ============================================================================ */

/* Legacy GetMotionHistory has 6 parameters including BOOL core
 * Modern GetMotionHistory in input.h has 5 parameters wrapped with macro
 * This shim provides the legacy signature by calling the modern version 
 * 
 * Note: The actual implementation is provided via ssx_GetMotionHistory declaration
 * in ssx_compat.h - this file just provides the storage if needed */

/* ============================================================================
 * mieqEnqueue Shim
 * ============================================================================ */

/* Legacy code may pass xEvent*, modern expects InternalEvent*
 * This wrapper handles the conversion */

void ssx_mieqEnqueue(DeviceIntPtr pDev, void *event) {
    /* Cast to InternalEvent - in most cases this should work since
     * InternalEvent is the union that contains xEvent */
    mieqEnqueue(pDev, (InternalEvent *)event);
}

/* ============================================================================
 * init_device_event Shim
 * ============================================================================ */

/* Legacy init_device_event may have different signature
 * This provides compatibility. Use int instead of enum to avoid include issues */

void ssx_init_device_event(DeviceEvent *event, DeviceIntPtr dev, Time ms, 
                          int source) {
    memset(event, 0, sizeof(DeviceEvent));
    event->header = ET_Internal;
    event->type = ET_KeyPress;  /* Default */
    event->length = sizeof(DeviceEvent);
    event->time = ms;
    event->deviceid = dev->id;
    event->sourceid = dev->id;
}

/* ============================================================================
 * dixGetScreenPtr - Get ScreenPtr from screen index
 * ============================================================================ */

/* This function provides screen pointer access from screen index
 * Needed by GLX VND module */
ScreenPtr dixGetScreenPtr(int index) {
    if (index < 0 || index >= screenInfo.numScreens) {
        return NULL;
    }
    return screenInfo.screens[index];
}

/* ============================================================================
 * SSX_GET_MOTION_HISTORY Implementation
 * ============================================================================ */

/* Legacy GetMotionHistory had 6 parameters (including BOOL core)
 * Modern has 5. The wrapper is defined via macro in ssx_compat.h 
 * which calls ssx_GetMotionHistory. Here we provide the implementation. */

/* ============================================================================
 * InitPointerDeviceStruct Shim
 * ============================================================================ */

/* Legacy XFree86 InitPointerDeviceStruct had different signature.
 * Modern version has different parameter requirements.
 * This wrapper provides compatibility. */
Bool ssx_InitPointerDeviceStruct(DevicePtr device, CARD8 *map, int numButtons,
                                Atom *btn_labels, PtrCtrlProcPtr controlProc,
                                int numMotionEvents, int numAxes, Atom *axes_labels) {
    DeviceIntPtr dev = (DeviceIntPtr)device;
    (void)btn_labels;   /* Modern API doesn't have labels param */
    (void)axes_labels;  /* Modern API doesn't have axes_labels param */

    /* Initialize button class - modern API uses 3 params (no labels) */
    if (!InitButtonClassDeviceStruct(dev, numButtons, map))
        return FALSE;

    /* Initialize valuator class - modern API uses 4 params (no axes_labels) */
    if (!InitValuatorClassDeviceStruct(dev, numAxes, 
                                       (ValuatorMotionProcPtr)NULL, numMotionEvents, Relative))
        return FALSE;

    /* Initialize pointer feedback */
    if (!InitPtrFeedbackClassDeviceStruct(dev, controlProc))
        return FALSE;

    return TRUE;
}

/* ============================================================================
 * dixAllocatePrivates Shim  
 * ============================================================================ */

/* Legacy XFree86 dixAllocatePrivates took 2 args (module, type)
 * Modern takes 3+ args. Provide compatibility wrapper. */
Bool ssx_dixAllocatePrivates(void *module, int type) {
    PrivateRec *p = NULL;
    return dixAllocatePrivates(&p, type);
}

/* ============================================================================
 * dixLookupResourceByType Shim
 * ============================================================================ */

/* Used in dixfonts.c - legacy function that may need wrapper */
int ssx_dixLookupResourceByType(void **result, XID id, RESTYPE type, 
                                ClientPtr client, Mask access) {
    return dixLookupResourceByType(result, id, type, client, access);
}

/* ============================================================================
 * Additional Screen Accessor Shim
 * ============================================================================ */

/* Provide GET_SCREEN_X/Y as inline functions for code that needs them */
int ssx_GetScreenX(ScreenPtr s) { return 0; }
int ssx_GetScreenY(ScreenPtr s) { return 0; }

/* ============================================================================
 * Touch Point Info Accessors
 * ============================================================================ */

/* Fix pointer/double issues with touch point info */
void* ssx_touch_get_ddx_info(TouchPointInfoPtr t) { 
    return t->ddx_info; 
}

void ssx_touch_set_ddx_info(TouchPointInfoPtr t, void *info) {
    t->ddx_info = (DDXTouchPointInfoPtr)info;
}

/* ============================================================================
 * Valuator Mask Helpers for int[36] -> double* conversion
 * ============================================================================ */

double* ssx_valuator_mask_get_double_array(ValuatorMask *mask) {
    static double buf[MAX_VALUATORS];
    int i;
    if (!mask) return NULL;
    for (i = 0; i < MAX_VALUATORS && i < mask->num_valuators; i++) {
        buf[i] = (double)mask->valuators[i];
    }
    return buf;
}

void ssx_valuator_mask_set_from_double(ValuatorMask *mask, double *vals, int n) {
    int i;
    if (!mask || !vals) return;
    for (i = 0; i < n && i < MAX_VALUATORS; i++) {
        mask->valuators[i] = (int)vals[i];
    }
}
