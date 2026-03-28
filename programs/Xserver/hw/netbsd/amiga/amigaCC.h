/* Includes for AmigaCC driver */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



#include <sys/device.h>
#include <sys/queue.h>
#include "dev/grfabs_reg.h"
#include "dev/viewioctl.h"
#include "dev/grfvar.h"


#define MAX_COLORS 256


struct viewinfo {
    bmap_t bm;
    struct view_size vs;
    colormap_t colormap;
    long entry [MAX_COLORS];
};

