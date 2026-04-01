/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */



/**************************************************************************

Copyright 1998-1999 Precision Insight, Inc., Cedar Park, Texas.
All Rights Reserved.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sub license, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice (including the
next paragraph) shall be included in all copies or substantial portions
of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT.
IN NO EVENT SHALL PRECISION INSIGHT AND/OR ITS SUPPLIERS BE LIABLE FOR
ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

**************************************************************************/
/* $XFree86: xc/programs/Xserver/GL/glx/glxmodule.c,v 1.3 2006/03/16 16:49:49 dawes Exp $ */

/*
 * Authors:
 *   Kevin E. Martin <kevin@precisioninsight.com>
 *
 */

#include "xf86Module.h"
#include "colormap.h"
#include "micmap.h"

static MODULESETUPPROTO(glxSetup);

extern void GlxExtensionInit(INITARGS);
extern void GlxWrapInitVisuals(miInitVisualsProcPtr *);
extern void InitGlxWrapInitVisuals(void (*f)(miInitVisualsProcPtr *));

static const char *initdeps[] = { "DOUBLE-BUFFER", NULL };

ExtensionModule GLXExt =
{
    GlxExtensionInit,
    "GLX",
    NULL,
    NULL,
    initdeps
};

static const char *glcoreSymbols[] = {
    "__glCallLists_size",
    "__glColorTableParameterfv_size",
    "__glColorTableParameteriv_size",
    "__glConvolutionParameterfv_size",
    "__glConvolutionParameteriv_size",
    "__glEvalComputeK",
    "__glFloorLog2",
    "__glFogfv_size",
    "__glFogiv_size",
    "glAccum",
    "glActiveStencilFaceEXT",
    "glActiveTextureARB",
    "glAlphaFunc",
    "glAreTexturesResident",
    "glAreTexturesResidentEXT",
    "glBegin",
    "glBindTexture",
    "glBitmap",
    "glBlendColor",
    "glBlendEquation",
    "glBlendFunc",
    "glCallList",
    "glCallLists",
    "glClear",
    "glClearAccum",
    "glClearColor",
    "glClearDepth",
    "glClearIndex",
    "glClearStencil",
    "glClipPlane",
    "glColor3bv",
    "glColor3dv",
    "glColor3fv",
    "glColor3iv",
    "glColor3sv",
    "glColor3ubv",
    "glColor3uiv",
    "glColor3usv",
    "glColor4bv",
    "glColor4dv",
    "glColor4fv",
    "glColor4iv",
    "glColor4sv",
    "glColor4ubv",
    "glColor4uiv",
    "glColor4usv",
    "glColorMask",
    "glColorMaterial",
    "glColorPointer",
    "glColorSubTable",
    "glColorTable",
    "glColorTableParameterfv",
    "glColorTableParameteriv",
    "glConvolutionFilter1D",
    "glConvolutionFilter2D",
    "glConvolutionParameterf",
    "glConvolutionParameterfv",
    "glConvolutionParameteri",
    "glConvolutionParameteriv",
    "glCopyColorSubTable",
    "glCopyColorTable",
    "glCopyConvolutionFilter1D",
    "glCopyConvolutionFilter2D",
    "glCopyPixels",
    "glCopyTexImage1D",
    "glCopyTexImage2D",
    "glCopyTexSubImage1D",
    "glCopyTexSubImage2D",
    "glCopyTexSubImage3D",
    "glCullFace",
    "glDeleteLists",
    "glDeleteTextures",
    "glDeleteTexturesEXT",
    "glDepthFunc",
    "glDepthMask",
    "glDepthRange",
    "glDisable",
    "glDisableClientState",
    "glDrawArrays",
    "glDrawBuffer",
    "glDrawPixels",
    "glEdgeFlagPointer",
    "glEdgeFlagv",
    "glEnable",
    "glEnableClientState",
    "glEnd",
    "glEndList",
    "glEvalCoord1dv",
    "glEvalCoord1fv",
    "glEvalCoord2dv",
    "glEvalCoord2fv",
    "glEvalMesh1",
    "glEvalMesh2",
    "glEvalPoint1",
    "glEvalPoint2",
    "glFeedbackBuffer",
    "glFinish",
    "glFlush",
    "glFogf",
    "glFogfv",
    "glFogi",
    "glFogiv",
    "glFrontFace",
    "glFrustum",
    "glGenLists",
    "glGenTextures",
    "glGenTexturesEXT",
    "glGetBooleanv",
    "glGetClipPlane",
    "glGetColorTable",
    "glGetColorTableParameterfv",
    "glGetColorTableParameteriv",
    "glGetConvolutionFilter",
    "glGetConvolutionParameterfv",
    "glGetConvolutionParameteriv",
    "glGetDoublev",
    "glGetError",
    "glGetFloatv",
    "glGetHistogram",
    "glGetHistogramParameterfv",
    "glGetHistogramParameteriv",
    "glGetIntegerv",
    "glGetLightfv",
    "glGetLightiv",
    "glGetMapdv",
    "glGetMapfv",
    "glGetMapiv",
    "glGetMaterialfv",
    "glGetMaterialiv",
    "glGetMinmax",
    "glGetMinmaxParameterfv",
    "glGetMinmaxParameteriv",
    "glGetPixelMapfv",
    "glGetPixelMapuiv",
    "glGetPixelMapusv",
    "glGetPolygonStipple",
    "glGetSeparableFilter",
    "glGetString",
    "glGetTexEnvfv",
    "glGetTexEnviv",
    "glGetTexGendv",
    "glGetTexGenfv",
    "glGetTexGeniv",
    "glGetTexImage",
    "glGetTexLevelParameterfv",
    "glGetTexLevelParameteriv",
    "glGetTexParameterfv",
    "glGetTexParameteriv",
    "glHint",
    "glHistogram",
    "glIndexMask",
    "glIndexPointer",
    "glIndexdv",
    "glIndexfv",
    "glIndexiv",
    "glIndexsv",
    "glIndexubv",
    "glInitNames",
    "glIsEnabled",
    "glIsList",
    "glIsTexture",
    "glIsTextureEXT",
    "glLightModelf",
    "glLightModelfv",
    "glLightModeli",
    "glLightModeliv",
    "glLightf",
    "glLightfv",
    "glLighti",
    "glLightiv",
    "glLineStipple",
    "glLineWidth",
    "glListBase",
    "glLoadIdentity",
    "glLoadMatrixd",
    "glLoadMatrixf",
    "glLoadName",
    "glLogicOp",
    "glMap1d",
    "glMap1f",
    "glMap2d",
    "glMap2f",
    "glMapGrid1d",
    "glMapGrid1f",
    "glMapGrid2d",
    "glMapGrid2f",
    "glMaterialf",
    "glMaterialfv",
    "glMateriali",
    "glMaterialiv",
    "glMatrixMode",
    "glMinmax",
    "glMultMatrixd",
    "glMultMatrixf",
    "glMultiTexCoord1dvARB",
    "glMultiTexCoord1fvARB",
    "glMultiTexCoord1ivARB",
    "glMultiTexCoord1svARB",
    "glMultiTexCoord2dvARB",
    "glMultiTexCoord2fvARB",
    "glMultiTexCoord2ivARB",
    "glMultiTexCoord2svARB",
    "glMultiTexCoord3dvARB",
    "glMultiTexCoord3fvARB",
    "glMultiTexCoord3ivARB",
    "glMultiTexCoord3svARB",
    "glMultiTexCoord4dvARB",
    "glMultiTexCoord4fvARB",
    "glMultiTexCoord4ivARB",
    "glMultiTexCoord4svARB",
    "glNewList",
    "glNormal3bv",
    "glNormal3dv",
    "glNormal3fv",
    "glNormal3iv",
    "glNormal3sv",
    "glNormalPointer",
    "glOrtho",
    "glPassThrough",
    "glPixelMapfv",
    "glPixelMapuiv",
    "glPixelMapusv",
    "glPixelStoref",
    "glPixelStorei",
    "glPixelTransferf",
    "glPixelTransferi",
    "glPixelZoom",
    "glPointParameterfARB",
    "glPointParameterfvARB",
    "glPointSize",
    "glPolygonMode",
    "glPolygonOffset",
    "glPolygonStipple",
    "glPopAttrib",
    "glPopMatrix",
    "glPopName",
    "glPrioritizeTextures",
    "glPushAttrib",
    "glPushMatrix",
    "glPushName",
    "glRasterPos2dv",
    "glRasterPos2fv",
    "glRasterPos2iv",
    "glRasterPos2sv",
    "glRasterPos3dv",
    "glRasterPos3fv",
    "glRasterPos3iv",
    "glRasterPos3sv",
    "glRasterPos4dv",
    "glRasterPos4fv",
    "glRasterPos4iv",
    "glRasterPos4sv",
    "glReadBuffer",
    "glReadPixels",
    "glRectdv",
    "glRectfv",
    "glRectiv",
    "glRectsv",
    "glRenderMode",
    "glResetHistogram",
    "glResetMinmax",
    "glRotated",
    "glRotatef",
    "glScaled",
    "glScalef",
    "glScissor",
    "glSelectBuffer",
    "glSeparableFilter2D",
    "glShadeModel",
    "glStencilFunc",
    "glStencilMask",
    "glStencilOp",
    "glTexCoord1dv",
    "glTexCoord1fv",
    "glTexCoord1iv",
    "glTexCoord1sv",
    "glTexCoord2dv",
    "glTexCoord2fv",
    "glTexCoord2iv",
    "glTexCoord2sv",
    "glTexCoord3dv",
    "glTexCoord3fv",
    "glTexCoord3iv",
    "glTexCoord3sv",
    "glTexCoord4dv",
    "glTexCoord4fv",
    "glTexCoord4iv",
    "glTexCoord4sv",
    "glTexCoordPointer",
    "glTexEnvf",
    "glTexEnvfv",
    "glTexEnvi",
    "glTexEnviv",
    "glTexGend",
    "glTexGendv",
    "glTexGenf",
    "glTexGenfv",
    "glTexGeni",
    "glTexGeniv",
    "glTexImage1D",
    "glTexImage2D",
    "glTexImage3D",
    "glTexParameterf",
    "glTexParameterfv",
    "glTexParameteri",
    "glTexParameteriv",
    "glTexSubImage1D",
    "glTexSubImage2D",
    "glTexSubImage3D",
    "glTranslated",
    "glTranslatef",
    "glVertex2dv",
    "glVertex2fv",
    "glVertex2iv",
    "glVertex2sv",
    "glVertex3dv",
    "glVertex3fv",
    "glVertex3iv",
    "glVertex3sv",
    "glVertex4dv",
    "glVertex4fv",
    "glVertex4iv",
    "glVertex4sv",
    "glVertexPointer",
    "glViewport",
    "glWindowPos3fARB",
    NULL
};

