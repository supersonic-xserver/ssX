/* infblock.h -- header to use infblock.c
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


 * Copyright (C) 1995-2002 Mark Adler
 * For conditions of distribution and use, see copyright notice in zlib.h 
 */

/* WARNING: this file should *not* be used by applications. It is
   part of the implementation of the compression library and is
   subject to change. Applications should only use zlib.h.
 */

struct inflate_blocks_state;
typedef struct inflate_blocks_state FAR inflate_blocks_statef;

extern inflate_blocks_statef * inflate_blocks_new OF((
    z_streamp z,
    check_func c,               /* check function */
    uInt w));                   /* window size */

extern int inflate_blocks OF((
    inflate_blocks_statef *,
    z_streamp ,
    int));                      /* initial return code */

extern void inflate_blocks_reset OF((
    inflate_blocks_statef *,
    z_streamp ,
    uLongf *));                  /* check value on output */

extern int inflate_blocks_free OF((
    inflate_blocks_statef *,
    z_streamp));

extern void inflate_set_dictionary OF((
    inflate_blocks_statef *s,
    const Bytef *d,  /* dictionary */
    uInt  n));       /* dictionary length */

extern int inflate_blocks_sync_point OF((
    inflate_blocks_statef *s));
