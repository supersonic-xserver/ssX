/*
 * Private screen access functions for internal DIX use
 * 
 * This header provides access to internal screen functions that were
 * previously in XFree86's private headers.
 */

#ifndef _SCREENINT_PRIV_H
#define _SCREENINT_PRIV_H

#include "include/scrnintstr.h"

/* Get screen pointer from screen index - needed by GLX */
extern _X_EXPORT ScreenPtr dixGetScreenPtr(int index);

#endif /* _SCREENINT_PRIV_H */
