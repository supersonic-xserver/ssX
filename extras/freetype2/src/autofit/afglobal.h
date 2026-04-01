/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef __AF_GLOBAL_H__
#define __AF_GLOBAL_H__

#include "aftypes.h"

FT_BEGIN_HEADER

 /**************************************************************************/
 /**************************************************************************/
 /*****                                                                *****/
 /*****                F A C E   G L O B A L S                         *****/
 /*****                                                                *****/
 /**************************************************************************/
 /**************************************************************************/


 /*
  *  models the global hints data for a given face, decomposed into
  *  script-specific items..
  *
  */
  typedef struct AF_FaceGlobalsRec_*   AF_FaceGlobals;


  FT_LOCAL( FT_Error )
  af_face_globals_new( FT_Face          face,
                       AF_FaceGlobals  *aglobals );

  FT_LOCAL( FT_Error )
  af_face_globals_get_metrics( AF_FaceGlobals     globals,
                               FT_UInt            gindex,
                               AF_ScriptMetrics  *ametrics );

  FT_LOCAL( void )
  af_face_globals_free( AF_FaceGlobals  globals );

 /* */

FT_END_HEADER

#endif /* __AF_GLOBALS_H__ */
