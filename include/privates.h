/***********************************************************

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHOR BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN
AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

******************************************************************/

#ifndef PRIVATES_H
#define PRIVATES_H 1

#include "dix.h"
#include "resource.h"

/*****************************************************************
 * STUFF FOR PRIVATES
 *****************************************************************/

/* DevPrivateKeyRec - used by older XAA code for private key storage */
typedef struct _DevPrivateKeyRec {
    int offset;
    int size;
    Bool initialized;
    Bool allocated;
    int type;
    struct _DevPrivateKeyRec *next;
} DevPrivateKeyRec;

/* DevPrivateKey is a pointer to DevPrivateKeyRec - for XFree86/XAA compatibility */
typedef DevPrivateKeyRec *DevPrivateKey;

typedef struct _DevPrivateSetRec {
    DevPrivateKey key;
    unsigned offset;
    int created;
} DevPrivateSetRec, *DevPrivateSet;

struct _Private;
typedef struct _Private PrivateRec;

/* DevPrivateList - list of private pointers for an object */
typedef struct _DevPrivateList {
    DevPrivateKey key;
    pointer val;
    struct _DevPrivateList *next;
} DevPrivateList;

/* Define ConfigNotifyProcPtr - used by DRI3 and others */
typedef int (*ConfigNotifyProcPtr) (ScreenPtr screen, 
                                    int x, int y, int w, int h, int bw);

/*
 * Look up a private pointer.
 */
pointer
dixLookupPrivate(PrivateRec **privates, const DevPrivateKey key);

/* Add compatibility wrapper for dixLookupPrivate that accepts DevUnion** */
static inline pointer
dixLookupPrivateCompat(PrivateRec **privates, DevPrivateKey key)
{
    return dixLookupPrivate(privates, key);
}
#define dixLookupPrivate(d, k) dixLookupPrivateCompat((PrivateRec**)(d), (DevPrivateKey)(k))

/* Private key type identifiers - for dixRegisterPrivateKey */
#define PRIVATE_SCREEN 1
#define PRIVATE_WINDOW 2
#define PRIVATE_PIXMAP 3
#define PRIVATE_GC 4
#define PRIVATE_FONT 5
#define PRIVATE_CURSOR 6
#define PRIVATE_DEVICE 7

/* Compatibility function for registering private keys - used by DRI3, randr, etc. */
/* Returns TRUE if successful */
static inline int
dixRegisterPrivateKey(DevPrivateKey *key, int private_id, unsigned size)
{
    *key = (DevPrivateKey)(intptr_t)private_id;
    return 1;
}

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
 * Look up the address of a private pointer.
 */
pointer *
dixLookupPrivateAddr(PrivateRec **privates, const DevPrivateKey key);

/*
 * Set a private pointer.
 */
int
dixSetPrivate(PrivateRec **privates, const DevPrivateKey key, pointer val);

/* Add compatibility wrapper for dixSetPrivate that accepts DevUnion** */
static inline int
dixSetPrivateCompat(PrivateRec **privates, DevPrivateKey key, pointer val)
{
    return dixSetPrivate(privates, key, val);
}
#define dixSetPrivate(d, k, v) dixSetPrivateCompat((PrivateRec**)(d), (DevPrivateKey)(k), (pointer)(v))

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

/*
 * Screen-specific private allocation functions
 * These are used by the pixmap code
 */
extern unsigned int
dixScreenSpecificPrivatesSize(ScreenPtr pScreen, int private_id);

extern void
dixInitScreenPrivates(ScreenPtr pScreen, void *p1, void *p2, int private_id);

extern void
dixFiniPrivates(void *p, int private_id);

#endif /* PRIVATES_H */
