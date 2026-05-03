/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef _FONTPROTO_H
#define _FONTPROTO_H

/* Externally provided functions required by libXfont */

extern int RegisterFPEFunctions ( NameCheckFunc name_func, 
				  InitFpeFunc init_func, 
				  FreeFpeFunc free_func, 
				  ResetFpeFunc reset_func, 
				  OpenFontFunc open_func, 
				  CloseFontFunc close_func, 
				  ListFontsFunc list_func, 
				  StartLfwiFunc start_lfwi_func, 
				  NextLfwiFunc next_lfwi_func, 
				  WakeupFpeFunc wakeup_func, 
				  ClientDiedFunc client_died, 
				  LoadGlyphsFunc load_glyphs, 
				  StartLaFunc start_list_alias_func, 
				  NextLaFunc next_list_alias_func, 
				  SetPathFunc set_path_func);

extern int GetDefaultPointSize ( void );

extern int init_fs_handlers ( FontPathElementPtr fpe, 
			      BlockHandlerProcPtr block_handler);
extern void remove_fs_handlers ( FontPathElementPtr fpe, 
				 BlockHandlerProcPtr block_handler, 
				 Bool all );

extern int client_auth_generation ( ClientPtr client );

#ifndef ___CLIENTSIGNAL_DEFINED___
#define ___CLIENTSIGNAL_DEFINED___
extern Bool ClientSignal ( ClientPtr client );
#endif /* ___CLIENTSIGNAL_DEFINED___ */

extern void DeleteFontClientID ( Font id );
extern Font GetNewFontClientID ( void );
extern int StoreFontClientFont ( FontPtr pfont, Font id );
extern void FontFileRegisterFpeFunctions ( void );
extern void FontFileCheckRegisterFpeFunctions ( void );

extern Bool XpClientIsBitmapClient ( ClientPtr client );
extern Bool XpClientIsPrintClient( ClientPtr client, FontPathElementPtr fpe );
extern void PrinterFontRegisterFpeFunctions ( void );

extern void fs_register_fpe_functions ( void );
extern void check_fs_register_fpe_functions ( void );

/* util/private.c */
extern FontPtr  CreateFontRec (void);
extern void  DestroyFontRec (FontPtr font);
extern Bool     _FontSetNewPrivate (FontPtr        /* pFont */,
				    int            /* n */,
				    pointer        /* ptr */);
extern int      AllocateFontPrivateIndex (void);
extern void ResetFontPrivateIndex (void);

/* Type1/t1funcs.c */
extern void Type1RegisterFontFileFunctions(void);
extern void CIDRegisterFontFileFunctions(void);

/* Speedo/spfuncs.c */
extern void SpeedoRegisterFontFileFunctions(void);

/* FreeType/ftfuncs.c */
extern void FreeTypeRegisterFontFileFunctions(void);

#endif
