/* $XFree86: xc/programs/Xserver/hw/xfree86/ramdac/BTPriv.h,v 1.2 1998/07/25 16:57:18 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#include "BT.h"

typedef struct {
	char *DeviceName;
} xf86BTramdacInfo;

extern xf86BTramdacInfo BTramdacDeviceInfo[];

#ifdef INIT_BT_RAMDAC_INFO
xf86BTramdacInfo BTramdacDeviceInfo[] = {
	{"AT&T 20C504"},
	{"AT&T 20C505"},
	{"BT485/484"}
};
#endif
