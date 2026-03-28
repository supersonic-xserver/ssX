/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifdef __cplusplus
extern "C" {
#endif

/* Registered charset names are at most 40 characters long. */

#define CHARSET_MAX 41

/* Figure out the charset to use from the ContentType.
   buf contains the body of the header field (the part after "Content-Type:").
   charset gets the charset to use.  It must be at least CHARSET_MAX chars
   long.  charset will be empty if the default charset should be used.
*/

void getXMLCharset(const char *buf, char *charset);

#ifdef __cplusplus
}
#endif