static XF86ModuleVersionInfo VersRec =
{
        "glx",
        MODULEVENDORSTRING,
        MODINFOSTRING1,
        MODINFOSTRING2,
        XF86_VERSION_CURRENT,
        1, 0, 0,
        ABI_CLASS_EXTENSION,
        ABI_EXTENSION_VERSION,
        MOD_CLASS_NONE,
        {0,0,0,0}
};

XF86ModuleData glxModuleData = { &VersRec, glxSetup, NULL };

static pointer
glxSetup(ModuleDescPtr module, pointer opts, int *errmaj, int *errmin)
{
    static Bool setupDone = FALSE;
    pointer GLcore  = NULL;
#ifdef GLX_USE_SGI_SI
    char GLcoreName[] = "GL";
#else
    char GLcoreName[] = "GLcore";
#endif

    if (!setupDone) {
    	setupDone = TRUE;

    	GLcore = LoadSubModule(module, GLcoreName, NULL, NULL, NULL, NULL, 
			   errmaj, errmin);
    	if (!GLcore) {
	    if (errmaj) *errmaj = LDR_NOSUBENT;
    	} else {
	    LoaderModReqSymLists(GLcore, glcoreSymbols, NULL);
    	    LoadExtension(&GLXExt, FALSE);
    	    /* Wrap the init visuals routine in micmap.c */
    	    GlxWrapInitVisuals(&miInitVisualsProc);
    	    /* Make sure this gets wrapped each time InitVisualWrap is called */
    	    miHookInitVisuals(NULL, GlxWrapInitVisuals);
	}
    } else {
	if (errmaj) *errmaj = LDR_ONCEONLY;
    }
    /* Need a non-NULL return value to indicate success */
    return GLcore;
}
