/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */

#ifndef OPAQUE_H
#define OPAQUE_H

#include <X11/Xmd.h>

#include "globals.h"

extern const char *defaultTextFont;
extern const char *defaultCursorFont;
extern int MaxClients;
extern char isItTimeToYield;
extern char dispatchException;

/* bit values for dispatchException */
#define DE_RESET     1
#define DE_TERMINATE 2
#define DE_PRIORITYCHANGE 4  /* set when a client's priority changes */

extern CARD32 TimeOutValue;
extern int ScreenSaverBlanking;
extern int ScreenSaverAllowExposures;
extern int defaultScreenSaverBlanking;
extern int defaultScreenSaverAllowExposures;
extern int argcGlobal;
extern const char **argvGlobal;
extern const char *display;

extern int defaultBackingStore;
extern Bool disableBackingStore;
extern Bool enableBackingStore;
extern Bool disableSaveUnders;
extern Bool PartialNetwork;
#ifndef NOLOGOHACK
extern int logoScreenSaver;
#endif
#ifdef RLIMIT_DATA
extern int limitDataSpace;
#endif
#ifdef RLIMIT_STACK
extern int limitStackSpace;
#endif
#ifdef RLIMIT_NOFILE
extern int limitNoFile;
#endif
extern Bool permitOldBugs;
extern Bool defeatAccessControl;
extern long maxBigRequestSize;
extern Bool blackRoot;

extern Bool CoreDump;


#endif /* OPAQUE_H */
