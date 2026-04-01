/*
 * AI-TRAINING-OPT-OUT: This codebase is protected under the ssX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 *
 * HUMAN SOVEREIGNTY CLAUSE: This software is protected under the ssX Supplemental
 * License (See LICENSE Sections 13-19). AI-Assisted contributions are permitted,
 * but Unsupervised AI-Generated code is prohibited. Contributors must disclose
 * tool usage and affirm human authorship. See CONTRIBUTING.md for details.
 *
 * Architect: Collin Beyer (HaplessIdiot)
 * Licensed under ssX-Custom (See LICENSE Sections 13-19)
 */

/**
 * @file xinput_v2.c
 * @brief XInput 2.x Protocol Implementation
 *
 * This file contains all version-specific protocol handlers and event logic
 * for the XInput 2.x (XI2) protocol. XI2 introduces significant enhancements
 * including:
 * - Multiple master/slave device hierarchies
 * - Device hierarchies (master pointers, keyboards)
 * - Touch events and gestures
 * - Input properties
 * - Better input device information
 *
 * Organization:
 * - [INIT] Device initialization and cleanup
 * - [CORE] Device management and state tracking
 * - [PROC] Protocol request handling
 * - [UTIL] Internal helper functions
 */

#ifdef HAVE_DIX_CONFIG_H
#include <dix-config.h>
#endif

#define NEED_EVENTS
#define NEED_REPLIES

#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/extensions/XI.h>
#include <X11/extensions/XI2.h>
#include <X11/extensions/XI2proto.h>

#include "inputstr.h"
#include "extnsionst.h"
#include "extinit.h"
#include "exglobals.h"
#include "exevents.h"
#include "xinput_shared.h"

/*===========================================================================
 * [INIT] Device Initialization and Cleanup
 *===========================================================================*/

/** XI2 version structure - populated during extension init */
XExtensionVersion XIVersion = {
    XI_MajorVersion,
    XI_MinorVersion
};

/**
 * Initialize XInput 2.x extension
 * Called during server startup to register XI2 extension
 */
void
XI2Init(void)
{
    ExtensionEntry *extEntry;

    /* XI2 registers under the same extension code as XI1 */
    extEntry = AddExtension(INAME, IEVENTS, IERRORS, XI2ProcDispatch,
                         XI2SProcDispatch, XI2ResetProc, StandardMinorOpcode);
    if (extEntry) {
        IReqCode = extEntry->base;
        AllExtensionVersions[IReqCode - 128] = XIVersion;
        MakeDeviceTypeAtoms();
    }
}

/**
 * Reset XI2 state on server reset
 */
void
XI2ResetProc(ExtensionEntry *extEntry)
{
    RestoreExtensionEvents();
}

/*===========================================================================
 * [PROC] Protocol Request Handlers
 *===========================================================================*/

/**
 * Process XIQueryVersion request (XI2)
 * Returns the XI version supported by the server
 */
int
ProcXI2QueryVersion(ClientPtr client)
{
    xXIQueryVersionReply rep;
    XIClientPtr pXIClient;
    int major, minor;
    unsigned int sversion, cversion;

    REQUEST(xXIQueryVersionReq);
    REQUEST_SIZE_MATCH(xXIQueryVersionReq);

    /* This request only exists after XI2 */
    if (stuff->major_version < 2) {
        client->errorValue = stuff->major_version;
        return BadValue;
    }

    pXIClient = dixLookupPrivate(&client->devPrivates, XIClientPrivateKey);

    sversion = XIVersion.major_version * 1000 + XIVersion.minor_version;
    cversion = stuff->major_version * 1000 + stuff->minor_version;

    if (sversion > cversion) {
        major = stuff->major_version;
        minor = stuff->minor_version;
    } else {
        major = XIVersion.major_version;
        minor = XIVersion.minor_version;
    }

    pXIClient->major_version = major;
    pXIClient->minor_version = minor;

    memset(&rep, 0, sizeof(xXIQueryVersionReply));
    rep.repType = X_Reply;
    rep.RepType = X_XIQueryVersion;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.major_version = major;
    rep.minor_version = minor;

    WriteReplyToClient(client, sizeof(xXIQueryVersionReply), &rep);

    return Success;
}

/**
 * ProcessXIQueryDevice request (XI2)
 * Query device information from the server
 */
