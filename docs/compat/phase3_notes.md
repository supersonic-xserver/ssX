# Phase 3: DIX Source-Level Surgery - Implementation Notes

## Session Update: March 17, 2026 - Meson Build Analysis

### Build Analysis Summary
Ran Meson build on OpenMandriva Cooker with Clang to identify remaining incompatibilities between legacy XFree86 codebase and modern xlibre headers.

### Fixes Applied This Session:

#### 1. Damage Extension Stub Conflicts ✅ FIXED
**Issue:** Macros in ssx_compat.h (DamageReportLevel, DamageReportNone, DamageCreate, DamageRegion) conflicted with actual definitions in miext/damage/damage.h

**Solution:** Added proper include guard handling:
```c
// In include/ssx_compat.h
#ifdef _DAMAGE_H_
#undef _DAMAGE_H_
#endif
#ifndef DamageReportLevel
typedef enum { DamageReportNoneVal = 0 } DamageReportLevel;
#define DamageReportNone ((DamageReportLevel)0)
#endif
// Stub declarations...
```

Also removed duplicate DamageReportNone macro from miext/damage/damage.h

#### 2. Valuator Scroll Type Assignment ✅ FIXED
**Issue:** `dce->valuators[i].scroll = slave->valuator->axes[i].scroll` - assigning union to int

**Solution:** Changed to use `.scroll.type` since it's a union with `increment` and `type` members:
```c
dce->valuators[i].scroll = slave->valuator->axes[i].scroll.type;
```

#### 3. AccelSchemeProc Signature Mismatch ✅ FIXED
**Issue:** Legacy XAA used 5 parameters (dev, first_valuator, num_valuators, valuators*, time), modern uses ValuatorMask*

**Solution:** Modified accelPointer() in dix/getevents.c to convert:
```c
static void accelPointer(DeviceIntPtr dev, ValuatorMask *valuators, CARD32 ms)
{
    if (dev->valuator->accelScheme.AccelSchemeProc) {
        int vals[MAX_VALUATORS];
        int i;
        for (i = 0; i < valuator_mask_num_valuators(valuators); i++) {
            double v;
            if (valuator_mask_fetch_double(valuators, i, &v))
                vals[i] = (int)v;
        }
        dev->valuator->accelScheme.AccelSchemeProc(dev, 0, valuator_mask_num_valuators(valuators), vals, ms);
    }
}
```

---

## Previous Session: Core Philosophy & Objectives

## Objective
Resolve source-level incompatibilities in dix/devices.c, dix/events.c, and dix/getevents.c to enable a static build of ssX on modern LLVM/Clang environments.

## Core Philosophy
We are preserving the XFree86 Acceleration Architecture (XAA) and CPU-side rendering. Do not adopt modern Glamor/Wayland abstractions. Re-skin the 2009 logic to fit 2026 signatures.

---

## Task 1: XKB Structural Reconciliation (devices.c) ✅ COMPLETED
**Status:** The xkb_acts, xkb_sli, and xkb_interest members are already present in modern XKBDesc and related structures. The existing code in devices.c should compile as-is.

**Verified:**
- `xkb_acts` exists in ButtonClassRec
- `xkb_sli` exists in KbdFeedbackPtr and LedFeedbackPtr
- `xkb_interest` exists in DeviceIntRec

---

## Task 2: SyncEvents & Event Queue Reconciliation (events.c) ⚠️ PENDING

### Issue: syncEvents redefinition
The syncEvents global is defined in events.c. Need to verify it's declared properly in ssx_compat.h.

### Issue: XI2Mask type mismatches
Modern X uses xorg_list for event synchronization. Legacy uses discrete queue.

**Action:**
- Use ssx_mieqEnqueue wrapper from Phase 2
- Map legacy bitmasks to modern XI2Mask using cast or helper macro in ssx_compat.h

---

## Task 3: Screen Coordinate Alignment (events.c / getevents.c) 🔄 IN PROGRESS

### Completed Fixes:
- ✅ Fixed `scr->x` → `GET_SCREEN_X(scr)` in scale_from_screen()
- ✅ Fixed `scr->y` → `GET_SCREEN_Y(scr)` in scale_from_screen()

### Remaining Issues in getevents.c:
1. **Line 747:** `valuator_mask_set_double(dev->last.scroll, valuator, 0)` - dev->last.scroll is `int[36]`, not `ValuatorMask*`
2. **Lines ~979-986:** positionSprite function uses `scr->x` and `scr->y`
3. **Lines ~1008, 1012:** updateMotionHistory passes `dev->last.valuators` (int array) as double* 

### Solution for dev->last.scroll:
```c
// Current code:
valuator_mask_set_double(dev->last.scroll, valuator, 0);

// Fix: Cast to ValuatorMask* or create wrapper
// Option 1: Create wrapper macro
#define SSX_LAST_SCROLL(dev) ((ValuatorMask*)(dev)->last.scroll)
valuator_mask_set_double(SSX_LAST_SCROLL(dev), valuator, 0);
```

---

## Task 4: GetEvents Type Matching (getevents.c) 🔄 IN PROGRESS

### Issue 1: GetMotionHistory signature conflict
- **Modern API (input.h):** 5 parameters
- **Legacy code:** 6 parameters (includes BOOL core)

**Solution:** Add to ssx_compat.h to override modern declaration:
```c
#ifdef GetMotionHistory
#undef GetMotionHistory
#endif
extern int GetMotionHistory(DeviceIntPtr pDev, xTimecoord **buff,
                           unsigned long start, unsigned long stop,
                           ScreenPtr pScreen, BOOL core);
```

### Issue 2: GetKeyboardEvents signature conflict
- **Modern API:** Takes `InternalEvent*`
- **Legacy code:** Takes `xEvent*`

**Solution:** The code already uses InternalEvent* correctly. Need to verify init_device_event is called properly.

### Issue 3: miPointerSetPosition signature
- **Modern API:** 5 parameters (dev, mode, x, y, time)
- **Legacy code:** 6+ parameters (includes nevents, events for barriers)

**Solution:** Need to check if modern API supports barrier events or if we need a wrapper.

---

## Compilation Status

### Current Errors from `ninja -C build dix/liblibxserver_dix.a.p/getevents.c.o`:

1. ❌ GetMotionHistory conflict (still present)
2. ❌ dev->last.scroll type mismatch (line 747)
3. ❌ Screen x/y access in positionSprite (lines ~979, 986)
4. ❌ miPointerSetPosition call (line 961)
5. ❌ updateMotionHistory double* vs int[] (lines 1008, 1012)

---

## Next Steps (Priority Order)

### Priority 1: Fix getevents.c compilation
1. Fix GetMotionHistory declaration in ssx_compat.h
2. Add SSX_LAST_SCROLL macro for dev->last.scroll
3. Replace remaining scr->x/scr->y with GET_SCREEN_X/Y
4. Fix miPointerSetPosition call signature

### Priority 2: Fix events.c compilation
1. Verify syncEvents declaration
2. Add XI2Mask compatibility macros

### Priority 3: Verify devices.c compilation
1. Test compilation of dix/devices.c
2. Fix any remaining XKB issues

---

## Files Modified

- `include/ssx_compat.h` - Enhanced shims and macro fixes
- `dix/getevents.c` - Screen coordinate fixes (partial)

---

## Testing Approach

Use iterative compilation:
```bash
ninja -C build dix/liblibxserver_dix.a.p/getevents.c.o
ninja -C build dix/liblibxserver_dix.a.p/events.c.o
ninja -C build dix/liblibxserver_dix.a.p/devices.c.o
```

Do NOT batch-fix entire files without testing each fix individually.
