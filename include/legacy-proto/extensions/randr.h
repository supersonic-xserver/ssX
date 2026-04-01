/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _RANDR_H_
#define _RANDR_H_

typedef unsigned short	Rotation;
typedef unsigned short	SizeID;
typedef unsigned short	SubpixelOrder;

#define RANDR_NAME		"RANDR"
#define RANDR_MAJOR		1
#define RANDR_MINOR		1

#define RRNumberErrors		0
#define RRNumberEvents		1

#define X_RRQueryVersion	0
/* we skip 1 to make old clients fail pretty immediately */
#define X_RROldGetScreenInfo	1
#define X_RR1_0SetScreenConfig	2
/* V1.0 apps share the same set screen config request id */
#define X_RRSetScreenConfig	2
#define X_RROldScreenChangeSelectInput	3
/* 3 used to be ScreenChangeSelectInput; deprecated */
#define X_RRSelectInput		4
#define X_RRGetScreenInfo	5

/* used in XRRSelectInput */

#define RRScreenChangeNotifyMask  (1L << 0)

#define RRScreenChangeNotify	0

/* used in the rotation field; rotation and reflection in 0.1 proto. */
#define RR_Rotate_0		1
#define RR_Rotate_90		2
#define RR_Rotate_180		4
#define RR_Rotate_270		8

/* new in 1.0 protocol, to allow reflection of screen */

#define RR_Reflect_X		16
#define RR_Reflect_Y		32

#define RRSetConfigSuccess		0
#define RRSetConfigInvalidConfigTime	1
#define RRSetConfigInvalidTime		2
#define RRSetConfigFailed		3

#endif	/* _RANDR_H_ */
