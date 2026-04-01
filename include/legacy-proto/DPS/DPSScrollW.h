/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _DPSScrolledWindow_h
#define _DPSScrolledWindow_h

#include <DPS/dpsXshare.h>

/* New resouce names and classes */

#define XtNcontext "context"
#define XtCContext "Context"
#define XtNareaWidth "areaWidth"
#define XtCAreaWidth "AreaWidth"
#define XtNareaHeight "areaHeight"
#define XtCAreaHeight "AreaHeight"
#define XtNscale "scale"
#define XtCScale "Scale"
#define XtNctm "ctm"
#define XtCCtm "Ctm"
#define XtNinvCtm "invCtm"
#define XtCInvCtm "InvCtm"
#define XtNuseBackingPixmap "useBackingPixmap"
#define XtCUseBackingPixmap "UseBackingPixmap"
#define XtNuseFeedbackPixmap "useFeedbackPixmap"
#define XtCUseFeedbackPixmap "UseFeedbackPixmap"
#define XtNbackingPixmap "backingPixmap"
#define XtCBackingPixmap "BackingPixmap"
#define XtNfeedbackPixmap "feedbackPixmap"
#define XtCFeedbackPixmap "FeedbackPixmap"
#define XtNdocumentSizePixmaps "documentSizePixmaps"
#define XtCDocumentSizePixmaps "DocumentSizePixmaps"
#define XtNwindowGState "windowGState"
#define XtCWindowGState "WindowGState"
#define XtNbackingGState "backingGState"
#define XtCBackingGState "BackingGState"
#define XtNfeedbackGState "feedbackGState"
#define XtCFeedbackGState "FeedbackGState"
#define XtNdirtyAreas "dirtyAreas"
#define XtCDirtyAreas "DirtyAreas"
#define XtNnumDirtyAreas "numDirtyAreas"
#define XtCNumDirtyAreas "NumDirtyAreas"
#define XtNpixmapLimit "pixmapLimit"
#define XtCPixmapLimit "PixmapLimit"
#define XtNabsolutePixmapLimit "absolutePixmapLimit"
#define XtCAbsolutePixmapLimit "AbsolutePixmapLimit"
#define XtNwatchProgress "watchProgress"
#define XtCWatchProgress "WatchProgress"
#define XtNminimalDrawing "minimalDrawing"
#define XtCMinimalDrawing "MinimalDrawing"
#define XtNwatchProgressDelay "watchProgressDelay"
#define XtCWatchProgressDelay "WatchProgressDelay"
#define XtNapplicationScrolling "applicationScrolling"
#define XtCApplicationScrolling "ApplicationScrolling"
#define XtNsetupCallback "setupCallback"
#define XtNexposeCallback "exposeCallback"
#define XtNbackgroundCallback "backgroundCallback"
#define XtNfeedbackCallback "feedbackCallback"
#define XtNresizeCallback "resizeCallback"

/* New resource types */

#define XtRDPSContext "DPSContext"
#define XtRDPSGState "DPSGState"
#define XtRFloatArray "FloatArray"

/* Callback records */

typedef struct {
    DPSContext context;
} DSWSetupCallbackRec;    

typedef enum {DSWWindow, DSWBackingPixmap, DSWFeedbackPixmap} DSWDrawableType;
typedef enum {DSWDrawSome, DSWAbort, DSWFinish,
	      DSWAbortOrFinish} DSWDirections;
typedef enum {DSWUndefined, DSWCallAgain, DSWAborted, DSWFinished} DSWResults;

typedef struct {
    DSWDrawableType type;
    DSWDirections directions;
    DSWResults results;		/* Filled in by callback */
    Boolean first;
    Boolean background;
    Drawable drawable;
    DPSGState gstate;
    DPSContext context;
    float *rects;
    int rect_count;
} DSWExposeCallbackRec;	

typedef struct {
    Dimension oldw, oldh;
    Dimension neww, newh;
    Position x, y;
} DSWResizeCallbackRec;

typedef struct {
    XtPointer start_feedback_data;
    XtPointer continue_feedback_data;
    DSWDrawableType type;
    Drawable drawable;
    DPSGState gstate;
    DPSContext context;
    float *dirty_rects;
    int dirty_count;
} DSWFeedbackCallbackRec;

/* Class record constants */

extern WidgetClass dpsScrolledWindowWidgetClass;

typedef struct _DPSScrolledWindowRec *DPSScrolledWindowWidget;

/* Interface routines */

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of long and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

extern void DSWSetScale(Widget w, double scale, long fixedX, long fixedY);
extern void DSWScrollPoint(Widget w, double psX, double psY, long xX, long xY);
extern void DSWScrollBy(Widget w, long dx, long dy);
extern void DSWScrollTo(Widget w, long x, long y);
extern void DSWSetScaleAndScroll(Widget w, double scale,
				 double psX, double psY, long xX, long xY);
extern void DSWConvertXToPS(Widget w, long xX, long xY,
			    float *psX, float *psY);
extern void DSWConvertPSToX(Widget w, double psX, double psY,
			    int *xX, int *xY);
extern void DSWAddToDirtyArea(Widget w, float *rect, long n);
extern Boolean DSWTakeFeedbackPixmap(Widget w, Pixmap *p, int *width,
				     int *height, int *depth, Screen **screen);
extern Boolean DSWGiveFeedbackPixmap(Widget w, Pixmap p, int width, int height,
				     int depth, Screen *screen);
extern void DSWStartFeedbackDrawing(Widget w, XtPointer start_feedback_data);
extern void DSWEndFeedbackDrawing(Widget w, Bool restore_window);
extern void DSWSetFeedbackDirtyArea(Widget w, float *rects, int count,
				    XtPointer continue_feedback_data);
extern void DSWFinishPendingDrawing(Widget w);
extern void DSWAbortPendingDrawing(Widget w);
extern void DSWGetDrawingInfo(Widget w, DSWDrawableType *type,
			      Drawable *drawable, DPSGState *gstate,
			      DPSContext *context);
extern void DSWUpdateDrawing(Widget w, float *rects, int count);
extern void DSWGetScrollInfo(Widget w, int *h_value, int *h_size, int *h_max,
			     int *v_value, int *v_size, int *v_max);

#if defined(__cplusplus) || defined(c_plusplus)
};
#endif

#endif /* _DPSScrolledWindow_h */
/* DON'T ADD ANYTHING AFTER THIS #endif */
