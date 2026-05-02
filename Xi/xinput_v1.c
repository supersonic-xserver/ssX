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
 * @file xinput_v1.c
 * @brief XInput 1.x Protocol Implementation
 *
 * This file contains all version-specific protocol handlers and event logic
 * for the XInput 1.x (XI1) protocol. XI1 is the original X11 input
 * extension protocol.
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
#include <X11/extensions/XIproto.h>

#include "inputstr.h"
#include "extnsionst.h"
#include "extinit.h"
#include "exglobals.h"
#include "exevents.h"
#include "xinput_shared.h"

/*===========================================================================
 * [INIT] Device Initialization and Cleanup
 *===========================================================================*/

/**
 * Initialize XInput 1.x extension
 * Called during server startup to register XI1 extension
 */
void
XI1Init(void)
{
    ExtensionEntry *extEntry;
    XExtensionVersion thisversion = {
        XI_Present,
        XI_Add_XChangeDeviceControl_Major,
        XI_Add_XChangeDeviceControl_Minor
    };

    extEntry = AddExtension(INAME, IEVENTS, IERRORS, ProcIDispatch,
                         SProcIDispatch, IResetProc, StandardMinorOpcode);
    if (extEntry) {
        IReqCode = extEntry->base;
        AllExtensionVersions[IReqCode - 128] = thisversion;
        MakeDeviceTypeAtoms();
    }
}

/**
 * Cleanup XI1 extension on server reset
 */
void
XI1Reset(void)
{
    RestoreExtensionEvents();
}

/*===========================================================================
 * [PROC] Protocol Request Handlers
 *===========================================================================*/

/**
 * Process GetExtensionVersion request (XI1)
 */
int
ProcXI1GetExtensionVersion(ClientPtr client)
{
    xGetExtensionVersionReply rep;
    REQUEST(xGetExtensionVersionReq);

    REQUEST_AT_LEAST_SIZE(xGetExtensionVersionReq);

    if (stuff->length != (sizeof(xGetExtensionVersionReq) +
                        stuff->nbytes + 3) >> 2) {
        SendErrorToClient(client, IReqCode, X_GetExtensionVersion, 0,
                        BadLength);
        return Success;
    }

    rep.repType = X_Reply;
    rep.RepType = X_GetExtensionVersion;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;
    rep.major_version = 0;
    rep.minor_version = 0;

    rep.present = TRUE;
    if (rep.present) {
        rep.major_version =
            AllExtensionVersions[IReqCode - 128].major_version;
        rep.minor_version =
            AllExtensionVersions[IReqCode - 128].minor_version;
    }
    WriteReplyToClient(client, sizeof(xGetExtensionVersionReply), &rep);

    return Success;
}

/**
 * Process ListInputDevices request (XI1)
 */
int
ProcXI1ListInputDevices(ClientPtr client)
{
    xListInputDevicesReply rep;
    int numdevs;
    int namesize = 1;
    int size = 0;
    int total_length;
    char *devbuf;
    char *classbuf;
    char *namebuf;
    char *savbuf;
    xDeviceInfo *dev;
    DeviceIntPtr d;

    REQUEST_SIZE_MATCH(xListInputDevicesReq);

    rep.repType = X_Reply;
    rep.RepType = X_ListInputDevices;
    rep.length = 0;
    rep.sequenceNumber = client->sequence;

    AddOtherInputDevices();
    numdevs = inputInfo.numDevices;

    for (d = inputInfo.devices; d; d = d->next)
        SizeDeviceInfo(d, &namesize, &size);
    for (d = inputInfo.off_devices; d; d = d->next)
        SizeDeviceInfo(d, &namesize, &size);

    total_length = numdevs * sizeof(xDeviceInfo) + size + namesize;
    devbuf = (char *)xalloc(total_length);
    classbuf = devbuf + (numdevs * sizeof(xDeviceInfo));
    namebuf = classbuf + size;
    savbuf = devbuf;

    dev = (xDeviceInfoPtr) devbuf;
    for (d = inputInfo.devices; d; d = d->next, dev++)
        ListDeviceInfo(client, d, dev, &devbuf, &classbuf, &namebuf);
    for (d = inputInfo.off_devices; d; d = d->next, dev++)
        ListDeviceInfo(client, d, dev, &devbuf, &classbuf, &namebuf);

    rep.ndevices = numdevs;
    rep.length = (total_length + 3) >> 2;
    WriteReplyToClient(client, sizeof(xListInputDevicesReply), &rep);
    WriteToClient(client, total_length, savbuf);
    xfree(savbuf);
    return Success;
}

/**
 * Process OpenDevice request (XI1)
 */
