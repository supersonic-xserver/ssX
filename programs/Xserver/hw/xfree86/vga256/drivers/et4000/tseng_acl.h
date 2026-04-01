/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* $XFree86$ */

#ifndef _TSENG_ACL_H
#define _TSENG_ACL_H

typedef unsigned char *ByteP; 
typedef volatile unsigned char *VByteP;
typedef unsigned short *WordP;
typedef unsigned *LongP;

/*
 * Shortcuts to Tseng memory-mapped accelerator-control registers
 */

extern
ByteP MMU_CONTROL;


extern
ByteP ACL_SUSPEND_TERMINATE,
      ACL_OPERATION_STATE,
      ACL_SYNC_ENABLE,
      ACL_INTERRUPT_MASK,
      ACL_INTERRUPT_STATUS,
      ACL_ACCELERATOR_STATUS;

/* for ET6000: */
#define ACL_6K_CONFIG ACL_SYNC_ENABLE

extern
WordP ACL_X_POSITION,
      ACL_Y_POSITION;

extern
WordP ACL_NQ_X_POSITION,
      ACL_NQ_Y_POSITION;


extern
LongP ACL_PATTERN_ADDRESS,
      ACL_SOURCE_ADDRESS;


extern
WordP ACL_PATTERN_Y_OFFSET,
      ACL_SOURCE_Y_OFFSET,
      ACL_DESTINATION_Y_OFFSET;


extern
ByteP ACL_VIRTUAL_BUS_SIZE,     /* only for w32 and w32i */
      ACL_XY_DIRECTION,
      ACL_PIXEL_DEPTH;          /* only for w32p_rev_A and w32p_rev_B */


extern
ByteP ACL_PATTERN_WRAP,
      ACL_SOURCE_WRAP;


extern
WordP ACL_X_COUNT,
      ACL_Y_COUNT;


extern
ByteP ACL_ROUTING_CONTROL,
      ACL_RELOAD_CONTROL,
      ACL_BACKGROUND_RASTER_OPERATION,
      ACL_FOREGROUND_RASTER_OPERATION;

/* for ET6000: */
#define ACL_MIX_CONTROL ACL_ROUTING_CONTROL
#define ACL_STEPPING_INHIBIT ACL_RELOAD_CONTROL

extern
LongP ACL_DESTINATION_ADDRESS,

      /* only for w32p_rev_A and w32p_rev_B */
      ACL_MIX_ADDRESS;


extern
WordP ACL_MIX_Y_OFFSET,
      ACL_ERROR_TERM,
      ACL_DELTA_MINOR,
      ACL_DELTA_MAJOR;

/* for ET6000 only */
extern
ByteP ACL_POWER_CONTROL;


extern int W32OpTable[16];
extern int W32PatternOpTable[16];

extern int W32BresTable[8];

extern long W32ForegroundPing;
extern long W32ForegroundPong;
extern long W32BackgroundPing;
extern long W32BackgroundPong;
extern long W32PatternPing;
extern long W32PatternPong;
extern long W32Mix;

extern LongP MemW32ForegroundPing;
extern LongP MemW32ForegroundPong;
extern LongP MemW32BackgroundPing;
extern LongP MemW32BackgroundPong;
extern LongP MemW32PatternPing;
extern LongP MemW32PatternPong;
extern LongP MemW32Mix;    /* ping-ponging the MIX map is done by XAA */ 

/******************************************************************************/

#define WAIT_QUEUE \
{while (*(volatile unsigned char *)ACL_ACCELERATOR_STATUS & 0x1);}


#define WAIT_ACL_VERBOSE \
  { int cnt=0; while (*(volatile unsigned char *)ACL_ACCELERATOR_STATUS & 0x2) cnt++; ErrorF("W%d ",cnt);}

#define WAIT_ACL \
  { while (*(volatile unsigned char *)ACL_ACCELERATOR_STATUS & 0x2); }

  
#define WAIT_XY \
  {while (*(volatile unsigned char *)ACL_ACCELERATOR_STATUS & 0x4);}


#define SET_XY(X, Y) \
    {*((LongP) ACL_X_COUNT) = (((Y) - 1) << 16) + ((X) * bytesperpixel - 1);}

#define SET_XY_RAW(X, Y) \
    {*((LongP) ACL_X_COUNT) = ((Y) << 16) + (X);}

#define SET_DELTA(Min, Maj) \
    {*((LongP) ACL_DELTA_MINOR) = ((Maj) << 16) + (Min);}


/* Must do 0x09 (in one operation) for the W32 */
#define START_ACL(dst) \
{ \
    *(ACL_DESTINATION_ADDRESS) = dst; \
    if (et4000_type <= TYPE_ET4000W32I) *ACL_OPERATION_STATE = 0x09; \
}


#define START_ACL_CPU(dst) \
{ \
	*(ACL_DESTINATION_ADDRESS) = dst; \
}

#define PINGPONG \
    if (Fg == W32ForegroundPing) \
    { \
      MemFg = MemW32ForegroundPong; Fg = W32ForegroundPong;  \
      MemBg = MemW32BackgroundPong; Bg = W32BackgroundPong;  \
      MemPat = MemW32PatternPong; Pat = W32PatternPong;  \
    } \
    else \
    { \
      MemFg = MemW32ForegroundPing; Fg = W32ForegroundPing; \
      MemBg = MemW32BackgroundPing; Bg = W32BackgroundPing;  \
      MemPat = MemW32PatternPing; Pat = W32PatternPing;  \
    }


/***********************************************************************/

void tseng_init_acl();


#endif
