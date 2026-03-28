/* $XFree86: xc/programs/Xserver/XTrap/xtrapdiswp.c,v 1.3 2005/10/14 15:16:10 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/****************************************************************************
Copyright 1987, 1988, 1989, 1990, 1991, 1992 by 

	Digital Equipment Corp., Maynard, MA

X11R6 Changes Copyright (c) 1994 by Robert Chesler of Absol-Puter, Hudson, NH.

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the name of Digital not be
used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL AND ABSOL-PUTER DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL DIGITAL OR ABSOL-PUTER BE LIABLE FOR ANY
SPECIAL, INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER
RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF
CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

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
 *      This module is the device independent module responsible for all
 *      routines required for proper communication in a heterogeneous
 *      networking environment (i.e. client & server on different endian
 *      machines).  The bulk of this module is patterned after X11/R4's
 *      server/dix/swapreq.c ; however, they infact swap fields
 *      in the exact opposite order since XTrap requires "unswapped" data
 *      to become "swapped" before sending it to a "swapped" client.
 *
 *  CONTRIBUTORS:
 *
 *      Ken Miller
 *      Marc Evans
 *
 * CHANGES:
 *
 *	Robert Chesler - added client arg for X11R6 port in many spots
 *
 */

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
# include "swapreq.h"        /* Server SwapColorItem definition */
#include "xtrapddmi.h"
#include "xtrapproto.h"

/* In-coming XTrap requests needing to be swapped to native format */

int
sXETrapReset(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapReset(request,client));
}

int
sXETrapGetAvailable(xXTrapReq *r, ClientPtr client)
{
    char n;
    xXTrapGetReq *request = (xXTrapGetReq *)r;

    swaps(&(request->length),n);
    swaps(&(request->protocol),n);
    return(XETrapGetAvailable(r, client));
}

int
sXETrapConfig(xXTrapReq *r, ClientPtr client)
{
    char n;
    xXTrapConfigReq *request = (xXTrapConfigReq *)r;

    swaps(&(request->length),n);
    swaps(&(request->config_max_pkt_size),n);
    return(XETrapConfig(r,client));
}

int
sXETrapStartTrap(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapStartTrap(request,client));
}

int
sXETrapStopTrap(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapStopTrap(request,client));
}

int
sXETrapGetCurrent(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapGetCurrent(request,client));
}

int
sXETrapGetStatistics(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapGetStatistics(request, client));
}

#ifndef _XINPUT
int
sXETrapSimulateXEvent(xXTrapReq *r, ClientPtr client)
{
    char n;
    xXTrapInputReq *request = (xXTrapInputReq *)r;

    swaps(&(request->input.x),n);
    swaps(&(request->input.y),n);
    return(XETrapSimulateXEvent(r, client));
}
#endif

int
sXETrapGetVersion(xXTrapReq *r, ClientPtr client)
{
    char n;
    xXTrapGetReq *request = (xXTrapGetReq *)r;

    swaps(&(request->length),n);
    swaps(&(request->protocol),n);
    return(XETrapGetVersion(r, client));
}

int
sXETrapGetLastInpTime(xXTrapReq *request, ClientPtr client)
{
    char n;
    swaps(&(request->length),n);
    return(XETrapGetLastInpTime(request,client));
}


/* Out-going XTrap replies needing to be swapped *from* native format */

void
sReplyXETrapGetAvail(ClientPtr client, int size, char *reply)
{
    xXTrapGetAvailReply *rep = (xXTrapGetAvailReply *)reply;
    char n;
    swaps(&(rep->hdr.sequenceNumber),n);
    swapl(&(rep->hdr.length),n);
    swapl(&(rep->data.pf_ident),n);
    swaps(&(rep->data.xtrap_release),n);
    swaps(&(rep->data.xtrap_version),n);
    swaps(&(rep->data.xtrap_revision),n);
    swaps(&(rep->data.max_pkt_size),n);
    swapl(&(rep->data.major_opcode),n);
    swapl(&(rep->data.event_base),n);
    swaps(&(rep->data.cur_x),n);
    swaps(&(rep->data.cur_y),n);
    (void)WriteToClient(client,size,reply);
    return;
}

void
sReplyXETrapGetVers(ClientPtr client, int size, char *reply)
{
    xXTrapGetVersReply *rep = (xXTrapGetVersReply *)reply;
    char n;
    swaps(&(rep->hdr.sequenceNumber),n);
    swapl(&(rep->hdr.length),n);
    swaps(&(rep->data.xtrap_release),n);
    swaps(&(rep->data.xtrap_version),n);
    swaps(&(rep->data.xtrap_revision),n);
    (void)WriteToClient(client,size,reply);
    return;
}

