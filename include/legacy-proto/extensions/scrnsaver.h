/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _SCRNSAVER_H_
#define _SCRNSAVER_H_

#include <X11/Xfuncproto.h>
#include <X11/extensions/saver.h>

typedef struct {
    int	type;		    /* of event */
    unsigned long serial;   /* # of last request processed by server */
    Bool send_event;	    /* true if this came frome a SendEvent request */
    Display *display;	    /* Display the event was read from */
    Window window;	    /* screen saver window */
    Window root;	    /* root window of event screen */
    int state;		    /* ScreenSaverOff, ScreenSaverOn, ScreenSaverCycle*/
    int kind;		    /* ScreenSaverBlanked, ...Internal, ...External */
    Bool forced;	    /* extents of new region */
    Time time;		    /* event timestamp */
} XScreenSaverNotifyEvent;

typedef struct {
    Window  window;	    /* screen saver window - may not exist */
    int	    state;	    /* ScreenSaverOff, ScreenSaverOn, ScreenSaverDisabled*/
    int	    kind;	    /* ScreenSaverBlanked, ...Internal, ...External */
    unsigned long    til_or_since;   /* time til or since screen saver */
    unsigned long    idle;	    /* total time since last user input */
    unsigned long   eventMask; /* currently selected events for this client */
} XScreenSaverInfo;

_XFUNCPROTOBEGIN

extern Bool XScreenSaverQueryExtension (
    Display*	/* display */,
    int*	/* event_base */,
    int*	/* error_base */
);

extern Status XScreenSaverQueryVersion (
    Display*	/* display */,
    int*	/* major_version */,
    int*	/* minor_version */
);

extern XScreenSaverInfo *XScreenSaverAllocInfo (
    void
);

extern Status XScreenSaverQueryInfo (
    Display*		/* display */,
    Drawable		/* drawable */,
    XScreenSaverInfo*	/* info */
);

extern void XScreenSaverSelectInput (
    Display*	/* display */,
    Drawable	/* drawable */,
    unsigned long   /* eventMask */
);

extern void XScreenSaverSetAttributes (
    Display*		    /* display */,
    Drawable		    /* drawable */,
    int			    /* x */,
    int			    /* y */,
    unsigned int	    /* width */,
    unsigned int	    /* height */,
    unsigned int	    /* border_width */,
    int			    /* depth */,
    unsigned int	    /* class */,
    Visual *		    /* visual */,
    unsigned long	    /* valuemask */,
    XSetWindowAttributes *  /* attributes */
);

extern void XScreenSaverUnsetAttributes (
    Display*	/* display */,
    Drawable	/* drawable */
);

extern Status XScreenSaverRegister (
    Display*	/* display */,
    int		/* screen */,
    XID		/* xid */,
    Atom	/* type */
);

extern Status XScreenSaverUnregister (
    Display*	/* display */,
    int		/* screen */
);

extern Status XScreenSaverGetRegistered (
    Display*	/* display */,
    int		/* screen */,
    XID*	/* xid */,
    Atom*	/* type */
);

_XFUNCPROTOEND

#endif /* _SCRNSAVER_H_ */
