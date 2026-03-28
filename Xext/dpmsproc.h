/* $XFree86: xc/programs/Xserver/Xext/dpmsproc.h,v 1.4 2003/07/16 01:38:29 dawes Exp $ */
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


/* Prototypes for functions that the DDX must provide */

#ifndef _DPMSPROC_H_
#define _DPMSPROC_H_

void DPMSSet(int level);
int  DPMSGet(int *plevel);
Bool DPMSSupported(void);

#endif
