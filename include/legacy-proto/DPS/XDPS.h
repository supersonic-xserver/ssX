/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XDPS_h
#define _XDPS_h

#include <X11/Xmd.h>

/*
 * Number of events and errors required by extension
 */
#define NPSEVENTS		3               /* L2-DPS/PROTO 9 change */
#define NPSERRORS		3               /* L2-DPS/PROTO 9 change */

#define NPSEVENTS_P8		2
#define NPSERRORS_P8		2


/*
 * For XPSNotifyContext: types of notification.
 */

#define PSKILL			0
#define PSINTERRUPT		1
#define PSUNFREEZE		2


/*
 * For XPSGetStatus: types of status.
 */

#define PSSTATUSERROR		0
#define PSRUNNING		1
#define PSNEEDSINPUT		2
#define PSZOMBIE		3
#define PSFROZEN		4

#define PSNUMSTATUS		4 /* Number of real status codes */

/*
 * For XPSSetStatusMask: Status Masks
 */

#define PSRUNNINGMASK           0x0001
#define PSNEEDSINPUTMASK        0x0002
#define PSZOMBIEMASK            0x0004
#define PSFROZENMASK            0x0008


/*
 * Error codes (offset from extension error base)
 */

#define PSERRORBADCONTEXT	0
#define PSERRORBADSPACE		1
#define PSERRORABORT		2             /* L2-DPS/PROTO 9 addition */


/*
 * Event codes (offset from extension event base)
 */

#define PSEVENTOUTPUT		0
#define PSEVENTSTATUS		1
#define PSEVENTREADY		2             /* L2-DPS/PROTO 9 addition */


/*
 * Request field types
 */

typedef int	 ContextPSID;
typedef XID	 ContextXID;
typedef XID	 SpaceXID;


/*
 * Floating point types (the same as in dpsfriends.h).
 */

#ifndef DPS_HI_IEEE

#define DPS_HI_IEEE	128
#define DPS_LO_IEEE	129
#define DPS_HI_NATIVE	130
#define DPS_LO_NATIVE	131

#endif /* not DPS_HI_IEEE */

#endif /* _XDPS_h */
