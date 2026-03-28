/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef TESTS_COMMON_H
#define TESTS_COMMON_H

#include "tests.h"

#define ARRAY_SIZE(a)  (sizeof((a)) / sizeof((a)[0]))

#define run_test(func) run_test_in_child(func, #func)

void run_test_in_child(int (*func)(void), const char *funcname);

#endif /* TESTS_COMMON_H */
