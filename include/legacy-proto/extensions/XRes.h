/*
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


   Copyright (c) 2002  XFree86 Inc
*/
/* $XFree86: xc/include/extensions/XRes.h,v 1.5 2006/11/07 20:03:29 tsi Exp $ */

#ifndef _XRES_H
#define _XRES_H

#include <X11/X.h>
#include <X11/Xfuncproto.h>

typedef struct {
  XID resource_base;
  XID resource_mask;
} XResClient;

typedef struct {
  Atom resource_type;
  unsigned int count;
} XResType;

_XFUNCPROTOBEGIN


Bool XResQueryExtension (
   Display *dpy,
   int *event_base,
   int *error_base
);

Status XResQueryVersion (
   Display *dpy,
   int *major_versionp,
   int *minor_versionp
);

Status XResQueryClients (
   Display *dpy,
   int *num_clients,
   XResClient **clients
);

Status XResQueryClientResources (
   Display *dpy,
   XID xid,
   int *num_types,
   XResType **types
);

Status XResQueryClientPixmapBytes (
   Display *dpy,
   XID xid,
   unsigned long *bytes
);

_XFUNCPROTOEND

#endif /* _XRES_H */
