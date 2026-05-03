/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _PSres_h
#define _PSres_h

extern char *PSResFontOutline, *PSResFontPrebuilt, *PSResFontAFM,
	*PSResFontBDF, *PSResFontFamily, *PSResFontBDFSizes,
	*PSResForm, *PSResPattern, *PSResEncoding, *PSResProcSet;

typedef enum {PSSaveReturnValues, PSSaveByType, PSSaveEverything}
	PSResourceSavePolicy;

#if defined(__cplusplus) || defined(c_plusplus)
extern "C" {
#endif

extern int ListPSResourceFiles(char *psResourcePathOverride,
			       char *defaultPath,
			       char *resourceType,
			       char *resourceName,
			       char ***resourceNamesReturn,
			       char ***resourceFilesReturn);

extern int ListPSResourceTypes(char *psResourcePathOverride,
			       char *defaultPath,
			       char ***resourceTypeReturn);

extern void FreePSResourceStorage(int everything);

extern void SetPSResourcePolicy(PSResourceSavePolicy policy,
				int willList,
				char **resourceTypes);

typedef int (*PSResourceEnumerator)(char *resourceType,
				    char *resourceName,
				    char *resourceFile,
				    char *privateData);

extern void EnumeratePSResourceFiles(char *psResourcePathOverride,
				     char *defaultPath,
				     char *resourceType,
				     char *resourceName,
				     PSResourceEnumerator enumerator,
				     char *privateData);

extern int CheckPSResourceTime(char *psResourcePathOverride,
			       char *defaultPath);

typedef char *(*PSResMallocProc)(int size);

typedef char *(*PSResReallocProc)(char *ptr,
				  int size);

typedef void (*PSResFreeProc)(char *ptr);

typedef void (*PSResFileWarningHandlerProc)(char *fileNamem, char *extraInfo);

#if defined(__cplusplus) || defined(c_plusplus)
}
#endif

extern PSResMallocProc PSResMalloc;

extern PSResReallocProc PSResRealloc;

extern PSResFreeProc PSResFree;

extern PSResFileWarningHandlerProc PSResFileWarningHandler;

#endif /* _PSres_h */
