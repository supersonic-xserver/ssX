/************************************************************
 * XACE - X Access Control Extension
 * Compatibility header for ssX modernization
 ************************************************************/

#ifndef _XACE_SSX_H
#define _XACE_SSX_H

#include "X.h"

/* Hook return codes */
#define XaceErrorOperation  0
#define XaceAllowOperation 1
#define XaceIgnoreOperation 2

/* Access types for security hooks */
#define XACE_SERVER_ACCESS       1
#define XACE_DEVICE_ACCESS       2
#define XACE_PROPERTY_ACCESS     3
#define XACE_SELECTION_ACCESS    4
#define XACE_DRAWABLE_ACCESS    5
#define XACE_SCREEN_ACCESS       6
#define XACE_WINDOW_ACCESS       7
#define XACE_PIXMAP_ACCESS       8
#define XACE_CURSOR_ACCESS       9
#define XACE_GC_ACCESS          10
#define XACE_FONT_ACCESS        11

/* Access masks used by DixAccess checks */
#define DixReadAccess           (1 << 0)
#define DixWriteAccess          (1 << 1)
#define DixGetAttrAccess        (1 << 2)
#define DixSetAttrAccess        (1 << 3)
#define DixUseAccess            (1 << 4)
#define DixCreateAccess         (1 << 5)
#define DixManageAccess         (1 << 6)
#define DixDestroyAccess        (1 << 7)
#define DixRemoveAccess         (1 << 13)
#define DixListPropAccess       (1 << 9)
#define DixGetFocusAccess      (1 << 10)
#define DixSetFocusAccess      (1 << 11)
#define DixGrabAccess          (1 << 12)


/* XACE is enabled in ssX build */
#define XACE 1

/* Hook dispatch types */
#define XACE_CORE_DISPATCH      0
#define XACE_EXT_DISPATCH       1
#define XACE_RESOURCE_ACCESS    2
#define XACE_DEVICE_ACCESS_HOOK 3

/* Forward declarations - use Xdefs.h definitions to avoid conflicts */
typedef struct _Selection Selection;
typedef struct _DevPrivateList DevPrivateList;
typedef unsigned long Mask;

/* Selection access hook */
typedef int (*XaceHookSelectionAccessProc)(ClientPtr client, Selection **ppSel, Mask access_mode);

/* XaceHookSelectionAccess - Selection access hook wrapper */
static inline int
XaceHookSelectionAccess(ClientPtr client, Selection **ppSel, Mask access_mode)
{
    return Success;
}

/* Main XACE hook - stub implementation for ssX
 * This is a compatibility shim that always returns Success.
 * Note: Don't define as macro to avoid conflicts with Xext/xace.h function decl.
 * Use inline function instead. */
static inline int ssx_XaceHook(int hook_type, void *client, int access_mode) {
    return Success;
}
#define XaceHook ssx_XaceHook

#endif /* _XACE_SSX_H */