void
sReplyXETrapGetLITim(ClientPtr client, int size, char *reply)
{
    xXTrapGetLITimReply *rep = (xXTrapGetLITimReply *)reply;
    char n;
    swaps(&(rep->hdr.sequenceNumber),n);
    swapl(&(rep->hdr.length),n);
    swapl(&(rep->data_last_time),n);
    (void)WriteToClient(client,size,reply);
    return;
}

void
sReplyXETrapGetCur(ClientPtr client, int size, char *reply)
{
    xXTrapGetCurReply *rep = (xXTrapGetCurReply *)reply;
    char n;
    swaps(&(rep->hdr.sequenceNumber),n);
    swapl(&(rep->hdr.length),n);
    swaps(&(rep->data_config_max_pkt_size),n);
    (void)WriteToClient(client,size,reply);
    return;
}

void
sReplyXETrapGetStats(ClientPtr client, int size, char *reply)
{
    xXTrapGetStatsReply *rep = (xXTrapGetStatsReply *)reply;
    char n;
    int i;
    long *p;

    swaps(&(rep->sequenceNumber),n);
    swapl(&(rep->length),n);
    for (i=0L, p = (long *)rep->data.requests; i<256L; i++, p++)
    { 
        swapl(p,n);
    }
    for (i=0L, p = (long *)rep->data.events; i<XETrapCoreEvents; i++, p++)
    {
        swapl(p,n); 
    }
    (void)WriteToClient(client,size,reply);
    return;
}

/* Out-going XTrap I/O header needing to be swapped *from* native format */

void
sXETrapHeader(XETrapHeader *hdr)
{
    char n;

    swapl(&(hdr->count), n);
    swapl(&(hdr->timestamp), n);
    swaps(&(hdr->win_x), n);
    swaps(&(hdr->win_y), n);
    swaps(&(hdr->client), n);
}

    /* Out-going requests needing to be swapped *from* native format
     * aka swapreq.c "equivalents" 
     */

/* The following is used for all requests that have
   no fields to be swapped (except "length") */
void
XETSwSimpleReq(xResourceReq *data, ClientPtr client)
{
    char n;
    swaps(&(data->length), n);
}

/* The following is used for all requests that have
   only a single 32-bit field to be swapped, coming
   right after the "length" field */

void
XETSwResourceReq(xResourceReq *data, ClientPtr client)
{
    char n;

    swaps(&(data->length), n);
    swapl(&(data->id), n);
}

