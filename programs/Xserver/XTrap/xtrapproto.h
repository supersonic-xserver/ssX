/* $XFree86: xc/include/extensions/xtrapproto.h,v 1.2 2002/02/22 21:32:51 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef __XTRAPPROTO__
#define __XTRAPPROTO__

/*****************************************************************************
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
 *
 *  CONTRIBUTORS:
 *
 *      Dick Annicchiarico
 *      Robert Chesler
 *      Dan Coutu
 *      Gene Durso
 *      Marc Evans
 *      Alan Jamison
 *      Mark Henry
 *      Ken Miller
 *
 *  DESCRIPTION:
 *      This header file contains the function prototypes for extension
 *      routines sorted by module (globally defined routines *only*).
 */
#ifndef Bool
# define Bool int
#endif

typedef void (*XETSwReqFunc)(xResourceReq *data, ClientPtr client);
typedef int (*XETDispatchFunc)(xXTrapReq *stuff, ClientPtr client);
typedef int (*XETProcFunc)(ClientPtr client);

/* xtrapdi.c */
int XETrapDestroyEnv (pointer value , XID id );
void XETrapCloseDown ( ExtensionEntry *extEntry );
Bool XETrapRedirectDevices (void );
void DEC_XTRAPInit (void );
int XETrapCreateEnv (ClientPtr client );
int XETrapDispatch (ClientPtr client );
int sXETrapDispatch (ClientPtr client );
int XETrapReset (xXTrapReq *request , ClientPtr client );
int XETrapGetAvailable (xXTrapReq *request , ClientPtr client );
int XETrapGetCurrent (xXTrapReq *request , ClientPtr client );
int XETrapGetStatistics (xXTrapReq *request , ClientPtr client );
int XETrapConfig (xXTrapReq *request , ClientPtr client );
int XETrapStartTrap (xXTrapReq *request , ClientPtr client );
int XETrapStopTrap (xXTrapReq *request , ClientPtr client );
int XETrapGetVersion (xXTrapReq *request , ClientPtr client );
int XETrapGetLastInpTime (xXTrapReq *request , ClientPtr client );
int XETrapRequestVector (ClientPtr client );
void XETrapKeyboard (xEvent *x_event , DeviceIntPtr keybd , int count );
#ifndef VECTORED_EVENTS
void XETrapPointer (xEvent *x_event , DeviceIntPtr ptrdev , int count );
#else
int XETrapEventVector (ClientPtr client , xEvent *x_event );
#endif
void XETrapStampAndMail (xEvent *x_event );
void sReplyXTrapDispatch (ClientPtr client , int size , void *reply );
int XETrapWriteXLib (XETrapEnv *penv , BYTE *data , CARD32 nbytes );

/* xtrapddmi.c */
void XETrapPlatformSetup (void );
int XETrapSimulateXEvent (xXTrapReq *request , ClientPtr client );

