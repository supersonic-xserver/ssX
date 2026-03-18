/************************************************************

Author: Eamon Walsh <ewalsh@epoch.ncsc.mil>

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
this permission notice appear in supporting documentation.  This permission
notice shall be included in all copies or substantial portions of the
Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

********************************************************/

#ifndef _XACE_H
#define _XACE_H

/* Hook return codes */
#define XaceErrorOperation  0
#define XaceAllowOperation  1
#define XaceIgnoreOperation 2

/* ssX compatibility: Additional access types */
#define XACE_SERVER_ACCESS       1
#define XACE_DEVICE_ACCESS       2
#define XACE_PROPERTY_ACCESS    3
#define XACE_SELECTION_ACCESS    4
#define XACE_DRAWABLE_ACCESS    5
#define XACE_SCREEN_ACCESS      6
#define XACE_WINDOW_ACCESS      7
#define XACE_PIXMAP_ACCESS     8
#define XACE_CURSOR_ACCESS     9
#define XACE_GC_ACCESS         10
#define XACE_FONT_ACCESS       11

/* Access masks */
#define DixReadAccess           (1 << 0)
#define DixWriteAccess          (1 << 1)
#define DixGetAttrAccess       (1 << 2)
#define DixSetAttrAccess       (1 << 3)
#define DixUseAccess           (1 << 4)
#define DixCreateAccess        (1 << 5)
#define DixManageAccess        (1 << 6)
#define DixDestroyAccess       (1 << 7)
#define DixRemoveAccess        (1 << 13)
#define DixListPropAccess      (1 << 9)
#define DixGetFocusAccess     (1 << 10)
#define DixSetFocusAccess     (1 << 11)
#define DixGrabAccess         (1 << 12)

#ifdef XACE

#define XACE_EXTENSION_NAME		"XAccessControlExtension"
#define XACE_MAJOR_VERSION		1
#define XACE_MINOR_VERSION		0

#include "pixmap.h"     /* for DrawablePtr */
#include "regionstr.h"  /* for RegionPtr */

#define XaceNumberEvents		0
#define XaceNumberErrors		0

/* security hooks */
/* Constants used to identify the available security hooks
 */
#define XACE_CORE_DISPATCH		0
#define XACE_EXT_DISPATCH		1
#define XACE_RESOURCE_ACCESS		2
#define XACE_DEVICE_ACCESS		3
#define XACE_PROPERTY_ACCESS		4
#define XACE_DRAWABLE_ACCESS		5
#define XACE_MAP_ACCESS			6
#define XACE_BACKGRND_ACCESS		7
#define XACE_EXT_ACCESS			8
#define XACE_HOSTLIST_ACCESS		9
#define XACE_SITE_POLICY		10
#define XACE_DECLARE_EXT_SECURE		11
#define XACE_AUTH_AVAIL			12
#define XACE_KEY_AVAIL			13
#define XACE_WINDOW_INIT		14
#define XACE_AUDIT_BEGIN		15
#define XACE_AUDIT_END			16
#define XACE_NUM_HOOKS			17

extern CallbackListPtr XaceHooks[XACE_NUM_HOOKS];

/* Note: XaceHook is defined in include/xace.h as an inline function
 * when XACE is enabled. Don't declare it here to avoid conflicts. */

/* Register a callback for a given hook.
 */
#define XaceRegisterCallback(hook,callback,data) \
    AddCallback(XaceHooks+(hook), callback, data)

/* Unregister an existing callback for a given hook.
 */
#define XaceDeleteCallback(hook,callback,data) \
    DeleteCallback(XaceHooks+(hook), callback, data)


/* From the original Security extension...
 */

extern void XaceCensorImage(
    ClientPtr client,
    RegionPtr pVisibleRegion,
    long widthBytesLine,
    DrawablePtr pDraw,
    int x, int y, int w, int h,
    unsigned int format,
    char * pBuf
    );

#else /* XACE */

/* Define calls away when XACE is not being built. */

#define XaceHook(...) (Success)
#define XaceCensorImage(...) do { } while(0)

#endif /* XACE */

#endif /* _XACE_H */
