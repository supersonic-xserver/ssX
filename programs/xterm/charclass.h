/* $XFree86: xc/programs/xterm/charclass.h,v 1.1 2000/08/26 04:33:53 dawes Exp $ */
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


#ifndef CHARCLASS_H
#define CHARCLASS_H

extern void init_classtab(void);
/* intialise the table. needs calling before either of the 
   others. */

extern int SetCharacterClassRange(int low, int high, int value);
extern int CharacterClass(int c);

#endif