void
XETSwCreateWindow(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreateWindowReq *data = (xCreateWindowReq *)d;

    swapl(&(data->wid), n);
    swapl(&(data->parent), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
    swaps(&(data->borderWidth), n);
    swaps(&(data->class), n);
    swapl(&(data->visual), n);
    swapl(&(data->mask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

void
XETSwChangeWindowAttributes(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangeWindowAttributesReq *data = (xChangeWindowAttributesReq *)d;

    swapl(&(data->window), n);
    swapl(&(data->valueMask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

void
XETSwReparentWindow(xResourceReq *d, ClientPtr client)
{
    char n;
    xReparentWindowReq *data = (xReparentWindowReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->parent), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
}

void
XETSwConfigureWindow(xResourceReq *d, ClientPtr client)
{
    char n;
    xConfigureWindowReq *data = (xConfigureWindowReq *)d;

    swapl(&(data->window), n);
    swaps(&(data->mask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}


void
XETSwInternAtom(xResourceReq *d, ClientPtr client)
{
    char n;
    xInternAtomReq *data = (xInternAtomReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->nbytes), n);
}

void
XETSwChangeProperty(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangePropertyReq *data = (xChangePropertyReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->property), n);
    swapl(&(data->type), n);
    switch ( data->format ) {
        case 8L : break;
        case 16L:
            SwapShorts((short *)(data + 1), data->nUnits);
        break;
    case 32L:
            SwapLongs((CARD32 *)(data + 1), data->nUnits);
        break;
    }
    swapl(&(data->nUnits), n);
}

void
XETSwDeleteProperty(xResourceReq *d, ClientPtr client)
{
    char n;
    xDeletePropertyReq *data = (xDeletePropertyReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->property), n);
              
}
void
XETSwGetProperty(xResourceReq *d, ClientPtr client)
{
    char n;
    xGetPropertyReq *data = (xGetPropertyReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->property), n);
    swapl(&(data->type), n);
    swapl(&(data->longOffset), n);
    swapl(&(data->longLength), n);
}

void
XETSwSetSelectionOwner(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetSelectionOwnerReq *data = (xSetSelectionOwnerReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->selection), n);
    swapl(&(data->time), n);
}

void
XETSwConvertSelection(xResourceReq *d, ClientPtr client)
{
    char n;
    xConvertSelectionReq *data = (xConvertSelectionReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->requestor), n);
    swapl(&(data->selection), n);
    swapl(&(data->target), n);
    swapl(&(data->property), n);
    swapl(&(data->time), n);
}

void
XETSwSendEvent(xResourceReq *d, ClientPtr client)
{
    char n;
    xSendEventReq *data = (xSendEventReq *)d;

    xEvent eventT;
    EventSwapPtr proc;
    swapl(&(data->destination), n);
    swapl(&(data->eventMask), n);

    /* Swap event */
    proc = EventSwapVector[data->event.u.u.type & 0177];
    if (!proc || proc == NotImplemented)   
        (*proc)(&(data->event), &eventT);
    data->event = eventT;
    swaps(&(data->length), n);
}

void
XETSwGrabPointer(xResourceReq *d, ClientPtr client)
{
    char n;
    xGrabPointerReq *data = (xGrabPointerReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swaps(&(data->eventMask), n);
    swapl(&(data->confineTo), n);
    swapl(&(data->cursor), n);
    swapl(&(data->time), n);
}

void
XETSwGrabButton(xResourceReq *d, ClientPtr client)
{
    char n;
    xGrabButtonReq *data = (xGrabButtonReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swaps(&(data->eventMask), n);
    swapl(&(data->confineTo), n);
    swapl(&(data->cursor), n);
    swaps(&(data->modifiers), n);
}

void
XETSwUngrabButton(xResourceReq *d, ClientPtr client)
{
    char n;
    xUngrabButtonReq *data = (xUngrabButtonReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swaps(&(data->modifiers), n);
}

void
XETSwChangeActivePointerGrab(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangeActivePointerGrabReq *data = (xChangeActivePointerGrabReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cursor), n);
    swapl(&(data->time), n);
    swaps(&(data->eventMask), n);
}

void
XETSwGrabKeyboard(xResourceReq *d, ClientPtr client)
{
    char n;
    xGrabKeyboardReq *data = (xGrabKeyboardReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swapl(&(data->time), n);
}

void
XETSwGrabKey(xResourceReq *d, ClientPtr client)
{
    char n;
    xGrabKeyReq *data = (xGrabKeyReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swaps(&(data->modifiers), n);
}

void
XETSwUngrabKey(xResourceReq *d, ClientPtr client)
{
    char n;
    xUngrabKeyReq *data = (xUngrabKeyReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->grabWindow), n);
    swaps(&(data->modifiers), n);
}

void
XETSwGetMotionEvents(xResourceReq *d, ClientPtr client)
{
    char n;
    xGetMotionEventsReq *data = (xGetMotionEventsReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swapl(&(data->start), n);
    swapl(&(data->stop), n);
}

void
XETSwTranslateCoords(xResourceReq *d, ClientPtr client)
{
    char n;
    xTranslateCoordsReq *data = (xTranslateCoordsReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->srcWid), n);
    swapl(&(data->dstWid), n);
    swaps(&(data->srcX), n);
    swaps(&(data->srcY), n);
}

void
XETSwWarpPointer(xResourceReq *d, ClientPtr client)
{
    char n;
    xWarpPointerReq *data = (xWarpPointerReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->srcWid), n);
    swapl(&(data->dstWid), n);
    swaps(&(data->srcX), n);
    swaps(&(data->srcY), n);
    swaps(&(data->srcWidth), n);
    swaps(&(data->srcHeight), n);
    swaps(&(data->dstX), n);
    swaps(&(data->dstY), n);
}

void
XETSwSetInputFocus(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetInputFocusReq *data = (xSetInputFocusReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->focus), n);
    swapl(&(data->time), n);
}

void
XETSwOpenFont(xResourceReq *d, ClientPtr client)
{
    char n;
    xOpenFontReq *data = (xOpenFontReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->fid), n);
    swaps(&(data->nbytes), n);
}

void
XETSwListFonts(xResourceReq *d, ClientPtr client)
{
    char n;
    xListFontsReq *data = (xListFontsReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->maxNames), n);
    swaps(&(data->nbytes), n);
}

void
XETSwListFontsWithInfo(xResourceReq *d, ClientPtr client)
{
    char n;
    xListFontsWithInfoReq *data = (xListFontsWithInfoReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->maxNames), n);
    swaps(&(data->nbytes), n);
}

void
XETSwSetFontPath(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetFontPathReq *data = (xSetFontPathReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->nFonts), n);
}

