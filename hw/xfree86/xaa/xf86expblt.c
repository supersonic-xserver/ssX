/* $XFree86$ */

/*
 * Copyright 1996  The XFree86 Project
 *
 * Permission is hereby granted, free of charge, to any person obtaining a 
 * copy of this software and associated documentation files (the "Software"), 
 * to deal in the Software without restriction, including without limitation 
 * the rights to use, copy, modify, merge, publish, distribute, sublicense, 
 * and/or sell copies of the Software, and to permit persons to whom the 
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL 
 * HARM HANEMAAYER BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, 
 * WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF 
 * OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE 
 * SOFTWARE.
 * 
 * Written by Harm Hanemaayer (H.Hanemaayer@inter.nl.net).
 */

#include "compiler.h"
#include "misc.h"

#include "xf86expblt.h"

/*
 * When compiled with MSBFIRST defined,
 * this file produces MSB-first versions of most of the functions.
 */

/* These are macros for 64-bit integer handling. */

#define UINT64_DECLARE(uint64) \
    unsigned int uint64##low32; \
    unsigned int uint64##high32
#define UINT64_ASSIGN(uint64, int32, int32_2) \
    uint64##low32 = int32; uint64##high32 = int32_2
#define UINT64_LOW32(uint64) uint64##low32
#define UINT64_SHIFTRIGHT32(uint64) uint64##low32 = uint64##high32; uint64##high32 = 0
/*
 * Something fishy is going on with ">> 32". This seems to be equivalent to
 * ">> 0" on my system. I'm not sure whether this is a CPU or compiler bug.
 * We check for this case (shift == 0).
 */
/* shift <= 32 */
#define UINT64_ORLEFTSHIFTEDINT(uint64, int32, shift) \
    uint64##low32 |= int32 << shift; \
    if (shift > 0) \
        uint64##high32 |= int32 >> (32 - shift)


extern unsigned char byte_reversed[256];
/* This is isn't defined yet. Keep the compiler happy. */
#ifndef MSBFIRST
unsigned int byte_reversed_expand3[1] = { 0x00000000 };
unsigned int byte_expand3[1] = { 0x00000000 };
#else
extern unsigned int byte_expand3[1];
extern unsigned int byte_reversed_expand3[1];
#endif

/* Macros to write a word, converting the per-byte bit order if required. */

#ifndef MSBFIRST

#define WRITE_IN_BITORDER(dest, data) *(dest) = data;

#else	/* "Nasty" bit order within bytes. */

#if defined(__GNUC__) && defined(__i386__)
static __inline__ unsigned int reverse_bitorder(data) {
#if defined(Lynx) || (defined(SYSV) || defined(SVR4)) && !defined(ACK_ASSEMBLER) || defined(linux) && defined(__ELF__)
	__asm__(
		"movl $0,%%ecx\n"
		"movb %%al,%%cl\n"
		"movb byte_reversed(%%ecx),%%al\n"
		"movb %%ah,%%cl\n"
		"movb byte_reversed(%%ecx),%%ah\n"
		"roll $16,%%eax\n"
		"movb %%al,%%cl\n"
		"movb byte_reversed(%%ecx),%%al\n"
		"movb %%ah,%%cl\n"
		"movb byte_reversed(%%ecx),%%ah\n"
		"roll $16,%%eax\n"
		: "=a" (data) : "0" (data)
		: "cx"
		);
#else
	__asm__(
		"movl $0,%%ecx\n"
		"movb %%al,%%cl\n"
		"movb _byte_reversed(%%ecx),%%al\n"
		"movb %%ah,%%cl\n"
		"movb _byte_reversed(%%ecx),%%ah\n"
		"roll $16,%%eax\n"
		"movb %%al,%%cl\n"
		"movb _byte_reversed(%%ecx),%%al\n"
		"movb %%ah,%%cl\n"
		"movb _byte_reversed(%%ecx),%%ah\n"
		"roll $16,%%eax\n"
		: "=a" (data) : "0" (data)
		: "cx"
		);
#endif
	return data;
}
#define WRITE_IN_BITORDER(dest, data) *(dest) = reverse_bitorder(data);
#else	/* If no (gcc on i386), don't use asm. */
#define WRITE_IN_BITORDER(dest, data) \
	{ unsigned data2; \
	data2 = byte_reversed[data & 0xFF]; \
	data2 |= byte_reversed[(data & 0xFF00) >> 8] << 8; \
	data2 |= byte_reversed[(data & 0xFF0000) >> 16] << 16; \
	data2 |= byte_reversed[(data & 0xFF000000) >> 24] << 24; \
	*(dest) = data2; \
	}
