/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FontCreatorP_H
#define _FontCreatorP_H

#define MAX_AXES 4

#include <DPS/FontCreato.h>

typedef struct {
    float *sizes;
    int size_count;
    FontSelectionBoxWidget fsb;
    XtCallbackList dismiss_callback;

    Widget pane_child;
    Widget preview_child;
    Widget display_text_child;
    Widget axis_label_child[MAX_AXES];
    Widget axis_scale_child[MAX_AXES];
    Widget axis_min_label_child[MAX_AXES];
    Widget axis_max_label_child[MAX_AXES];
    Widget axis_value_text_child[MAX_AXES];
    Widget face_scrolled_list_child;
    Widget blend_label_child;
    Widget blend_scrolled_list_child;
    Widget size_text_field_child;
    Widget size_option_menu_child;
    Widget generate_button_child;
    Widget name_label_child;
    Widget name_text_child;
    Widget do_all_toggle_child;
    Widget follow_size_toggle_child;

    /* Private fields */

    DPSGState gstate;
    Widget other_size;
    Widget size_menu;
    Widget option_box;
    FontFamilyRec *family;
    FontRec *font;
    int managed_axes;
    Boolean preview_fixed;
} FontCreatorPart;

typedef struct _FontCreatorRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    FontCreatorPart		creator;
} FontCreatorRec;

typedef struct {
    XtPointer			extension;
} FontCreatorClassPart;

typedef struct _FontCreatorClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    FontCreatorClassPart	creator_class;
} FontCreatorClassRec, *FontCreatorWidgetClass;

extern FontCreatorClassRec fontCreatorClassRec;

#endif /* _FontCreatorP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
