/* $Id: mmx.h,v 1.1.1.1 2005/03/18 13:07:00 tron Exp $ */
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
 * Mesa 3-D graphics library
 * Version:  3.5
 *
 * Copyright (C) 1999-2001  Brian Paul   All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * BRIAN PAUL BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
 * AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */


#ifndef ASM_MMX_H
#define ASM_MMX_H

extern void _ASMAPI
_mesa_mmx_blend_transparency( GLcontext *ctx, GLuint n, const GLubyte mask[],
                              GLubyte rgba[][4], const GLubyte dest[][4] );

extern void _ASMAPI
_mesa_mmx_blend_add( GLcontext *ctx, GLuint n, const GLubyte mask[],
                     GLubyte rgba[][4], const GLubyte dest[][4] );

extern void _ASMAPI
_mesa_mmx_blend_min( GLcontext *ctx, GLuint n, const GLubyte mask[],
                     GLubyte rgba[][4], const GLubyte dest[][4] );

extern void _ASMAPI
_mesa_mmx_blend_max( GLcontext *ctx, GLuint n, const GLubyte mask[],
                     GLubyte rgba[][4], const GLubyte dest[][4] );

extern void _ASMAPI
_mesa_mmx_blend_modulate( GLcontext *ctx, GLuint n, const GLubyte mask[],
                          GLubyte rgba[][4], const GLubyte dest[][4] );

#endif