#endif

#endif


/*
 * Macros for 24bpp color expansion in 8bpp pixel mode (each bit is
 * expanded to three bits).
 */

#define WRITE_IN_BITORDER3_FIRSTWORD_MACRO(dest, data, mapping) \
    { unsigned data2; \
	data2 = mapping[data & 0xFF]; \
	data2 |= mapping[(data & 0xFF00) >> 8] << 24; \
	*(dest) = data2; \
    }
#define WRITE_IN_BITORDER3_SECONDWORD_MACRO(dest, data, mapping) \
    { unsigned data2; \
	data2 = mapping[(data & 0xFF00) >> 8] >> 8; \
	data2 |= mapping[(data & 0xFF0000) >> 16] << 16; \
	*(dest + 1) = data2; \
    }
#define WRITE_IN_BITORDER3_THIRDWORD_MACRO(dest, data, mapping) \
    { unsigned data2; \
	data2 = mapping[(data & 0xFF0000) >> 16] >> 16; \
	data2 |= mapping[(data & 0xFF000000) >> 24] << 8; \
	*(dest + 2) = data2; \
    }
#define WRITE_IN_BITORDER3_MACRO(dest, data, mapping) \
	WRITE_IN_BITORDER3_FIRSTWORD_MACRO(dest, data, mapping) \
	WRITE_IN_BITORDER3_SECONDWORD_MACRO(dest, data, mapping) \
	WRITE_IN_BITORDER3_THIRDWORD_MACRO(dest, data, mapping)

#ifndef MSBFIRST
#define WRITE_IN_BITORDER3(dest, data) \
	WRITE_IN_BITORDER3_MACRO(dest, data, byte_expand3)
#define WRITE_IN_BITORDER3_FIRSTWORD(dest, data) \
	WRITE_IN_BITORDER3_FIRSTWORD_MACRO(dest, data, byte_expand3)
#define WRITE_IN_BITORDER3_SECONDWORD(dest, data) \
	WRITE_IN_BITORDER3_SECONDWORD_MACRO(dest, data, byte_expand3)
#define WRITE_IN_BITORDER3_THIRDWORD(dest, data) \
	WRITE_IN_BITORDER3_THIRDWORD_MACRO(dest, data, byte_expand3)
#else
#define WRITE_IN_BITORDER3(dest, data) \
	WRITE_IN_BITORDER3_MACRO(dest, data, byte_reversed_expand3)
#define WRITE_IN_BITORDER3_FIRSTWORD(dest, data) \
	WRITE_IN_BITORDER3_FIRSTWORD_MACRO(dest, data, byte_reversed_expand3)
#define WRITE_IN_BITORDER3_SECONDWORD(dest, data) \
	WRITE_IN_BITORDER3_SECONDWORD_MACRO(dest, data, byte_reversed_expand3)
#define WRITE_IN_BITORDER3_THIRDWORD(dest, data) \
	WRITE_IN_BITORDER3_THIRDWORD_MACRO(dest, data, byte_reversed_expand3)
#endif



/* Functions for plain bitmap scanlines. */

#ifdef MSBFIRST
unsigned int *xf86DrawBitmapScanlineMSBFirst(base, src, nbytes)
#else
unsigned int *xf86DrawBitmapScanline(base, src, nbytes)
#endif
    unsigned int *base;
    unsigned int *src;
    int nbytes;
{
    int i, nwords;
    nwords = nbytes / 4;
    while (nwords >= 4) {
    	/* Reshuffled a bit for performance. */
    	WRITE_IN_BITORDER(base, *src);
    	WRITE_IN_BITORDER(base + 1, *(src + 1));
    	nwords -= 4;
    	WRITE_IN_BITORDER(base + 2, *(src + 2));
    	base += 4;
    	WRITE_IN_BITORDER(base - 1, *(src + 3));
    	src += 4;
    }
    for (i = 0; i < nwords; i++) {
    	WRITE_IN_BITORDER(base + i, *(src + i));
    }
    src += i;
    base += i;
    switch (nbytes % 4) {
    case 1 :
        WRITE_IN_BITORDER(base, *(unsigned char *)src);
        return base + 1;
    case 2 :
        WRITE_IN_BITORDER(base, *(unsigned short *)src);
        return base + 1;
    case 3 :
        WRITE_IN_BITORDER(base,
            *(unsigned short *)src | (*((unsigned char *)src + 2) << 16));
        return base + 1;
    default :
        break;
    }
    return base;
}

