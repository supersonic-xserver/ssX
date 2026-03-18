/*

Copyright 1991, 1993, 1994, 1998  The Open Group

Permission to use, copy, modify, distribute, and sell this software and its
documentation for any purpose is hereby granted without fee, provided that
the above copyright notice appear in all copies and that both that
copyright notice and this permission notice appear in supporting
documentation.

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
OPEN GROUP BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

Except as contained in this notice, the name of The Open Group shall not be
used in advertising or otherwise to promote the sale, use or other dealings
in this Software without prior written authorization from The Open Group.

*/

/***********************************************************
Copyright 1991,1993 by Digital Equipment Corporation, Maynard, Massachusetts,
and Olivetti Research Limited, Cambridge, England.

                        All Rights Reserved

Permission to use, copy, modify, and distribute this software and its 
documentation for any purpose and without fee is hereby granted, 
provided that the above copyright notice appear in all copies and that
both that copyright notice and this permission notice appear in 
supporting documentation, and that the names of Digital or Olivetti
not be used in advertising or publicity pertaining to distribution of the
software without specific, written prior permission.  

DIGITAL AND OLIVETTI DISCLAIM ALL WARRANTIES WITH REGARD TO THIS
SOFTWARE, INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND
FITNESS, IN NO EVENT SHALL THEY BE LIABLE FOR ANY SPECIAL, INDIRECT OR
CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
PERFORMANCE OF THIS SOFTWARE.

******************************************************************/

#ifndef _SYNCSRV_H_
#define _SYNCSRV_H_

#include <X11/Xproto.h>
#include <stdint.h>

/* --- Primitives Fix ---
 * We define these only if they haven't been seen yet
 * to stop the 'Unknown type name' errors.
 */
#ifndef _XTYPEDEF_POINTER
typedef void *pointer;
#define _XTYPEDEF_POINTER
#endif

#ifndef _XTYPEDEF_XID
typedef unsigned long XID;
#define _XTYPEDEF_XID
#endif

#ifndef Bool
#define Bool int
#define TRUE 1
#define FALSE 0
#endif

/* --- LOCAL XSYNC REPLACEMENTS --- */
typedef XID XSyncCounter;
typedef XID XSyncAlarm;

/* --- CARD64 / XSyncValue FIX ---
 * To avoid 'redefinition with different types', we check if CARD64 exists.
 * If your Xmd.h defines CARD64 as 'unsigned long', we use that to keep
 * the compiler from complaining.
 */
#ifndef CARD64
#if defined(__alpha__) || defined(__alpha) || defined(_XSERVER64)
typedef unsigned long CARD64;
#else
typedef uint64_t CARD64;
#endif
#endif

typedef CARD64 XSyncValue;

/* --- The rest of the file follows --- */

#ifndef _CLIENT_PTR
typedef struct _Client *ClientPtr;
#define _CLIENT_PTR
#endif

typedef struct _SyncCounter {
    ClientPtr           client;
    XSyncCounter        id;
    CARD64              value;
    struct _SyncTriggerList *pTriglist;
    Bool                beingDestroyed;
    struct _SysCounterInfo *pSysCounterInfo;
} SyncCounter;

typedef enum {
    XSyncCounterNeverChanges,
    XSyncCounterNeverIncreases,
    XSyncCounterNeverDecreases,
    XSyncCounterUnrestricted
} SyncCounterType;

typedef struct _SysCounterInfo {
    char    *name;
    CARD64  resolution;
    CARD64  bracket_greater;
    CARD64  bracket_less;
    SyncCounterType counterType;
    void        (*QueryValue)(
        pointer /*pCounter*/,
        CARD64 * /*freshvalue*/
    );
    void    (*BracketValues)(
        pointer /*pCounter*/,
        CARD64 * /*lessthan*/,
        CARD64 * /*greaterthan*/
    );
} SysCounterInfo;

typedef struct _SyncTrigger {
    SyncCounter *pCounter;
    CARD64  wait_value;
    unsigned int value_type;
    unsigned int test_type;
    CARD64  test_value;
    Bool    (*CheckTrigger)(
        struct _SyncTrigger * /*pTrigger*/,
        CARD64 /*newval*/
    );
    void    (*TriggerFired)(
        struct _SyncTrigger * /*pTrigger*/
    );
    void    (*CounterDestroyed)(
        struct _SyncTrigger * /*pTrigger*/
    );
} SyncTrigger;

typedef struct _SyncTriggerList {
    SyncTrigger *pTrigger;
    struct _SyncTriggerList *next;
} SyncTriggerList;

typedef struct _SyncAlarmClientList {
    ClientPtr   client;
    XID         delete_id;
    struct _SyncAlarmClientList *next;
} SyncAlarmClientList;

typedef struct _SyncAlarm {
    SyncTrigger trigger;
    ClientPtr   client;
    XSyncAlarm  alarm_id;
    CARD64      delta;
    int         events;
    int         state;
    SyncAlarmClientList *pEventClients;
} SyncAlarm;

typedef struct {
    ClientPtr   client;
    uint32_t    delete_id; /* Using uint32_t to be safe */
    int         num_waitconditions;
} SyncAwaitHeader;

typedef struct {
    SyncTrigger trigger;
    CARD64      event_threshold;
    SyncAwaitHeader *pHeader;
} SyncAwait;

typedef union {
    SyncAwaitHeader header;
    SyncAwait       await;
} SyncAwaitUnion;

/* Prototypes */
extern pointer SyncCreateSystemCounter(
    char * /* name */,
    CARD64 inital_value,
    CARD64 resolution,
    SyncCounterType /* change characterization */,
    void (*QueryValue)(pointer, CARD64 *),
                                       void (*BracketValues)(pointer, CARD64 *, CARD64 *)
);

extern void SyncChangeCounter(SyncCounter *pCounter, CARD64 new_value);
extern void SyncDestroySystemCounter(pointer pCounter);
extern void InitServertime(void);
extern void SyncExtensionInit(void);

#endif /* _SYNCSRV_H_ */
