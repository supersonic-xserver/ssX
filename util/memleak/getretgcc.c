/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */
/* Use gcc's __builtin_frame_address() function to get the stack trace.
 */

/* $XFree86: xc/util/memleak/getretgcc.c,v 1.1 2006/04/03 18:13:45 dawes Exp $ */

#include "getstack.h"

#define MIN_ADDR 0x1000

struct gccframe {
	struct gccframe *next;
	void *ret;
};

void
getStackTrace(unsigned long *results, int max)
{
    struct gccframe *frame;

    frame = (struct gccframe *)__builtin_frame_address(0);
#if defined(__powerpc__)
    if (frame)
	frame = frame->next;
#endif
    while ((unsigned long)frame > MIN_ADDR && max-- > 1) {
	*results = (unsigned long)frame->ret;
	if (*results < MIN_ADDR)
		break;
	results++;
	frame = frame->next;
    }
    *results = 0;
}

