/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifdef __cplusplus
extern "C" {
#endif

int XML_URLInit();
void XML_URLUninit();
int XML_ProcessURL(XML_Parser parser,
                   const XML_Char *url,
                   unsigned flags);

#ifdef __cplusplus
}
#endif
