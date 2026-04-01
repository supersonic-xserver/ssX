/* $XFree86: xc/programs/Xserver/XTrap/xtrapddmi.c,v 1.4 2005/10/14 15:16:10 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


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
 *  ABSTRACT:
 *
 *      This module is the platform-specific but conditionally independent
 *      code for the XTrap extension (usually I/O or platform setup).
 *      This is shared code and is subject to change only by team approval.
 *
 *  CONTRIBUTORS:
 *
 *      Dick Annicchiarico
 *      Robert Chesler
 *      Gene Durso
 *      Marc Evans
 *      Alan Jamison
 *      Mark Henry
 *      Ken Miller
 *
 */

#ifndef EXTMODULE
#include <errno.h>
#include <X11/Xos.h>
#ifdef PC
# include "fcntl.h"
# include "io.h"
# define O_NDELAY 0L
#endif
#else
#include "xf86_ansic.h"
#endif

#define NEED_REPLIES
#define NEED_EVENTS
#include <X11/X.h>        /* From library include environment */
#include "input.h"    /* From server include env. (must be before Xlib.h!) */
#ifdef PC
# include "scrintst.h"          /* Screen struct */
# include "extnsist.h"
#else
# include "extnsionst.h"        /* Server ExtensionEntry definitions */
# include "scrnintstr.h"        /* Screen struct */
#endif

#include <X11/extensions/xtrapdi.h>
#include "xtrapddmi.h"
#include "xtrapproto.h"

extern int XETrapErrorBase;
extern xXTrapGetAvailReply XETrap_avail;
extern DevicePtr XETrapKbdDev;
extern DevicePtr XETrapPtrDev;

/*
 *  DESCRIPTION:
 *
 *      This function performs the platform specific setup for server
 *      extension implementations.
 */
void
XETrapPlatformSetup()
{
}


#if !defined _XINPUT
/*
 *  DESCRIPTION:
 *
 *  This routine processes the simulation of some input event.
 *
 */
int
XETrapSimulateXEvent(xXTrapReq *r, ClientPtr client)
{
    ScreenPtr pScr = NULL;
    int status = Success;
    xEvent xev;
    xXTrapInputReq *request = (xXTrapInputReq *)r;
    int x = request->input.x;
    int y = request->input.y;
    DevicePtr keydev = LookupKeyboardDevice();
    DevicePtr ptrdev = LookupPointerDevice();

    if (request->input.screen < screenInfo.numScreens)
    {
        pScr = screenInfo.screens[request->input.screen];
    }
    else
    {   /* Trying to play bogus events to this WS! */
#ifdef VERBOSE
        ErrorF("%s:  Trying to send events to screen %d!\n", XTrapExtName,
            request->input.screen);
#endif
        status = XETrapErrorBase + BadScreen;
    }
    /* Fill in the event structure with the information
     * Note:  root, event, child, eventX, eventY, state, and sameScreen
     *        are all updated by FixUpEventFromWindow() when the events
     *        are delivered via DeliverDeviceEvents() or whatever.  XTrap
     *        needs to only concern itself with type, detail, time, rootX, 
     *        and rootY.
     */
    if (status == Success)
    {
        xev.u.u.type   = request->input.type;
        xev.u.u.detail = request->input.detail;
        xev.u.keyButtonPointer.time   = GetTimeInMillis();
        xev.u.keyButtonPointer.rootX = x;
        xev.u.keyButtonPointer.rootY = y;

        if (request->input.type == MotionNotify)
        {   /* Set new cursor position on screen */
            XETrap_avail.data.cur_x = x;
            XETrap_avail.data.cur_y = y;
          NewCurrentScreen (pScr, x, y); /* fix from amnonc@mercury.co.il */
            if (!(*pScr->SetCursorPosition)(pScr, x, y, xFalse))
            {
                status = BadImplementation;
            }
        }
    }
    if (status == Success)
    {
        switch(request->input.type)
        {   /* Now process the event appropriately */
            case KeyPress:
            case KeyRelease:
                (*XETrapKbdDev->realInputProc)(&xev,(DeviceIntPtr)keydev, 1L);
                break;
            case MotionNotify:
            case ButtonPress:
            case ButtonRelease:
                (*XETrapPtrDev->realInputProc)(&xev,(DeviceIntPtr)ptrdev, 1L);
                break;
            default:
                status = BadValue;
                break;
        }
    }
    return(status);
}
#endif /* _XINPUT */

#if defined vms && !defined LINKED_IN
/* Used by swapping code not visible from VMS (from main.c) */
#ifndef BLADE
void
NotImplemented()
{
    FatalError("Not implemented");
}
#endif

#endif /* vms && ! LINKED_IN */