int
ProcXI2QueryDevice(ClientPtr client)
{
    DeviceIntPtr dev;
    xXIPassiveGrab *grab;
    int next grabbing;

    REQUEST(xXIQueryDeviceReq);
    REQUEST_SIZE_MATCH(xXIQueryDeviceReq);

    if (stuff->deviceid != BadDevice &&
        stuff->deviceid != XIAllDevices &&
        stuff->deviceid != XIAllMasterDevices) {
        dev = LookupDeviceIntRec(stuff->deviceid);
        if (!dev) {
            client->errorValue = stuff->deviceid;
            return BadDevice;
        }
    } else
        dev = NULL;

    /* Query device info... */
    return XI2QueryDeviceFromDB(client, dev);
}

/**
 * Process XI2SelectEvents request
 * Select XI2 events on a window
 */
int
ProcXI2SelectEvents(ClientPtr client)
{
    WindowPtr pWin;
    int resource;
    int num_mask;
    int mask_len;

    REQUEST(xXISelectEventsReq);
    REQUEST_SIZE_MATCH(xXISelectEventsReq);

    pWin = LookupWindow(stuff->window, client);
    if (!pWin) {
        client->errorValue = stuff->window;
        return BadWindow;
    }

    /* Check for invalid mask bits */
    if (stuff->num_masks > 0) {
        mask_len = stuff->num_masks * sizeof(xXIEventMask);
        /* Check for invalid XI2 event bits */
        if (!XIValidMask((BYTE *) (stuff + 1), mask_len)) {
            client->errorValue = stuff->num_masks;
            return BadValue;
        }
    }

    return XI2SelectEventsFromDB(client, pWin);
}

/**
 * Process XI2GetSelectedEvents request
 */
