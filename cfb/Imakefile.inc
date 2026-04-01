XCOMM $XFree86: xc/programs/Xserver/cfb/Imakefile.inc,v 1.15 2007/07/01 15:14:49 tsi Exp $
/*
 * Copyright (c) 1994-2004 by The XFree86 Project, Inc.
 * All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject
 * to the following conditions:
 *
 *   1.  Redistributions of source code must retain the above copyright
 *       notice, this list of conditions, and the following disclaimer.
 *
 *   2.  Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer
 *       in the documentation and/or other materials provided with the
 *       distribution, and in the same place and form as other copyright,
 *       license and disclaimer information.
 *
 *   3.  The end-user documentation included with the redistribution,
 *       if any, must include the following acknowledgment: "This product
 *       includes software developed by The XFree86 Project, Inc
 *       (http://www.xfree86.org/) and its contributors", in the same
 *       place and form as other third-party acknowledgments.  Alternately,
 *       this acknowledgment may appear in the software itself, in the
 *       same form and location as other such third-party acknowledgments.
 *
 *   4.  Except as contained in this notice, the name of The XFree86
 *       Project, Inc shall not be used in advertising or otherwise to
 *       promote the sale, use or other dealings in this Software without
 *       prior written authorization from The XFree86 Project, Inc.
 *
 * THIS SOFTWARE IS PROVIDED ``AS IS'' AND ANY EXPRESSED OR IMPLIED
 * WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE XFREE86 PROJECT, INC OR ITS CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT
 * OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#if DoLoadableServer
#if !BuildModuleInSubdir
#define IHaveModules
#elif !defined(IHaveModules)
#define IHaveSubdirs
SUBDIRS = module
#endif
#endif

#include <Server.tmpl>

#ifndef PixelSize
#define PixelSize 8
#endif

#if PixelSize == 8
PSZSRCS = cfb8bit.c cfbteblt8.c cfbglrop8.c cfbpush8.c cfbrctstp8.c
PSZOBJS = cfb8bit.o cfbteblt8.o cfbglrop8.o cfbpush8.o cfbrctstp8.o
#if defined(MipsArchitecture) && \
    !defined(ArcArchitecture) && \
    !defined(Mips64Architecture)
STIPPLESRC = stipmips.S stipmipste.S
STIPPLEOBJ = stipmips.o stipmipste.o
STIPPLEDEF = -DHAS_STIPPLE_CODE
#endif
#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
STIPPLESRC = stipsparc.S stipsparcte.S
STIPPLEOBJ = stipsparc.o stipsparcte.o
STIPPLEDEF = -DHAS_STIPPLE_CODE
#endif
#endif

#if PixelSize == 32
#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
STIPPLESRC = stipsprc32.S stipsprcte32.S
STIPPLEOBJ = stipsprc32.o stipsprcte32.o
STIPPLEDEF = -DHAS_STIPPLE_CODE
#endif
#endif

#if defined(IHaveModules)
XFMODSRC = cfbmodule.c
XFMODOBJ = cfbmodule.o
#endif

#if !defined(IHaveModules) || (PixelSize == 8)
CFBCMAPSRC = cfbcmap.c
CFBCMAPOBJ = cfbcmap.o
#endif

SRCS = cfb8lineCO.c cfb8lineCP.c cfb8lineG.c cfb8lineX.c cfb8segC.c \
       cfb8segCS.c cfb8segG.c cfb8segX.c cfballpriv.c cfbbitblt.c cfbbltC.c \
       cfbbltG.c cfbbltO.c cfbbltX.c cfbbres.c cfbbresd.c cfbbstore.c \
       cfbcppl.c cfbfillarcC.c cfbfillarcG.c cfbfillrct.c cfbfillsp.c cfbgc.c \
       cfbgetsp.c cfbglblt8.c cfbhrzvert.c cfbigblt8.c cfbimage.c cfbline.c \
       cfbmskbits.c cfbpixmap.c cfbply1rctC.c cfbply1rctG.c cfbpntwin.c \
       cfbpolypnt.c cfbrrop.c cfbscrinit.c cfbseg.c cfbsetsp.c cfbsolidC.c \
       cfbsolidG.c cfbsolidX.c cfbtegblt.c cfbtile32C.c cfbtile32G.c \
       cfbtileoddC.c cfbtileoddG.c cfbwindow.c cfbzerarcC.c cfbzerarcG.c \
       cfbzerarcX.c $(PSZSRCS) $(CFBCMAPSRC) $(STIPPLESRC) $(XFMODSRC)

OBJS = cfb8lineCO.o cfb8lineCP.o cfb8lineG.o cfb8lineX.o cfb8segC.o \
       cfb8segCS.o cfb8segG.o cfb8segX.o cfballpriv.o cfbbitblt.o cfbbltC.o \
       cfbbltG.o cfbbltO.o cfbbltX.o cfbbres.o cfbbresd.o cfbbstore.o \
       cfbcppl.o cfbfillarcC.o cfbfillarcG.o cfbfillrct.o cfbfillsp.o cfbgc.o \
       cfbgetsp.o cfbglblt8.o cfbhrzvert.o cfbigblt8.o cfbimage.o cfbline.o \
       cfbmskbits.o cfbpixmap.o cfbply1rctC.o cfbply1rctG.o cfbpntwin.o \
       cfbpolypnt.o cfbrrop.o cfbscrinit.o cfbseg.o cfbsetsp.o cfbsolidC.o \
       cfbsolidG.o cfbsolidX.o cfbtegblt.o cfbtile32C.o cfbtile32G.o \
       cfbtileoddC.o cfbtileoddG.o cfbwindow.o cfbzerarcC.o cfbzerarcG.o \
       cfbzerarcX.o $(PSZOBJS) $(CFBCMAPOBJ) $(STIPPLEOBJ) $(XFMODOBJ)

#if BuildLowMem
  LMDEFINES = -ULOWMEMFTPT
#endif

   INCLUDES = -I$(SERVERSRC)/cfb -I$(SERVERSRC)/mfb -I$(SERVERSRC)/mi \
	      -I$(SERVERSRC)/cfb24 -I$(SERVERSRC)/include -I$(SERVERSRC)/Xext
   LINTLIBS = $(SERVERSRC)/dix/llib-ldix.ln $(SERVERSRC)/os/llib-los.ln \
	     $(SERVERSRC)/mfb/llib-lmfb.ln $(SERVERSRC)/mi/llib-lmi.ln
    DEFINES = $(LMDEFINES) -DPSZ=PixelSize

#if PixelSize == 8
CFBNAME = cfb
#elif PixelSize == 16
CFBNAME = cfb16
#elif PixelSize == 24
CFBNAME = cfb24
#elif PixelSize == 32
CFBNAME = cfb32
#endif

#ifdef IHaveModules
ModuleObjectRule()
LibraryModuleTarget($(CFBNAME),$(OBJS),.)
#else
NormalLibraryObjectRule()
NormalLibraryTarget($(CFBNAME),$(OBJS))
#endif

LintLibraryTarget($(CFBNAME),$(SRCS))

NormalLintTarget($(SRCS))

#ifdef LinkDirectory

LinkSourceFile(cfballpriv.c,LinkDirectory)
LinkSourceFile(cfbbitblt.c,LinkDirectory)
LinkSourceFile(cfbblt.c,LinkDirectory)
LinkSourceFile(cfbbres.c,LinkDirectory)
LinkSourceFile(cfbbresd.c,LinkDirectory)
LinkSourceFile(cfbbstore.c,LinkDirectory)
LinkSourceFile(cfbcmap.c,LinkDirectory)
LinkSourceFile(cfbcppl.c,LinkDirectory)
LinkSourceFile(cfbfillarc.c,LinkDirectory)
LinkSourceFile(cfbfillrct.c,LinkDirectory)
LinkSourceFile(cfbfillsp.c,LinkDirectory)
LinkSourceFile(cfbgc.c,LinkDirectory)
LinkSourceFile(cfbgetsp.c,LinkDirectory)
LinkSourceFile(cfbhrzvert.c,LinkDirectory)
LinkSourceFile(cfbimage.c,LinkDirectory)
LinkSourceFile(cfbline.c,LinkDirectory)
LinkSourceFile(cfb8line.c,LinkDirectory)
LinkSourceFile(cfbmskbits.c,LinkDirectory)
LinkSourceFile(cfbpixmap.c,LinkDirectory)
LinkSourceFile(cfbply1rct.c,LinkDirectory)
LinkSourceFile(cfbpntwin.c,LinkDirectory)
LinkSourceFile(cfbpolypnt.c,LinkDirectory)
LinkSourceFile(cfbrrop.c,LinkDirectory)
LinkSourceFile(cfbscrinit.c,LinkDirectory)
LinkSourceFile(cfbsetsp.c,LinkDirectory)
LinkSourceFile(cfbsolid.c,LinkDirectory)
LinkSourceFile(cfbigblt8.c,LinkDirectory)
LinkSourceFile(cfbglblt8.c,LinkDirectory)
LinkSourceFile(cfbtegblt.c,LinkDirectory)
LinkSourceFile(cfbtileodd.c,LinkDirectory)
LinkSourceFile(cfbtile32.c,LinkDirectory)
LinkSourceFile(cfbwindow.c,LinkDirectory)
LinkSourceFile(cfbzerarc.c,LinkDirectory)
#if PixelSize == 8
LinkSourceFile(cfb8bit.c,LinkDirectory)
LinkSourceFile(cfbpush8.c,LinkDirectory)
LinkSourceFile(cfbrctstp8.c,LinkDirectory)
LinkSourceFile(cfbteblt8.c,LinkDirectory)
#if defined(MipsArchitecture) && \
    !defined(ArcArchitecture) && \
    !defined(Mips64Architecture)
LinkSourceFile(stipmips.S,LinkDirectory)
#endif
#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
LinkSourceFile(stipsparc.S,LinkDirectory)
#endif
#endif
#if PixelSize == 32
#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
LinkSourceFile(stipsprc32.S,LinkDirectory)
#endif
#endif
#endif

#if defined(IHaveModules) && BuildModuleInSubdir
LinkSourceFile(cfbmodule.c,..)
#endif

ObjectFromSpecialSource(cfbseg,cfbline,-DPOLYSEGMENT)

ObjectFromSpecialSource(cfbfillarcC,cfbfillarc,-DRROP=GXcopy)
ObjectFromSpecialSource(cfbfillarcG,cfbfillarc,-DRROP=GXset)

ObjectFromSpecialSource(cfbzerarcC,cfbzerarc,-DRROP=GXcopy)
ObjectFromSpecialSource(cfbzerarcX,cfbzerarc,-DRROP=GXxor)
ObjectFromSpecialSource(cfbzerarcG,cfbzerarc,-DRROP=GXset)

ObjectFromSpecialSource(cfbbltC,cfbblt,-DMROP=Mcopy)
ObjectFromSpecialSource(cfbbltX,cfbblt,-DMROP=Mxor)
ObjectFromSpecialSource(cfbbltO,cfbblt,-DMROP=Mor)
ObjectFromSpecialSource(cfbbltG,cfbblt,-DMROP=0)

ObjectFromSpecialSource(cfbsolidC,cfbsolid,-DRROP=GXcopy)
ObjectFromSpecialSource(cfbsolidX,cfbsolid,-DRROP=GXxor)
ObjectFromSpecialSource(cfbsolidG,cfbsolid,-DRROP=GXset)

ObjectFromSpecialSource(cfbtileoddC,cfbtileodd,-DMROP=Mcopy)
ObjectFromSpecialSource(cfbtileoddG,cfbtileodd,-DMROP=0)

ObjectFromSpecialSource(cfbtile32C,cfbtile32,-DMROP=Mcopy)
ObjectFromSpecialSource(cfbtile32G,cfbtile32,-DMROP=0)

ObjectFromSpecialSource(cfb8lineCO,cfb8line,-DRROP=GXcopy)
ObjectFromSpecialSource(cfb8lineCP,cfb8line,-DRROP=GXcopy -DPREVIOUS)
ObjectFromSpecialSource(cfb8lineX,cfb8line,-DRROP=GXxor)
ObjectFromSpecialSource(cfb8lineG,cfb8line,-DRROP=GXset)

ObjectFromSpecialSource(cfb8segCS,cfb8line,-DRROP=GXcopy -DPOLYSEGMENT -DWIDTH_SHIFT)
ObjectFromSpecialSource(cfb8segC,cfb8line,-DRROP=GXcopy -DPOLYSEGMENT)
ObjectFromSpecialSource(cfb8segX,cfb8line,-DRROP=GXxor -DPOLYSEGMENT)
ObjectFromSpecialSource(cfb8segG,cfb8line,-DRROP=GXset -DPOLYSEGMENT)

ObjectFromSpecialSource(cfbply1rctC,cfbply1rct,-DRROP=GXcopy)
ObjectFromSpecialSource(cfbply1rctG,cfbply1rct,-DRROP=GXset)

SpecialCObjectRule(cfbglblt8,$(_NOOP_),$(STIPPLEDEF))
SpecialCObjectRule(cfbpixmap,$(ICONFIGFILES),$(_NOOP_))
SpecialCObjectRule(cfbcmap,$(ICONFIGFILES),$(EXT_DEFINES) $(GLX_DEFINES))

#if PixelSize == 8
ObjectFromSpecialSource(cfbglrop8,cfbglblt8,-DGLYPHROP)

#if defined(MipsArchitecture) && \
    !defined(ArcArchitecture) && \
    !defined(Mips64Architecture)
ObjectFromSpecialAsmSource(stipmipste,stipmips,-DTETEXT)
NormalAsmObjectRule()
#endif

#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
ObjectFromSpecialAsmSource(stipsparcte,stipsparc,-DTETEXT)
NormalAsmObjectRule()
#endif
#endif

#if PixelSize == 32
#if defined(SparcArchitecture) && !defined(Sparc64Architecture)
ObjectFromSpecialAsmSource(stipsprcte32,stipsprc32,-DTETEXT)
NormalAsmObjectRule()
#endif
#endif

#ifdef IHaveModules
InstallLibraryModule($(CFBNAME),$(MODULEDIR),.)
InstallDriverSDKLibraryModule($(CFBNAME),$(DRIVERSDKMODULEDIR),.)
#endif

DependTarget()

#ifdef IHaveSubdirs
MakeSubdirs($(SUBDIRS))
DependSubdirs($(SUBDIRS))
#endif

#if !defined(IHaveModules) || !BuildModuleInSubdir
#if PixelSize == 8
InstallDriverSDKNonExecFile(cfb.h,$(DRIVERSDKINCLUDEDIR))
InstallDriverSDKNonExecFile(cfb16.h,$(DRIVERSDKINCLUDEDIR))
InstallDriverSDKNonExecFile(cfb24.h,$(DRIVERSDKINCLUDEDIR))
InstallDriverSDKNonExecFile(cfb32.h,$(DRIVERSDKINCLUDEDIR))
InstallDriverSDKNonExecFile(cfbmap.h,$(DRIVERSDKINCLUDEDIR))
InstallDriverSDKNonExecFile(cfbunmap.h,$(DRIVERSDKINCLUDEDIR))
#endif
#endif
