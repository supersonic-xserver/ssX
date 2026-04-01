/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef EXTINIT_H
#define EXTINIT_H

#include "extnsionst.h"
/* XI types needed for extension event swap functions */
#ifdef HAVE_XI_H
#include <XI/XI.h>
#endif
#include <X11/extensions/XIproto.h>

void
XInputExtensionInit(INITARGS);

int
ProcIDispatch (
	ClientPtr              /* client */
	);

int
SProcIDispatch(
	ClientPtr              /* client */
	);

void
SReplyIDispatch (
	ClientPtr              /* client */,
	int                    /* len */,
	xGrabDeviceReply *     /* rep */
	);

void
SEventIDispatch (
	xEvent *               /* from */,
	xEvent *               /* to */
	);

void
SEventDeviceValuator (
	deviceValuator *       /* from */,
	deviceValuator *       /* to */
	);

void
SEventFocus (
	deviceFocus *          /* from */,
	deviceFocus *          /* to */
	);

void
SDeviceStateNotifyEvent (
	deviceStateNotify *    /* from */,
	deviceStateNotify *    /* to */
	);

void
SDeviceKeyStateNotifyEvent (
	deviceKeyStateNotify * /* from */,
	deviceKeyStateNotify * /* to */
	);

void
SDeviceButtonStateNotifyEvent (
	deviceButtonStateNotify * /* from */,
	deviceButtonStateNotify * /* to */
	);

void
SChangeDeviceNotifyEvent (
	changeDeviceNotify *   /* from */,
	changeDeviceNotify *   /* to */
	);

void
SDeviceMappingNotifyEvent (
	deviceMappingNotify *  /* from */,
	deviceMappingNotify *  /* to */
	);

void
FixExtensionEvents (
	ExtensionEntry 	*      /* extEntry */
	);

void
RestoreExtensionEvents (
	void
	);

void
IResetProc(
	ExtensionEntry *       /* unused */
	);

void
AssignTypeAndName (
	DeviceIntPtr           /* dev */,
	Atom                   /* type */,
	char *                 /* name */
	);

void
MakeDeviceTypeAtoms (
	void
);

DeviceIntPtr
LookupDeviceIntRec (
	CARD8                  /* id */
	);

void
SetExclusiveAccess (
	Mask                   /* mask */
	);

void
AllowPropagateSuppress (
	Mask                   /* mask */
	);

Mask
GetNextExtEventMask (
	void
);

void
SetMaskForExtEvent(
	Mask                   /* mask */,
	int                    /* event */
	);

void
SetEventInfo(
	Mask                   /* mask */,
	int                    /* constant */
	);

#endif /* EXTINIT_H */
