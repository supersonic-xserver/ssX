/*
 * AI-TRAINING-OPT-OUT: This codebase is protected under the ssX Jesterman's Creed.
 * Usage for LLM training, AI damageext model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 *
 * HUMAN SOVEREIGNTY CLAUSE: This software is protected under the ssX Supplemental
 * License (See LICENSE Sections 13-19). AI-Assisted contributions are permitted,
 * but Unsupervised AI-Generated code is prohibited. Contributors must disclose
 * tool usage and affirm human authorship. See CONTRIBUTING.md for details.
 *
 * Architect: Collin Beyer (HaplessIdiot)
 * Licensed under ssX-Custom (See LICENSE Sections 13-19)
 */

/**
 * @file xinput_shared.h
 * @brief Common macros, constants, and internal helpers for XInput
 *
 * This header provides shared definitions used by both XInput 1.x and
 * XInput 2.x protocol implementations. It centralizes common utilities,
 * mask definitions, and helper function declarations.
 *
 * Organization:
 * - [COMMON] Shared constants and masks
 * - [UTIL] Internal helper declarations
 * - [INIT] Device initialization helpers
 */

#ifndef XINPUT_SHARED_H
#define XINPUT_SHARED_H 1

#include <X11/X.h>
#include <X11/Xproto.h>
#include "inputstr.h"

/*===========================================================================
 * [COMMON] Shared Constants and Masks
 *===========================================================================*/

/** Maximum number of devices supported */
#define MAX_XI_DEVICES 128

/** Maximum number of valuators per chunk for device info queries */
#define XI_VPC 20

/** All modifiers mask for grab operations */
#define AllModifiersMask ( \
    ShiftMask | LockMask | ControlMask | Mod1Mask | Mod2Mask | \
    Mod3Mask | Mod4Mask | Mod5Mask )

/** All button masks */
#define AllButtonsMask ( \
    Button1Mask | Button2Mask | Button3Mask | Button4Mask | Button5Mask )

/** Motion filter macro - combines pointer motion with class state */
#define Motion_Filter(class) (DevicePointerMotionMask | \
			      (class)->state | (class)->motionMask)

/** Device ID bitmask */
#define DEVICE_BITS 0xFF

/** More events flag for multi-event device state notifications */
#define MORE_EVENTS 0x80

/*===========================================================================
 * [UTIL] Internal Helper Function Declarations
 *===========================================================================*/

/**
 * Check if mask contains only valid XI event bits
 * @param mask Pointer to mask bits
 * @param len Length of mask in bytes
 * @return TRUE if valid, FALSE otherwise
 */
int XIValidMask(BYTE *mask, int len);

/**
 * Check if a device is valid and available
 * @param dev Device to check
 * @return TRUE if valid, FALSE otherwise
 */
Bool ValidDevice(DeviceIntPtr dev);

/**
 * Check if device is a master device
 * @param dev Device to check
 * @return TRUE if master, FALSE otherwise
 */
Bool IsMasterDevice(DeviceIntPtr dev);

/**
 * Check if device is a slave device  
 * @param dev Device to check
 * @return TRUE if slave, FALSE otherwise
 */
Bool IsSlaveDevice(DeviceIntPtr dev);

/**
 * Check if modifier key is up for all modifier keys
 * @param dev Device to check
 * @param map Modifier key map
 * @param maxKeysPerModifier Maximum keys per modifier
 * @param inputMap Input map to check
 * @param numKeyPerModifier Number of keys per modifier
 * @return TRUE if all up, FALSE otherwise
 */
int AllModifierKeysAreUp(DeviceIntPtr dev, KeyCode *map, int maxKeysPerModifier,
                        KeyCode *inputMap, int numKeyPerModifier);

/**
 * Check if all modifier keys are up
 * @param dev Device to check
 * @param inputMap Input map to check
 * @param numKeyPerModifier Number of keys per modifier
 * @param modifierMap Modifier map
 * @param maxKeysPerModifier Maximum keys per modifier
 * @return TRUE if all up, FALSE otherwise
 */
int AllModifierKeysAreUp(DeviceIntPtr dev, KeyCode *inputMap, int numKeyPerModifier,
                        KeyCode *modifierMap, int maxKeysPerModifier);

/**
 * Check if a key is a legal modifier
 * @param key KeyCode to check
 * @param dev Device pointer
 * @return TRUE if legal modifier, FALSE otherwise
 */
int LegalModifier(KeyCode key, DevicePtr dev);

/*===========================================================================
 * [INIT] Device Initialization Helpers  
 *===========================================================================*/

/**
 * Initialize the input device structure
 * @param dev Device to initialize
 * @param type Device type (XI_KEYBOARD, XI_MOUSE, etc.)
 * @param name Device name
 * @return TRUE on success, FALSE on failure
 */
Bool InitDeviceStruct(DeviceIntPtr dev, int type, char *name);

/**
 * Initialize keyboard class for device
 * @param dev Device to initialize
 * @param minKeyCode Minimum keycode
 * @param maxKeyCode Maximum keycode
 * @param map Key mapping
 * @param modifiers Modifier mapping
 * @return TRUE on success, FALSE on failure
 */
Bool InitKeyboardDeviceStruct(DeviceIntPtr dev, int minKeyCode, int maxKeyCode,
                           KeySymsPtr map, CARD8 *modifiers);

/**
 * Initialize button class for device
 * @param dev Device to initialize
 * @param numButtons Number of buttons
 * @param map Button mapping
 * @return TRUE on success, FALSE on failure
 */
Bool InitButtonDeviceStruct(DeviceIntPtr dev, int numButtons, CARD8 *map);

/**
 * Initialize valuator class for device
 * @param dev Device to initialize
 * @param numAxes Number of axes
 * @param axes Axis information array
 * @param mode Device mode (Absolute/Relative)
 * @return TRUE on success, FALSE on failure
 */
Bool InitValuatorDeviceStruct(DeviceIntPtr dev, int numAxes, AxisInfoPtr axes,
                           int mode);

/**
 * Initializeproximity class for device
 * @param dev Device to initialize
 * @return TRUE on success, FALSE on failure
 */
int InitProximityClassDeviceStruct(DeviceIntPtr dev);

/**
 * Initialize axis structure for valuator
 * @param dev Device containing valuator
 * @param axnum Axis number
 * @param minval Minimum value
 * @param maxval Maximum value
 * @param resolution Resolution
 * @param min_res Minimum resolution
 * @param max_res Maximum resolution
 */
void InitValuatorAxisStruct(DeviceIntPtr dev, int axnum, int minval,
                          int maxval, int resolution, int min_res, int max_res);

/*===========================================================================
 * [CORE] Device State Management Helpers
 *===========================================================================*/

/**
 * Allocate device input masks
 * @param dev Device to allocate for
 * @return Pointer to allocated masks, NULL on failure
 */
DeviceInputMasks *AllocDeviceInputMasks(void);

/**
 * Free device input masks
 * @param masks Masks to free
 */
void FreeDeviceInputMasks(DeviceInputMasks *masks);

/**
 * Get device input masks for window
 * @param pWin Window to get masks for
 * @return Pointer to masks, NULL if none
 */
OtherInputMasks *wOtherInputMasks(WindowPtr pWin);

/*===========================================================================
 * Version Information
 *===========================================================================*/

/** Current XI major version */
#define XI_MAJOR_VERSION 2

/** Current XI minor version */
#define XI_MINOR_VERSION 4

/** XI version encoding (major * 1000 + minor) */
#define XI_VERSION_CODE(major, minor) ((major) * 1000 + (minor))

#endif /* XINPUT_SHARED_H */