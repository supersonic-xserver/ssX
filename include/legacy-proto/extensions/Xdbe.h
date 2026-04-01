/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef XDBE_H
#define XDBE_H


/* INCLUDES */

#include <X11/Xfuncproto.h>
#include <X11/extensions/Xdbeproto.h>


/* DEFINES */

/* Errors */
#define XdbeBadBuffer    0


/* TYPEDEFS */

typedef Drawable XdbeBackBuffer;

typedef unsigned char XdbeSwapAction;

typedef struct
{
    Window		swap_window;    /* window for which to swap buffers   */
    XdbeSwapAction	swap_action;    /* swap action to use for swap_window */
}
XdbeSwapInfo;

typedef struct
{
    Window	window;			/* window that buffer belongs to */
}
XdbeBackBufferAttributes;

typedef struct
{
    int			type;
    Display		*display;	/* display the event was read from */
    XdbeBackBuffer	buffer;		/* resource id                     */
    unsigned long	serial;		/* serial number of failed request */
    unsigned char	error_code;	/* error base + XdbeBadBuffer      */
    unsigned char	request_code;	/* major opcode of failed request  */
    unsigned char	minor_code;	/* minor opcode of failed request  */
}
XdbeBufferError;

/* _XFUNCPROTOBEGIN and _XFUNCPROTOEND are defined as noops
 * (for non-C++ builds) in X11/Xfuncproto.h.
 */
_XFUNCPROTOBEGIN

extern Status XdbeQueryExtension(
    Display*		/* dpy                  */,
    int*		/* major_version_return */,
    int*		/* minor_version_return */
);

extern XdbeBackBuffer XdbeAllocateBackBufferName(
    Display*		/* dpy         */,
    Window		/* window      */,
    XdbeSwapAction	/* swap_action */
);

extern Status XdbeDeallocateBackBufferName(
    Display*		/* dpy    */,
    XdbeBackBuffer	/* buffer */
);

extern Status XdbeSwapBuffers(
    Display*		/* dpy         */,
    XdbeSwapInfo*	/* swap_info   */,
    int			/* num_windows */
);

extern Status XdbeBeginIdiom(
    Display*		/* dpy */
);

extern Status XdbeEndIdiom(
    Display*		/* dpy */
);

extern XdbeScreenVisualInfo *XdbeGetVisualInfo(
    Display*		/* dpy               */,
    Drawable*		/* screen_specifiers */,
    int*		/* num_screens       */
);

extern void XdbeFreeVisualInfo(
    XdbeScreenVisualInfo*	/* visual_info */
);

extern XdbeBackBufferAttributes *XdbeGetBackBufferAttributes(
    Display*		/* dpy    */,
    XdbeBackBuffer	/* buffer */
);

_XFUNCPROTOEND

#endif /* XDBE_H */

