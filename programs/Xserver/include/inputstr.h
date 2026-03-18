/************************************************************

Copyright 1987, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.


Copyright 1987 by Digital Equipment Corporation, Maynard, Massachusetts.

                        All Rights Reserved

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

********************************************************/


#ifndef INPUTSTRUCT_H
#define INPUTSTRUCT_H

#include "input.h"
#include "window.h"
#include "cursorstr.h"
#include <pixman.h>
#include "dixstruct.h"

#define BitIsOn(ptr, bit) (((BYTE *) (ptr))[(bit)>>3] & (1 << ((bit) & 7))

#define SameClient(obj,client) \
	(CLIENT_BITS((obj)->resource) == (client)->clientAsMask)

#define MAX_DEVICES	20

/* Device type constants for device->type */
#define MASTER_POINTER 1
#define MASTER_KEYBOARD 2
#define SLAVE 3

/* Maximum number of event types */
#define MAXEVENTS 128

/* Additional device type constants */
#define MASTER_ATTACHED 4
#define POINTER_OR_FLOAT 5
#define KEYBOARD_OR_FLOAT 6

/* SpriteInfo - for tracking pointer sprite and device pairing */
typedef struct _SpriteInfo {
    SpritePtr sprite;
    Bool spriteOwner;
    DeviceIntPtr paired;
} SpriteInfoRec, *SpriteInfoPtr;

/* Legacy device grab tracking */
typedef struct _DeviceGrabRec {
    GrabPtr grab;
    Bool fromPassiveGrab;
    TimeStamp timestamp;
    WindowPtr window;
    int state;
    /* Additional members needed for XI2 compatibility */
    TimeStamp grabTime;
    void (*ActivateGrab)(DeviceIntPtr device, GrabPtr grab, TimeStamp time, Bool autoGrab);
    void (*DeactivateGrab)(DeviceIntPtr device);
    struct {
        Bool frozen;
        int state;
        GrabPtr other;
        xEvent *event;
        int evcount;
    } sync;
} DeviceGrabRec;

#define EMASKSIZE	MAX_DEVICES

extern int CoreDevicePrivatesIndex;

/* Kludge: OtherClients and InputClients must be compatible, see code */

typedef struct _OtherClients {
    OtherClientsPtr	next;
    XID			resource; /* id for putting into resource manager */
    Mask		mask;
} OtherClients;

typedef struct _InputClients {
    InputClientsPtr	next;
    XID			resource; /* id for putting into resource manager */
    Mask		mask[EMASKSIZE];
    void		*xi2mask; /* XI2 event mask */
} InputClients;

typedef struct _OtherInputMasks {
    Mask		deliverableEvents[EMASKSIZE];
    Mask		inputEvents[EMASKSIZE];
    Mask		dontPropagateMask[EMASKSIZE];
    InputClientsPtr	inputClients;
    void		*xi2mask; /* XI2 event mask */
} OtherInputMasks;

/*
 * The following structure gets used for both active and passive grabs. For
 * active grabs some of the fields (e.g. modifiers) are not used. However,
 * that is not much waste since there aren't many active grabs (one per
 * keyboard/pointer device) going at once in the server.
 */

#define MasksPerDetailMask 8		/* 256 keycodes and 256 possible
                                           modifier combinations, but only	
                                           3 buttons. */

typedef struct _DetailRec {		/* Grab details may be bit masks */
    unsigned short      exact;
    Mask                *pMask;
} DetailRec;

typedef struct _GrabRec {
    GrabPtr		next;		/* for chain of passive grabs */
    XID			resource;
    DeviceIntPtr	device;
    WindowPtr		window;
    unsigned		ownerEvents:1;
    unsigned		keyboardMode:1;
    unsigned		pointerMode:1;
    unsigned		coreGrab:1;	/* grab is on core device */
    unsigned		coreMods:1;	/* modifiers are on core keyboard */
    CARD8		type;		/* event type */
    DetailRec		modifiersDetail;
    DeviceIntPtr	modifierDevice;
    DetailRec		detail;		/* key or button */
    WindowPtr		confineTo;	/* always NULL for keyboards */
    CursorPtr		cursor;		/* always NULL for keyboards */
    Mask		eventMask;
} GrabRec;

typedef struct _KeyClassRec {
    CARD8		down[DOWN_LENGTH];
    CARD8		postdown[DOWN_LENGTH];
    KeyCode 		*modifierKeyMap;
    KeySymsRec		curKeySyms;
    int			modifierKeyCount[8];
    CARD8		modifierMap[MAP_LENGTH];
    CARD8		maxKeysPerModifier;
    unsigned short	state;
    unsigned short	prev_state;
#ifdef XKB
    struct _XkbSrvInfo *xkbInfo;
#else
    struct _XkbSrvInfo *xkbInfo;  /* Backward compat - always available */
#endif
} KeyClassRec;
#ifndef KeyClassPtr
#define KeyClassPtr KeyClassRec *
#endif

