/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _XRANDRP_H_
#define RANDR_COMPAT_PROTO_H

#include <X11/extensions/randrproto.h>
#include "dixstruct.h"
#include "windowstr.h"
#include "randrstr.h"

/* RandR 1.2 GetCrtcInfo request/reply */
#ifndef xRRGetCrtcInfoReq_DEFINED
#define xRRGetCrtcInfoReq_DEFINED
typedef struct {
    CARD8  reqType, randrReqType;
    CARD16 length;
    RRCrtc crtc;
    Time   configTimestamp;
} xRRGetCrtcInfoReq;
#endif

#ifndef xRRGetCrtcInfoReply_DEFINED
#define xRRGetCrtcInfoReply_DEFINED
typedef struct {
    BYTE   type, status;
    CARD16 sequenceNumber;
    CARD32 length;
    Time   timestamp;
    INT16  x, y;
    CARD16 width, height, mode, rotation, rotations, nOutput, nPossibleOutput;
} xRRGetCrtcInfoReply;
#endif
#define sz_xRRGetCrtcInfoReply 32

/* RandR 1.2 CreateMode request/reply */
#ifndef xRRCreateModeReq_DEFINED
#define xRRCreateModeReq_DEFINED
typedef struct {
    CARD8       reqType, randrReqType;
    CARD16      length;
    Window      window;
    xRRModeInfo modeInfo;
} xRRCreateModeReq;
#endif

#ifndef xRRCreateModeReply_DEFINED
#define xRRCreateModeReply_DEFINED
typedef struct {
    BYTE   type, pad0;
    CARD16 sequenceNumber;
    CARD32 length;
    RRMode mode;
    CARD32 pad[5];
} xRRCreateModeReply;
#endif
#define sz_xRRCreateModeReply 32

/* RandR 1.2 GetOutputInfo request/reply */
#ifndef xRRGetOutputInfoReq_DEFINED
#define xRRGetOutputInfoReq_DEFINED
typedef struct {
    CARD8  reqType, randrReqType;
    CARD16 length;
    RROutput output;
    Time   configTimestamp;
} xRRGetOutputInfoReq;
#endif

#ifndef xRRGetOutputInfoReply_DEFINED
#define xRRGetOutputInfoReply_DEFINED
typedef struct {
    BYTE   type, status;
    CARD16 sequenceNumber;
    CARD32 length;
    Time   timestamp;
    RRCrtc crtc;
    CARD32 mmWidth, mmHeight;
    CARD8  connection, subpixelOrder;
    CARD16 nCrtcs, nModes, nPreferred, nClones, nameLen;
} xRRGetOutputInfoReply;
#endif
#define sz_xRRGetOutputInfoReply 36

/* RandR 1.6 CreateLease request */
#ifndef xRRCreateLeaseReq_DEFINED
#define xRRCreateLeaseReq_DEFINED
typedef struct {
    CARD8  reqType, randrReqType;
    CARD16 length;
    Window window;
    CARD16 nCrtcs, nOutputs;
    RRLease lid;
} xRRCreateLeaseReq;
#endif

/* RandR 1.6 FreeLease request */
#ifndef xRRFreeLeaseReq_DEFINED
#define xRRFreeLeaseReq_DEFINED
typedef struct {
    CARD8  reqType, randrReqType;
    CARD16 length;
    RRLease lid;
    CARD8  terminate;
    CARD8  pad[19];
} xRRFreeLeaseReq;
#endif

/* Access mode constants */
#ifndef DixGetAttrAccess
#define DixGetAttrAccess  (1<<4)
#define DixSetAttrAccess  (1<<5)
#define DixDestroyAccess (1<<8)
#endif

#endif /* _XRANDRP_H_ */
