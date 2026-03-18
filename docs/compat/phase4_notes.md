# Phase 4: Extended Shim Development Plan

## Current Status
- Build errors reduced from **152 to 88** through Phase 4 fixes (42% reduction!)
- Comprehensive compatibility layer established in `ssx_compat.h` and `ssx_shims.c`
- Fixed duplicate DamageReportLevel typedef conflicts with damage.h
- Fixed stray #endif preprocessor errors in ssx_compat.h
- Remaining errors require source-level changes to .c files

## Error Analysis (88 remaining errors)

### Fixes Applied in This Session:
1. Removed duplicate DamageReportLevel typedef (lines 181-183 and 303-305)
2. Removed conflicting #ifdef _DAMAGE_H_ / #undef pattern causing redefinitions
3. Fixed stray/unmatched #endif statements
4. Cleaned up damage extension stub conflicts

### By Category:

#### 1. Function Parameter Mismatches (~25 errors)
| Function | Modern Args | Legacy Args | Location |
|---------|-------------|--------------|----------|
| GetMotionHistory | 5 | 6 | dix/getevents.c:970 |
| InitPointerDeviceStruct | 7 | 8 | dix/devices.c:654 |
| other functions | varies | varies | various |

#### 2. Struct Member Access (~30 errors)
- `ScreenRec.x` / `ScreenRec.y` - removed in modern X
- `ClientRec.minorOp` / `ClientRec.majorOp` - replaced with requestBuffer
- `RawDeviceEvent.flags` - removed
- `TouchPointInfoRec.client_id`, `sourceid`, `emulate_pointer` - not present in modern

#### 3. Type Mismatches (~15 errors)
- `int[36]` vs `double*` for valuator arrays
- `InternalEvent*` vs `xEvent*` for event handling
- `pixman_f_transform*` vs `pict_f_transform*`

#### 4. Missing Identifiers (~10 errors)
- `syncEvents` - global variable removed
- `PRIVATE_CLIENT` - private index removed
- Various TouchClass/TouchPoint members

## Phase 4 Implementation Plan

### Priority 1: Critical File Fixes

#### A. dix/getevents.c (highest impact - ~30 errors)
1. Add explicit includes for needed headers
2. Create getevents-specific shims for:
   - GetPointerEvents / GetKeyboardEvents signature mismatches
   - Screen x/y access via accessor functions
   - Valuator array type conversions

#### B. dix/devices.c (~15 errors)
1. Add missing includes (already partially done - xi2proto.h added)
2. Fix InitPointerDeviceStruct call at line 654
3. Add XKB struct member accessors for xkb_acts/xkb_sli

#### C. dix/pixmap.c (~5 errors)
1. Fix pict_f_transform type mapping
2. Fix ChangeGCVal* → XID* type issues

### Priority 2: Additional Shim Functions

#### A. Event Handling Wrappers
```c
// In ssx_shims.c - add these functions:
void* ssx_InternalEvent_to_xEvent(InternalEvent *ev);
InternalEvent* ssx_xEvent_to_InternalEvent(xEvent *ev);
```

#### B. Client Accessor Functions
```c
// Replace client->minorOp / client->majorOp access
#define SSX_CLIENT_MINOR_OP(c) ((c)->requestBuffer[1])
#define SSX_CLIENT_MAJOR_OP(c) ((c)->requestBuffer[0])
```

#### C. Screen Accessor Functions
```c
// Replace scr->x / scr->y access
int ssx_screen_get_x(ScreenPtr scr);
int ssx_screen_get_y(ScreenPtr scr);
```

### Priority 3: Build System Improvements

1. **Consider removing global `-include ssx_compat.h`** from meson.build
   - Creates include order dependencies
   - Add to specific sources that need it instead

2. **Create file-specific build options**:
   ```python
   # In meson.build - example approach
   ssx_compat_sources = [
       'dix/devices.c',
       'dix/getevents.c',
       'dix/pixmap.c',
   ]
   ```

## Implementation Checklist

- [ ] Fix dix/getevents.c - add targeted includes and function wrappers
- [ ] Fix dix/devices.c - complete InitPointerDeviceStruct fix
- [ ] Fix dix/pixmap.c - add pict_f_transform and type fixes  
- [ ] Add more accessor functions to ssx_shims.c
- [ ] Test build with selective includes approach
- [ ] Document all shims in ssx_compat.h with clear comments

## Testing Strategy

1. Run `ninja -C build 2>&1 | grep -c "error:"` after each fix
2. Target: Reduce from 80 → 50 → 20 → 0 errors
3. Test specific functionality after each major fix

## Notes

- The fundamental challenge is bridging 2006 XFree86 API to modern Xlibre
- Some errors cannot be fixed with macros alone - require code changes
- Consider this a long-term migration project, not a quick fix
- The shim approach preserves legacy code while allowing modern compilation

