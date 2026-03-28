/* $XFree86: xc/programs/Xserver/hw/xfree86/ramdac/TIPriv.h,v 1.2 2000/03/21 21:15:28 alanh Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include "TI.h"

typedef struct {
	char *DeviceName;
} xf86TIramdacInfo;

extern xf86TIramdacInfo TIramdacDeviceInfo[];

#ifdef INIT_TI_RAMDAC_INFO
xf86TIramdacInfo TIramdacDeviceInfo[] = {
	{"TI TVP3030"},
	{"TI TVP3026"}
};
#endif

#define TISAVE(_reg) do { 						\
    ramdacReg->DacRegs[_reg] = (*ramdacPtr->ReadDAC)(pScrn, _reg);	\
} while (0)

#define TIRESTORE(_reg) do { 						\
    (*ramdacPtr->WriteDAC)(pScrn, _reg, 				\
	(ramdacReg->DacRegs[_reg] & 0xFF00) >> 8, 			\
	ramdacReg->DacRegs[_reg]);					\
} while (0)
