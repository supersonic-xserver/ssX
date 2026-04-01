/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _SAVER_H_
#define _SAVER_H_

#define ScreenSaverName	"MIT-SCREEN-SAVER"
#define ScreenSaverPropertyName "_MIT_SCREEN_SAVER_ID"

#define ScreenSaverNotifyMask	0x00000001
#define ScreenSaverCycleMask	0x00000002

#define ScreenSaverMajorVersion	1
#define ScreenSaverMinorVersion	0

#define ScreenSaverOff		0
#define ScreenSaverOn		1
#define ScreenSaverCycle	2
#define ScreenSaverDisabled	3

#define ScreenSaverBlanked	0
#define ScreenSaverInternal	1
#define ScreenSaverExternal	2

#define ScreenSaverNotify	0
#define ScreenSaverNumberEvents	1

#endif /* _SAVER_H_ */
