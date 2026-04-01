/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


   See the file COPYING for copying permission.
*/

#define XML_MAP_FILE 01
#define XML_EXTERNAL_ENTITIES 02

extern int XML_ProcessFile(XML_Parser parser,
                           const XML_Char *filename,
                           unsigned flags);
