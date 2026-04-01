/* $XFree86: xc/lib/X11/Key.h,v 1.1 2003/04/13 19:22:16 dawes Exp $ */
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


#ifndef _KEY_H_
#define _KEY_H_

#ifndef NEEDKTABLE
extern const unsigned char _XkeyTable[];
#endif

extern int
_XKeyInitialize(
    Display *dpy);

extern XrmDatabase
_XInitKeysymDB(
        void);

#endif /* _KEY_H_ */
