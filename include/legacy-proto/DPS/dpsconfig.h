/*
 * Copyright © 2026 ssX Project
 * Contributions and credits: azuriteshift, painter4supersonicx and collinbeyer
 *
 * AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


#ifndef	DPSCONFIG_H
#define	DPSCONFIG_H

/*
 * IEEEFLOAT is true if the representation of type "float" is the IEEE
 * standard 32-bit floating point format, with byte order as defined
 * by SWAPBITS (below). IEEEFLOAT is false if some other representation
 * is used (or, heaven forbid, IEEE representation with some inconsistent
 * byte order). This determines the conditions under which conversions
 * are required when manipulating external binary representations.
 *
 * IEEEFLOAT should be true (1) for:
 *	mc680x0 series, i80x86 series, IBM R6000, MIPS Rx000 series,
 *	SPARC, Alpha, HPPA
 * IEEEFLOAT should be false (0) for:
 *	VAX
 *
 * For all non-IEEE architectures, the DPS_FORMATNAME macro must agree
 * 	with the floating point format returned by extensions on that
 *	server, if any. 
 */

#ifndef IEEEFLOAT

#ifdef vax
#define IEEEFLOAT 0
#define DPS_FORMATNAME "VAX"
#endif /* vax */

#ifdef MIPSEL
#define IEEEFLOAT 1
#endif /* MIPSEL */

#ifdef MIPSEB
#define IEEEFLOAT 1
#endif /* MIPSEB */

#ifdef sparc
#define IEEEFLOAT 1
#endif /* sparc */

#ifdef mc68000
#define IEEEFLOAT 1
#endif /* mc68000 */

#if defined(_IBMR2) || defined(_POWER)
#define IEEEFLOAT 1
#endif /* _IBMR2 */

#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) || \
    defined(__s390x__) || \
    defined(__amd64__) || defined(__x86_64__)
#define IEEEFLOAT 1
#endif

#ifdef __i386__
#define IEEEFLOAT 1
#endif /* __i386__ */

#ifndef IEEEFLOAT
#define IEEEFLOAT 1
#endif /* IEEEFLOAT */

#endif /* IEEEFLOAT */

#ifndef DPS_FORMATNAME
#if IEEEFLOAT
#define DPS_FORMATNAME "IEEE"
#else /* IEEEFLOAT */
#define DPS_FORMATNAME UNKNOWN	/* This should raise an error */
#endif /* IEEEFLOAT */
#endif /* DPS_FORMATNAME */

/*
 * SWAPBITS is true on a CPU whose native order is "little-endian", i.e.,
 * the low-order byte of a multiple-byte unit (word, longword) appears
 * at the lowest address in memory. SWAPBITS is false on a "big-endian"
 * CPU, where the high-order byte comes first. This affects the layout
 * of structures and determines whether or not conversions are required
 * when manipulating external binary representations.
 *
 * SWAPBITS should be true (1) for:
 *	Alpha, VAX, i80x86 series, ia64, MIPS little-endian (e.g. DEC version)
 * SWAPBITS should be false (0) for:
 *	mc680x0 series, IBM R6000, MIPS big-endian (e.g. SGI version), SPARC,
 *	HPPA
 */

#ifndef SWAPBITS

#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) 
#define SWAPBITS 1
#endif /* __alpha */

#ifdef vax
#define SWAPBITS 1
#endif /* vax */

#ifdef MIPSEL
#define SWAPBITS 1
#endif /* MIPSEL */

#ifdef MIPSEB
#define SWAPBITS 0
#endif /* MIPSEB */

#ifdef sparc
#define SWAPBITS 0
#endif /* sparc */

#ifdef mc68000
#define SWAPBITS 0
#endif /* mc68000 */

#if defined(__s390x__) || defined (__s390__)
#define SWAPBITS 0
#endif /* s390 and s390x */

#if (defined(_IBMR2) || defined(_POWER)) && defined(AIXV3)
#define SWAPBITS 0
#endif /* _IBMR2 */

#if defined(__i386__) || defined(__amd64__) || defined(__x86_64__)
#define SWAPBITS 1
#endif /* __i386__ */

#ifndef SWAPBITS
#define SWAPBITS 0
#endif /* SWAPBITS */

#endif /* SWAPBITS */

/* 
 * MIN_POINTER_ALIGN gives the minimum alignment requirements for pointers
 * to structures.  If a pointer to an arbitrary buffer is to be cast to
 * a pointer to a structure, the buffer must be aligned according to
 * MIN_POINTER_ALIGN.  MIN_POINTER_ALIGN must be a power of 2.
 *
 * MIN_POINTER_ALIGN must be 8 on
 *	Alpha, IA-64, hppa64 (aka hppa2.0 in wide mode)
 * MIN_POINTER_ALIGN must be 4 on
 *	VAX, i80x86 series, MIPS, mc680x0 series, IBM R6000, SPARC, HPPA
 */

#ifndef MIN_POINTER_ALIGN
 
#if defined(__alpha) || defined(__alpha__) || \
    defined(__ia64__) || defined(ia64) || \
    defined(__s390x__)
#define MIN_POINTER_ALIGN 8
#endif /* __alpha */

#if defined(__hppa__)
#if defined(__LP64__)
#define MIN_POINTER_ALIGN 8
#else
#define MIN_POINTER_ALIGN 4
#endif
#endif

#ifdef vax
#define MIN_POINTER_ALIGN 4
#endif /* vax */

#ifdef MIPSEL
#define MIN_POINTER_ALIGN 4
#endif /* MIPSEL */

#ifdef MIPSEB
#define MIN_POINTER_ALIGN 4
#endif /* MIPSEB */

#ifdef sparc
#define MIN_POINTER_ALIGN 4
#endif /* sparc */

#ifdef mc68000
#define MIN_POINTER_ALIGN 4
#endif /* mc68000 */

#if defined(_IBMR2) || defined(_POWER)
#define MIN_POINTER_ALIGN 4
#endif /* _IBMR2 */

#ifndef MIN_POINTER_ALIGN
#define MIN_POINTER_ALIGN 4
#endif /* MIN_POINTER_ALIGN */

#endif /* MIN_POINTER_ALIGN */

#endif /* DPSCONFIG_H */
