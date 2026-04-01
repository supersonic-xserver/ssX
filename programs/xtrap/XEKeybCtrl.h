/* $XFree86: xc/programs/xtrap/XEKeybCtrl.h,v 1.1 2001/11/02 23:29:34 dawes Exp $ */
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


extern int XEEnableCtrlKeys(void(*rtn)(int));
extern int XEEnableCtrlC(void (*rtn)(int));
extern int XEEnableCtrlY(void (*rtn)(int));
extern int XEClearCtrlKeys(void);
extern int XEDeclExitHndlr(void (*rtn)(int));

