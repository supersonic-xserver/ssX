/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef DIX_REGISTRY_H
#define DIX_REGISTRY_H

/*
 * Result returned from any unsuccessful lookup
 */
#define XREGISTRY_UNKNOWN "<unknown>"

#ifdef XREGISTRY

#include "resource.h"
#include "extnsionst.h"

/* Internal string registry - for auditing, debugging, security, etc. */

/*
 * Registration functions.  The name string is not copied, so it must
 * not be a stack variable.
 */
void RegisterResourceName(RESTYPE type, char *name);
void RegisterExtensionNames(ExtensionEntry *ext);

/*
 * Lookup functions.  The returned string must not be modified or freed.
 */
const char *LookupMajorName(int major);
const char *LookupRequestName(int major, int minor);
const char *LookupEventName(int event);
const char *LookupErrorName(int error);
const char *LookupResourceName(RESTYPE rtype);

/*
 * Setup and teardown
 */
void dixResetRegistry(void);

#else /* XREGISTRY */

/* Define calls away when the registry is not being built. */

#define RegisterResourceName(a, b) { ; }
#define RegisterExtensionNames(a) { ; }

#define LookupMajorName(a) XREGISTRY_UNKNOWN
#define LookupRequestName(a, b) XREGISTRY_UNKNOWN
#define LookupEventName(a) XREGISTRY_UNKNOWN
#define LookupErrorName(a) XREGISTRY_UNKNOWN
#define LookupResourceName(a) XREGISTRY_UNKNOWN

#define dixResetRegistry() { ; }

#endif /* XREGISTRY */
#endif /* DIX_REGISTRY_H */
