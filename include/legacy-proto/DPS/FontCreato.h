/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FontCreator_h
#define _FontCreator_h

/* New resouce names and classes */

#define XtNsizes "sizes"
#define XtCSizes "Sizes"
#define XtNsizeCount "sizeCount"
#define XtCSizeCount "SizeCount"
#define XtNdismissCallback "dismissCallback"
#define XtNfontSelectionBox "fontSelectionBox"
#define XtCFontSelectionBox "FontSelectionBox"

/* Class record constants */

extern WidgetClass fontCreatorWidgetClass;

typedef struct _FontCreatorRec *FontCreatorWidget;

#endif /* _FontCreator_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
