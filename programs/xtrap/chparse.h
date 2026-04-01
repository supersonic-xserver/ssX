/* $XFree86: xc/programs/xtrap/chparse.h,v 1.1 2001/11/02 23:29:34 dawes Exp $ */
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


extern int chparse(int max_delay, int rest_delay, int *state, int *private,
		   int param[], int *nparam, int inter[], int *ninter,
		   int *final);
extern void dumpsequence(int state, int c, int private, int param[],
			int nparam, int inter[], int ninter, int final,
			short *column);


