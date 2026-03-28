/* $XFree86: xc/programs/Xserver/XTrap/xtrapditbl.c,v 1.3 2005/10/14 15:16:10 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/****************************************************************************
Copyright 1987, 1988, 1989, 1990, 1991 by Digital Equipment Corp., Maynard, MA

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO EVENT SHALL
DIGITAL BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR
ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS,
WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION,
ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS
SOFTWARE.

*****************************************************************************/
/*
 * Copyright (c) 2005 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 *  ABSTRACT:
 *
 *      This module is contains Vector tables used for swapping and general   
 *      dispatch by the XTrap server extension.
 *
 *  CONTRIBUTORS:
 *
 *      Ken Miller
 *      Marc Evans
 *
 */

/*-----------------*
 *  Include Files  *
 *-----------------*/
#include <X11/X.h>
#define NEED_REPLIES
#define NEED_EVENTS
#include <X11/Xproto.h>
#include <X11/Xprotostr.h>
#include <X11/extensions/xtrapdi.h>
#include "input.h"          /* Server DevicePtr definitions */
#include "misc.h"
#include "dixstruct.h"
#ifdef PC
# include "extnsist.h"
#else
# include "extnsionst.h"        /* Server ExtensionEntry definitions */
#endif
#include "xtrapddmi.h"
#include "xtrapproto.h"

globaldef XETSwReqFunc XETSwProcVector[256L] =
{
    XETSwProcBadRequest,
    XETSwCreateWindow,
    XETSwChangeWindowAttributes,
    XETSwResourceReq,			/* GetWindowAttributes */
    XETSwResourceReq,			/* DestroyWindow */
    XETSwResourceReq,			/* 5 DestroySubwindows */
    XETSwResourceReq,			/* XETSwChangeSaveSet, */
    XETSwReparentWindow,
    XETSwResourceReq,			/* MapWindow */
    XETSwResourceReq,			/* MapSubwindows */
    XETSwResourceReq,			/* 10 UnmapWindow */
    XETSwResourceReq,			/* UnmapSubwindows */
    XETSwConfigureWindow,
    XETSwResourceReq,			/* XETSwCirculateWindow, */
    XETSwResourceReq,			/* GetGeometry */
    XETSwResourceReq,			/* 15 QueryTree */
    XETSwInternAtom,
    XETSwResourceReq,			/* XETSwGetAtomName, */
    XETSwChangeProperty,
    XETSwDeleteProperty,
    XETSwGetProperty,			/* 20 */
    XETSwResourceReq,			/* XETSwListProperties, */
    XETSwSetSelectionOwner,
    XETSwResourceReq, 			/* XETSwGetSelectionOwner, */
    XETSwConvertSelection,
    XETSwSendEvent,			/* 25 */
    XETSwGrabPointer,
    XETSwResourceReq, 			/* XETSwUngrabPointer, */
    XETSwGrabButton,
    XETSwUngrabButton,
    XETSwChangeActivePointerGrab,	/* 30 */
    XETSwGrabKeyboard,
    XETSwResourceReq,			/* XETSwUngrabKeyboard, */
    XETSwGrabKey,
    XETSwUngrabKey,
    XETSwResourceReq,			/* 35 XETSwAllowEvents, */
    XETSwSimpleReq,			/* XETSwGrabServer, */
    XETSwSimpleReq,			/* XETSwUngrabServer, */
    XETSwResourceReq,			/* XETSwQueryPointer, */
    XETSwGetMotionEvents,
    XETSwTranslateCoords,		/*40 */
    XETSwWarpPointer,
    XETSwSetInputFocus,
    XETSwSimpleReq,			/* XETSwGetInputFocus, */
    XETSwSimpleReq,			/* QueryKeymap, */
    XETSwOpenFont,			/* 45 */
    XETSwResourceReq,			/* XETSwCloseFont, */
    XETSwResourceReq, 			/* XETSwQueryFont, */
    XETSwResourceReq,			/* XETSwQueryTextExtents,  */
    XETSwListFonts,
    XETSwListFontsWithInfo,		/* 50 */
    XETSwSetFontPath,
    XETSwSimpleReq,			/* GetFontPath, */
    XETSwCreatePixmap,
    XETSwResourceReq,			/* XETSwFreePixmap, */
    XETSwCreateGC,			/* 55 */
    XETSwChangeGC,
    XETSwCopyGC,
    XETSwSetDashes,
    XETSwSetClipRectangles,
    XETSwResourceReq,			/* 60 XETSwFreeGC, */
    XETSwClearToBackground,
    XETSwCopyArea,
    XETSwCopyPlane,
    XETSwPoly,				/* PolyPoint, */
    XETSwPoly,				/* 65 PolyLine */
    XETSwPoly,				/* PolySegment, */
    XETSwPoly,				/* PolyRectangle, */
    XETSwPoly,				/* PolyArc, */
    XETSwFillPoly,
    XETSwPoly,				/* 70 PolyFillRectangle */
    XETSwPoly,				/* PolyFillArc, */
    XETSwPutImage,
    XETSwGetImage,
    XETSwPolyText,
    XETSwPolyText,			/* 75 */
    XETSwImageText,
    XETSwImageText,
    XETSwCreateColormap,
    XETSwResourceReq,			/* XETSwFreeColormap, */
    XETSwCopyColormapAndFree,		/* 80 */
    XETSwResourceReq,			/* XETSwInstallColormap, */
    XETSwResourceReq,			/* XETSwUninstallColormap, */
    XETSwResourceReq, 			/* XETSwListInstalledColormaps, */
    XETSwAllocColor,
    XETSwAllocNamedColor,		/* 85 */
    XETSwAllocColorCells,
    XETSwAllocColorPlanes,
    XETSwFreeColors,
    XETSwStoreColors,
    XETSwStoreNamedColor,		/* 90 */
    XETSwQueryColors,
    XETSwLookupColor,
    XETSwCreateCursor,
    XETSwCreateGlyphCursor,
    XETSwResourceReq,			/* 95 XETSwFreeCursor, */
    XETSwRecolorCursor,
    XETSwQueryBestSize,
    XETSwQueryExtension,
    XETSwSimpleReq,			/* ListExtensions, */
    XETSwChangeKeyboardMapping,		/* 100 */
    XETSwSimpleReq,			/* GetKeyboardMapping, */
    XETSwChangeKeyboardControl,
    XETSwSimpleReq,			/* GetKeyboardControl, */
    XETSwSimpleReq,			/* Bell, */
    XETSwChangePointerControl,		/* 105 */
    XETSwSimpleReq,			/* GetPointerControl, */
    XETSwSetScreenSaver,
    XETSwSimpleReq,			/* GetScreenSaver, */
    XETSwChangeHosts,
    XETSwSimpleReq,			/* 110 ListHosts, */
    XETSwSimpleReq,			/* XETSwChangeAccessControl, */
    XETSwSimpleReq,			/* XETSwChangeCloseDownMode, */
    XETSwResourceReq,			/* XETSwKillClient, */
    XETSwRotateProperties,
    XETSwSimpleReq,			/* 115 ForceScreenSaver */
    XETSwSimpleReq,			/* SetPointerMapping, */
    XETSwSimpleReq,			/* GetPointerMapping, */
    XETSwSimpleReq,			/* SetModifierMapping, */
    XETSwSimpleReq,			/* GetModifierMapping, */
    XETSwNotImplemented,		/* 120 */
    XETSwNotImplemented,
    XETSwNotImplemented,
    XETSwNotImplemented,
    XETSwNotImplemented,
    XETSwNotImplemented,		/* 125 */
    XETSwNotImplemented,
    XETSwNoOperation
};