typedef struct _AxisInfo {
    int		resolution;
    int		min_resolution;
    int		max_resolution;
    int		min_value;
    int		max_value;
    int             mode;           /* Relative or Absolute */
    Atom            label;          /* axis label */
    union {
        struct {
            int increment;
            int type;           /* SCROLL_TYPE_* */
        } scroll;
    } scroll;
} AxisInfo, *AxisInfoPtr;

/* Forward declarations - defined in ptrveloc.h */
typedef void (*AccelSchemeProcPtr)(DeviceIntPtr /*pDev*/, int /*first_valuator*/,
                                    int /*num_valuators*/, int */*valuators*/, int /*evtime*/);
typedef Bool (*AccelInitProcPtr)(DeviceIntPtr /*dev*/, void */*scheme*/);
typedef void (*AccelCleanupProcPtr)(DeviceIntPtr /*dev*/);

/* Valuator acceleration scheme record */
typedef struct _ValuatorAccelerationRec {
    int number;
    AccelSchemeProcPtr AccelSchemeProc;
    void *accelData;
    AccelInitProcPtr AccelInitProc;
    AccelCleanupProcPtr AccelCleanupProc;
} ValuatorAccelerationRec, *ValuatorAccelerationPtr;

/* Legacy last device info for tracking previous coordinates */
/* Forward declaration - actual definition below */
/* Forward declarations - only if not already defined */
/* ssX: Use _TOUCHPOINTINFOPTR guard to match dix.h definition */
#ifndef _TOUCHPOINTINFOPTR
typedef struct _TouchPointInfoRec *TouchPointInfoPtr;
#define _TOUCHPOINTINFOPTR
#endif

#ifndef _DEFINED_DDXTouchPointInfoPtr
typedef struct _DDXTouchPointInfoRec *DDXTouchPointInfoPtr;
#define _DEFINED_DDXTouchPointInfoPtr 1
#endif

typedef struct _LastDeviceInfo {
    int valuators[MAX_VALUATORS];          /* previous valuator values */
    float remainder[2];                    /* fractional remainders for acceleration */
    int numValuators;
    /* XI2 compatibility members */
    struct {
        int value;
        int type;
    } scroll[MAX_VALUATORS];
    /* ssX: Touch support */
    int num_touches;
    DDXTouchPointInfoPtr *touches;  /* array of active touch points */
    /* Master/slave tracking for XI2 */
    DeviceIntPtr slave;
} LastDeviceInfo, *LastDeviceInfoPtr;

typedef struct _ValuatorClassRec {
    ValuatorAccelerationRec accelScheme;
    ValuatorMotionProcPtr GetMotionProc;
    int		 	  numMotionEvents;
    int                   first_motion;
    int                   last_motion;
    void                  *motion;

    WindowPtr    	  motionHintWindow;

    AxisInfoPtr 	  axes;
    unsigned short	  numAxes;
    int			  *axisVal;
    int                   lastx, lasty; /* last event recorded, not posted to
                                         * client; see dix/devices.c */
    int                   dxremaind, dyremaind; /* for acceleration */
    CARD8	 	  mode;
} ValuatorClassRec;
#ifndef ValuatorClassPtr
#define ValuatorClassPtr ValuatorClassRec *
#endif

typedef struct _ButtonClassRec {
    CARD8		numButtons;
    CARD8		buttonsDown;	/* number of buttons currently down */
    unsigned short	state;
    Mask		motionMask;
    CARD8		down[DOWN_LENGTH];
    CARD8		postdown[DOWN_LENGTH];	/* buttons posted to client */
    CARD8		map[MAP_LENGTH];
    Atom		labels[MAX_BUTTONS];
#ifdef XKB
    union _XkbAction    *xkb_acts;
#else
    void                *pad0;
#endif
    unsigned int	sourceid;
} ButtonClassRec;
#ifndef ButtonClassPtr
#define ButtonClassPtr ButtonClassRec *
#endif

typedef struct _FocusClassRec {
    WindowPtr	win;
    int		revert;
    TimeStamp	time;
    WindowPtr	*trace;
    int		traceSize;
    int		traceGood;
} FocusClassRec;
#ifndef FocusClassPtr
#define FocusClassPtr FocusClassRec *
#endif

typedef struct _ProximityClassRec {
    char	pad;
} ProximityClassRec;
#ifndef ProximityClassPtr
#define ProximityClassPtr ProximityClassRec *
#endif

