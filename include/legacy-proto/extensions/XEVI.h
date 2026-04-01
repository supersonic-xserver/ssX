/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XEVI_H_
#define _XEVI_H_
#include <X11/Xfuncproto.h>
#define X_EVIQueryVersion		0
#define X_EVIGetVisualInfo		1
#define XEVI_TRANSPARENCY_NONE		0
#define XEVI_TRANSPARENCY_PIXEL		1
#define XEVI_TRANSPARENCY_MASK		2
#ifndef _XEVI_SERVER_
typedef struct {
    VisualID		core_visual_id;
    int			screen;
    int			level;
    unsigned int	transparency_type;
    unsigned int	transparency_value;
    unsigned int	min_hw_colormaps;
    unsigned int	max_hw_colormaps;
    unsigned int	num_colormap_conflicts;
    VisualID*		colormap_conflicts;
} ExtendedVisualInfo;
_XFUNCPROTOBEGIN
Bool XeviQueryExtension(
    Display*            /* dpy */
);
Status XeviQueryVersion(
    Display*		/* dpy */,
    int*		/* majorVersion */,
    int*		/* minorVersion */
);
Status XeviGetVisualInfo(
    Display*		 	/* dpy */,
    VisualID*			/* visual_query */,
    int				/* nVisual_query */,
    ExtendedVisualInfo**	/* extendedVisualInfo_return */,
    int*			/* nInfo_return */
);
_XFUNCPROTOEND
#endif
#endif
