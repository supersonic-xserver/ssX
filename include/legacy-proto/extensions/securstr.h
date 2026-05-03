/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _SECURSTR_H
#define _SECURSTR_H

#include <X11/extensions/security.h>

#define SECURITY_EXTENSION_NAME		"SECURITY"
#define SECURITY_MAJOR_VERSION		1
#define SECURITY_MINOR_VERSION		0

#define X_SecurityQueryVersion		0
#define X_SecurityGenerateAuthorization 1
#define X_SecurityRevokeAuthorization   2

typedef struct {
    CARD8       reqType;
    CARD8       securityReqType;
    CARD16      length B16;
    CARD16      majorVersion B16;
    CARD16      minorVersion B16;
} xSecurityQueryVersionReq;
#define sz_xSecurityQueryVersionReq 	8

typedef struct {
    CARD8   type;
    CARD8   pad0;
    CARD16  sequenceNumber B16;
    CARD32  length	 B32;
    CARD16  majorVersion B16;
    CARD16  minorVersion B16;
    CARD32  pad1	 B32;
    CARD32  pad2	 B32;
    CARD32  pad3	 B32;
    CARD32  pad4	 B32;
    CARD32  pad5	 B32;
 } xSecurityQueryVersionReply;
#define sz_xSecurityQueryVersionReply  	32

typedef struct {
    CARD8       reqType;
    CARD8       securityReqType;
    CARD16      length B16;
    CARD16	nbytesAuthProto B16;
    CARD16	nbytesAuthData B16;
    CARD32	valueMask B32; 
    /* auth protocol name padded to 4 bytes */
    /* auth protocol data padded to 4 bytes */
    /* list of CARD32 values, if any */
} xSecurityGenerateAuthorizationReq;
#define sz_xSecurityGenerateAuthorizationReq 12

typedef struct {
    CARD8   type;
    CARD8   pad0;
    CARD16  sequenceNumber B16;
    CARD32  length	 B32;
    CARD32  authId	 B32;
    CARD16  dataLength   B16;
    CARD16  pad1	 B16;
    CARD32  pad2	 B32;
    CARD32  pad3	 B32;
    CARD32  pad4	 B32;
    CARD32  pad5	 B32;
 } xSecurityGenerateAuthorizationReply;
#define sz_xSecurityGenerateAuthorizationReply  	32

typedef struct {
    CARD8       reqType;
    CARD8       securityReqType;
    CARD16      length B16;
    CARD32	authId B32;
} xSecurityRevokeAuthorizationReq;
#define sz_xSecurityRevokeAuthorizationReq 8

typedef struct _xSecurityAuthorizationRevokedEvent {
    BYTE	type;
    BYTE	detail;
    CARD16	sequenceNumber B16;
    CARD32	authId B32;
    CARD32	pad0	 B32;
    CARD32	pad1	 B32;
    CARD32	pad2	 B32;
    CARD32	pad3	 B32;
    CARD32	pad4	 B32;
    CARD32	pad5	 B32;
} xSecurityAuthorizationRevokedEvent;
#define sz_xSecurityAuthorizationRevokedEvent 32

#endif /* _SECURSTR_H */
