/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef CLOSESTR_H
#define CLOSESTR_H

#define	NEED_REPLIES
#include <X11/Xproto.h>
#include "closure.h"
#include "dix.h"
#include "misc.h"
#include "gcstruct.h"

/* closure structures */

/* OpenFont */

typedef struct _OFclosure {
    ClientPtr   client;
    short       current_fpe;
    short       num_fpes;
    FontPathElementPtr *fpe_list;
    Mask        flags;
    Bool        slept;

/* XXX -- get these from request buffer instead? */
    const char       *origFontName;
    int		origFontNameLen;
    XID         fontid;
    char       *fontname;
    int         fnamelen;
    FontPtr	non_cachable_font;
}           OFclosureRec;

/* ListFontsWithInfo */

#define XLFDMAXFONTNAMELEN	256
typedef struct _LFWIstate {
    char	pattern[XLFDMAXFONTNAMELEN];
    int		patlen;
    int		current_fpe;
    int		max_names;
    Bool	list_started;
    pointer	private;
} LFWIstateRec, *LFWIstatePtr;

typedef struct _LFWIclosure {
    ClientPtr		client;
    int			num_fpes;
    FontPathElementPtr	*fpe_list;
    xListFontsWithInfoReply *reply;
    int			length;
    LFWIstateRec	current;
    LFWIstateRec	saved;
    int			savedNumFonts;
    Bool		haveSaved;
    Bool		slept;
    char		*savedName;
} LFWIclosureRec;

/* ListFonts */

typedef struct _LFclosure {
    ClientPtr   client;
    int         num_fpes;
    FontPathElementPtr *fpe_list;
    FontNamesPtr names;
    LFWIstateRec current;
    LFWIstateRec saved;
    Bool        haveSaved;
    Bool        slept;
    char	*savedName;
    int		savedNameLen;
}	LFclosureRec;

/* PolyText */

typedef
    int			(* PolyTextPtr)(
			DrawablePtr /* pDraw */,
			GCPtr /* pGC */,
			int /* x */,
			int /* y */,
			int /* count */,
			void * /* chars or shorts */
			);

typedef struct _PTclosure {
    ClientPtr		client;
    DrawablePtr		pDraw;
    GC			*pGC;
    unsigned char	*pElt;
    unsigned char	*endReq;
    unsigned char	*data;
    int			xorg;
    int			yorg;
    CARD8		reqType;
    PolyTextPtr		polyText;
    int			itemSize;
    XID			did;
    int			err;
    Bool		slept;
} PTclosureRec;

/* ImageText */

typedef
    void		(* ImageTextPtr)(
			DrawablePtr /* pDraw */,
			GCPtr /* pGC */,
			int /* x */,
			int /* y */,
			int /* count */,
			void * /* chars or shorts */
			);

typedef struct _ITclosure {
    ClientPtr		client;
    DrawablePtr		pDraw;
    GC			*pGC;
    BYTE		nChars;
    unsigned char	*data;
    int			xorg;
    int			yorg;
    CARD8		reqType;
    ImageTextPtr	imageText;
    int			itemSize;
    XID			did;
    Bool		slept;
} ITclosureRec;
#endif				/* CLOSESTR_H */
