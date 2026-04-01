/* $XFree86$ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * Copyright 1996 by Alan Hourihane, Wigan, England.
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Alan Hourihane not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Alan Hourihane makes no representations
 * about the suitability of this software for any purpose.  It is provided
 * "as is" without express or implied warranty.
 *
 * ALAN HOURIHANE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS, IN NO
 * EVENT SHALL ALAN HOURIHANE BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Author:  Alan Hourihane, alanh@fairlite.demon.co.uk
 */

/* Merge XY */
#define XY_MERGE(x,y) \
		(((unsigned long)(y) << 16) | ((unsigned long)(x) & 0xffff))

/* MMIO */
#ifndef PC98_TGUI
#define GER_BASE 0x2100
#else
#define GER_BASE 0x0000
#endif /* PC98_TGUI */

#ifdef TRIDENT_MMIO
#define BLTBUSY(b) \
		b = (*(unsigned char *)(tguiMMIOBase + GER_STATUS)) & GE_BUSY;
#define TGUI_STATUS(c) \
		*(unsigned char *)(tguiMMIOBase + GER_STATUS) = c;
#define TGUI_OPERMODE(c) \
		*(unsigned short *)(tguiMMIOBase + GER_OPERMODE) = c;
#define TGUI_FCOLOUR(c) \
		*(unsigned long *)(tguiMMIOBase + GER_FCOLOUR) = c;
#define TGUI_BCOLOUR(c) \
		*(unsigned long *)(tguiMMIOBase + GER_BCOLOUR) = c;
#define TGUI_DRAWFLAG(c) \
		*(unsigned long *)(tguiMMIOBase + GER_DRAWFLAG) = c;
#define TGUI_FMIX(c) \
		*(unsigned char *)(tguiMMIOBase + GER_FMIX) = c;
#define TGUI_DIM_XY(w,h) \
		*(unsigned long *)(tguiMMIOBase + GER_DIM_XY) = XY_MERGE(w-1,h-1);
#define TGUI_SRC_XY(x,y) \
		*(unsigned long *)(tguiMMIOBase + GER_SRC_XY) = XY_MERGE(x,y);
#define TGUI_DEST_XY(x,y) \
		*(unsigned long *)(tguiMMIOBase + GER_DEST_XY) = XY_MERGE(x,y);
#define TGUI_SRCCLIP_XY(x,y) \
		*(unsigned long *)(tguiMMIOBase + GER_SRCCLIP_XY) = XY_MERGE(x,y);
#define TGUI_DSTCLIP_XY(x,y) \
		*(unsigned long *)(tguiMMIOBase + GER_DSTCLIP_XY) = XY_MERGE(x,y);
#define TGUI_PATLOC(addr) \
		*(unsigned short *)(tguiMMIOBase +GER_PATLOC) = addr;
#define TGUI_COMMAND(c) \
		*(unsigned char *)(tguiMMIOBase + GER_COMMAND) = c;
#else
#define BLTBUSY(b) \
		b = inb(GER_BASE+GER_STATUS) & GE_BUSY;
#define TGUI_STATUS(c) \
		outb(GER_BASE+GER_STATUS, c);
#define TGUI_OPERMODE(c) \
		outw(GER_BASE+GER_OPERMODE, c);
#define TGUI_FCOLOUR(c) \
		outl(GER_BASE+GER_FCOLOUR, c);
#define TGUI_BCOLOUR(c) \
		outl(GER_BASE+GER_BCOLOUR, c);
#define TGUI_DRAWFLAG(c) \
		outl(GER_BASE+GER_DRAWFLAG, c);
#define TGUI_FMIX(c) \
		outb(GER_BASE+GER_FMIX, c);
#define TGUI_DIM_XY(w,h) \
		outl(GER_BASE+GER_DIM_XY, XY_MERGE(w-1,h-1));
#define TGUI_SRC_XY(x,y) \
		outl(GER_BASE+GER_SRC_XY, XY_MERGE(x,y));
#define TGUI_DEST_XY(x,y) \
		outl(GER_BASE+GER_DEST_XY, XY_MERGE(x,y));
#define TGUI_SRCCLIP_XY(x,y) \
		outl(GER_BASE+GER_SRCCLIP_XY, XY_MERGE(x,y));
#define TGUI_DSTCLIP_XY(x,y) \
		outl(GER_BASE+GER_DSTCLIP_XY, XY_MERGE(x,y));
#define TGUI_PATLOC(addr) \
		outw(GER_BASE+GER_PATLOC, addr);
#define TGUI_COMMAND(c) \
		outb(GER_BASE+GER_COMMAND, c);
#endif
