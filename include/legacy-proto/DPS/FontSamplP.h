/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FontSamplerP_H
#define _FontSamplerP_H

#include <DPS/FontSample.h>
#include <DPS/FontSB.h>

typedef struct _DisplayedTextRec {
    String str;
    float size;
    struct _DisplayedTextRec *next;
} DisplayedTextRec;

typedef struct _DisplayedFontRec {
    Position l, r, t, b;
    Position x, y;
    FontRec *font;
    BlendRec *blend;
    DisplayedTextRec *text;
    struct _DisplayedFontRec *next;
} DisplayedFontRec;

typedef struct {
    FontSamplerWidget sampler;
    Boolean inited, any_shown;
    Dimension column_width;
    Position x, y;
    Dimension height, width;
    Dimension window_height;
    int depth;
    FontFamilyRec *current_family;
    FontRec *current_font;
    BlendRec *current_blend;
    DisplayedTextRec *text_list;
    DisplayedFontRec *shown_fonts;
} DisplayRecord;

typedef struct {
    float *sizes;
    int size_count;
    FontSelectionBoxWidget fsb;
    XtCallbackList dismiss_callback;
    Dimension minimum_width;
    Dimension minimum_height;
    XmString no_room_message;
    XmString no_font_message;
    XmString no_selected_font_message;
    XmString no_selected_family_message;
    XmString no_family_font_message;
    XmString no_match_message;
    Widget panel_child;
    Widget area_child;
    Widget text_child;
    Widget font_label_child;
    Widget scrolled_window_child;
    Widget display_button_child;
    Widget dismiss_button_child;
    Widget stop_button_child;
    Widget clear_button_child;
    Widget radio_frame_child;
    Widget radio_box_child;
    Widget all_toggle_child;
    Widget selected_toggle_child;
    Widget selected_family_toggle_child;
    Widget filter_toggle_child;
    Widget filter_text_child;
    Widget filter_box_child;
    Widget filter_frame_child;
    Widget size_option_menu_child;
    Widget size_text_field_child;
    Widget size_label_child;

 /* Private fields */

    Widget size_menu;
    Widget other_size;
    Widget *filter_widgets;
    Widget clip_widget;
    Boolean displaying;
    Pixmap pixmap;
    XtWorkProcId current_display_proc;
    DisplayRecord *current_display_info;
    DisplayedFontRec *highlighted_font;
    DPSGState gstate;
    DPSGState pixmap_gstate;
    GC gc;
    char *filter_text;
    Boolean *filter_flags;
    Boolean filters_changed;
    float ctm[6];
    float invctm[6];
} FontSamplerPart;

typedef struct _FontSamplerRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    FontSamplerPart		sampler;
} FontSamplerRec;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

typedef void (*FSBCancelProc) (Widget w);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritCancel ((FSBCancelProc) _XtInherit)

typedef struct {
    FSBCancelProc		cancel;
    XtPointer			extension;
} FontSamplerClassPart;

typedef struct _FontSamplerClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    FontSamplerClassPart	sampler_class;
} FontSamplerClassRec, *FontSamplerWidgetClass;

extern FontSamplerClassRec fontSamplerClassRec;

#endif /* _FontSamplerP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