#ifdef MSBFIRST
unsigned int *xf86DrawBitmapScanline3MSBFirst(base, src, w)
#else
unsigned int *xf86DrawBitmapScanline3(base, src, w)
#endif
    unsigned int *base;
    unsigned int *src;
    int w;
{
    int i, nwords;
    unsigned int bits;
    /* Number of full words in the source. */
    nwords = w / 32;
    while (nwords >= 4) {
    	/* Reshuffled a bit for performance. */
    	WRITE_IN_BITORDER3(base, *src);
    	WRITE_IN_BITORDER3(base + 3, *(src + 1));
    	nwords -= 4;
    	WRITE_IN_BITORDER3(base + 6, *(src + 2));
    	base += 12;
    	WRITE_IN_BITORDER3(base - 3, *(src + 3));
    	src += 4;
    }
    while (nwords >= 1) {
    	WRITE_IN_BITORDER3(base, *src);
    	src++;
    	base += 3;
    	nwords --;
    }
    w &= 31;
    if (w == 0)
        return base;
    /* Get the last source bits. */
    switch ((w + 7) / 8) {
    case 1 :
        bits = *(unsigned char *)src;
        break;
    case 2 :
        bits = *(unsigned short *)src;
        break;
    case 3 :
        bits = *(unsigned short *)src | (*((unsigned char *)src + 2) << 16);
        break;
    default : /* 4 */
        bits = *src;
    }
    WRITE_IN_BITORDER3_FIRSTWORD(base, bits);
    base++;
    if (w >= 11) {
        WRITE_IN_BITORDER3_SECONDWORD(base, bits);
        base++;
        if (w >= 22) {
            WRITE_IN_BITORDER3_THIRDWORD(base, bits);
            base++;
        }
    }
    return base;
}

/*
 * nbytes > 0, src access can be unaligned.
 */

#ifdef MSBFIRST
ScanlineReturn xf86DrawBitmapScanlineMSBFirstBytePadded(base, src, bits, nbytes)
    unsigned int *base;
    unsigned int *src;
    unsigned int bits;
    int nbytes;
{
    int i, leftedgebytes, nwords;
    ScanlineReturn ret;
    if (nbytes <= 2) {
        if (nbytes == 1) {
           if (((unsigned int)base & 3) == 3)
               *(unsigned int *)((unsigned int)base & ~3) = bits |
                   ((unsigned int)*(unsigned char *)src << 24);
           else
               ret.bits |= *(unsigned char *)src << 
                   (((unsigned int)base & 3) * 8);
        }
        else {
            /* nbytes == 2 */
           if (((unsigned int)base & 3) == 3) {
               *(unsigned int *)((unsigned int)base & ~3) = bits |
                   ((unsigned int)*(unsigned char *)src << 24);
               ret.bits = *((unsigned char *)src + 1);
           }
           else
           if (((unsigned int)base & 3) == 2)
               *(unsigned int *)((unsigned int)base & ~3) = bits |
                   ((unsigned int)*(unsigned short *)src << 16);
           else
               ret.bits |= (unsigned int)*(unsigned short *)src << 
                   (((unsigned int)base & 3) * 8);
        }
        ret.base = (unsigned int *)((unsigned int)base + nbytes);
        return ret;
    }
    /* First combine the left over bytes with new ones to form a word. */
    switch ((unsigned int)base & 3) {
    case 0 :
        leftedgebytes = 0;
        break;
    case 1 :
        bits |= *(unsigned char *)src << 8;
        bits |= *(unsigned short *)((unsigned char *)src + 1) << 16;
        leftedgebytes = 3;
        break;
    case 2 :
        bits |= *(unsigned short *)src << 16;
        leftedgebytes = 2;
        break;
    case 3 :
        bits |= *(unsigned char *)src << 24;
        leftedgebytes = 1;
        break;
    }
    if (leftedgebytes > 0) {
        base = (unsigned int *)((unsigned int)base & ~3);
        WRITE_IN_BITORDER(base, bits);
        nbytes -= leftedgebytes;
        base++;
    }
    nwords = nbytes / 4;
    while (nwords >= 4) {
    	/* Reshuffled a bit for performance. */
    	WRITE_IN_BITORDER(base, *src);
    	WRITE_IN_BITORDER(base + 1, *(src + 1));
    	nwords -= 4;
    	WRITE_IN_BITORDER(base + 2, *(src + 2));
    	base += 4;
    	WRITE_IN_BITORDER(base - 1, *(src + 3));
    	src += 4;
    }
    for (i = 0; i < nwords; i++) {
    	WRITE_IN_BITORDER(base + i, *(src + i));
    }
    switch (nbytes) {
    case 0 :
    	ret.base = base + i;
    	break;
    case 1 :
        ret.base = (unsigned int *)((unsigned char *)(base + i) + 1);
        ret.bits = *(unsigned char *)src;
        break;
    case 2 :
        ret.base = (unsigned int *)((unsigned char *)(base + i) + 2);
        ret.bits = *(unsigned short *)src;
        break;
    case 3 :
        ret.base = (unsigned int *)((unsigned char *)(base + i) + 3);
        ret.bits = *(unsigned short *)src;
        ret.bits |= *((unsigned char *)src + 2) << 16;
        break;
    }
    return ret;
}
#endif


