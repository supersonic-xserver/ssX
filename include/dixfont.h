/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef DIXFONT_H
#define DIXFONT_H 1

#include "dix.h"
#include <X11/fonts/font.h>
#include "closure.h"
#include <X11/fonts/fontstruct.h>

#define NullDIXFontProp ((DIXFontPropPtr)0)

typedef struct _DIXFontProp *DIXFontPropPtr;

extern FPEFunctions *fpe_functions;

extern int FontToXError(int /*err*/);

extern Bool SetDefaultFont(char * /*defaultfontname*/);

extern void QueueFontWakeup(FontPathElementPtr /*fpe*/);

extern void RemoveFontWakeup(FontPathElementPtr /*fpe*/);

extern void FontWakeup(pointer /*data*/,
		       int /*count*/,
		       pointer /*LastSelectMask*/);

extern int OpenFont(ClientPtr /*client*/,
		    XID /*fid*/,
		    Mask /*flags*/,
		    unsigned /*lenfname*/,
		    char * /*pfontname*/);

extern int CloseFont(pointer /*pfont*/,
		     XID /*fid*/);

typedef struct _xQueryFontReply *xQueryFontReplyPtr;

extern void QueryFont(FontPtr /*pFont*/,
		      xQueryFontReplyPtr /*pReply*/,
		      int /*nProtoCCIStructs*/);

extern int ListFonts(ClientPtr /*client*/,
		     unsigned char * /*pattern*/,
		     unsigned int /*length*/,
		     unsigned int /*max_names*/);

int
doListFontsWithInfo(ClientPtr /*client*/,
		    LFWIclosurePtr /*c*/);

extern int doPolyText(ClientPtr /*client*/,
		      PTclosurePtr /*c*/
);

extern int PolyText(ClientPtr /*client*/,
		    DrawablePtr /*pDraw*/,
		    GCPtr /*pGC*/,
		    unsigned char * /*pElt*/,
		    unsigned char * /*endReq*/,
		    int /*xorg*/,
		    int /*yorg*/,
		    int /*reqType*/,
		    XID /*did*/);

extern int doImageText(ClientPtr /*client*/,
		       ITclosurePtr /*c*/);

extern int ImageText(ClientPtr /*client*/,
		     DrawablePtr /*pDraw*/,
		     GCPtr /*pGC*/,
		     int /*nChars*/,
		     unsigned char * /*data*/,
		     int /*xorg*/,
		     int /*yorg*/,
		     int /*reqType*/,
		     XID /*did*/);

extern int SetFontPath(ClientPtr /*client*/,
		       int /*npaths*/,
		       unsigned char * /*paths*/,
		       int * /*error*/);

extern int SetDefaultFontPath(char * /*path*/);

extern unsigned char *GetFontPath(int * /*count*/,
				  int * /*length*/);

extern int LoadGlyphs(ClientPtr /*client*/,
		      FontPtr /*pfont*/,
		      unsigned /*nchars*/,
		      int /*item_size*/,
		      unsigned char * /*data*/);

extern void DeleteClientFontStuff(ClientPtr /*client*/);

/* Quartz support on Mac OS X pulls in the QuickDraw
   framework whose InitFonts function conflicts here. */
#ifdef __DARWIN__
#define InitFonts Darwin_X_InitFonts
#endif
extern void InitFonts(void);

extern void FreeFonts(void);

extern FontPtr find_old_font(XID /*id*/);

extern void GetGlyphs(FontPtr     /*font*/,
		      unsigned long /*count*/,
		      unsigned char * /*chars*/,
		      FontEncoding /*fontEncoding*/,
		      unsigned long * /*glyphcount*/,
		      CharInfoPtr * /*glyphs*/);

extern void QueryGlyphExtents(FontPtr     /*pFont*/,
			      CharInfoPtr * /*charinfo*/,
			      unsigned long /*count*/,
			      ExtentInfoPtr /*info*/);

extern Bool QueryTextExtents(FontPtr     /*pFont*/,
			     unsigned long /*count*/,
			     unsigned char * /*chars*/,
			     ExtentInfoPtr /*info*/);

extern Bool ParseGlyphCachingMode(const char * /*str*/);

extern void InitGlyphCaching(void);

extern void SetGlyphCachingMode(int /*newmode*/);

#endif				/* DIXFONT_H */
