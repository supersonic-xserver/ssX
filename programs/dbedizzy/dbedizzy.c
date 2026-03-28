/* $XFree86: xc/programs/dbedizzy/dbedizzy.c,v 1.0tsi Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/******************************************************************************
 *
 * Copyright (c) 1994, 1995  Silicon Graphics Inc.
 *
 * Permission to use, copy, modify, and distribute this
 * software and its documentation for any purpose and without
 * fee is hereby granted, provided that the above copyright
 * notice appear in all copies and that both that copyright
 * notice and this permission notice appear in supporting
 * documentation, and that the name of Silicon Graphics not be
 * used in advertising or publicity pertaining to distribution
 * of the software without specific prior written permission.
 * Silicon Graphics makes no representation about the suitability
 * of this software for any purpose. It is provided "as is"
 * without any express or implied warranty.
 *
 * SILICON GRAPHICS DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS
 * SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
 * AND FITNESS FOR A PARTICULAR PURPOSE. IN NO EVENT SHALL SILICON
 * GRAPHICS BE LIABLE FOR ANY SPECIAL, INDIRECT OR CONSEQUENTIAL
 * DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
 * OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION  WITH
 * THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 *****************************************************************************/

/*
 * dbedizzy - demo of DBE creating a double buffered spinning scene
 *
 * Original dizzy program written by Mark Kilgard.
 *
 * Adapted to use DBE for double buffering by Allen Leinwand, 2/24/95 .
 */

#include <X11/Xlib.h>
#include <X11/Xutil.h>
#include <X11/extensions/Xdbe.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <X11/Xpoll.h>

/* Global variables */
static char            *ProgName;
static Display		*dpy;
static int		black, pink, green, orange, blue;
static int		width = 300;
static int		height = 300;
static Window		win;
static XID		buf;
static XdbeSwapInfo	swapInfo;
static GC		gc;
static float		rotation = 0.0;
static float		delta = 0.05;
static int		paused = 0;
static int		manual_paused = 0;

/* Default values for unspecified command line arguments */
static char		*display_name = NULL;
static int		class = PseudoColor;
static int		depth = 0;
static int		listVis = 0;
static int		slow = 0;
static int		spokes = 10;
static int		db = 1;
static int		verbose = 0;
static int		visid = 0;

static char *help_message[] = {
"  where options include:",
"    -display host:dpy           X server connection to use",
"    -class [pseudo,true]        class of visual to use",
"    -depth n                    depth of visual to use",
"    -help                       print this message",
"    -list                       list double buffer capable visuals",
"    -slow                       rotate image slowly",
"    -spokes n                   specify number of spokes to draw",
"    -nodb                       single buffer (ignore -class, -depth, -visid)",
"    -verbose                    produce chatty messages while running",
"    -visid [nn,0xnn]            visual ID to use (ignore -class, -depth)",
NULL};

static void
usage(void)
{
    char **cpp;

    fprintf (stderr, "\nusage:  %s [-options ...]\n", ProgName);
    for (cpp = help_message; *cpp; cpp++) {
	fprintf (stderr, "%s\n", *cpp);
    }
    fprintf (stderr, "\n");
}

static int
getColor(Colormap cmap, char *color_name)
{
    XColor	color;
    XColor	exact;
    int		status;

    status = XAllocNamedColor(dpy, cmap, color_name, &color, &exact);
    if (status == 0) {
	fprintf(stderr, "%s: Couldn't get color: %s\n", ProgName, color_name);
	exit(1);
    }
    return (color.pixel);
}

#define RATIO1 0.4
#define RATIO2 0.7
#define RATIO3 0.95

#ifndef M_PI
#define M_PI 3.1415927
#endif

#define ANGLE (M_PI*2/spokes)

