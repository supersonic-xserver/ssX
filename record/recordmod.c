/* $XFree86: xc/programs/Xserver/record/recordmod.c,v 1.7 2006/03/16 16:50:36 dawes Exp $ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#include "xf86Module.h"

extern Bool noTestExtensions;

static MODULESETUPPROTO(recordSetup);

extern void RecordExtensionInit(INITARGS);

ExtensionModule recordExt = {
    RecordExtensionInit,
    "RECORD",
    &noTestExtensions,
    NULL,
    NULL
};

static XF86ModuleVersionInfo VersRec = {
	"record",
	MODULEVENDORSTRING,
	MODINFOSTRING1,
	MODINFOSTRING2,
	XF86_VERSION_CURRENT,
	1, 13, 0,
	ABI_CLASS_EXTENSION,
	ABI_EXTENSION_VERSION,
	MOD_CLASS_EXTENSION,
	{0,0,0,0}
};

XF86ModuleData recordModuleData = { &VersRec, recordSetup, NULL };

static pointer
recordSetup(ModuleDescPtr module, pointer opts, int *errmaj, int *errmin)
{
    LoadExtension(&recordExt, FALSE);

    /* Need a non-NULL return value to indicate success */
    return (pointer)1;
}

