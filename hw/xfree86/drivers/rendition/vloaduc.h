/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/rendition/vloaduc.h,v 1.4 2000/03/31 20:13:27 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

/*
 * file vloaduc.h
 *
 * loads microcode
 */

#ifndef __VLOADUC_H__
#define __VLOADUC_H__

/*
 * includes
 */

#include "vos.h"
#include "vtypes.h"

/*
 * defines 
 */

/*
 * function prototypes
 */

int verite_load_ucfile(ScrnInfoPtr pScreenInfo, char *file_name);

#endif /* __VLOADUC_H__ */

/*
 * end of file vloaduc.h
 */
