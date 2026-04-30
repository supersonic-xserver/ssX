/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef DIXGRABS_H
#define DIXGRABS_H 1

extern GrabPtr CreateGrab(
	int /* client */,
	DeviceIntPtr /* device */,
	WindowPtr /* window */,
	Mask /* eventMask */,
	Bool /* ownerEvents */,
	Bool /* keyboardMode */,
	Bool /* pointerMode */,
	DeviceIntPtr /* modDevice */,
	unsigned short /* modifiers */,
	int /* type */,
	KeyCode /* keybut */,
	WindowPtr /* confineTo */,
	CursorPtr /* cursor */);

extern int DeletePassiveGrab(
	pointer /* value */,
	XID /* id */);

extern Bool GrabMatchesSecond(
	GrabPtr /* pFirstGrab */,
	GrabPtr /* pSecondGrab */);

extern int AddPassiveGrabToList(
	GrabPtr /* pGrab */);

extern Bool DeletePassiveGrabFromList(
	GrabPtr /* pMinuendGrab */);

#endif /* DIXGRABS_H */
