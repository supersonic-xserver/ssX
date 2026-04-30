/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef LBX_DELTA_STRUCT_H
#define LBX_DELTA_STRUCT_H

#define MIN_CACHEABLE_LEN		8

#define DELTA_CACHEABLE(pcache, len)	\
	((len) > MIN_CACHEABLE_LEN && (len) <= (pcache)->maxDeltasize)

/*
 * An entry in the delta compactor cache
 */
typedef struct _LBXDeltaElem {
    int			length;
    unsigned char	*buf;
} LBXDeltaElemRec, *LBXDeltaElemPtr;


/*
 * Delta compactor cache
 */
typedef struct _LBXDeltas {
    unsigned short	nDeltas;
    unsigned short	maxDeltasize;
    LBXDeltaElemPtr	deltas;
    unsigned short	nextDelta;
    unsigned short	activeDeltas;	/* only needed for outgoing */
} LBXDeltasRec, *LBXDeltasPtr;


/*
 * Motion delta cache
 */

typedef struct {
    BYTE swapped;
    BYTE detail;
    CARD16 sequenceNumber B16;
    Time time B32;
    Window root B32, event B32, child B32;
    INT16 rootX B16, rootY B16, eventX B16, eventY B16;
    KeyButMask state B16;
    BOOL sameScreen;		
} lbxMotionCache;


/*
 * Motion delta events
 */

typedef struct {
    BYTE type;		/* always eventBase + LbxQuickMotionDeltaEvent */
    CARD8 deltaTime;
    INT8 deltaX;
    INT8 deltaY;
} lbxQuickMotionDeltaEvent;
#define sz_lbxQuickMotionDeltaEvent 4

typedef struct {
    BYTE type;		/* always eventBase + LbxEvent */
    BYTE lbxType;	/* LbxMotionDeltaEvent */
    INT8 deltaX;
    INT8 deltaY;
    CARD16 deltaTime B16;
    CARD16 deltaSequence B16;
} lbxMotionDeltaEvent;
#define sz_lbxMotionDeltaEvent 8

extern int LBXInitDeltaCache ( LBXDeltasPtr pcache, int nDeltas, 
			       int maxDeltasize );
extern void LBXFreeDeltaCache ( LBXDeltasPtr pcache );
extern int LBXDeltaMinDiffs ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			      int inmsglen, int maxdiff, int *pindex );
extern void LBXEncodeDelta ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			     int ndiff, int index, unsigned char *buf );
extern int LBXDecodeDelta ( LBXDeltasPtr pcache, xLbxDiffItem *deltas, 
			    int ndiff, int index, unsigned char **buf );
extern void LBXAddDeltaOut ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			     int inmsglen );
extern void LBXAddDeltaIn ( LBXDeltasPtr pcache, unsigned char *inmsg, 
			    int inmsglen );

#endif /* LBX_DELTA_STRUCT_H */
