/* $XFree86: xc/programs/Xserver/hw/xfree86/drivers/via/via_common.h,v 1.3 2004/12/15 01:26:50 tsi Exp $ */
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


#ifndef _VIA_COMMON_H_
#define _VIA_COMMON_H_ 1

/* WARNING: If you change any of these defines, make sure to change
 * the kernel include file as well (via_drm.h)
 */

/* Driver specific DRM command indices
 * NOTE: these are not OS specific, but they are driver specific
 */

#define DRM_VIA_ALLOCMEM	0
#define DRM_VIA_FREEMEM		1
#define DRM_VIA_AGP_INIT	2
#define DRM_VIA_FB_INIT		3
#define DRM_VIA_MAP_INIT	4

#define VIDEO 0

typedef struct 
{
    unsigned int context;
    unsigned int type;
    unsigned int size;
    unsigned long index;
    unsigned long offset;
} drmViaMem;

typedef struct {
    unsigned int offset;
    unsigned int size;
} drmViaAgp;

typedef struct {
    unsigned int offset;
    unsigned int size;
} drmViaFb;

typedef struct 
{
    enum {
	VIA_INIT_MAP = 0x01,
	VIA_CLEANUP_MAP = 0x02
    } func;
    unsigned long sarea_priv_offset;
    unsigned long fb_offset;
    unsigned long mmio_offset;
    unsigned long agpAddr;
} drmViaInit;

#endif /* _VIA_COMMON_H_ */
