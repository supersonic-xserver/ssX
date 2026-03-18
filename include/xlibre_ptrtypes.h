/*
 * xlibre_ptrtypes.h - X11Libre base type definitions
 * 
 * This header provides compatibility type definitions for the GLVND ABI.
 * Types are sourced from standard X11 headers.
 * 
 * IMPORTANT: This header is designed to work with XFree86/Xlibre server headers.
 * When used with the server, include resource.h BEFORE this header to get
 * proper RESTYPE definitions.
 */

#ifndef XLIBRE_PTRTYPES_H
#define XLIBRE_PTRTYPES_H

#include <X11/X.h>
#include <X11/Xlib.h>

/* XID types are defined in X.h */
typedef XID GlxTag;
typedef XID GlxContextID;
typedef XID GlxDrawableID;
typedef XID GlxFBConfigID;

/* Additional pointer types */
typedef void *GLXDrawable;
typedef void *GLXContext;

/* Legacy XFree86 convention: GLXContextTag is CARD32 for wire protocol */
/* Only define if not already defined - GL/glxproto.h may have already defined it */
/* Note: GL/glxproto.h defines GLXContextTag as CARD32, which may differ from unsigned int */
#ifndef GLXCONTEXTTAG_DEFINED
#define GLXCONTEXTTAG_DEFINED
#ifndef GLXContextTag
typedef unsigned int GLXContextTag;
#endif
#endif

/* RESTYPE is server-specific - include resource.h before this header */
/* If building for server, provide a fallback definition */
#ifndef RESTYPE
typedef unsigned long RESTYPE;
#endif

#endif /* XLIBRE_PTRTYPES_H */