/* Functions that generate text bitmap scanlines. */

static unsigned int *DrawTextScanlineWidth6();
static unsigned int *DrawTextScanlineWidth8();
static unsigned int *DrawTextScanlineWidth10();
static unsigned int *DrawTextScanlineWidth12();
static unsigned int *DrawTextScanlineWidth14();
static unsigned int *DrawTextScanlineWidth16();
static unsigned int *DrawTextScanlineWidth18();
static unsigned int *DrawTextScanlineWidth24();

static unsigned int *(*glyphwidth_function[32])(
#if NeedNestedPrototypes
    unsigned int *base, unsigned int **glyphp, int line, int nglyph
#endif
) = {
    NULL, NULL, NULL, NULL, 
    NULL, DrawTextScanlineWidth6, NULL, DrawTextScanlineWidth8,
    NULL, DrawTextScanlineWidth10, NULL, DrawTextScanlineWidth12,
    NULL, DrawTextScanlineWidth14, NULL, DrawTextScanlineWidth16,
    NULL, DrawTextScanlineWidth18, NULL, NULL,
    NULL, NULL, NULL, DrawTextScanlineWidth24,
    NULL, NULL, NULL, NULL,
    NULL, NULL, NULL, NULL,
};

static int glyphwidth_stretchsize[32] = {
    0, 0, 0, 0, 0, 16, 0, 8, 0, 16, 0, 8, 0, 16, 0, 8,
    0, 16, 0, 0, 0, 0, 0, 4, 0, 0, 0, 0, 0, 0, 0, 0
};

#ifdef MSBFIRST
unsigned int *xf86DrawTextScanlineMSBFirst(base, glyphp, line, nglyph, glyphwidth)
#else
unsigned int *xf86DrawTextScanline(base, glyphp, line, nglyph, glyphwidth)
#endif
    unsigned int *base;
    unsigned int **glyphp;
    int line;
    int nglyph;
    int glyphwidth;
{
    UINT64_DECLARE(bits);
    int shift, i;

    if (glyphwidth_stretchsize[glyphwidth - 1] > 0
    && glyphwidth_stretchsize[glyphwidth - 1] <= nglyph) {
        int glyphsleft;
        /* 
         * Draw the first stretches of characters using a function
         * customized for the glyph width.
         */
        base = (*glyphwidth_function[glyphwidth - 1])(base, glyphp, line,
            nglyph);
        glyphsleft = nglyph & (glyphwidth_stretchsize[glyphwidth - 1] - 1);
        /* Now do the rest. */
        glyphp += nglyph - glyphsleft;
        nglyph = glyphsleft;
    }

    UINT64_ASSIGN(bits, 0, 0);
    shift = 0;
    i = 0;
    while (i < nglyph) {
        UINT64_ORLEFTSHIFTEDINT(bits, glyphp[i][line], shift);
        shift += glyphwidth;
        if (shift >= 32) {
            /* Write a 32-bit word. */
            WRITE_IN_BITORDER(base, UINT64_LOW32(bits));
            base++;
            shift -= 32;
            UINT64_SHIFTRIGHT32(bits);
        }
        i++;
    }
    if (shift > 0) {
        WRITE_IN_BITORDER(base, UINT64_LOW32(bits));
        base++;
    }
    return base;
}