/* xtrapdiswap.c */
int sXETrapReset (xXTrapReq *request , ClientPtr client );
int sXETrapGetAvailable (xXTrapReq *request , ClientPtr client );
int sXETrapConfig (xXTrapReq *request , ClientPtr client );
int sXETrapStartTrap (xXTrapReq *request , ClientPtr client );
int sXETrapStopTrap (xXTrapReq *request , ClientPtr client );
int sXETrapGetCurrent (xXTrapReq *request , ClientPtr client );
int sXETrapGetStatistics (xXTrapReq *request , ClientPtr client );
int sXETrapSimulateXEvent (xXTrapReq *request , ClientPtr client );
int sXETrapGetVersion (xXTrapReq *request , ClientPtr client );
int sXETrapGetLastInpTime (xXTrapReq *request , ClientPtr client );
void sReplyXETrapGetAvail (ClientPtr client , int size , char *reply );
void sReplyXETrapGetVers (ClientPtr client , int size , char *reply );
void sReplyXETrapGetLITim (ClientPtr client , int size , char *reply );
void sReplyXETrapGetCur (ClientPtr client , int size , char *reply );
void sReplyXETrapGetStats (ClientPtr client , int size , char *reply );
void sXETrapHeader (XETrapHeader *hdr );
void XETSwSimpleReq (xResourceReq *data, ClientPtr client );
void XETSwResourceReq (xResourceReq *data, ClientPtr client );
void XETSwCreateWindow (xResourceReq *data , ClientPtr client );
void XETSwChangeWindowAttributes (xResourceReq *data , ClientPtr client );
void XETSwReparentWindow (xResourceReq *data, ClientPtr client );
void XETSwConfigureWindow (xResourceReq *data  , ClientPtr client );
void XETSwInternAtom (xResourceReq *data, ClientPtr client );
void XETSwChangeProperty (xResourceReq *data, ClientPtr client );
void XETSwDeleteProperty (xResourceReq *data, ClientPtr client );
void XETSwGetProperty (xResourceReq *data, ClientPtr client );
void XETSwSetSelectionOwner (xResourceReq *data, ClientPtr client );
void XETSwConvertSelection (xResourceReq *data, ClientPtr client );
void XETSwSendEvent (xResourceReq *data, ClientPtr client );
void XETSwGrabPointer (xResourceReq *data, ClientPtr client );
void XETSwGrabButton (xResourceReq *data, ClientPtr client );
void XETSwUngrabButton (xResourceReq *data, ClientPtr client );
void XETSwChangeActivePointerGrab (xResourceReq *data, ClientPtr client );
void XETSwGrabKeyboard (xResourceReq *data, ClientPtr client );
void XETSwGrabKey (xResourceReq *data, ClientPtr client );
void XETSwUngrabKey (xResourceReq *data, ClientPtr client );
void XETSwGetMotionEvents (xResourceReq *data, ClientPtr client );
void XETSwTranslateCoords (xResourceReq *data, ClientPtr client );
void XETSwWarpPointer (xResourceReq *data, ClientPtr client );
void XETSwSetInputFocus (xResourceReq *data, ClientPtr client );
void XETSwOpenFont (xResourceReq *data, ClientPtr client );
void XETSwListFonts (xResourceReq *data, ClientPtr client );
void XETSwListFontsWithInfo (xResourceReq *data, ClientPtr client );
void XETSwSetFontPath (xResourceReq *data, ClientPtr client );
void XETSwCreatePixmap (xResourceReq *data, ClientPtr client );
void XETSwCreateGC (xResourceReq *data , ClientPtr client );
void XETSwChangeGC (xResourceReq *data , ClientPtr client );
void XETSwCopyGC (xResourceReq *data, ClientPtr client );
void XETSwSetDashes (xResourceReq *data, ClientPtr client );
void XETSwSetClipRectangles (xResourceReq *data , ClientPtr client );
void XETSwClearToBackground (xResourceReq *data, ClientPtr client );
void XETSwCopyArea (xResourceReq *data, ClientPtr client );
void XETSwCopyPlane (xResourceReq *data, ClientPtr client );
void XETSwPoly (xResourceReq *data, ClientPtr client );
void XETSwFillPoly (xResourceReq *data, ClientPtr client );
void XETSwPutImage (xResourceReq *data, ClientPtr client );
void XETSwGetImage (xResourceReq *data, ClientPtr client );
void XETSwPolyText (xResourceReq *data, ClientPtr client );
void XETSwImageText (xResourceReq *data, ClientPtr client );
void XETSwCreateColormap (xResourceReq *data, ClientPtr client );
void XETSwCopyColormapAndFree (xResourceReq *data, ClientPtr client );
void XETSwAllocColor (xResourceReq *data, ClientPtr client );
void XETSwAllocNamedColor (xResourceReq *data, ClientPtr client );
void XETSwAllocColorCells (xResourceReq *data, ClientPtr client );
void XETSwAllocColorPlanes (xResourceReq *data, ClientPtr client );
void XETSwFreeColors (xResourceReq *data , ClientPtr client );
void XETSwStoreColors (xResourceReq *data , ClientPtr client );
void XETSwStoreNamedColor (xResourceReq *data, ClientPtr client );
void XETSwQueryColors (xResourceReq *data , ClientPtr client );
void XETSwLookupColor (xResourceReq *data, ClientPtr client );
void XETSwCreateCursor (xResourceReq *data, ClientPtr client );
void XETSwCreateGlyphCursor (xResourceReq *data, ClientPtr client );
void XETSwRecolorCursor (xResourceReq *data, ClientPtr client );
void XETSwQueryBestSize (xResourceReq *data, ClientPtr client );
void XETSwQueryExtension (xResourceReq *data, ClientPtr client );
void XETSwChangeKeyboardMapping (xResourceReq *data, ClientPtr client );
void XETSwChangeKeyboardControl (xResourceReq *data , ClientPtr client );
void XETSwChangePointerControl (xResourceReq *data, ClientPtr client );
void XETSwSetScreenSaver (xResourceReq *data, ClientPtr client );
void XETSwChangeHosts (xResourceReq *data, ClientPtr client );
void XETSwRotateProperties (xResourceReq *data , ClientPtr client );
void XETSwNoOperation (xResourceReq *data, ClientPtr client );
void XETSwNotImplemented (xResourceReq *data, ClientPtr client);
void XETSwProcBadRequest(xResourceReq *data, ClientPtr client);
#ifdef vms
void SwapLongs (long *list , unsigned long count );
void SwapShorts (short *list , unsigned long count );
int SwapColorItem (xColorItem *pItem );
#endif /* vms */


#endif /* __XTRAPPROTO__ */