typedef struct _AbsoluteClassRec {
    /* Calibration. */
    int         min_x;
    int         max_x;
    int         min_y;
    int         max_y;
    int         flip_x;
    int         flip_y;
    int		rotation;
    int         button_threshold;

    /* Area. */
    int         offset_x;
    int         offset_y;
    int         width;
    int         height;
    int         screen;
    XID		following;
} AbsoluteClassRec, *AbsoluteClassPtr;

#ifndef _KBDFEEDBACKPTR_TYPEDEF
#define _KBDFEEDBACKPTR_TYPEDEF
typedef struct _KbdFeedbackClassRec *KbdFeedbackPtr;
#endif

#ifndef _PTRFEEDBACKPTR_TYPEDEF
#define _PTRFEEDBACKPTR_TYPEDEF
typedef struct _PtrFeedbackClassRec *PtrFeedbackPtr;
#endif

#ifndef _INTEGERFEEDBACKPTR_TYPEDEF
#define _INTEGERFEEDBACKPTR_TYPEDEF
typedef struct _IntegerFeedbackClassRec *IntegerFeedbackPtr;
#endif

#ifndef _STRINGFEEDBACKPTR_TYPEDEF
#define _STRINGFEEDBACKPTR_TYPEDEF
typedef struct _StringFeedbackClassRec *StringFeedbackPtr;
#endif

#ifndef _BELLFEEDBACKPTR_TYPEDEF
#define _BELLFEEDBACKPTR_TYPEDEF
typedef struct _BellFeedbackClassRec *BellFeedbackPtr;
#endif

#ifndef _LEDFEEDBACKPTR_TYPEDEF
#define _LEDFEEDBACKPTR_TYPEDEF
typedef struct _LedFeedbackClassRec *LedFeedbackPtr;
#endif

typedef struct _KbdFeedbackClassRec {
    BellProcPtr		BellProc;
    KbdCtrlProcPtr	CtrlProc;
    KeybdCtrl	 	ctrl;
    KbdFeedbackPtr	next;
#ifdef XKB
    struct _XkbSrvLedInfo *xkb_sli;
#else
    void                *pad0;
#endif
} KbdFeedbackClassRec;

typedef struct _PtrFeedbackClassRec {
    PtrCtrlProcPtr	CtrlProc;
    PtrCtrl		ctrl;
    PtrFeedbackPtr	next;
} PtrFeedbackClassRec;

typedef struct _IntegerFeedbackClassRec {
    IntegerCtrlProcPtr	CtrlProc;
    IntegerCtrl	 	ctrl;
    IntegerFeedbackPtr	next;
} IntegerFeedbackClassRec;

typedef struct _StringFeedbackClassRec {
    StringCtrlProcPtr	CtrlProc;
    StringCtrl	 	ctrl;
    StringFeedbackPtr	next;
} StringFeedbackClassRec;

typedef struct _BellFeedbackClassRec {
    BellProcPtr		BellProc;
    BellCtrlProcPtr	CtrlProc;
    BellCtrl	 	ctrl;
    BellFeedbackPtr	next;
} BellFeedbackClassRec;

typedef struct _LedFeedbackClassRec {
    LedCtrlProcPtr	CtrlProc;
    LedCtrl	 	ctrl;
    LedFeedbackPtr	next;
#ifdef XKB
    struct _XkbSrvLedInfo *xkb_sli;
#else
    void                *pad0;
#endif
} LedFeedbackClassRec;

/* Touch class - for touchscreen/touchpad support */
/* Only define struct if not already defined */
#ifndef _DDXTOUCHPOINTINFOREC_DEFINED
#define _DDXTOUCHPOINTINFOREC_DEFINED
typedef struct _DDXTouchPointInfoRec {
    int x, y;
    WindowPtr win;
    Bool active;
    int ddx_id;
    TimeStamp timestamp;
    /* Additional fields for touch tracking */
    void *private;
    /* ssX: XI2 compatibility */
    XID client_id;
    Bool emulate_pointer;
} DDXTouchPointInfoRec;
#endif

/* Pointer type - only define if not already defined */
/* ssX: DDXTouchPointInfoPtr already defined above with _DEFINED_DDXTouchPointInfoPtr guard */
#ifndef _DDXTOUCHPOINTINFOPTR_TYPEDEF
#define _DDXTOUCHPOINTINFOPTR_TYPEDEF
/* Pointer typedef deferred to forward declaration above */
#endif

#ifndef _TOUCHPOINTINFOREC_DEFINED
#define _TOUCHPOINTINFOREC_DEFINED
typedef struct _TouchPointInfoRec {
    int id;
    int ddx_id;
    Bool active;
    Bool emulated_ptr;
    TimeStamp start;
    WindowPtr win;
    WindowPtr emulatedWin;
    int num_listeners;
    struct {
        DeviceIntPtr *listeners;
        int num_listeners;
    } listeners;
    int remaining_reason;
    DDXTouchPointInfoPtr ddx_info;
    /* ssX: XI2 compatibility */
    void *valuators;
    void *sprite;
} TouchPointInfoRec;
/* ssX: TouchPointInfoPtr already defined above with _TOUCHPOINTINFOPTR guard */

