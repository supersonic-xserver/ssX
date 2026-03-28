/* $XFree86$ */
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



/* Functions that are only referenced from within this directory. */

/*
 * These prototypes depend on xf86gcmap.h being included.
 * There are seperate versions for each depth.
 */

Bool
xf86CreateGC(
#if NeedFunctionPrototypes
    GCPtr	pGC
#endif
);

void
xf86ValidateGC(
#if NeedFunctionPrototypes
    GCPtr		pGC,
    unsigned long	changes,
    DrawablePtr		pDrawable
#endif
);

void
xf86GCNewFillPolygon(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    Bool	new_cfb_line
#endif
);

void
xf86GCNewRectangle(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    Bool	new_cfb_line
#endif
);

void
xf86GCNewLine(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    DrawablePtr pDrawable,
    Bool	new_cfb_line
#endif
);

void
xf86GCNewText(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    Bool	new_cfb_text
#endif
);

void
xf86GCNewFillSpans(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    Bool	new_cfb_fillspans
#endif
);

void
xf86GCNewFillArea(
#if NeedFunctionPrototypes
    GCPtr	pGC,
    Bool	new_cfb_fillarea
#endif
);

void
xf86GCNewCopyArea(
#if NeedFunctionPrototypes
    GCPtr	pGC
#endif
);

void
xf86ImageWriteFallBack(
#if NeedFunctionPrototypes
    int x,
    int y,
    int w,
    int h,
    void *src,
    int srcwidth,
    int rop,
    unsigned planemask
#endif
);

void
xf86WriteBitmapFallBack(
#if NeedFunctionPrototypes
    int x,
    int y,
    int w,
    int h,
    unsigned char *src,
    int srcwidth,
    int srcx,
    int srcy,
    int bg,
    int fg,
    int rop,
    unsigned planemask
#endif
);