int
ProcXI1OpenDevice(ClientPtr client)
{
    xOpenDeviceReq *req;
    xOpenDeviceReply rep;
    DeviceIntPtr dev;

    REQUEST(xOpenDeviceReq);
    REQUEST_SIZE_MATCH(xOpenDeviceReq);

    dev = LookupDeviceIntRec(req->device_id);
    if (!dev) {
        client->errorValue = req->device_id;
        SendErrorToClient(client, IReqCode, X_OpenDevice, req->device_id,
                      BadDevice);
        return Success;
    }

    if (dev->opened) {
        SendErrorToClient(client, IReqCode, X_OpenDevice, dev->id,
                      DeviceBusy);
        return Success;
    }

    dev->opened = TRUE;

    rep.repType = X_Reply;
    rep.RepType = X_OpenDevice;
    rep.device_id = dev->id;
    rep.num_classes = (dev->key ? 1 : 0) + (dev->button ? 1 : 0) +
                   (dev->valuator ? 1 : 0);
    rep.sequenceNumber = client->sequence;
    rep.length = rep.num_classes;

    WriteReplyToClient(client, sizeof(xOpenDeviceReply), &rep);
    WriteExtNewDeviceToClient(client, dev);

    return Success;
}

/**
 * Process CloseDevice request (XI1)
 */
int
ProcXI1CloseDevice(ClientPtr client)
{
    DeviceIntPtr dev;

    REQUEST(xCloseDeviceReq);
    REQUEST_SIZE_MATCH(xCloseDeviceReq);

    dev = LookupDeviceIntRec(stuff->device_id);
    if (!dev) {
        client->errorValue = stuff->device_id;
        SendErrorToClient(client, IReqCode, X_CloseDevice, stuff->device_id,
                      BadDevice);
        return Success;
    }

    if (!dev->opened) {
        return Success;
    }

    dev->opened = FALSE;

    return Success;
}

/**
 * Process SetDeviceMode request (XI1)
 */
int
ProcXI1SetDeviceMode(ClientPtr client)
{
    DeviceIntPtr dev;
    xSetDeviceModeReply rep;

    REQUEST(xSetDeviceModeReq);
    REQUEST_SIZE_MATCH(xSetDeviceModeReq);

    dev = LookupDeviceIntRec(stuff->device_id);
    if (!dev) {
        client->errorValue = stuff->device_id;
        SendErrorToClient(client, IReqCode, X_SetDeviceMode, stuff->device_id,
                      BadDevice);
        return Success;
    }

    if ((stuff->mode != GrabModeSync) && (stuff->mode != GrabModeAsync)) {
        client->errorValue = stuff->mode;
        SendErrorToClient(client, IReqCode, X_SetDeviceMode, stuff->device_id,
                      BadMode);
        return Success;
    }

    if (dev->valuator)
        dev->valuator->mode = stuff->mode;

    rep.repType = X_Reply;
    rep.RepType = X_SetDeviceMode;
    rep.sequenceNumber = client->sequence;
    rep.mode = stuff->mode;
    rep.length = 0;

    WriteReplyToClient(client, sizeof(xSetDeviceModeReply), &rep);

    return Success;
}

/**
 * Process SelectExtensionEvent request (XI1)
 */
int
ProcXI1SelectExtensionEvent(ClientPtr client)
{
    DeviceIntPtr dev;
    WindowPtr pWin;
    int resource;

    REQUEST(xSelectExtensionEventReq);
    REQUEST_SIZE_MATCH(xSelectExtensionEventReq);

    pWin = LookupWindow(stuff->window, client);
    if (!pWin) {
        client->errorValue = stuff->window;
        SendErrorToClient(client, IReqCode, X_SelectExtensionEvent, 0,
                        BadWindow);
        return Success;
    }

    dev = LookupDeviceIntRec(stuff->device_id);
    if (!dev) {
        client->errorValue = stuff->device_id;
        SendErrorToClient(client, IReqCode, X_SelectExtensionEvent,
                        stuff->device_id, BadDevice);
        return Success;
    }

    if (stuff->num_classes > 0) {
        resource = SelectExtensionEventForClient(pWin, dev, client,
                                               stuff->mask, stuff->num_classes);
        if (resource != Success)
            return resource;
    }

    return Success;
}

/**
 * Process GetSelectedExtensionEvents request (XI1)
 */
