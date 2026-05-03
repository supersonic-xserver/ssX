/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FontSampler_h
#define _FontSampler_h

/* New resouce names and classes */

#define XtNdismissCallback "dismissCallback"
#define XtNsizes "sizes"
#define XtCSizes "Sizes"
#define XtNsizeCount "sizeCount"
#define XtCSizeCount "SizeCount"
#define XtNfontSelectionBox "fontSelectionBox"
#define XtCFontSelectionBox "FontSelectionBox"
#define XtNminimumWidth "minimumWidth"
#define XtCMinimumWidth "MinimumWidth"
#define XtNminimumHeight "minimumHeight"
#define XtCMinimumHeight "MinimumHeight"
#define XtNnoRoomMessage "noRoomMessage"
#define XtNnoFontMessage "noFontMessage"
#define XtNnoSelectedFontMessage "noSelectedFontMessage"
#define XtNnoSelectedFamilyMessage "noSelectedFamilyMessage"
#define XtNnoFamilyFontMessage "noFamilyFontMessage"
#define XtNnoMatchMessage "noMatchMessage"
#define XtCMessage "Message"

/* Read-only resources for all the subwidgets */

#define XtNpanelChild "panelChild"
#define XtNareaChild "areaChild"
#define XtNtextChild "textChild"
#define XtNfontLabelChild "fontLabelChild"
#define XtNscrolledWindowChild "scrolledWindowChild"
#define XtNdisplayButtonChild "displayButtonChild"
#define XtNdismissButtonChild "dismissButtonChild"
#define XtNstopButtonChild "stopButtonChild"
#define XtNclearButtonChild "clearButtonChild"
#define XtNradioFrameChild "radioFrameChild"
#define XtNradioBoxChild "radioBoxChild"
#define XtNallToggleChild "allToggleChild"
#define XtNselectedToggleChild "selectedToggleChild"
#define XtNselectedFamilyToggleChild "selectedFamilyToggleChild"
#define XtNfilterToggleChild "filterToggleChild"
#define XtNfilterTextChild "filterTextChild"
#define XtNfilterBoxChild "filterBoxChild"
#define XtNfilterFrameChild "filterFrameChild"
#define XtNsizeOptionMenuChild "sizeOptionMenuChild"
#define XtNsizeTextFieldChild "sizeTextFieldChild"
#define XtNsizeLabelChild "sizeLabelChild"

/* Class record constants */

extern WidgetClass fontSamplerWidgetClass;

typedef struct _FontSamplerRec *FontSamplerWidget;

extern void FSBCancelSampler(Widget w);

#endif /* _FontSampler_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
