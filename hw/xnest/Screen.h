/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

Copyright 1993 by Davor Matic

Permission to use, copy, modify, distribute, and sell this software
and its documentation for any purpose is hereby granted without fee,
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in
supporting documentation.  Davor Matic makes no representations about
the suitability of this software for any purpose.  It is provided "as
is" without express or implied warranty.

*/
/* $XFree86: xc/programs/Xserver/hw/xnest/Screen.h,v 1.5 2007/01/23 18:03:12 tsi Exp $ */

#ifndef XNESTSCREEN_H
#define XNESTSCREEN_H

extern Window xnestDefaultWindows[MAXSCREENS];
extern Window xnestScreenSaverWindows[MAXSCREENS];

ScreenPtr xnestScreen(Window window);
Bool xnestOpenScreen(int index, ScreenPtr pScreen, const int argc, const char *argv[]);
Bool xnestCloseScreen(int index, ScreenPtr pScreen);

#endif /* XNESTSCREEN_H */