int
ProcXI1GetSelectedExtensionEvents(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangeDeviceDontPropagateList request (XI1)
 */
int
ProcXI1ChangeDeviceDontPropagateList(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceDontPropagateList request (XI1)
 */
int
ProcXI1GetDeviceDontPropagateList(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceMotionEvents request (XI1)
 */
int
ProcXI1GetDeviceMotionEvents(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangeKeyboardDevice request (XI1)
 */
int
ProcXI1ChangeKeyboardDevice(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangePointerDevice request (XI1)
 */
int
ProcXI1ChangePointerDevice(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GrabDevice request (XI1)
 */
int
ProcXI1GrabDevice(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process UngrabDevice request (XI1)
 */
int
ProcXI1UngrabDevice(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GrabDeviceKey request (XI1)
 */
int
ProcXI1GrabDeviceKey(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process UngrabDeviceKey request (XI1)
 */
int
ProcXI1UngrabDeviceKey(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GrabDeviceButton request (XI1)
 */
int
ProcXI1GrabDeviceButton(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process UngrabDeviceButton request (XI1)
 */
int
ProcXI1UngrabDeviceButton(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process AllowDeviceEvents request (XI1)
 */
int
ProcXI1AllowDeviceEvents(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceFocus request (XI1)
 */
int
ProcXI1GetDeviceFocus(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process SetDeviceFocus request (XI1)
 */
int
ProcXI1SetDeviceFocus(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetFeedbackControl request (XI1)
 */
int
ProcXI1GetFeedbackControl(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangeFeedbackControl request (XI1)
 */
int
ProcXI1ChangeFeedbackControl(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceKeyMapping request (XI1)
 */
int
ProcXI1GetDeviceKeyMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangeDeviceKeyMapping request (XI1)
 */
int
ProcXI1ChangeDeviceKeyMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceModifierMapping request (XI1)
 */
int
ProcXI1GetDeviceModifierMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process SetDeviceModifierMapping request (XI1)
 */
int
ProcXI1SetDeviceModifierMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceButtonMapping request (XI1)
 */
int
ProcXI1GetDeviceButtonMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process SetDeviceButtonMapping request (XI1)
 */
int
ProcXI1SetDeviceButtonMapping(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process QueryDeviceState request (XI1)
 */
int
ProcXI1QueryDeviceState(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process SendExtensionEvent request (XI1)
 */
int
ProcXI1SendExtensionEvent(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process DeviceBell request (XI1)
 */
int
ProcXI1DeviceBell(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process SetDeviceValuators request (XI1)
 */
int
ProcXI1SetDeviceValuators(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process GetDeviceControl request (XI1)
 */
int
ProcXI1GetDeviceControl(ClientPtr client)
{
    return BadImplementation;
}

/**
 * Process ChangeDeviceControl request (XI1)
 */
int
ProcXI1ChangeDeviceControl(ClientPtr client)
{
    return BadImplementation;
}

/*===========================================================================
 * [UTIL] Internal Helper Functions
 *===========================================================================*/

/**
 * Swap handler for GetExtensionVersion
 */
int
SProcXI1GetExtensionVersion(ClientPtr client)
{
    REQUEST(xGetExtensionVersionReq);
    swaps(&stuff->length);
    REQUEST_AT_LEAST_SIZE(xGetExtensionVersionReq);
    swaps(&stuff->nbytes);
    return ProcXI1GetExtensionVersion(client);
}

/**
 * Swap handler for ListInputDevices
 */
int
SProcXI1ListInputDevices(ClientPtr client)
{
    REQUEST(xListInputDevicesReq);
    swaps(&stuff->length);
    return ProcXI1ListInputDevices(client);
}

/**
 * Swap reply handler for GetExtensionVersion
 */
void
SRepXI1GetExtensionVersion(ClientPtr client, int size,
                        xGetExtensionVersionReply *rep)
{
    swaps(&rep->sequenceNumber);
    swapl(&rep->length);
    swaps(&rep->major_version);
    swaps(&rep->minor_version);
    WriteToClient(client, size, (char *)rep);
}

/**
 * Swap reply handler for ListInputDevices
 */
void
SRepXI1ListInputDevices(ClientPtr client, int size,
                     xListInputDevicesReply *rep)
{
    swaps(&rep->sequenceNumber);
    swapl(&rep->length);
    WriteToClient(client, size, (char *)rep);
}

/**
 * Swap reply handler for OpenDevice
 */
void
SRepXI1OpenDevice(ClientPtr client, int size, xOpenDeviceReply *rep)
{
    swaps(&rep->sequenceNumber);
    swapl(&rep->length);
    swaps(&rep->num_classes);
    WriteToClient(client, size, (char *)rep);
}

/**
 * Swap reply handler for SetDeviceMode
 */
void
SRepXI1SetDeviceMode(ClientPtr client, int size,
                   xSetDeviceModeReply *rep)
{
    swaps(&rep->sequenceNumber);
    swapl(&rep->length);
    WriteToClient(client, size, (char *)rep);
}

/**
 * Validate device for XI1 operations
 */
Bool
XI1ValidDevice(DeviceIntPtr dev)
{
    if (!dev)
        return FALSE;
    if (dev == inputInfo.keyboard || dev == inputInfo.pointer)
        return TRUE;
    return dev->opened;
}

/**
 * Check if device can receive events (XI1)
 */
Bool
XI1CanReceiveEvents(DeviceIntPtr dev)
{
    return (dev && dev->enabled);
}