typedef struct _TouchClassRec {
    TouchPointInfoPtr *touches;
    int num_touches;
    int max_touches;
    /* Touch mode - relative or absolute */
    int mode;
    /* For tracking touch ownership */
    TimeStamp *first_touch;
} TouchClassRec;
#ifndef TouchClassPtr
#define TouchClassPtr TouchClassRec *
#endif

/* states for devices */

#define NOT_GRABBED		0
#define THAWED			1
#define THAWED_BOTH		2	/* not a real state */
#define FREEZE_NEXT_EVENT	3
#define FREEZE_BOTH_NEXT_EVENT	4
#define FROZEN			5	/* any state >= has device frozen */
#define FROZEN_NO_EVENT		5
#define FROZEN_WITH_EVENT	6
#define THAW_OTHERS		7

typedef struct _DeviceIntRec {
    DeviceRec	public;
    DeviceIntPtr next;
    LastDeviceInfo       last; /* legacy tracking for previous coordinate states */
    DeviceGrabRec       deviceGrab; /* legacy device grab tracking */
    TimeStamp	grabTime;
    void               *idle_counter;  /* XI2 idle counter */
    Bool	startup;		/* true if needs to be turned on at
				          server intialization time */
    DeviceProc	deviceProc;		/* proc(DevicePtr, DEVICE_xx). It is
					  used to initialize, turn on, or
					  turn off the device */
    Bool	inited;			/* TRUE if INIT returns Success */
    Bool        enabled;                /* TRUE if ON returns Success */
    Bool        coreEvents;             /* TRUE if device also sends core */
    GrabPtr	grab;			/* the grabber - used by DIX */
    struct {
	Bool		frozen;
	int		state;
	GrabPtr		other;		/* if other grab has this frozen */
	xEvent		*event;		/* saved to be replayed */
	int		evcount;
    } sync;
    Atom		type;
    char		*name;
    CARD8		id;
    CARD8		activatingKey;
    Bool		fromPassiveGrab;
    GrabRec		activeGrab;
    void		(*ActivateGrab) (
			DeviceIntPtr /*device*/,
			GrabPtr /*grab*/,
			TimeStamp /*time*/,
			Bool /*autoGrab*/);
    void		(*DeactivateGrab)(
			DeviceIntPtr /*device*/);
    KeyClassPtr		key;
    ValuatorClassPtr	valuator;
    ButtonClassPtr	button;
    FocusClassPtr	focus;
    ProximityClassPtr	proximity;
    AbsoluteClassPtr    absolute;
    KbdFeedbackPtr	kbdfeed;
    PtrFeedbackPtr	ptrfeed;
    IntegerFeedbackPtr	intfeed;
    StringFeedbackPtr	stringfeed;
    BellFeedbackPtr	bell;
    LedFeedbackPtr	leds;
    TouchClassPtr	touch;		/* Touch device class */
#ifdef XKB
    struct _XkbInterest *xkb_interest;
#else
    void                *pad0;
#endif
    char                *config_info; /* used by the hotplug layer */
    DevUnion		*devPrivates;
    int			nPrivates;
    DeviceUnwrapProc    unwrapProc;
    struct pixman_f_transform relative_transform;
	struct pixman_f_transform transform;
    struct pixman_f_transform scale_and_transform;
    /* Master/slave device tracking */
    DeviceIntPtr master;         /* master device if this is a slave */
    DeviceIntPtr lastSlave;      /* last attached slave device */
    /* Sprite for cursor tracking */
    SpriteInfoPtr spriteInfo;
} DeviceIntRec;

typedef struct {
    int			numDevices;	/* total number of devices */
    DeviceIntPtr	devices;	/* all devices turned on */
    DeviceIntPtr	off_devices;	/* all devices turned off */
    DeviceIntPtr	keyboard;	/* the main one for the server */
    DeviceIntPtr	pointer;
} InputInfo;

extern InputInfo inputInfo;

/* for keeping the events for devices grabbed synchronously */
typedef struct _QdEvent *QdEventPtr;
typedef struct _QdEvent {
    QdEventPtr		next;
    DeviceIntPtr	device;
    ScreenPtr		pScreen;	/* what screen the pointer was on */
    unsigned long	months;		/* milliseconds is in the event */
    xEvent		*event;
    int			evcount;
} QdEventRec;    

#endif /* INPUTSTRUCT_H */
