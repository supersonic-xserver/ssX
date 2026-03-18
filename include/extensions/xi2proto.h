/*
 * XI2 Protocol definitions for ssX
 * This header provides types and definitions for XI2 (X Input Extension 2)
 * that are needed internally by the X server but not provided by the 
 * system headers.
 */

#ifndef _XI2PROTO_H_
#define _XI2PROTO_H_

#include <X11/extensions/XI2proto.h>
#include <X11/extensions/XI2.h>

/* Only define these if not already defined by the system headers */
#ifndef _XI2PROPERTY_VALUE_DEFINED
#define _XI2PROPERTY_VALUE_DEFINED

/* Property value structure - complete definition for ssX */
typedef struct _XI2PropertyValue {
    int type;
    int format;
    unsigned long len;
    union {
        char *str;
        int *card;
        float *flt;
        Atom *atom;
    } data;
} XI2PropertyValue;

/* Property value pointer type - use XI2 version to avoid conflict */
typedef XI2PropertyValue *XI2PropertyValuePtr;

/* Legacy alias for code using old name */
#ifndef XIPropertyValuePtr
typedef XI2PropertyValuePtr XIPropertyValuePtr;
#endif

#endif /* _XI2PROPERTY_VALUE_DEFINED */

/* Known property atoms - these are initialized by XIInitKnownProperties() */
#define XI_PROP_ENABLED "Device Enabled"
#define XI_PROP_TRANSFORM "Device Transform"
#define XI_PROP_CALIBRATION "Device Calibration"
#define XI_PROP_DISABLE "Device Disable"

/* XI Property flags */
#define XIPropertyTypeNone        0
#define XIPropertyTypeInteger     1
#define XIPropertyTypeFloat       2
#define XIPropertyTypeString      3
#define XIPropertyTypeAtom        4
#define XIPropertyTypeCardinal   5

/* Device property notify flags */
#define XIPropertyDeleted      0
#define XIPropertyCreated     1
#define XIPropertyModified    2

/* Touch mode constants - for compatibility with XI2 */
#ifndef XIDirectTouch
#define XIDirectTouch 1
#endif
#ifndef XIIndirectTouch
#define XIIndirectTouch 2
#endif

/* XI2 Event types for touch - needed for touch code */
#define XI_TouchBegin  11
#define XI_TouchUpdate 12
#define XI_TouchEnd    13
#define XI_TouchOwnership 14

/* XI2 Flags */
#define XIPropertyModified 2
#define XIPointerEmulated  (1 << 0)

#endif /* _XI2PROTO_H_ */
