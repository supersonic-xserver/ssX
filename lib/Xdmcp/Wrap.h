/* $Xorg: Wrap.h,v 1.3 2000/08/17 19:45:50 cpqbld Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * header file for compatibility with something useful
 */

/* $XFree86: xc/lib/Xdmcp/Wrap.h,v 1.5 2004/06/09 18:30:56 dawes Exp $ */

typedef unsigned char auth_cblock[8];	/* block size */

typedef struct auth_ks_struct { auth_cblock _; } auth_wrapper_schedule[16];

extern void _XdmcpWrapperToOddParity (unsigned char *in, unsigned char *out);

#ifdef HASXDMAUTH
extern void _XdmcpAuthSetup (auth_cblock key, auth_wrapper_schedule schedule);
extern void _XdmcpAuthDoIt (auth_cblock input, auth_cblock output,
	auth_wrapper_schedule schedule, int edflag);
#endif
