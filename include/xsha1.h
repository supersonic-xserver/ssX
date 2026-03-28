/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef XSHA1_H
#define XSHA1_H

/* Initialize SHA1 computation.  Returns NULL on error. */
void *x_sha1_init(void);

/*
 * Add some data to be hashed.  ctx is the value returned by x_sha1_init()
 * Returns 0 on error, 1 on success.
 */
int x_sha1_update(void *ctx, void *data, int size);

/*
 * Place the hash in result, and free ctx.
 * Returns 0 on error, 1 on success. 
 */
int x_sha1_final(void *ctx, unsigned char result[20]);

#endif
