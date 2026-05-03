/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef SITE_H
#define SITE_H 1

/*
 * Xtrans transport macros - must be defined BEFORE including X11/Xtrans/Xtrans.h
 * These tell xtrans that we're building the server, not a client
 */
#define TRANS_SERVER
#define XSERV_t

/*
 * Legacy extension initialization macro from NetBSD 5.2.3
 * This handles the different ways extensions were initialized in 2009
 */
#ifndef INITARGS
#define INITARGS void
#endif

/*
 * XFree86 Version Information
 * These values define the server as XFree86 4.8.0
 */
#define VENDOR_RELEASE 40800000
#define VENDOR_STRING "XFree86 4.8.0 (Super Sonic X)"
#define VENDOR_NAME "The XFree86 Project"

/*
 * Legacy build mode flag
 * Set when building in XFree86 4.8.0 compatibility mode
 */
#ifdef SSX_LEGACY_MODE
#define SSX_LEGACY_BUILD 1
#endif

/*
 * Legacy Input Defaults restored from NetBSD 5.2.3 xsrc/xc
 * These were traditionally handled by imake or site.def in the XFree86 build
 */
#ifndef DEFAULT_LEDS
#define DEFAULT_LEDS           0
#define DEFAULT_LEDS_MASK      0
#define DEFAULT_BELL           50
#define DEFAULT_BELL_PITCH     400
#define DEFAULT_BELL_DURATION  100
#define DEFAULT_INT_RESOLUTION 1000
#define DEFAULT_INT_MIN_VALUE  0
#define DEFAULT_INT_MAX_VALUE  100
#define DEFAULT_INT_DISPLAYED  0
#endif

/*
 * Legacy Keyboard Defaults
 */
#ifndef DEFAULT_KEYBOARD_CLICK
#define DEFAULT_KEYBOARD_CLICK 0
#endif

#ifndef DEFAULT_AUTOREPEAT
#define DEFAULT_AUTOREPEAT 1
#endif

#ifndef DEFAULT_AUTOREPEATS
#define DEFAULT_AUTOREPEATS 24
#endif

/*
 * Legacy Mouse/Pointer Defaults  
 */
#ifndef DEFAULT_PTR_NUMERATOR
#define DEFAULT_PTR_NUMERATOR 1
#endif

#ifndef DEFAULT_PTR_DENOMINATOR  
#define DEFAULT_PTR_DENOMINATOR 1
#endif

#ifndef DEFAULT_PTR_THRESHOLD
#define DEFAULT_PTR_THRESHOLD 4
#endif

/*
 * Legacy Screen Saver Defaults
 */
#ifndef DEFAULT_SCREEN_SAVER_TIME
#define DEFAULT_SCREEN_SAVER_TIME 600000
#endif

#ifndef DEFAULT_SCREEN_SAVER_INTERVAL
#define DEFAULT_SCREEN_SAVER_INTERVAL 10000
#endif

#ifndef DEFAULT_SCREEN_SAVER_BLANKING
#define DEFAULT_SCREEN_SAVER_BLANKING 2
#endif

#ifndef DEFAULT_SCREEN_SAVER_MODE
#define DEFAULT_SCREEN_SAVER_MODE 2
#endif

#ifndef DEFAULT_SCREEN_SAVER_EXPOSURES
#define DEFAULT_SCREEN_SAVER_EXPOSURES  1
#endif

#ifndef DEFAULT_LOGO_SCREEN_SAVER
#define DEFAULT_LOGO_SCREEN_SAVER       1
#endif

/*
 * Access Control Default
 * Standard X11 access control setting - enabled by default
 */
#ifndef DEFAULT_ACCESS_CONTROL
#define DEFAULT_ACCESS_CONTROL TRUE
#endif

#ifndef COMPILEDDEFAULTFONTPATH
#define COMPILEDDEFAULTFONTPATH "/usr/share/fonts/X11/misc/,/usr/share/fonts/X11/75dpi/:unscaled"
#endif

/* Cast away const for legacy header compatibility */
#define COMPILEDDEFAULTFONTPATH_MUTABLE ((char *)COMPILEDDEFAULTFONTPATH)

#ifndef COMPILEDDEFAULTFONT
#define COMPILEDDEFAULTFONT "fixed"
#endif

#ifndef COMPILEDCURSORFONT
#define COMPILEDCURSORFONT "cursor"
#endif

#ifndef COMPILEDDISPLAYCLASS
#define COMPILEDDISPLAYCLASS "XFree86"
#endif

/* RGB_DB: Undef before define to prevent warning from dix-config.h */
#undef RGB_DB
#ifndef RGB_DB
#define RGB_DB "/usr/share/X11/rgb"
#endif

#ifndef DEFAULT_TIMEOUT
#define DEFAULT_TIMEOUT 60
#endif

/*
 * 
 * End of site-specific definitions
 *****************************************************************/

#endif /* SITE_H */
/* Stub for DeviceUnwrapProc - modern XKB type not available in legacy build */
typedef void (*DeviceUnwrapProc)(void);
