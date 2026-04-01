/* $XFree86: xc/programs/Xserver/dbe/dbemodule.c,v 1.8 2006/03/16 16:49:52 dawes Exp $ */
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

static MODULESETUPPROTO(dbeSetup);

extern void DbeExtensionInit(INITARGS);

ExtensionModule dbeExt = {
    DbeExtensionInit,
    "DOUBLE-BUFFER",
    NULL,
    NULL,
    NULL
};

static XF86ModuleVersionInfo VersRec =
{
	"dbe",
	MODULEVENDORSTRING,
	MODINFOSTRING1,
	MODINFOSTRING2,
	XF86_VERSION_CURRENT,
	1, 0, 0,
	ABI_CLASS_EXTENSION,
	ABI_EXTENSION_VERSION,
	MOD_CLASS_EXTENSION,
	{0,0,0,0}
};

/*
 * Data for the loader
 */
XF86ModuleData dbeModuleData = { &VersRec, dbeSetup, NULL };

static pointer
dbeSetup(ModuleDescPtr module, pointer opts, int *errmaj, int *errmin)
{
    LoadExtension(&dbeExt, FALSE);

    /* Need a non-NULL return value to indicate success */
    return (pointer)1;
}
