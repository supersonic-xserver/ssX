/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef DPS_X_DOUSERPATH_H
#define DPS_X_DOUSERPATH_H

#include <DPS/dpsXcommon.h>
#include <X11/Xlib.h>
#include <DPS/dpsconfig.h>

/* Should be 1 for high-order byte first, 0 for low-order byte first.  I can
   never rember which is big- and which is little-endian. */

typedef enum _DPSNumberFormat {
#if SWAPBITS == 1
    dps_float = 128+48,
    dps_long = 128,
    dps_short = 128+32
#else /* SWAPBITS */
    dps_float = 48,
    dps_long = 0,
    dps_short = 32
#endif /* SWAPBITS */
} DPSNumberFormat;

/* Constants for DPSDoUserPath describing what type of coordinates are
   being used.  Other legal values are:

   For 32-bit fixed point numbers, use dps_long plus the number of bits
   in the fractional part.

   For 16-bit fixed point numbers, use dps_short plus the number of bits
   in the fractional part.
*/
 
enum _DPSUserPathOp {
    dps_setbbox = 0,
    dps_moveto,
    dps_rmoveto,
    dps_lineto,
    dps_rlineto,
    dps_curveto,
    dps_rcurveto,
    dps_arc,
    dps_arcn,
    dps_arct,
    dps_closepath,
    dps_ucache
};

/* We count on the fact that this is a char, so can't put it in the above
   typedef. */

typedef char DPSUserPathOp;

typedef enum _DPSUserPathAction {
    dps_uappend = 176,
    dps_ufill = 179,
    dps_ueofill = 178,
    dps_ustroke = 183,
    dps_ustrokepath = 364,
    dps_inufill = 93,
    dps_inueofill = 92,
    dps_inustroke = 312,
    dps_infill = 90,
    dps_ineofill = 89,
    dps_instroke = 311,
    dps_def = 51,
    dps_put = 120,
    dps_send = 113	/* This is really the null operator */
} DPSUserPathAction;
 
#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern void PSDoUserPath(DPSPointer coords,
			 int numCoords,
			 DPSNumberFormat numType,
			 DPSUserPathOp *ops,
			 int numOp,
			 DPSPointer bbox,
			 DPSUserPathAction action);

extern void DPSDoUserPath(DPSContext ctx,
			  DPSPointer coords,
			  int numCoords,
			  DPSNumberFormat numType,
			  DPSUserPathOp *ops,
			  int numOp,
			  DPSPointer bbox,
			  DPSUserPathAction action);

extern Bool PSHitUserPath(double x, double y,
			  double radius,

			  DPSPointer coords,
			  int numCoords,
			  DPSNumberFormat numType,
			  DPSUserPathOp *ops,
			  int numOp,
			  DPSPointer bbox,
			  DPSUserPathAction action);

extern Bool DPSHitUserPath(DPSContext ctx,
			   double x, double y,
			   double radius,

			   DPSPointer coords,
			   int numCoords,
			   DPSNumberFormat numType,
			   DPSUserPathOp *ops,
			   int numOp,
			   DPSPointer bbox,
			   DPSUserPathAction action);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

#endif /* DPS_X_DOUSERPATH_H */