#ifdef MSBFIRST
unsigned int *xf86DrawNonTETextScanlineMSBFirst(base, glyphinfop, line, nglyph)
#else
unsigned int *xf86DrawNonTETextScanline(base, glyphinfop, line, nglyph)
#endif
    unsigned int *base;
    NonTEGlyphInfo *glyphinfop;
    int line;
    int nglyph;
{
    UINT64_DECLARE(bits);
    int shift, i;

    UINT64_ASSIGN(bits, 0, 0);
    shift = 0;
    i = 0;
    line = 0;
    while (i < nglyph) {
        /* Check whether the current glyph has bits for this scanline. */
        if (line >= glyphinfop[i].firstline
        && line <= glyphinfop[i].lastline) {
            UINT64_ORLEFTSHIFTEDINT(bits, glyphinfop[i].bitsp[line], shift);
        }
        shift += glyphinfop[i].width;
        if (shift >= 32) {
            /* Write a 32-bit word. */
            WRITE_IN_BITORDER(base, UINT64_LOW32(bits));
            base++;
            shift -= 32;
            UINT64_SHIFTRIGHT32(bits);
        }
        i++;
    }
    if (shift > 0) {
        WRITE_IN_BITORDER(base, UINT64_LOW32(bits));
        base++;
    }
    return base;
}


#ifdef MSBFIRST
unsigned int *xf86DrawTextScanline3MSBFirst(base, glyphp, line, nglyph, glyphwidth)
#else
unsigned int *xf86DrawTextScanline3(base, glyphp, line, nglyph, glyphwidth)
#endif
    unsigned int *base;
    unsigned int **glyphp;
    int line;
    int nglyph;
    int glyphwidth;
{
    UINT64_DECLARE(bits);
    int shift, i;

    UINT64_ASSIGN(bits, 0, 0);
    shift = 0;
    i = 0;
    while (i < nglyph) {
        UINT64_ORLEFTSHIFTEDINT(bits, glyphp[i][line], shift);
        shift += glyphwidth;
        if (shift >= 32) {
            /* Write a 32-bit word. */
            WRITE_IN_BITORDER3(base, UINT64_LOW32(bits));
            base += 3;
            shift -= 32;
            UINT64_SHIFTRIGHT32(bits);
        }
        i++;
    }
    if (shift > 0) {
        WRITE_IN_BITORDER3_FIRSTWORD(base, UINT64_LOW32(bits));
        base++;
        if (shift >= 11) {
            WRITE_IN_BITORDER3_SECONDWORD(base, UINT64_LOW32(bits));
            base++;
            if (shift >= 22) {
                WRITE_IN_BITORDER3_THIRDWORD(base, UINT64_LOW32(bits));
                base++;
            }
        }
    }
    return base;
}


/*
 * The functions below write stretches of glyphs for special font widths.
 * Actually, these functions could also be used for 24bpp color expansion
 * in 8bpp mode.
 */

