/***************************************************************************/
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*                                                                         */
/*  sfnt.c                                                                 */
/*                                                                         */
/*    Single object library component.                                     */
/*                                                                         */
/*  Copyright 1996-2001, 2002, 2003 by                                     */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


#define FT_MAKE_OPTION_SINGLE_OBJECT

#include <ft2build.h>
#include "ttload.c"
#include "ttcmap0.c"
#include "sfobjs.c"
#include "sfdriver.c"

#ifdef TT_CONFIG_OPTION_EMBEDDED_BITMAPS
#include "ttsbit.c"
#endif

#ifdef TT_CONFIG_OPTION_POSTSCRIPT_NAMES
#include "ttpost.c"
#endif


/* END */
