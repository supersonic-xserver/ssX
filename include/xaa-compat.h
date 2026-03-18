/*
 * XAA Compatibility Adapter Layer
 * 
 * This header provides backward compatibility definitions for XAA code
 * that was written for XFree86 to work with modern Xorg headers.
 * 
 * IMPORTANT: This header should be included AFTER all standard X server
 * headers (dix.h, input.h, etc.) to provide additional compatibility
 * macros without redefining existing types.
 * 
 * The X server headers already define: ScreenPtr, WindowPtr, DrawablePtr,
 * GCPtr, DeviceIntPtr, ValuatorMask, TimeStamp, ClientPtr, etc.
 * This file provides macros and additional definitions only.
 */

#ifndef XAA_COMPAT_H
#define XAA_COMPAT_H

/* Provide xorg_list typedef if not available */
#ifndef _XORG_LIST_T
#define _XORG_LIST_T
typedef struct xorg_list xorg_list;
#endif

/* Define MAXDEVICES if not already defined */
#ifndef MAXDEVICES
#define MAXDEVICES 256
#endif

/* Define MAXEVENTS if not already defined */
#ifndef MAXEVENTS
#define MAXEVENTS 128
#endif

/* Screen position - for older multi-screen XAA code */
#ifndef ScreenGetPage
#define screenInfoNumScreens screenInfo.numScreens
#define screenInfoScreens(i) screenInfo.screens[i]
#endif

/* Define EXTENSION_BASE for extensions */
#ifndef EXTENSION_BASE
#define EXTENSION_BASE 128
#endif

/* Define EXTENSION_EVENT_BASE for extension events */
#ifndef EXTENSION_EVENT_BASE  
#define EXTENSION_EVENT_BASE 64
#endif

/* Touch event types - ssX uses these for internal event handling */
#ifndef ET_TouchBegin
#define ET_TouchBegin 35
#define ET_TouchUpdate 36
#define ET_TouchEnd 37
#endif

#ifndef ET_RawTouchBegin
#define ET_RawTouchBegin 38
#define ET_RawTouchUpdate 39
#define ET_RawTouchEnd 40
#endif

#ifndef ET_TouchOwnership
#define ET_TouchOwnership 41
#endif

/* Scroll types */
#ifndef SCROLL_TYPE_NONE
#define SCROLL_TYPE_NONE 0
#define SCROLL_TYPE_VERTICAL 1
#define SCROLL_TYPE_HORIZONTAL 2
#endif

/* Screen->root compatibility for XAA code */
#ifndef ScreenGetRoot
#define ScreenGetRoot(pScreen) WindowTable[(pScreen)->myNum]
#endif

/* Backward compatibility for event sync macros */
#define syncEventsPlayingEvents (syncEvents.playingEvents)
#define syncEventsTime (syncEvents.time)

#endif /* XAA_COMPAT_H */
