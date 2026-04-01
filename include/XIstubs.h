/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef XI_STUBS_H
#define XI_STUBS_H 1

int
ChangeKeyboardDevice (
	DeviceIntPtr           /* old_dev */,
	DeviceIntPtr           /* new_dev */);

int
ChangePointerDevice (
	DeviceIntPtr           /* old_dev */,
	DeviceIntPtr           /* new_dev */,
	unsigned char          /* x */,
	unsigned char          /* y */);

void
CloseInputDevice (
	DeviceIntPtr           /* d */,
	ClientPtr              /* client */);

void
AddOtherInputDevices (void);

void
OpenInputDevice (
	DeviceIntPtr           /* dev */,
	ClientPtr              /* client */,
	int *                  /* status */);

int
SetDeviceMode (
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	int                    /* mode */);

int
SetDeviceValuators (
	ClientPtr              /* client */,
	DeviceIntPtr           /* dev */,
	int *                  /* valuators */,
	int                    /* first_valuator */,
	int                    /* num_valuators */);

int
ChangeDeviceControl (
	ClientPtr             /* client */,
	DeviceIntPtr          /* dev */,
	xDeviceCtl *          /* control */);

#endif /* XI_STUBS_H */
