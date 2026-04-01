/***************************************************************************/
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*                                                                         */
/*  pshnterr.h                                                             */
/*                                                                         */
/*    PS Hinter error codes (specification only).                          */
/*                                                                         */
/*  Copyright 2003 by                                                      */
/*  David Turner, Robert Wilhelm, and Werner Lemberg.                      */
/*                                                                         */
/*  This file is part of the FreeType project, and may only be used,       */
/*  modified, and distributed under the terms of the FreeType project      */
/*  license, LICENSE.TXT.  By continuing to use, modify, or distribute     */
/*  this file you indicate that you have read the license and              */
/*  understand and accept it fully.                                        */
/*                                                                         */
/***************************************************************************/


  /*************************************************************************/
  /*                                                                       */
  /* This file is used to define the PSHinter error enumeration constants. */
  /*                                                                       */
  /*************************************************************************/

#ifndef __PSHNTERR_H__
#define __PSHNTERR_H__

#include FT_MODULE_ERRORS_H

#undef __FTERRORS_H__

#define FT_ERR_PREFIX  PSH_Err_
#define FT_ERR_BASE    FT_Mod_Err_PShinter

#include FT_ERRORS_H

#endif /* __PSHNTERR_H__ */


/* END */
