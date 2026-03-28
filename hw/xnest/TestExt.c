/* $XFree86: xc/programs/Xserver/hw/xnest/TestExt.c,v 3.7 2005/10/14 15:17:15 tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/

#include <X11/X.h>
#include <X11/Xproto.h>
#include <X11/Xlib.h>
#undef Bool
#include "screenint.h"
#include "input.h"
#include "misc.h"
#include "scrnintstr.h"
#include "servermd.h"
#include "mipointer.h"
#define XTestSERVER_SIDE
#include <X11/extensions/xtestext1.h>
#include "xtest1dd.h"

extern CARD32 lastEventTime;

void
XTestGetPointerPos(short *fmousex, short *fmousey)
{
  int x,y;
  
  miPointerPosition(&x, &y);
  *fmousex = x;
  *fmousey = y;
}

void
XTestJumpPointer(int jx, int jy, int dev_type)
{
  miPointerAbsoluteCursor(jx, jy, GetTimeInMillis());
}

void
XTestGenerateEvent(int dev_type, int keycode, int keystate, int mousex,
		   int mousey)
{
/*
  xEvent tevent;
  
  tevent.u.u.type = (dev_type == XE_POINTER) ?
    (keystate == XTestKEY_UP) ? ButtonRelease : ButtonPress :
      (keystate == XTestKEY_UP) ? KeyRelease : KeyPress;
  tevent.u.u.detail = keycode;
  tevent.u.keyButtonPointer.rootX = mousex;
  tevent.u.keyButtonPointer.rootY = mousey;
  tevent.u.keyButtonPointer.time = lastEventTime = GetTimeInMillis();
  mieqEnqueue(&tevent);
*/
}
