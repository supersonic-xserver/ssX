/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


 * Don't #include any of the AppKit, etc stuff directly since it will
 * pollute the X11 namespace.
 */

#ifndef _XQ_SANITIZED_COCOA_H_
#define _XQ_SANITIZED_COCOA_H_

// QuickDraw in ApplicationServices has the following conflicts with
// the basic X server headers. Use QD_<name> to use the QuickDraw
// definition of any of these symbols, or the normal name for the
// X11 definition.
#define Cursor       QD_Cursor
#define WindowPtr    QD_WindowPtr
#define Picture      QD_Picture
#define BOOL         OSX_BOOL
#define EventType    HIT_EventType

#include <Cocoa/Cocoa.h>

#undef Cursor
#undef WindowPtr
#undef Picture
#undef BOOL
#undef EventType

#endif  /* _XQ_SANITIZED_COCOA_H_ */
