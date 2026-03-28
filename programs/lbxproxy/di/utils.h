/* $XFree86: xc/programs/lbxproxy/di/utils.h,v 1.1 2004/04/03 22:38:54 tsi Exp $ */
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


#ifndef _UTILS_H_
#define _UTILS_H_

/* from utils.c */
extern Bool lbxZeroPad;
extern Bool lbxWinAttr;
extern Bool lbxDoCmapGrabbing;

extern int lbxMaxMotionEvents;
extern int zlevel;

extern char *atomsFile;

extern char *rgbPath;

/* from wire.c */
extern Bool reconnectAfterCloseServer;

/* from tags.c */
extern int lbxTagCacheSize;

/* from lbxutil.c */
extern Bool compStats;

/* from os/conncetion.c */
extern Bool PartialNetwork;

#endif /* _UTILS_H_ */