static unsigned int *DrawTextScanlineWidth6(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp;
    int line;
    int nglyph;
{
    while (nglyph >= 16) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 6;
        bits |= glyphp[2][line] << 12;
        bits |= glyphp[3][line] << 18;
        bits |= glyphp[4][line] << 24;
        bits |= glyphp[5][line] << 30;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[5][line] >> 2;
        bits |= glyphp[6][line] << 4;
        bits |= glyphp[7][line] << 10;
        bits |= glyphp[8][line] << 16;
        bits |= glyphp[9][line] << 22;
        bits |= glyphp[10][line] << 28;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[10][line] >> 4;
        bits |= glyphp[11][line] << 2;
        bits |= glyphp[12][line] << 8;
        bits |= glyphp[13][line] << 14;
        bits |= glyphp[14][line] << 20;
        bits |= glyphp[15][line] << 26;
        WRITE_IN_BITORDER(base + 2, bits);
        base += 3;
        nglyph -= 16;
        glyphp += 16;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth8(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp;
    int line;
    int nglyph;
{
#ifdef MSBFIRST
    /*
     * For this font width (and only this one), there's a seperate
     * MSB-first version.
     */
    while (nglyph >= 8) {
        unsigned int bits;
        bits = byte_reversed[glyphp[0][line]];
        bits |= byte_reversed[glyphp[1][line]] << 8;
        bits |= byte_reversed[glyphp[2][line]] << 16;
        bits |= byte_reversed[glyphp[3][line]] << 24;
        *base = bits;
        bits = byte_reversed[glyphp[4][line]];
        bits |= byte_reversed[glyphp[5][line]] << 8;
        bits |= byte_reversed[glyphp[6][line]] << 16;
        bits |= byte_reversed[glyphp[7][line]] << 24;
        *(base + 1) = bits;
        base += 2;
        nglyph -= 8;	    
        glyphp += 8;
    }
#else
    while (nglyph >= 8) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 8;
        bits |= glyphp[2][line] << 16;
        bits |= glyphp[3][line] << 24;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[4][line];
        bits |= glyphp[5][line] << 8;
        bits |= glyphp[6][line] << 16;
        bits |= glyphp[7][line] << 24;
        WRITE_IN_BITORDER(base + 1, bits);
        base += 2;
        nglyph -= 8;	    
        glyphp += 8;
    }
#endif
#ifdef WHOLE_SCANLINE
    if (nglyph == 0)
        return base;
    do {
        bits = glyphp[8][line];
        if (nglyph == 1)
    	    break;
        bits |= glyphp[9][line] << 16;
        if (nglyph == 2)
            break;
        bits |= glyphp[10][line] << 16;
        if (nglyph == 3)
            break;
        bits |= glyphp[11][line] << 24;
    } while (0);
    WRITE_IN_BITORDER(base, bits);
    if (nglyph <= 4)
        return base + 1;
    do {
        bits = glyphp[8][line];
        if (nglyph == 5)
    	    break;
        bits |= glyphp[9][line] << 16;
        if (nglyph == 6)
            break;
        bits |= glyphp[10][line] << 16;
        if (nglyph == 7)
            break;
        bits |= glyphp[11][line] << 24;
    } while (0);
    WRITE_IN_BITORDER(base + 1, bits);
    return base + 2;
#endif
    return base;
}

static unsigned int *DrawTextScanlineWidth10(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp; 
    int line;
    int nglyph;
{
    while (nglyph >= 16) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 10;
        bits |= glyphp[2][line] << 20;
        bits |= glyphp[3][line] << 30;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[3][line] >> 2;
        bits |= glyphp[4][line] << 8;
        bits |= glyphp[5][line] << 18;
        bits |= glyphp[6][line] << 28;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[6][line] >> 4;
        bits |= glyphp[7][line] << 6;
        bits |= glyphp[8][line] << 16;
        bits |= glyphp[9][line] << 26;
        WRITE_IN_BITORDER(base + 2, bits);
        bits = glyphp[9][line] >> 6;
        bits |= glyphp[10][line] << 4;
        bits |= glyphp[11][line] << 14;
        bits |= glyphp[12][line] << 24;
        WRITE_IN_BITORDER(base + 3, bits);
        bits = glyphp[12][line] >> 8;
        bits |= glyphp[13][line] << 2;
        bits |= glyphp[14][line] << 12;
        bits |= glyphp[15][line] << 22;
        WRITE_IN_BITORDER(base + 4, bits);
        base += 5;
        nglyph -= 16;
        glyphp += 16;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth12(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp; 
    int line;
    int nglyph;
{
    while (nglyph >= 8) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 12;
        bits |= glyphp[2][line] << 24;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[2][line] >> 8;
        bits |= glyphp[3][line] << 4;
        bits |= glyphp[4][line] << 16;
        bits |= glyphp[5][line] << 28;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[5][line] >> 4;
        bits |= glyphp[6][line] << 8;
        bits |= glyphp[7][line] << 20;
        WRITE_IN_BITORDER(base + 2, bits);
        base += 3;
        nglyph -= 8;
        glyphp += 8;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth14(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp; 
    int line;
    int nglyph;
{
    while (nglyph >= 16) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 14;
        bits |= glyphp[2][line] << 28;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[2][line] >> 4;
        bits |= glyphp[3][line] << 10;
        bits |= glyphp[4][line] << 24;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[4][line] >> 8;
        bits |= glyphp[5][line] << 6;
        bits |= glyphp[6][line] << 20;
        WRITE_IN_BITORDER(base + 2, bits);
        bits = glyphp[6][line] >> 12;
        bits |= glyphp[7][line] << 2;
        bits |= glyphp[8][line] << 16;
        bits |= glyphp[9][line] << 30;
        WRITE_IN_BITORDER(base + 3, bits);
        bits = glyphp[9][line] >> 2;
        bits |= glyphp[10][line] << 12;
        bits |= glyphp[11][line] << 26;
        WRITE_IN_BITORDER(base + 4, bits);
        bits = glyphp[11][line] >> 6;
        bits |= glyphp[12][line] << 8;
        bits |= glyphp[13][line] << 22;
        WRITE_IN_BITORDER(base + 5, bits);
        bits = glyphp[13][line] >> 10;
        bits |= glyphp[14][line] << 4;
        bits |= glyphp[15][line] << 18;
        WRITE_IN_BITORDER(base + 6, bits);
        base += 7;
        nglyph -= 16;
        glyphp += 16;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth16(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp;
    int line;
    int nglyph;
{
    while (nglyph >= 8) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 16;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[2][line];
        bits |= glyphp[3][line] << 16;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[4][line];
        bits |= glyphp[5][line] << 16;
        WRITE_IN_BITORDER(base + 2, bits);
        bits = glyphp[6][line];
        bits |= glyphp[7][line] << 16;
        WRITE_IN_BITORDER(base + 3, bits);
        base += 4;
        nglyph -= 8;	    
        glyphp += 8;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth18(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp; 
    int line;
    int nglyph;
{
    while (nglyph >= 16) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 18;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[1][line] >> 14;
        bits |= glyphp[2][line] << 4;
        bits |= glyphp[3][line] << 22;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[3][line] >> 10;
        bits |= glyphp[4][line] << 8;
        bits |= glyphp[5][line] << 26;
        WRITE_IN_BITORDER(base + 2, bits);
        bits = glyphp[5][line] >> 6;
        bits |= glyphp[6][line] << 12;
        bits |= glyphp[7][line] << 30;
        WRITE_IN_BITORDER(base + 3, bits);
        bits = glyphp[7][line] >> 2;
        bits |= glyphp[8][line] << 16;
        WRITE_IN_BITORDER(base + 4, bits);
        bits = glyphp[8][line] >> 16;
        bits |= glyphp[9][line] << 2;
        bits |= glyphp[10][line] << 20;
        WRITE_IN_BITORDER(base + 5, bits);
        bits = glyphp[10][line] >> 12;
        bits |= glyphp[11][line] << 6;
        bits |= glyphp[12][line] << 24;
        WRITE_IN_BITORDER(base + 6, bits);
        bits = glyphp[12][line] >> 8;
        bits |= glyphp[13][line] << 10;
        bits |= glyphp[14][line] << 28;
        WRITE_IN_BITORDER(base + 7, bits);
        bits = glyphp[14][line] >> 4;
        bits |= glyphp[15][line] << 14;
        WRITE_IN_BITORDER(base + 8, bits);
        base += 9;
        nglyph -= 16;
        glyphp += 16;
    }
    return base;
}

static unsigned int *DrawTextScanlineWidth24(base, glyphp, line, nglyph)
    unsigned int *base;
    unsigned int **glyphp; 
    int line;
    int nglyph;
{
    while (nglyph >= 4) {
        unsigned int bits;
        bits = glyphp[0][line];
        bits |= glyphp[1][line] << 24;
        WRITE_IN_BITORDER(base, bits);
        bits = glyphp[1][line] >> 8;
        bits |= glyphp[2][line] << 16;
        WRITE_IN_BITORDER(base + 1, bits);
        bits = glyphp[2][line] >> 16;
        bits |= glyphp[3][line] << 8;
        WRITE_IN_BITORDER(base + 2, bits);
        base += 3;
        nglyph -= 4;
        glyphp += 4;
    }
    return base;
}
