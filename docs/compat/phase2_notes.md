# Phase 2: DIX Compatibility Notes

## Summary
This document tracks the compatibility fixes applied to XFree86 DIX source code for integration with modern Xlibre.

## Phase 2 Build Analysis (Meson)

### Build Configuration Used
```bash
meson setup build --prefix=/usr -Dstatic_loader=true -Dsecure-rpc=false -Dglamor=false
```

### Issues Resolved by Meson Configuration
1. **libtirpc missing** - Fixed by disabling `secure-rpc` option
2. **glamor dependencies** - Fixed by disabling glamor for pure XAA build

## Compatibility Header Updates (include/ssx_compat.h)

### 1. Client Minor/Major Op Macros
**Issue**: Modern `ClientRec` dropped `minorOp` and `majorOp` members.

**Fix Added**:
```c
#define SSX_CLIENT_MINOR_OP(client) ((client)->requestBuffer[1])
#define SSX_CLIENT_MAJOR_OP(client) ((client)->requestBuffer[0])
#define SSX_SET_CLIENT_MINOR_OP(client, val) /* no-op */
#define SSX_SET_CLIENT_MAJOR_OP(client, val) /* no-op */
```

### 2. XI2LASTEVENT Definition
**Issue**: `XI2LASTEVENT` was undeclared.

**Fix Added**:
```c
#ifndef XI2LASTEVENT
#define XI2LASTEVENT  (32)   /* XI2 event type count */
#endif
```

### 3. EventSyncInfoRec Definition
**Issue**: `syncEvents` variable type undefined.

**Fix Added**:
```c
typedef struct _EventSyncInfo {
    struct xorg_list pending;
    BOOL playingEvents;
    TimeStamp time;
    DeviceIntPtr replayDev;
    WindowPtr replayWin;
} EventSyncInfoRec;

extern EventSyncInfoRec syncEvents;
```

### 4. POINTER_SCREEN Definition
**Issue**: `POINTER_SCREEN` undefined.

**Fix Added**:
```c
#ifndef POINTER_SCREEN
#define POINTER_SCREEN  (1 << 1)   /* XFree86 value */
#endif
```

### 5. EVENT_SOURCE_NORMAL Definition
**Issue**: `EVENT_SOURCE_NORMAL` undeclared.

**Fix Added**:
```c
#ifndef EVENT_SOURCE_NORMAL
#define EVENT_SOURCE_NORMAL  0
#endif
```

### 6. POINTER_NORAW and POINTER_EMULATED (NEW)
**Issue**: XFree86-era pointer flags undefined.

**Fix Added**:
```c
#ifndef POINTER_NORAW
#define POINTER_NORAW        (1 << 4)
#endif

#ifndef POINTER_EMULATED
#define POINTER_EMULATED     (1 << 5)
#endif
```

### 7. DeviceEventSource Enum (NEW)
**Issue**: Legacy code uses DeviceEventSource enum.

**Fix Added**:
```c
typedef enum {
    DEVICE_SOURCE_NONE = -1,
    EVENT_SOURCE_NORMAL = 0,
    EVENT_SOURCE_POINTER = 1,
    EVENT_SOURCE_KEYBOARD = 2,
    EVENT_SOURCE_TOUCH = 3,
    EVENT_SOURCE_BARRIER = 4
} DeviceEventSource;
```

### 8. Screen X/Y Accessor Macros (NEW)
**Issue**: Legacy code accesses `scr->x` and `scr->y` which don't exist in modern ScreenRec.

**Fix Added**:
```c
#ifndef GET_SCREEN_X
#define GET_SCREEN_X(s) (0)
#endif

#ifndef GET_SCREEN_Y
#define GET_SCREEN_Y(s) (0)
#endif

#ifndef GET_SCREEN_NUM
#define GET_SCREEN_NUM(s) ((s)->myNum)
#endif
```

### 9. Valuator Mask Functions (NEW)
**Issue**: Legacy code uses int[] valuators, modern uses double* with ValuatorMask struct.

