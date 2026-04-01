/* $XFree86: xc/programs/Xserver/hw/xfree86/ramdac/IBMPriv.h,v 1.2 1998/07/25 16:57:19 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#include "IBM.h"

typedef struct {
	char *DeviceName;
} xf86IBMramdacInfo;

extern xf86IBMramdacInfo IBMramdacDeviceInfo[];

#ifdef INIT_IBM_RAMDAC_INFO
xf86IBMramdacInfo IBMramdacDeviceInfo[] = {
	{"IBM 524"},
	{"IBM 524A"},
	{"IBM 525"},
	{"IBM 526"},
	{"IBM 526DB(DoubleBuffer)"},
	{"IBM 528"},
	{"IBM 528A"},
	{"IBM 624"},
	{"IBM 624DB(DoubleBuffer)"},
	{"IBM 640"}
};
#endif
