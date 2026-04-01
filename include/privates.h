/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef PRIVATES_H
#define PRIVATES_H 1

#include "dix.h"
#include "resource.h"

/*****************************************************************
 * STUFF FOR PRIVATES
 *****************************************************************/

/*
 * XFree86 4.8.0 (May 2009) style DevPrivateKey definitions.
 * The modern Xorg code uses 'typedef int *DevPrivateKey' which is
 * incompatible with the 2009 DIX code that expects a struct.
 */
typedef struct _DevPrivateKeyRec {
    int privateIndex;
} DevPrivateKeyRec, *DevPrivateKey;

struct _Private;
typedef struct _Private PrivateRec;

/*
 * Legacy private key types for XFree86 4.8.0 compatibility
 * These are used by miext/sync and other legacy extensions
 */
typedef enum {
    PRIVATE_SCREEN,
    PRIVATE_SYNC_FENCE,
    PRIVATE_SYNC_FENCE_OBJ,
    PRIVATE_SYNC_TRIGGER,
    PRIVATE_SYNC_ITEMS,
    PRIVATE_WINDOW,
    PRIVATE_GC,
    PRIVATE_PIXMAP,
    PRIVATE_DEVICE,
    PRIVATE_CLIENT,
} DevPrivateType;

/*
 * Request pre-allocated private space for your driver/module.
 * Calling this is not necessary if only a pointer by itself is needed.
 */
extern int
dixRequestPrivate(const DevPrivateKey key, unsigned size);

/*
 * Allocates a new private and attaches it to an existing object.
 */
extern pointer *
dixAllocatePrivate(PrivateRec **privates, const DevPrivateKey key);

/*
 * Look up a private pointer.
 * In legacy mode, use _dixLookupPrivate with DevUnion** to PrivateRec** cast
 */
extern void *
_dixLookupPrivate(PrivateRec **privates, const DevPrivateKey key);

/*
 * Compatibility wrapper for DevUnion vs PrivateRec type mismatch
 * In legacy mode, pScreen->devPrivates is DevUnion** but functions expect PrivateRec**
 */
#ifdef SSX_LEGACY_MODE
#include "miscstruct.h"
#define dixLookupPrivate(p, k) _dixLookupPrivate((PrivateRec **)(p), k)
#else
#define dixLookupPrivate(p, k) _dixLookupPrivate(p, k)
#endif

/*
 * Look up the address of a private pointer.
 */
pointer *
dixLookupPrivateAddr(PrivateRec **privates, const DevPrivateKey key);

/*
 * Set a private pointer.
 */
int
dixSetPrivate(PrivateRec **privates, const DevPrivateKey key, pointer val);

/*
 * Register callbacks to be called on private allocation/freeing.
 * The calldata argument to the callbacks is a PrivateCallbackPtr.
 */
typedef struct _PrivateCallback {
    DevPrivateKey key;	/* private registration key */
    pointer *value;	/* address of private pointer */
} PrivateCallbackRec;

extern int
dixRegisterPrivateInitFunc(const DevPrivateKey key, 
			   CallbackProcPtr callback, pointer userdata);

extern int
dixRegisterPrivateDeleteFunc(const DevPrivateKey key,
			     CallbackProcPtr callback, pointer userdata);

/*
 * Frees private data.
 */
extern void
dixFreePrivates(PrivateRec *privates);

/*
 * Resets the subsystem, called from the main loop.
 */
extern int
dixResetPrivates(void);

/*
 * These next two functions are necessary because the position of
 * the devPrivates field varies by structure and calling code might
 * only know the resource type, not the structure definition.
 */

/*
 * Looks up the offset where the devPrivates field is located.
 * Returns -1 if no offset has been registered for the resource type.
 */
extern int
dixLookupPrivateOffset(RESTYPE type);

/*
 * Specifies the offset where the devPrivates field is located.
 * A negative value indicates no devPrivates field is available.
 */
extern int
dixRegisterPrivateOffset(RESTYPE type, int offset);

/*
 * Convenience macro for adding an offset to an object pointer
 * when making a call to one of the devPrivates functions
 */
#define DEVPRIV_AT(ptr, offset) ((PrivateRec **)((char *)ptr + offset))

#endif /* PRIVATES_H */