static void
redraw(void)
{
    int		i;
    int		x, y;
    XPoint	pnt[4];

    if (verbose) {
	printf("redraw.\n");
    }
    if (!db) {
	XClearWindow(dpy, win);
    }
    x = width / 2;
    x += (int) (sin(rotation * 2) * 20);
    y = height / 2;
    y += (int) (cos(rotation * 2) * 20);
    for (i = 5; i < 20; i += 3) {
	XSetForeground(dpy, gc, orange);
	XDrawArc(dpy, buf, gc, x - i * 10, y - i * 10,
		 i * 20, i * 20, 0, 360 * 64);
	XSetForeground(dpy, gc, green);
	XDrawArc(dpy, buf, gc, x - i * 10 - 5, y - i * 10 - 5,
		 i * 20 + 10, i * 20 + 10, 0, 360 * 64);
	XSetForeground(dpy, gc, blue);
	XDrawArc(dpy, buf, gc, x - i * 10 - 10, y - i * 10 - 10,
		 i * 20 + 20, i * 20 + 20, 0, 360 * 64);
    }
    x = width / 2;
    y = height / 2;
    XSetForeground(dpy, gc, pink);
    pnt[0].x = x;
    pnt[0].y = y;
    for (i = 0; i < spokes; i++) {
	pnt[1].x = (int) (cos(i * ANGLE + rotation) * (RATIO1 * x)) + x;
	pnt[1].y = (int) (sin(i * ANGLE + rotation) * (RATIO1 * y)) + y;
	pnt[2].x = (int) (cos(i * ANGLE + rotation - 0.1) * (RATIO2 * x)) + x;
	pnt[2].y = (int) (sin(i * ANGLE + rotation - 0.1) * (RATIO2 * y)) + y;
	pnt[3].x = (int) (cos(i * ANGLE + rotation - 0.2) * (RATIO3 * x)) + x;
	pnt[3].y = (int) (sin(i * ANGLE + rotation - 0.2) * (RATIO3 * y)) + y;
	XDrawLines(dpy, buf, gc, pnt, 4, CoordModeOrigin);
    }
    if (db) {
	XdbeSwapBuffers(dpy, &swapInfo, 1);
    }
}

static Visual *
choose_DB_visual( /* Input */		Display *dpy, int listVis, int class,
		  /* Input, Output */	int *pDepth)
{
    Drawable		screen_list[1];
    int			num_screens;
    XdbeScreenVisualInfo	*DBEvisInfo;
    int			i, nitems;
    int			chosenDepth = 0;
    Visual		*chosenVisual = NULL;
    XVisualInfo		vinfo_template, *XvisInfo;
    char		visualClassName[12];

    screen_list[0] = DefaultRootWindow(dpy);
    num_screens = 1;
    DBEvisInfo = XdbeGetVisualInfo(dpy, screen_list, &num_screens);
    if (DBEvisInfo == NULL) {
	fprintf(stderr, "XdbeGetVisualInfo returned NULL\n");
	return (NULL);
    }

    if (listVis) {
	printf("\nThe double buffer capable visuals are:\n");
	printf("      visual ID    depth    class\n");
    }
    for (i = 0; i < DBEvisInfo->count; i++) {

	vinfo_template.visualid = DBEvisInfo->visinfo[i].visual;
	XvisInfo = XGetVisualInfo(dpy, VisualIDMask,
				   &vinfo_template, &nitems);
	if (XvisInfo == NULL) {
	    fprintf(stderr,
		    "%s: XGetVisualInfo returned NULL for visual %ld\n",
		    ProgName, (unsigned long)vinfo_template.visualid);
	    return (NULL);
	}
	if (listVis) {
	    if (XvisInfo->class == PseudoColor)
		strcpy(visualClassName, "PseudoColor");
	    else
		strcpy(visualClassName, "TrueColor");

	    printf("        %#4lx      %4d    %s\n",
		(unsigned long)DBEvisInfo->visinfo[i].visual,
		DBEvisInfo->visinfo[i].depth,
		visualClassName);
	}

	if (visid) {
	    if (XvisInfo->visualid == visid) {
		chosenVisual = XvisInfo->visual;
		chosenDepth = XvisInfo->depth;
	    }
	}
	else if (XvisInfo->class == class) {
	    if (*pDepth == 0) {
		/* Choose first deepest visual of matching class. */
		if (DBEvisInfo->visinfo[i].depth > chosenDepth) {
		    chosenVisual = XvisInfo->visual;
		    chosenDepth = XvisInfo->depth;
		}
	    }
	    else {
		/* Choose last visual of matching depth and class. */
		if (DBEvisInfo->visinfo[i].depth == *pDepth) {
		    chosenVisual = XvisInfo->visual;
		    chosenDepth = XvisInfo->depth;
		}
	    }
	}
    }

    if (chosenVisual) {
	if (listVis) {
	    printf("\n");
	}
	*pDepth = chosenDepth;
	return (chosenVisual);
    }
    else {
	return (NULL);
    }
}

