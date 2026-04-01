/* $XFree86: xc/lib/Xi/XIint.h,v 3.4 2005/01/27 02:28:59 dawes Exp $ */
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


/*
 *	XIint.h - Header definition and support file for the internal
 *	support routines used by the Xi library.
 */

#ifndef _XIINT_H_
#define _XIINT_H_

extern XExtDisplayInfo * XInput_find_display(
	Display*
);

extern int _XiCheckExtInit(
	Display*,
	int
);

extern XExtensionVersion * _XiGetExtensionVersion(
	Display*,
	_Xconst char*
);

extern Status _XiEventToWire(Display *dpy, XEvent *re, xEvent **event,
			     int *count);

#endif
