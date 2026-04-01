/***************************************************************************/
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*                                                                         */
/*  ftcache.c                                                              */
/*                                                                         */
/*    The FreeType Caching sub-system (body only).                         */
/*                                                                         */
/*  Copyright 2000-2001, 2003 by                                           */
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
#include "ftcmru.c"
#include "ftcmanag.c"
#include "ftccache.c"
#include "ftccmap.c"
#include "ftcglyph.c"
#include "ftcimage.c"
#include "ftcsbits.c"
#include "ftcbasic.c"

/* END */