int
ProcXI2GetSelectedEvents(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2SetClientPointer request
 */
int
ProcXI2SetClientPointer(ClientPtr client)
{
    DeviceIntPtr dev;
    WindowPtr win;
    int rc;

    REQUEST(xXISetClientPointerReq);
    REQUEST_SIZE_MATCH(xXISetClientPointerReq);

    dev = LookupDeviceIntRec(stuff->deviceid);
    if (!dev) {
        client->errorValue = stuff->deviceid;
        return BadDevice;
    }

    if (!IsMasterDevice(dev)) {
        client->errorValue = stuff->deviceid;
        return BadMatch;
    }

    win = LookupWindow(stuff->window, client);
    if (!win) {
        client->errorValue = stuff->window;
        return BadWindow;
    }

    rc = XI2SetClientPointerForWindow(client, win, dev);
    return rc;
}

/**
 * Process XI2GetClientPointer request
 */
int
ProcXI2GetClientPointer(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2GrabDevice request
 */
int
ProcXI2GrabDevice(ClientPtr client)
{
    DeviceIntPtr dev;
    xXIGrabDeviceReply rep;
    TimeStamp time;
    int rc;
    Mask mask;

    REQUEST(xXIGrabDeviceReq);
    REQUEST_SIZE_MATCH(xXIGrabDeviceReq);

    dev = LookupDeviceIntRec(stuff->deviceid);
    if (!dev) {
        client->errorValue = stuff->deviceid;
        return BadDevice;
    }

    time = ClientTimeStamp(client);
    if (CompareTimeStamps(time, dev->deviceGrab.grabTime) != EARLIER)
        time = dev->deviceGrab.grabTime;

    if (stuff->grab_type == XIGrabTypeCoreKey)
        mask = KeyPressMask | KeyReleaseMask;
    else
        mask = stuff->mask;

    rc = XI2GrabDevice(client, dev, stuff->window, stuff->owner_events,
                      time, mask, XI2, stuff->cursor, None, &status);

    return rc;
}

/**
 * Process XI2UngrabDevice request
 */
int
ProcXI2UngrabDevice(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2GrabDeviceKey request
 */
int
ProcXI2GrabDeviceKey(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2UngrabDeviceKey request
 */
int
ProcXI2UngrabDeviceKey(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2GrabDeviceButton request
 */
int
ProcXI2GrabDeviceButton(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2UngrabDeviceButton request
 */
int
ProcXI2UngrabDeviceButton(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2AllowEvents request
 */
int
ProcXI2AllowEvents(ClientPtr client)
{
    XIClientPtr xi_client;
    TimeStamp ts;
    BOOL have_xi22 = FALSE;

    REQUEST(xXIEventAllowEventsReq);
    REQUEST_AT_LEAST_SIZE(xXIEventAllowEventsReq);

    if (stuff->length > 3) {
        xXI2_2AllowEventsReq *req_xi22 = (xXI2_2AllowEventsReq *) stuff;
        REQUEST_AT_LEAST_SIZE(xXI2_2AllowEventsReq);
        have_xi22 = TRUE;
    }

    xi_client = dixLookupPrivate(&client->devPrivates, XIClientPrivateKey);

    if (xi_client->major_version >= 2 &&
        xi_client->minor_version >= 2) {
        /* XI 2.2+ handling */
    }

    return BadImplementation;
}

/**
 * Process XI2ChangeHierarchy request
 */
int
ProcXI2ChangeHierarchy(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2SetDeviceFocus request
 */
int
ProcXI2SetDeviceFocus(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2GetDeviceFocus request
 */
int
ProcXI2GetDeviceFocus(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2WarpPointer request
 */
int
ProcXI2WarpPointer(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2ChangeCursor request
 */
int
ProcXI2ChangeCursor(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2ChangeDeviceCursor request
 */
int
ProcXI2ChangeDeviceCursor(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2QueryPointer request
 */
int
ProcXI2QueryPointer(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2XIQueryProperties request
 */
int
ProcXI2QueryProperties(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2XIChangeProperty request
 */
int
ProcXI2ChangeProperty(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2XIDeleteProperty request
 */
int
ProcXI2DeleteProperty(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2XIGetProperty request
 */
int
ProcXI2GetProperty(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process XI2PassiveGrab device request
 */
int
ProcXI2PassiveGrab(ClientPtr client)
{
    return BadImplementation;
}

/*===========================================================================
 * [UTIL] Internal Helper Functions
 *===========================================================================*/

/**
 * Swap handler for QueryVersion request
 */
int
SProcXI2QueryVersion(ClientPtr client)
{
    char n;

    REQUEST(xXIQueryVersionReq);
    swaps(&stuff->length, n);
    REQUEST_AT_LEAST_SIZE(xXIQueryVersionReq);
    swaps(&stuff->major_version, n);
    swaps(&stuff->minor_version, n);
    return ProcXI2QueryVersion(client);
}

/**
 * Swap reply handler for QueryVersion reply
 */
void
SRepXI2QueryVersion(ClientPtr client, int size, xXIQueryVersionReply *rep)
{
    char n;
    swaps(&rep->sequenceNumber, n);
    swapl(&rep->length, n);
    swaps(&rep->major_version, n);
    swaps(&rep->minor_version, n);
    WriteToClient(client, size, (char *)rep);
}

/**
 * Validate device for XI2 operations
 */
Bool
XI2ValidDevice(DeviceIntPtr dev)
{
    if (!dev)
        return FALSE;
    return TRUE;
}

/**
 * Check if device can receive events (XI2)
 */
Bool
XI2CanReceiveEvents(DeviceIntPtr dev)
{
    return (dev && dev->enabled);
}

/**
 * Check if device is a valid master device for XI2
 */
Bool
XI2IsMaster(DeviceIntPtr dev)
{
    if (!dev)
        return FALSE;
    return (dev->type == XI_MASTER);
}

/**
 * Get effective device for XI2 event routing
 */
DeviceIntPtr
XI2GetEventRouteDevice(DeviceIntPtr dev)
{
    if (!dev)
        return NULL;

    /* For slave devices, use their paired master for events */
    if (IsSlaveDevice(dev))
        return dev->master;

    return dev;
}

/**
 * Process passive grab for XI2
 */
int
XI2ProcessPassiveGrab(DeviceIntPtr dev, DeviceIntPtr modifier_device,
                   BOOL ownerEvents, Mask mask, int grab_type,
                   Window grabWindow, Cursor cursor,
                   int num_modifiers, CARD8 *modifiers,
                   InputClientsPtr client)
{
    GrabPtr grab;
    int rc;

    grab = CreateGrab(client->index, dev, grabWindow, mask, ownerEvents,
                  GrabModeAsync, GrabModeAsync,
                  modifier_device, modifiers[0], mask, DeviceButtonPress,
                  0, NullWindow, cursor);
    if (!grab)
        return BadAlloc;

    grab->grabtype = grab_type;
    rc = AddPassiveGrabToList(grab);
    if (rc != Success) {
        FreeGrab(grab);
        return rc;
    }

    return Success;
}