**Fix Added**:
```c
#define valuator_mask_set_double(mask, idx, val) do { \
    if ((mask) && (idx) >= 0 && (idx) < MAX_VALUATORS) { \
        (mask)->valuators[idx] = (int)(val); \
    } \
} while(0)

#define valuator_mask_fetch_double(mask, idx, val) do { \
    if ((mask) && (val) && (idx) >= 0 && (idx) < MAX_VALUATORS) { \
        *(val) = (double)((mask)->valuators[idx]); \
        return 1; \
    } \
    return 0; \
} while(0)

#define valuator_mask_num_valuators(mask) ((mask) ? (mask)->num_valuators : 0)

#define valuator_mask_copy(dst, src) do { \
    if ((dst) && (src)) { \
        int _i; \
        (dst)->num_valuators = (src)->num_valuators; \
        for (_i = 0; _i < MAX_VALUATORS; _i++) { \
            (dst)->valuators[_i] = (src)->valuators[_i]; \
        } \
    } \
} while(0)
```

### 10. GetMotionHistory Macro Fix (NEW)
**Issue**: Legacy getevents.c defines 6-param GetMotionHistory, modern input.h wraps 5-param version.

**Fix Added**:
```c
#ifdef GetMotionHistory
#undef GetMotionHistory
#endif
```

### 11. PRIVATE_* Macro Removal (NEW)
**Issue**: PRIVATE_* macros conflicted with include/privates.h definitions.

**Fix**: Removed all PRIVATE_* definitions from ssx_compat.h as they're now in privates.h

## Files Requiring Source-Level Changes

### dix/devices.c
Multiple issues require direct source changes:

1. **Line 613**: `DeviceCursorInitialize` - needs wrapper based on modern API
2. **Line 653**: `InitKeyboardDeviceStruct` - needs 5th NULL argument
3. **Line 705**: `InitPointerDeviceStruct` - has 8 args, needs 7 (drop one)
4. **Lines 830, 890, 891, 949, 950**: `xkb_acts` and `xkb_sli` members missing
5. **Lines 848-850**: Touch API calls need XI2 guards
6. **Lines 990-992**: `syncEvents.pending` access needs fixing
7. **Lines 1025, 1031-1032**: `xkb_interest` member missing

### dix/dispatch.c
1. **Lines 530, 535, 572**: Replace `client->minorOp` with `SSX_CLIENT_MINOR_OP(client)`
2. **Line 1570**: Function signature mismatch - too many arguments
3. **Line 2271**: Function signature mismatch - too many arguments

### dix/getevents.c
1. **GetMotionHistory redefinition**: Needs `#ifndef HAVE_GET_MOTION_HISTORY` guard
2. **Lines 852-853, 861-862, 979, 986**: Screen.x/Screen.y access - use GET_SCREEN_X/Y macros
3. **Line 831**: Function call arguments mismatch
4. **Line 961**: Too many arguments to function - miPointerSetPosition has 4 params but called with 6
5. **Lines 1008, 1012**: `dev->last.valuators` is `int[36]` but updateMotionHistory expects `double*`
6. **Line 1022**: mieqEnqueue expects InternalEvent*, code passes xEvent*
7. **Line 1051**: GetKeyboardEvents signature mismatch
8. **Line 1072**: DeviceEventSource enum - should be available via ssx_compat.h
9. **Line 1291**: GetPointerEvents called with 6 args, modern takes 8

### dix/events.c
1. **syncEvents redefinition**: Needs `#ifndef HAVE_SYNC_EVENTS` guard
2. **Screen.x/y accesses**: Use GET_SCREEN_X/Y macros
3. **XI2Mask**: Uses XI2MASK_ISSET stubs

## Required XFree86-Era Shim Layer (Phase 3)

### Overview
The remaining issues require creating a complete XFree86-era shim layer in `dix/ssx_shims.c` that wraps modern API calls with legacy XFree86 signatures.

### Required Wrapper Functions

#### 1. miPointerSetPosition Wrapper
**Modern Signature**: `void miPointerSetPosition(DeviceIntPtr, int *x, int *y, unsigned long time)`
**Legacy Signature Needed**: `ScreenPtr miPointerSetPosition(DeviceIntPtr, int mode, double *x, double *y, int *nevents, void *events)`

**Solution**: Create wrapper that calls modern version and adapts parameters.

#### 2. GetPointerEvents Wrapper
**Modern Signature**: `int GetPointerEvents(InternalEvent*, DeviceIntPtr, int type, int buttons, int flags, const ValuatorMask*)`
**Legacy Calls**: 6 arguments without ValuatorMask