/* NOTE: This array must align with the values of the constants used
 * as minor_opcode values in the request structure. Failure to do this
 * could result in random code paths.
 */
globaldef XETDispatchFunc XETrapDispatchVector[10L] = 
{
    XETrapReset,            /* 0 XETrap_Reset */
    XETrapGetAvailable,     /* 1 XETrap_GetAvailable */
    XETrapConfig,           /* 2 XETrap_Config */
    XETrapStartTrap,        /* 3 XETrap_StartTrap */
    XETrapStopTrap,         /* 4 XETrap_StopTrap */
    XETrapGetCurrent,       /* 5 XETrap_GetCurrent */
    XETrapGetStatistics,    /* 6 XETrap_GetStatistics */
#ifndef _XINPUT
    XETrapSimulateXEvent,   /* 7 XETrap_SimulateXEvent */
#endif
    XETrapGetVersion,       /* 8 XETrap_GetVersion */
    XETrapGetLastInpTime,   /* 9 XETrap_GetLastInpTime */
};

/* NOTE: This array must align with the values of the constants used
 * as minor_opcode values in the request structure. Failure to do this
 * could result in random code paths.
 */
globaldef XETDispatchFunc XETSwDispatchVector[10L] = 
{
    sXETrapReset,           /* 0 XETrap_Reset */
    sXETrapGetAvailable,    /* 1 XETrap_GetAvailable */
    sXETrapConfig,          /* 2 XETrap_Config */
    sXETrapStartTrap,       /* 3 XETrap_StartTrap */
    sXETrapStopTrap,        /* 4 XETrap_StopTrap */
    sXETrapGetCurrent,      /* 5 XETrap_GetCurrent */
    sXETrapGetStatistics,   /* 6 XETrap_GetStatistics */
#ifndef _XINPUT
    sXETrapSimulateXEvent,  /* 7 XETrap_SimulateXEvent */
#endif
    sXETrapGetVersion,      /* 8 XETrap_GetVersion */
    sXETrapGetLastInpTime,  /* 9 XETrap_GetLastInpTime */
};

/* ProcVector shadow vector */
globaldef XETProcFunc XETrapProcVector[256L]       = {XETrapRequestVector};
/*
 * Events are faked as if they're vectored since that's
 * the way it'll eventually be (X11 R5?).
 */
#ifndef VECTORED_EVENTS
globaldef ProcessInputProc EventProcVector[XETrapCoreEvents]       = {NULL};
#endif
globaldef ProcessInputProc XETrapEventProcVector[XETrapCoreEvents] = {NULL};


