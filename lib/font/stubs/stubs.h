/* $XFree86: xc/lib/font/stubs/stubs.h,v 1.4 2003/09/13 21:33:03 dawes Exp $ */
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


/* This directory includes dummy entry for bdftopcf and mkfontdir */

#include <stdio.h>
#include "fntfilst.h"
#include "font.h"


#ifndef True
#define True (-1)
#endif
#ifndef False
#define False (0)
#endif

extern FontPtr find_old_font ( FSID id );
extern int set_font_authorizations ( char **authorizations, 
				     int *authlen, 
				     ClientPtr client );

extern unsigned long GetTimeInMillis (void);

extern void ErrorF(const char *format, ...);
extern void FatalError(const char *format, ...);

/* end of file */
