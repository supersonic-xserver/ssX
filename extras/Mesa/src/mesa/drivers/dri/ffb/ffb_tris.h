/* $XFree86: xc/extras/Mesa/src/mesa/drivers/dri/ffb/ffb_tris.h,v 1.1.1.4 2004/12/10 15:05:37 alanh Exp $ */
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


#ifndef _FFB_TRIS_H
#define _FFB_TRIS_H

extern void ffbDDInitRenderFuncs( GLcontext *ctx );


#define _FFB_NEW_RENDER (_DD_NEW_TRI_LIGHT_TWOSIDE |	\
			 _DD_NEW_TRI_OFFSET |		\
			 _DD_NEW_TRI_UNFILLED)

extern void ffbChooseRenderState(GLcontext *ctx);


#define _FFB_NEW_TRIANGLE (_DD_NEW_TRI_SMOOTH |	\
			   _DD_NEW_FLATSHADE |	\
			   _NEW_POLYGON | 	\
			   _NEW_COLOR)

extern void ffbChooseTriangleState(GLcontext *ctx);

extern void ffbFallback( GLcontext *ctx, GLuint bit, GLboolean mode );
#define FALLBACK( ctx, bit, mode ) ffbFallback( ctx, bit, mode )

#endif /* !(_FFB_TRIS_H) */
