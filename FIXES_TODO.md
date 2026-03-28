# ssX-legacy Build Fix Pass - Task List

## Bucket 1: re_execute duplicate in present_priv.h
- [x] Open present_priv.h, find struct with duplicate re_execute field
- [x] Remove the duplicate definition

## Bucket 2: struct _Screen missing ConfigNotify, root, output_slave_list
- [x] Fields already in scrnintstr.h - verified

## Bucket 3: struct _Pixmap missing screen_x/screen_y
- [x] Removed #ifdef HAVE_PIXMAP_SCREEN_XY guard in pixmapstr.h

## Bucket 4: struct _Pixmap missing devPrivates
- [x] Removed #ifdef PIXPRIV guard in pixmapstr.h

## Bucket 5: swapll macro wrong arg count
- [x] Fixed swapll macro in present_request.c and present_event.c

## Bucket 6: present_scmd.c issues
- [x] Added PRESENT_FLIP_REASON_DRIVER_TEARFREE to PresentFlipReason enum
- [x] Added PRESENT_FLIP_REASON_DRIVER_TEARFREE_FLIPPING to enum
- [x] Added exec_msc to struct present_vblank

## Bucket 7: present_event.c - present_select_input issues
- [x] Signatures compatible - no action needed

## Bucket 8: present_screen.c line 64 - too few arguments
- [x] Need to check actual build error

## Bucket 9: randr/rrdispatch.c issues
- [x] Added #include "dixstruct.h"

## Bucket 10: randr rrmode.c/rroutput.c - _RRMode/_RROutput missing
- [x] Added all missing fields to randrstr.h

## Bucket 11: randr/rrcrtc.c issues
- [x] Added typedefs for RROutputRec, RRCrtcRec
- [x] Added RREventBase/RRErrorBase extern declarations
- [x] Added RRClientPrivateKey

## Bucket 12: randr/rrlease.c - _RRLease incomplete
- [x] Added complete _RRLease struct to randrstr.h

## Bucket 13: randr/rrmonitor.c - RRMonitorPtr, etc.
- [x] Added RRMonitorGeometryRec and RRMonitorRec structs

## Bucket 14: randr/rrpointer.c issues
- [x] Added pointerCrtc to _rrScrPriv
- [x] Added #include "windowstr.h"
