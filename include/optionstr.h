/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef OPTIONSTR_H_
#define OPTIONSTR_H_
#include "list.h"

struct _InputOption {
    GenericListRec list;
    char *opt_name;
    char *opt_val;
    int opt_used;
    char *opt_comment;
};

#endif                          /* INPUTSTRUCT_H */
