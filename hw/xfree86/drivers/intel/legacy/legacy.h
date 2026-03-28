/* The old i810 (only) driver. */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


const OptionInfoRec *lg_i810_available_options(int chipid, int busid);
Bool lg_i810_init(ScrnInfoPtr scrn);
