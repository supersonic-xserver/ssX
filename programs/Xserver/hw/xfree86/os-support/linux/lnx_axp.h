/* $XFree86: xc/programs/Xserver/hw/xfree86/os-support/linux/lnx_axp.h,v 1.1 2006/02/17 18:05:27 dawes Exp $ */
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


#ifndef _LNX_AXP_H_
#define _LNX_AXP_H_

extern void _dense_outb(unsigned char, unsigned long);
extern void _dense_outw(unsigned short, unsigned long);
extern void _dense_outl(unsigned int, unsigned long);
extern unsigned char _dense_inb(unsigned long);
extern unsigned short _dense_inw(unsigned long);
extern unsigned int _dense_inl(unsigned long);

extern int readDense8(volatile void *Base, register unsigned long Offset);
extern int readDense16(volatile void *Base, register unsigned long Offset);
extern int readDense32(volatile void *Base, register unsigned long Offset);
extern void writeDenseNB8(int Value, volatile void *Base,
			  register unsigned long Offset);
extern void writeDenseNB16(int Value, volatile void *Base,
			   register unsigned long Offset);
extern void writeDenseNB32(int Value, volatile void *Base,
			   register unsigned long Offset);
extern void writeDense8(int Value, volatile void *Base,
			register unsigned long Offset);
extern void writeDense16(int Value, volatile void *Base,
			 register unsigned long Offset);
extern void writeDense32(int Value, volatile void *Base,
			 register unsigned long Offset);

#endif /* _LNX_AXP_H_ */