int
main(int argc, char *argv[])
{
    int			i;
    XSetWindowAttributes attrs;
    Visual		*visual;
    Colormap		cmap;
    XGCValues		gcvals;
    fd_set		select_mask;
    int			fd;
    struct timeval	timeout;
    int			new_event;
    int			pending;

    ProgName = argv[0];

    for (i = 1; i < argc; i++) {
	char	   *arg;

	arg = argv[i];
	if (strcmp(arg, "-display") == 0) {
	    if (++i >= argc) {
		fprintf(stderr, "%s: Missing argument to -display\n", ProgName);
		exit(1);
	    }
	    display_name = argv[i];
	} else if (strcmp(arg, "-class") == 0) {
	    arg = argv[++i];
	    if (arg == NULL) {
		fprintf(stderr, "%s: Missing argument to -class\n", ProgName);
		exit(1);
	    }
	    if (strcmp(arg, "True") == 0)
		class = TrueColor;
	    else if (strcmp(arg, "Pseudo") == 0)
		class = PseudoColor;
	    else {
		fprintf(stderr, "%s: Wrong argument %s for -class\n",
					ProgName, arg);
		exit(1);
	    }
	} else if (strcmp(arg, "-depth") == 0) {
	    arg = argv[++i];
	    if (arg == NULL) {
		fprintf(stderr, "%s: Missing argument to -depth\n", ProgName);
		exit(1);
	    }
	    depth = atoi(arg);
	} else if (strcmp(arg, "-help") == 0) {
	    usage();
	} else if (strcmp(arg, "-list") == 0) {
	    listVis = 1;
	} else if (strcmp(arg, "-slow") == 0) {
	    slow = 1;
	} else if (strcmp(arg, "-spokes") == 0) {
	    arg = argv[++i];
	    if (arg == NULL) {
		fprintf(stderr, "%s: Missing argument to -spokes\n", ProgName);
		exit(1);
	    }
	    spokes = atoi(arg);
	} else if (strcmp(arg, "-nodb") == 0) {
	    db = 0;
	} else if (strcmp(arg, "-verbose") == 0) {
	    verbose = 1;
	} else if (strcmp(arg, "-visid") == 0) {
	    arg = argv[++i];
	    if (arg == NULL) {
		fprintf(stderr, "%s: Missing argument to -visid\n", ProgName);
		exit(1);
	    }
	    visid = (int) strtol(arg, (char **)NULL, 0);
	}
	else {
	    fprintf(stderr, "%s: Unrecognized option %s\n", ProgName, arg);
	    usage();
	    exit(1);
	}
    }

    dpy = XOpenDisplay(display_name);
    if (dpy == NULL) {
	fprintf(stderr, "%s: Cannot open display %s\n",
			ProgName, XDisplayName(display_name));
	exit(1);
    }

    if (db) {
	int	majorVersion, minorVersion;

	if (!XdbeQueryExtension (dpy, &majorVersion, &minorVersion)) {
	    fprintf(stderr, "%s: XdbeQueryExtension() failed.\n", ProgName);
	    exit(1);
	}

	if ((visual = choose_DB_visual(dpy, listVis, class, &depth)) == NULL) {
	    fprintf(stderr,
	      "%s: Failed to find matching double buffer capable visual.\n",
	      ProgName);
	    exit(1);
	}
	fprintf(stdout, "%s: Chose visual ID: %#lx depth: %d\n\n",
		ProgName, (unsigned long)visual->visualid, depth);
    }
    else {
	/* No double buffering: ignore class, depth; use default visual. */
	visual = DefaultVisual(dpy, DefaultScreen(dpy));
	depth = DefaultDepth(dpy, DefaultScreen(dpy));
    }

    cmap = XCreateColormap(dpy, DefaultRootWindow(dpy), visual, AllocNone);
    black = getColor(cmap, "black");
    pink = getColor(cmap, "pink");
    green = getColor(cmap, "green");
    orange = getColor(cmap, "orange");
    blue = getColor(cmap, "blue");
    attrs.colormap = cmap;
    attrs.background_pixel = black;
    attrs.border_pixel = black;
    win = XCreateWindow(dpy, DefaultRootWindow(dpy), 10, 10, width, height,
			0, depth, InputOutput, visual,
			CWBorderPixel | CWColormap | CWBackPixel, &attrs);
    XSetStandardProperties(dpy, win, "DBE dizzy demo", ProgName, None,
			   argv, argc, NULL);
    XSelectInput(dpy, win,
	VisibilityChangeMask | ExposureMask | ButtonPressMask | KeyPressMask |
		StructureNotifyMask);
    if (db) {
	swapInfo.swap_action = XdbeBackground;
	buf = XdbeAllocateBackBufferName (dpy, win, swapInfo.swap_action);
	if (buf == None) {
	    fprintf(stderr, "%s: Couldn't create buffers\n", ProgName);
	    exit(1);
	}
	else {
	    swapInfo.swap_window = win;
	}
    }
    else {
	buf = win;		/* No double buffering. */
    }

    gcvals.line_width = 8;
    gcvals.cap_style = CapRound;
    gc = XCreateGC(dpy, win, GCLineWidth | GCCapStyle, &gcvals);

    XMapWindow(dpy, win);

    fd = ConnectionNumber(dpy);
    FD_ZERO(&select_mask);
    FD_SET(fd, &select_mask);

    while (1) {
	XEvent	  event;

	if (!paused && !manual_paused) {
	    pending = XEventsQueued(dpy, QueuedAfterFlush);
	    if (pending == 0) {
		do {
		    XFlush(dpy);
		    FD_ZERO(&select_mask);
		    FD_SET(fd, &select_mask);
		    if (slow) {
			timeout.tv_sec = 2;
			timeout.tv_usec = 0;
		    } else {
			timeout.tv_sec = 0;
			timeout.tv_usec = 100000;
		    }
		    new_event =
			select(fd + 1, &select_mask, NULL, NULL, &timeout);
		    rotation = rotation + delta;
		    redraw();
		} while (new_event == 0);
	    }
	}
	XNextEvent(dpy, &event);
	switch (event.type) {
	case MapNotify:
	    if (verbose)
		printf("mapping...\n");
	    paused = 0;
	    break;
	case UnmapNotify:
	    if (verbose)
		printf("unmapping...\n");
	    paused = 1;
	    break;
	case VisibilityNotify:
	    switch (event.xvisibility.state) {
	    case VisibilityUnobscured:
	    case VisibilityPartiallyObscured:
		if (verbose)
		    printf("resuming...\n");
		paused = 0;
		break;
	    case VisibilityFullyObscured:
		if (verbose)
		    printf("pausing...\n");
		paused = 1;
		break;
	    }
	    break;
	case Expose:
	    if (verbose)
		printf("expose.\n");
	    while (XCheckTypedEvent(dpy, Expose, &event));
	    redraw();
	    break;
	case ButtonPress:
	    switch (event.xbutton.button) {
	    case 1:
		printf("faster: %g\n", delta);
		delta += 0.005;
		break;
	    case 2:
		printf("slower: %g\n", delta);
		delta += -0.005;
		break;
	    case 3:
		if (manual_paused) {
		    printf("manual resume.\n");
		    manual_paused = 0;
		} else {
		    printf("manual pause.\n");
		    manual_paused = 1;
		}
	    }
	    break;
	case KeyPress:
	    printf("done.\n");
	    exit(1);
	    break;
	case ConfigureNotify:
	    if (verbose) {
		printf("resizing.\n");
	    }
	    width = event.xconfigure.width;
	    height = event.xconfigure.height;
	    break;
	}
    }
}