void
XETSwCreatePixmap(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreatePixmapReq *data = (xCreatePixmapReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->pid), n);
    swapl(&(data->drawable), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
}

void
XETSwCreateGC(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreateGCReq *data = (xCreateGCReq *)d;

    swapl(&(data->gc), n);
    swapl(&(data->drawable), n);
    swapl(&(data->mask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

void
XETSwChangeGC(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangeGCReq *data = (xChangeGCReq *)d;

    swapl(&(data->gc), n);
    swapl(&(data->mask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

void
XETSwCopyGC(xResourceReq *d, ClientPtr client)
{
    char n;
    xCopyGCReq *data = (xCopyGCReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->srcGC), n);
    swapl(&(data->dstGC), n);
    swapl(&(data->mask), n);
}

void
XETSwSetDashes(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetDashesReq *data = (xSetDashesReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->gc), n);
    swaps(&(data->dashOffset), n);
    swaps(&(data->nDashes), n);
}

void
XETSwSetClipRectangles(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetClipRectanglesReq *data = (xSetClipRectanglesReq *)d;

    swapl(&(data->gc), n);
    swaps(&(data->xOrigin), n);
    swaps(&(data->yOrigin), n);
    SwapRestS(data);
    swaps(&(data->length), n);
}

void
XETSwClearToBackground(xResourceReq *d, ClientPtr client)
{
    char n;
    xClearAreaReq *data = (xClearAreaReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->window), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
}

void
XETSwCopyArea(xResourceReq *d, ClientPtr client)
{
    char n;
    xCopyAreaReq *data = (xCopyAreaReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->srcDrawable), n);
    swapl(&(data->dstDrawable), n);
    swapl(&(data->gc), n);
    swaps(&(data->srcX), n);
    swaps(&(data->srcY), n);
    swaps(&(data->dstX), n);
    swaps(&(data->dstY), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
}

void
XETSwCopyPlane(xResourceReq *d, ClientPtr client)
{
    char n;
    xCopyPlaneReq *data = (xCopyPlaneReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->srcDrawable), n);
    swapl(&(data->dstDrawable), n);
    swapl(&(data->gc), n);
    swaps(&(data->srcX), n);
    swaps(&(data->srcY), n);
    swaps(&(data->dstX), n);
    swaps(&(data->dstY), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
    swapl(&(data->bitPlane), n);
}

/* The following routine is used for all Poly drawing requests
   (except FillPoly, which uses a different request format) */
void
XETSwPoly(xResourceReq *d, ClientPtr client)
{
    char n;
    xPolyPointReq *data = (xPolyPointReq *)d;

    swapl(&(data->drawable), n);
    swapl(&(data->gc), n);
    SwapRestS(data);
    swaps(&(data->length), n);
}
     /* cannot use XETSwPoly for this one, because xFillPolyReq
      * is longer than xPolyPointReq, and we don't want to swap
      * the difference as shorts! 
      */
void
XETSwFillPoly(xResourceReq *d, ClientPtr client)
{
    char n;
    xFillPolyReq *data = (xFillPolyReq *)d;

    swapl(&(data->drawable), n);
    swapl(&(data->gc), n);
    SwapRestS(data);
    swaps(&(data->length), n);
}

void
XETSwPutImage(xResourceReq *d, ClientPtr client)
{
    char n;
    xPutImageReq *data = (xPutImageReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->drawable), n);
    swapl(&(data->gc), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
    swaps(&(data->dstX), n);
    swaps(&(data->dstY), n);
    /* Image should already be swapped */
}

void
XETSwGetImage(xResourceReq *d, ClientPtr client)
{
    char n;
    xGetImageReq *data = (xGetImageReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->drawable), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);
    swapl(&(data->planeMask), n);
}

/* ProcPolyText used for both PolyText8 and PolyText16 */

void
XETSwPolyText(xResourceReq *d, ClientPtr client)
{
    char n;
    xPolyTextReq *data = (xPolyTextReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->drawable), n);
    swapl(&(data->gc), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
}

/* ProcImageText used for both ImageText8 and ImageText16 */

void
XETSwImageText(xResourceReq *d, ClientPtr client)
{
    char n;
    xImageTextReq *data = (xImageTextReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->drawable), n);
    swapl(&(data->gc), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
}

void
XETSwCreateColormap(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreateColormapReq *data = (xCreateColormapReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->mid), n);
    swapl(&(data->window), n);
    swapl(&(data->visual), n);
}


void
XETSwCopyColormapAndFree(xResourceReq *d, ClientPtr client)
{
    char n;
    xCopyColormapAndFreeReq *data = (xCopyColormapAndFreeReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->mid), n);
    swapl(&(data->srcCmap), n);

}

void
XETSwAllocColor(xResourceReq *d, ClientPtr client)
{
    char n;
    xAllocColorReq *data = (xAllocColorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swaps(&(data->red), n);
    swaps(&(data->green), n);
    swaps(&(data->blue), n);
}

void
XETSwAllocNamedColor(xResourceReq *d, ClientPtr client)
{
    char n;
    xAllocNamedColorReq *data = (xAllocNamedColorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swaps(&(data->nbytes), n);
}

void
XETSwAllocColorCells(xResourceReq *d, ClientPtr client)
{
    char n;
    xAllocColorCellsReq *data = (xAllocColorCellsReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swaps(&(data->colors), n);
    swaps(&(data->planes), n);
}

void
XETSwAllocColorPlanes(xResourceReq *d, ClientPtr client)
{
    char n;
    xAllocColorPlanesReq *data = (xAllocColorPlanesReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swaps(&(data->colors), n);
    swaps(&(data->red), n);
    swaps(&(data->green), n);
    swaps(&(data->blue), n);
}

void
XETSwFreeColors(xResourceReq *d, ClientPtr client)
{
    char n;
    xFreeColorsReq *data = (xFreeColorsReq *)d;

    swapl(&(data->cmap), n);
    swapl(&(data->planeMask), n);
    SwapRestL(data);
    swaps(&(data->length), n);

}

void
XETSwStoreColors(xResourceReq *d, ClientPtr client)
{
    char n;
    unsigned long count;
    xColorItem     *pItem;
    xStoreColorsReq *data = (xStoreColorsReq *)d;

    swapl(&(data->cmap), n);
    pItem = (xColorItem *) &(data[1]);
    for(count = LengthRestB(data)/sizeof(xColorItem); count != 0; count--)
        SwapColorItem(pItem++);
    swaps(&(data->length), n);
}

void
XETSwStoreNamedColor(xResourceReq *d, ClientPtr client)
{
    char n;
    xStoreNamedColorReq *data = (xStoreNamedColorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swapl(&(data->pixel), n);
    swaps(&(data->nbytes), n);
}

void
XETSwQueryColors(xResourceReq *d, ClientPtr client)
{
    char n;
    xQueryColorsReq *data = (xQueryColorsReq *)d;

    swapl(&(data->cmap), n);
    SwapRestL(data);
    swaps(&(data->length), n);
} 

void
XETSwLookupColor(xResourceReq *d, ClientPtr client)
{
    char n;
    xLookupColorReq *data = (xLookupColorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cmap), n);
    swaps(&(data->nbytes), n);
}

void
XETSwCreateCursor(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreateCursorReq *data = (xCreateCursorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cid), n);
    swapl(&(data->source), n);
    swapl(&(data->mask), n);
    swaps(&(data->foreRed), n);
    swaps(&(data->foreGreen), n);
    swaps(&(data->foreBlue), n);
    swaps(&(data->backRed), n);
    swaps(&(data->backGreen), n);
    swaps(&(data->backBlue), n);
    swaps(&(data->x), n);
    swaps(&(data->y), n);
}

void
XETSwCreateGlyphCursor(xResourceReq *d, ClientPtr client)
{
    char n;
    xCreateGlyphCursorReq *data = (xCreateGlyphCursorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cid), n);
    swapl(&(data->source), n);
    swapl(&(data->mask), n);
    swaps(&(data->sourceChar), n);
    swaps(&(data->maskChar), n);
    swaps(&(data->foreRed), n);
    swaps(&(data->foreGreen), n);
    swaps(&(data->foreBlue), n);
    swaps(&(data->backRed), n);
    swaps(&(data->backGreen), n);
    swaps(&(data->backBlue), n);
}


void
XETSwRecolorCursor(xResourceReq *d, ClientPtr client)
{
    char n;
    xRecolorCursorReq *data = (xRecolorCursorReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->cursor), n);
    swaps(&(data->foreRed), n);
    swaps(&(data->foreGreen), n);
    swaps(&(data->foreBlue), n);
    swaps(&(data->backRed), n);
    swaps(&(data->backGreen), n);
    swaps(&(data->backBlue), n);
}

void
XETSwQueryBestSize(xResourceReq *d, ClientPtr client)
{
    char n;
    xQueryBestSizeReq *data = (xQueryBestSizeReq *)d;

    swaps(&(data->length), n);
    swapl(&(data->drawable), n);
    swaps(&(data->width), n);
    swaps(&(data->height), n);

}

void
XETSwQueryExtension(xResourceReq *d, ClientPtr client)
{
    char n;
    xQueryExtensionReq *data = (xQueryExtensionReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->nbytes), n);
}

void
XETSwChangeKeyboardMapping(xResourceReq *d, ClientPtr client)
{
    char n;
    long *p;
    int i, count;
    xChangeKeyboardMappingReq *data = (xChangeKeyboardMappingReq *)d;

    swaps(&(data->length), n);
    p = (long *)&(data[1]);
    count = data->keyCodes * data->keySymsPerKeyCode;
    for(i = 0; i < count; i++)
    {
        swapl(p, n);
        p++;
    }
}


void
XETSwChangeKeyboardControl(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangeKeyboardControlReq *data = (xChangeKeyboardControlReq *)d;

    swapl(&(data->mask), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

void
XETSwChangePointerControl(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangePointerControlReq *data = (xChangePointerControlReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->accelNum), n);
    swaps(&(data->accelDenum), n);
    swaps(&(data->threshold), n);
}


void
XETSwSetScreenSaver(xResourceReq *d, ClientPtr client)
{
    char n;
    xSetScreenSaverReq *data = (xSetScreenSaverReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->timeout), n);
    swaps(&(data->interval), n);
}

void
XETSwChangeHosts(xResourceReq *d, ClientPtr client)
{
    char n;
    xChangeHostsReq *data = (xChangeHostsReq *)d;

    swaps(&(data->length), n);
    swaps(&(data->hostLength), n);

}
void
XETSwRotateProperties(xResourceReq *d, ClientPtr client)
{
    char n;
    xRotatePropertiesReq *data = (xRotatePropertiesReq *)d;

    swapl(&(data->window), n);
    swaps(&(data->nAtoms), n);
    swaps(&(data->nPositions), n);
    SwapRestL(data);
    swaps(&(data->length), n);
}

/*ARGSUSED*/
void
XETSwNoOperation(xResourceReq *d, ClientPtr client)
{
    /* noop -- don't do anything */
}

/*ARGSUSED*/
void
XETSwNotImplemented(xResourceReq *d, ClientPtr client)
{
    /* noop -- don't do anything */
}

/*ARGSUSED*/
void
XETSwProcBadRequest(xResourceReq *d, ClientPtr client)
{
    /* noop -- don't do anything */
}

/* Byte swap a list of longs */
#if defined vms && !defined MITR5
#ifndef LINKED_IN
void SwapLongs ( long *list, register unsigned long count)
{
    char n;

    while (count >= 8) {
        swapl(list+0, n);
        swapl(list+1, n);
        swapl(list+2, n);
        swapl(list+3, n);
        swapl(list+4, n);
        swapl(list+5, n);
        swapl(list+6, n);
        swapl(list+7, n);
        list += 8;
        count -= 8;
    }
    if (count != 0) {
        do {
        swapl(list, n);
        list++;
        } while (--count != 0);
    }
}

/* Byte swap a list of shorts */

void SwapShorts (short *list, register unsigned long count)
{
    char n;

    while (count >= 16) {
        swaps(list+0, n);
        swaps(list+1, n);
        swaps(list+2, n);
        swaps(list+3, n);
        swaps(list+4, n);
        swaps(list+5, n);
        swaps(list+6, n);
        swaps(list+7, n);
        swaps(list+8, n);
        swaps(list+9, n);
        swaps(list+10, n);
        swaps(list+11, n);
        swaps(list+12, n);
        swaps(list+13, n);
        swaps(list+14, n);
        swaps(list+15, n);
        list += 16;
        count -= 16;
    }
    if (count != 0) {
        do {
        swaps(list, n);
        list++;
        } while (--count != 0);
    }
}

SwapColorItem(xColorItem *pItem)
{
    char n;
    swapl(&pItem->pixel, n);
    swaps(&pItem->red, n);
    swaps(&pItem->green, n);
    swaps(&pItem->blue, n);
}
#endif /* LINKED_IN */
#endif /* vms */
