/* Copyright (c) 1998, 1999 Thai Open Source Software Center Ltd
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


   See the file COPYING for copying permission.
*/

#include <stddef.h>

#ifdef XML_UNICODE
int filemap(const wchar_t *name,
            void (*processor)(const void *, size_t,
                              const wchar_t *, void *arg),
            void *arg);
#else
int filemap(const char *name,
            void (*processor)(const void *, size_t,
                              const char *, void *arg),
            void *arg);
#endif
