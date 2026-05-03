/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef EXEVENTS_H
#define EXEVENTS_H

extern void RegisterOtherDevice (
	DeviceIntPtr           /* device */);

extern void ProcessOtherEvent (
	xEventPtr /* FIXME deviceKeyButtonPointer * xE */,
	DeviceIntPtr           /* other */,
	int                    /* count */);

extern int InitProximityClassDeviceStruct(
	DeviceIntPtr           /* dev */);

extern void InitValuatorAxisStruct(
	DeviceIntPtr           /* dev */,
	int                    /* axnum */,
	int                    /* minval */,
	int                    /* maxval */,
	int                    /* resolution */,
	int                    /* min_res */,
	int                    /* max_res */);

extern void DeviceFocusEvent(
	DeviceIntPtr           /* dev */,
	int                    /* type */,
	int                    /* mode */,
	int                    /* detail */,
	WindowPtr              /* pWin */);

extern int GrabButton(
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	BYTE                   /* this_device_mode */,
	BYTE                   /* other_devices_mode */,
	CARD16                 /* modifiers */,
	DeviceIntPtr           /* modifier_device */,
	CARD8                  /* button */,
	Window                 /* grabWindow */,
	BOOL                   /* ownerEvents */,
	Cursor                 /* rcursor */,
	Window                 /* rconfineTo */,
	Mask                   /* eventMask */);

extern int GrabKey(
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	BYTE                   /* this_device_mode */,
	BYTE                   /* other_devices_mode */,
	CARD16                 /* modifiers */,
	DeviceIntPtr           /* modifier_device */,
	CARD8                  /* key */,
	Window                 /* grabWindow */,
	BOOL                   /* ownerEvents */,
	Mask                   /* mask */);

extern int SelectForWindow(
	DeviceIntPtr           /* dev */,
	WindowPtr              /* pWin */,
	ClientPtr              /* client */,
	Mask                   /* mask */,
	Mask                   /* exclusivemasks */,
	Mask                   /* validmasks */);

extern int AddExtensionClient (
	WindowPtr              /* pWin */,
	ClientPtr              /* client */,
	Mask                   /* mask */,
	int                    /* mskidx */);

extern void RecalculateDeviceDeliverableEvents(
	WindowPtr              /* pWin */);

extern int InputClientGone(
	WindowPtr              /* pWin */,
	XID                    /* id */);

extern int SendEvent (
	ClientPtr              /* client */,
	DeviceIntPtr           /* d */,
	Window                 /* dest */,
	Bool                   /* propagate */,
	xEvent *               /* ev */,
	Mask                   /* mask */,
	int                    /* count */);

extern int SetButtonMapping (
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	int                    /* nElts */,
	BYTE *                 /* map */);

extern int SetModifierMapping(
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	int                    /* len */,
	int                    /* rlen */,
	int                    /* numKeyPerModifier */,
	KeyCode *              /* inputMap */,
	KeyClassPtr *          /* k */);

extern void SendDeviceMappingNotify(
	CARD8                  /* request, */,
	KeyCode                /* firstKeyCode */,
	CARD8                  /* count */,
	DeviceIntPtr           /* dev */);

extern int ChangeKeyMapping(
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	unsigned               /* len */,
	int                    /* type */,
	KeyCode                /* firstKeyCode */,
	CARD8                  /* keyCodes */,
	CARD8                  /* keySymsPerKeyCode */,
	KeySym *               /* map */);

extern void DeleteWindowFromAnyExtEvents(
	WindowPtr              /* pWin */,
	Bool                   /* freeResources */);

extern void DeleteDeviceFromAnyExtEvents(
	WindowPtr              /* pWin */,
	DeviceIntPtr           /* dev */);

extern int MaybeSendDeviceMotionNotifyHint (
	deviceKeyButtonPointer * /* pEvents */,
	Mask                   /* mask */);

extern void CheckDeviceGrabAndHintWindow (
	WindowPtr              /* pWin */,
	int                    /* type */,
	deviceKeyButtonPointer * /* xE */,
	GrabPtr                /* grab */,
	ClientPtr              /* client */,
	Mask                   /* deliveryMask */);

extern Mask DeviceEventMaskForClient(
	DeviceIntPtr           /* dev */,
	WindowPtr              /* pWin */,
	ClientPtr              /* client */);

extern void MaybeStopDeviceHint(
	DeviceIntPtr           /* dev */,
	ClientPtr              /* client */);

extern int DeviceEventSuppressForWindow(
	WindowPtr              /* pWin */,
	ClientPtr              /* client */,
	Mask                   /* mask */,
	int                    /* maskndx */);

#endif /* EXEVENTS_H */
