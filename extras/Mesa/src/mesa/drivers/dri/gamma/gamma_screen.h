/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


typedef struct _gammaRegion {
    drm_handle_t  handle;
    drmSize    size;
    drmAddress map;
} gammaRegion, *gammaRegionPtr;

typedef struct {

    int           regionCount;       /* Count of register regions */
    gammaRegion  *regions;           /* Vector of mapped region info */

    drmBufMapPtr  bufs;              /* Map of DMA buffers */

    __DRIscreenPrivate *driScreen; /* Back pointer to DRI screen */

    int		cpp;
    int		frontPitch;
    int		frontOffset;

    int		backPitch;
    int		backOffset;
    int		backX;
    int		backY;

    int		depthOffset;
    int		depthPitch;

    int		textureSize;
    int		logTextureGranularity;
} gammaScreenRec, *gammaScreenPtr;
