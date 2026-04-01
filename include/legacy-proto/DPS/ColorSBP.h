/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _ColorSelectionBoxP_H
#define _ColorSelectionBoxP_H

#include <DPS/ColorSB.h>

typedef struct {
    float red, green, blue;
    float cyan, magenta, yellow, black;
    float hue, saturation, brightness;
    float gray;
} ColorRec;

/* Redefining PALETTE_MAX requires program alterations. */

#define PALETTE_MAX 10

typedef struct {
    DPSContext context;
    String rgb_labels;
    String cmyk_labels;
    String hsb_labels;
    String gray_labels;
    Dimension cell_size;
    short num_cells;
    short current_palette;
    String fill_me;
    CSBColorSpace current_space;
    CSBRenderingType current_rendering;
    String broken_palette_label;
    String broken_palette_message;

    String palette_label[PALETTE_MAX];
    CSBColorSpace palette_space[PALETTE_MAX];
    Boolean palette_color_dependent[PALETTE_MAX];
    Boolean palette_broken[PALETTE_MAX];
    String palette_function[PALETTE_MAX];

    XtCallbackList ok_callback;
    XtCallbackList apply_callback;
    XtCallbackList reset_callback;
    XtCallbackList cancel_callback;
    XtCallbackList face_select_callback;
    XtCallbackList value_changed_callback;

 /* Subwidgets */
    Widget form_child;
    Widget slider_child[4];
    Widget value_child[4];
    Widget label_child[4];
    Widget model_option_menu_child;
    Widget display_option_menu_child;
    Widget patch_child;
    Widget dock_child;
    Widget palette_option_menu_child;
    Widget palette_child;

 /* Private fields */

    Pixel background;
    Boolean static_visual;
    Boolean no_background;
    Boolean palette_pixmap_valid;
    int visual_class;
    DPSGState base_gstate;
    DPSGState patch_gstate;
    DPSGState dock_gstate;
    ColorRec current_color;
    ColorRec palette_color;
    ColorRec save_color;

    Pixmap red_pixmap;
    Pixmap green_pixmap;
    Pixmap blue_pixmap;
    Pixmap cyan_pixmap;
    Pixmap magenta_pixmap;
    Pixmap yellow_pixmap;
    Pixmap black_pixmap;
    Pixmap hue_pixmap;
    Pixmap sat_pixmap;
    Pixmap bright_pixmap;
    Pixmap gray_pixmap;

    Dimension rgb_slider_width;
    Dimension cmyk_slider_width;
    Dimension hsb_slider_width;
    Dimension gray_slider_width;

    float itransform[6];

    float *dock_cyan, *dock_magenta, *dock_yellow, *dock_black;
    Boolean *dock_used;
    Boolean dock_changed;

    Cursor eyedrop;
    Cursor square;
    Boolean eyedrop_grabbed;
} ColorSelectionBoxPart;

typedef struct _ColorSelectionBoxRec {
    CorePart			core;
    CompositePart		composite;
    ConstraintPart		constraint;
    XmManagerPart		manager;
    ColorSelectionBoxPart	csb;
} ColorSelectionBoxRec;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

/* Note use of Bool and double in prototypes:  this makes the library
   work correctly when linked with no-prototype compiled objects */

typedef Boolean (*CSBSetColorProc) (Widget w, CSBColorSpace space, double c1,
			     double c2, double c3, double c4, Bool setSpace);

typedef void (*CSBGetColorProc) (Widget w, CSBColorSpace space, float *c1,
			     float *c2, float *c3, float *c4);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#define InheritSetColor ((CSBSetColorProc) _XtInherit)
#define InheritGetColor ((CSBGetColorProc) _XtInherit)

typedef struct {
    CSBSetColorProc		set_color;
    CSBGetColorProc		get_color;
    XtPointer			extension;
} ColorSelectionBoxClassPart;

typedef struct _ColorSelectionBoxClassRec {
    CoreClassPart		core_class;
    CompositeClassPart		composite_class;
    ConstraintClassPart		constraint_class;
    XmManagerClassPart		manager_class;
    ColorSelectionBoxClassPart	csb_class;
} ColorSelectionBoxClassRec, *ColorSelectionBoxWidgetClass;

extern ColorSelectionBoxClassRec colorSelectionBoxClassRec;

#endif /* _ColorSelectionBoxP_H */
/* DON'T ADD ANYTHING AFTER THIS #endif */