---

## Session 2025-03-17 Findings

### Issue 1: Global -include Causes Double-Include

The global `-include ssx_compat.h` in meson.build (line 17) combined with `-include os.h` (line 16) causes double-inclusion issues. When the compiler processes `-include os.h` first, os.h eventually includes headers that also trigger ssx_compat.h processing, causing the `#endif without #if` error at line 1119.

**Root Cause**: When `-include` is used, the header is prepended to EVERY compilation unit BEFORE any includes in the source file. This means ssx_compat.h gets processed twice when:
1. Explicitly via `-include ssx_compat.h`
2. Indirectly when os.h includes something that includes ssx_compat.h

**Attempted Fix**: Adding `#ifndef SSX_COMPAT_H` guard at the start of ssx_compat.h should prevent the double-include, BUT the error persists because the preprocessor state gets confused with the dual `-include` flags.

### Issue 2: Fundamental API Gaps

The build errors reveal deeper incompatibilities that cannot be solved with header shims alone:

1. **glx/vndserver_priv.h** - This file contains corrupted/encrypted legacy XFree86 code that cannot be parsed by modern compilers. The user indicated they will handle this separately.

2. **Type system changes**: Modern Xlibre uses fundamentally different types:
   - `InternalEvent*` vs `xEvent*` for event processing
   - `double*` vs `int[36]` for valuator arrays
   - `PrivateRec*` vs `DevUnion*` for private data

3. **Struct member removals**: Legacy code references struct members that were removed in modern X:
   - `ScreenRec.x`, `ScreenRec.y` - removed
   - `ClientRec.minorOp`, `ClientRec.majorOp` - replaced with `requestBuffer`
   - `RawDeviceEvent.flags` - removed

### Issue 3: Current Build Status

After fixing the duplicate #endif, the build now shows:
- `#endif without #if` error is FIXED (ssx_compat.h line 1119)
- BUT new errors appear in dix/getevents.c because ssx_compat.h macros aren't being applied globally

The fundamental problem: with global `-include` we get double-include, without it we get missing macros in source files.

### Recommendations for Next Agent

1. **Option A - Remove global include**: Remove `-include ssx_compat.h` from meson.build and add `#include "ssx_compat.h"` to individual .c files that need it

2. **Option B - Use include/os.h to include ssx_compat.h**: Modify os.h to include ssx_compat.h at the end, so only one `-include` flag is needed

3. **Focus on specific files**: Instead of trying to compile everything, focus on getting a minimal subset working (e.g., just dix/, mi/)

4. **Source-level changes**: Accept that many errors require actual code changes in .c files, not just header shims

### Current Error Count

```
ninja -C build 2>&1 | grep -c "error:"
```
Shows multiple errors in:
- dix/getevents.c (valuator types, screen access, event conversion)
- dix/devices.c (InitPointerDeviceStruct, XKB accessors)
- glx/vndserver files (corrupted legacy code)

---

## TODO: Next Agent Tasks

### Task 1: Fix Global Include Issue
- [ ] **Option A**: Remove global `-include ssx_compat.h` from meson.build line 17
- [ ] Add `#include "ssx_compat.h"` to the top of these files:
  - dix/getevents.c
  - dix/devices.c  
  - dix/pixmap.c
  - dix/eventconvert.c
  - Any other .c file that fails with missing macro errors

- [ ] **Option B**: Keep global include but modify os.h to include ssx_compat.h at the END instead of using separate -include flag

### Task 2: Fix dix/getevents.c Errors (~30 errors)
- [ ] Rebuild after Task 1 to see actual remaining errors
- [ ] Add explicit `#include "ssx_compat.h"` if not using global include
- [ ] Fix valuator mask type issues (int[36] vs double*)
- [ ] Fix GetMotionHistory 6-param → 5-param call
- [ ] Fix POINTER_SCREEN undeclared identifier (add to ssx_compat.h if missing)
- [ ] Fix EVENT_SOURCE_NORMAL undeclared
- [ ] Fix Screen x/y member access - add GET_SCREEN_X/Y macros to ssx_compat.h

### Task 3: Fix dix/devices.c Errors (~15 errors)
- [ ] Add explicit `#include "ssx_compat.h"` if not using global include
- [ ] Fix InitPointerDeviceStruct call signature (7 vs 8 params)
- [ ] Add XKB struct accessors for xkb_acts, xkb_sli members

### Task 4: Handle glx/vndserver Files
- [ ] These contain corrupted/encrypted XFree86 code - user is handling separately
- [ ] Consider disabling glx module in meson.build if blocking other builds

### Task 5: Test and Iterate
- [ ] Run `ninja -C build 2>&1 | grep -c "error:"` after each fix
- [ ] Target: <50 errors → <20 errors → 0 errors
