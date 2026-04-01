/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef DIXEVENTS_H
#define DIXEVENTS_H

extern void SetCriticalEvent(int /* event */);

extern CursorPtr GetSpriteCursor(void);

extern int ProcAllowEvents(ClientPtr /* client */);

extern int MaybeDeliverEventsToClient(
	WindowPtr              /* pWin */,
	xEvent *               /* pEvents */,
	int                    /* count */,
	Mask                   /* filter */,
	ClientPtr              /* dontClient */);

extern int ProcWarpPointer(ClientPtr /* client */);

#if 0
extern void
#ifdef XKB
CoreProcessKeyboardEvent (
#else
ProcessKeyboardEvent (
#endif
	xEvent *               /* xE */,
	DeviceIntPtr           /* keybd */,
	int                    /* count */);

extern void
#ifdef XKB
CoreProcessPointerEvent (
#else
ProcessPointerEvent (
#endif
	xEvent *               /* xE */,
	DeviceIntPtr           /* mouse */,
	int                    /* count */);
#endif

extern int EventSelectForWindow(
	WindowPtr              /* pWin */,
	ClientPtr              /* client */,
	Mask                   /* mask */);

extern int EventSuppressForWindow(
	WindowPtr              /* pWin */,
	ClientPtr              /* client */,
	Mask                   /* mask */,
	Bool *                 /* checkOptional */);

extern int ProcSetInputFocus(ClientPtr /* client */);

extern int ProcGetInputFocus(ClientPtr /* client */);

extern int ProcGrabPointer(ClientPtr /* client */);

extern int ProcChangeActivePointerGrab(ClientPtr /* client */);

extern int ProcUngrabPointer(ClientPtr /* client */);

extern int ProcGrabKeyboard(ClientPtr /* client */);

extern int ProcUngrabKeyboard(ClientPtr /* client */);

extern int ProcQueryPointer(ClientPtr /* client */);

extern int ProcSendEvent(ClientPtr /* client */);

extern int ProcUngrabKey(ClientPtr /* client */);

extern int ProcGrabKey(ClientPtr /* client */);

extern int ProcGrabButton(ClientPtr /* client */);

extern int ProcUngrabButton(ClientPtr /* client */);

extern int ProcRecolorCursor(ClientPtr /* client */);

#endif /* DIXEVENTS_H */