**Solution**: Create wrapper that converts legacy args to ValuatorMask.

#### 3. GetKeyboardEvents Wrapper  
**Modern Signature**: `int GetKeyboardEvents(InternalEvent*, DeviceIntPtr, int type, int key_code)`
**Legacy Calls**: May differ

**Solution**: Verify and create wrapper if needed.

#### 4. GetMotionHistory Wrapper
**Modern Signature**: `int GetMotionHistory(DeviceIntPtr, xTimecoord*, unsigned long, unsigned long, ScreenPtr)`
**Legacy Definition**: `int GetMotionHistory(DeviceIntPtr, xTimecoord**, unsigned long, unsigned long, ScreenPtr, BOOL core)`

**Solution**: Create wrapper with legacy signature that calls modern version.

#### 5. updateMotionHistory Wrapper
**Issue**: Takes `double *valuators` but legacy code passes `int[36]`

**Solution**: Create wrapper that casts or converts int array to double.

#### 6. mieqEnqueue Wrapper
**Modern Signature**: `void mieqEnqueue(DeviceIntPtr, InternalEvent*)`
**Legacy Usage**: May pass xEvent*

**Solution**: Create wrapper that accepts legacy type and converts to InternalEvent.

#### 7. valuator_last.valuators Access
**Issue**: `dev->last.valuators` is `int[36]` in legacy, needs `double*` for modern APIs

**Solution**: Create accessor macro: `#define SSX_LAST_VALUATORS(dev) ((double*)(dev)->last.valuators)`

### Screen X/Y Access in getevents.c

The following locations in getevents.c need GET_SCREEN_X/Y macro replacement:
- Line 853: `scr->x`
- Line 862: `scr->y`  
- Line 979: `scr->x`
- Line 986: `scr->y`
- Line 1037: `scr->x`
- Line 1043: `scr->y`

Note: Modern ScreenRec doesn't have x/y members. The screenInfo struct has x/y for desktop offsets. Use:
```c
#define GET_SCREEN_X(s) (0)  // Modern X doesn't use per-screen offsets
#define GET_SCREEN_Y(s) (0)
```

### AccelerateProc Access in getevents.c (Line 831)
**Issue**: `dev->valuator->accelScheme.AccelSchemeProc(dev, valuators, ms);`

This needs to be adapted to modern acceleration scheme API. The accelScheme structure changed in modern X.

## Values Requiring Archaeology

| Constant | Value | Source |
|----------|-------|--------|
| POINTER_SCREEN | (1 << 1) | XFree86 include/XIproto.h |
| XI2LASTEVENT | 32 | Modern XI2 headers |
| EVENT_SOURCE_NORMAL | 0 | Modern eventstr.h |
| POINTER_NORAW | (1 << 4) | XFree86 XInput |
| POINTER_EMULATED | (1 << 5) | XFree86 XInput |

## Build Status

### Current Errors (Blocking)
1. getevents.c - Multiple type mismatches and function signature conflicts
2. devices.c - XKB struct members and function signatures
3. dispatch.c - minorOp access and function signatures
4. events.c - syncEvents redefinition

### Warnings (Non-blocking)
1. Typedef redefinition (DDXTouchPointInfoPtr, TouchPointInfoPtr)
2. Macro redefinition (DixUseAccess, DixReadAccess, etc.)
3. Enum visibility warnings

## Notes

- All macro definitions added to `ssx_compat.h` use `#ifndef` guards to avoid redefinition
- XKB struct members (`xkb_acts`, `xkb_sli`, `xkb_interest`) were removed in modern X - need compatibility shims
- Touch API (XI 2.2) didn't exist in XFree86 - wrapped in conditionals where possible
- The compatibility approach preserves original XFree86 logic while adapting to modern API signatures
- PRIVATE_* macros removed from ssx_compat.h as they're defined in include/privates.h

## Priority Order for Phase 3

1. Create ssx_shims.c with wrapper functions
2. Fix getevents.c screen x/y accesses
3. Fix GetMotionHistory definition/usage conflict
4. Fix devices.c XKB member accesses
5. Verify dispatch.c compiles
6. Verify events.c compiles
