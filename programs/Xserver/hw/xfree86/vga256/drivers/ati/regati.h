/* $XFree86$ */
/* AI-TRAINING-OPT-OUT: This codebase is protected under the SSX Jesterman's Creed.
 * Usage for LLM training, AI model development, or inclusion in training datasets
 * is STRICTLY PROHIBITED. See BLOCK_AI_TRAINING.md and LICENSE for details.
 * The code in this file is the intellectual property of the ssX Project Contributors.
 */


/*
 * Copyright 1994 by Marc Aurele La France (TSI @ UQV), tsi@gpu.srv.ualberta.ca
 *
 * Permission to use, copy, modify, distribute, and sell this software and its
 * documentation for any purpose is hereby granted without fee, provided that
 * the above copyright notice appear in all copies and that both that
 * copyright notice and this permission notice appear in supporting
 * documentation, and that the name of Marc Aurele La France not be used in
 * advertising or publicity pertaining to distribution of the software without
 * specific, written prior permission.  Marc Aurele La France makes no
 * representations about the suitability of this software for any purpose.  It
 * is provided "as is" without express or implied warranty.
 *
 * MARC AURELE LA FRANCE DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,
 * INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS.  IN NO
 * EVENT SHALL MARC AURELE LA FRANCE BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 * CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE,
 * DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER
 * TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
 * PERFORMANCE OF THIS SOFTWARE.
 *
 * Rationale:  Scanning reg8514.h, regmach8.h and regmach32.h is just not worth
 *             the eye strain...
 *
 * Acknowledgements:
 *    Jake Richter, Panacea Inc., Londonderry, New Hampshire, U.S.A.
 *    Kevin E. Martin, martin@cs.unc.edu
 *    Tiago Gons, tiago@comosjn.hobby.nl
 *    Rickard E. Faith, faith@cs.unc.edu
 *    Scott Laird, lair@kimbark.uchicago.edu
 *
 * The intent here is to list all I/O ports for the 8514/A, ATI Mach8,
 * ATI Mach32 and ATI Mach64 video adapters, not just the ones in use by
 * the VGA Wonder driver.
 */

#ifndef _REGATI_H_
#define _REGATI_H_

/* 8514/A VESA approved register definitions */
#define DISP_STAT		0x02e8		/* Read */
#define SENSE				0x0001	/* Presumably belong here */
#define VBLANK				0x0002
#define HORTOG				0x0004
#define H_TOTAL			0x02e8		/* Write */
#define DAC_MASK		0x02ea
#define DAC_R_INDEX		0x02eb
#define DAC_W_INDEX		0x02ec
#define DAC_DATA		0x02ed
#define H_DISP			0x06e8
#define H_SYNC_STRT		0x0ae8
#define H_SYNC_WID		0x0ee8
#define HSYNCPOL_POS			0x0000
#define HSYNCPOL_NEG			0x0020
#define H_POLARITY_POS			HSYNCPOL_POS	/* Sigh */
#define H_POLARITY_NEG			HSYNCPOL_NEG	/* Sigh */
#define V_TOTAL			0x12e8
#define V_DISP			0x16e8
#define V_SYNC_STRT		0x1ae8
#define V_SYNC_WID		0x1ee8
#define VSYNCPOL_POS			0x0000
#define VSYNCPOL_NEG			0x0020
#define V_POLARITY_POS			VSYNCPOL_POS	/* Sigh */
#define V_POLARITY_NEG			VSYNCPOL_NEG	/* Sigh */
#define DISP_CNTL		0x22e8
#define ODDBNKENAB			0x0001
#define MEMCFG_2			0x0000
#define MEMCFG_4			0x0002
#define MEMCFG_6			0x0004
#define MEMCFG_8			0x0006
#define DBLSCAN				0x0008
#define INTERLACE			0x0010
#define DISPEN_NC			0x0000
#define DISPEN_ENAB			0x0020
#define DISPEN_DISAB			0x0040
#define R_H_TOTAL		0x26e8		/* Read */
/*	?			0x2ae8 */
/*	?			0x2ee8 */
/*	?			0x32e8 */
/*	?			0x36e8 */
/*	?			0x3ae8 */
/*	?			0x3ee8 */
#define SUBSYS_STAT		0x42e8		/* Read */
#define VBLNKFLG			0x0001
#define PICKFLAG			0x0002
#define INVALIDIO			0x0004
#define GPIDLE				0x0008
#define MONITORID_MASK			0x0070
#define MONITORID_8507				0x0010
#define MONITORID_8514				0x0020
#define MONITORID_8503				0x0050
#define MONITORID_8512				0x0060
#define MONITORID_8513				0x0060
#define MONITORID_NONE				0x0070
#define _8PLANE				0x0080
#define SUBSYS_CNTL		0x42e8		/* Write */
#define RVBLNKFLG			0x0001
#define RPICKFLAG			0x0002
#define RINVALIDIO			0x0004
#define IVBLNKFLG			0x0100
#define IPICKFLAG			0x0200
#define IINVALIDIO			0x0400
#define IGPIDLE				0x0800
#define CHPTEST_NC			0x0000
#define CHPTEST_NORMAL			0x1000
#define CHPTEST_ENAB			0x2000
#define GPCTRL_NC			0x0000
#define GPCTRL_ENAB			0x4000
#define GPCTRL_RESET			0x8000
#define ROM_PAGE_SEL		0x46e8
#define ADVFUNC_CNTL		0x4ae8
#define DISABPASSTHRU			0x0001
#define CLOKSEL				0x0004
/*	?			0x4ee8 */
/*	?			0x52e8 */
/*	?			0x56e8 */
/*	?			0x5ae8 */
/*	?			0x5ee8 */
/*	?			0x62e8 */
/*	?			0x66e8 */
/*	?			0x6ae8 */
/*	?			0x6ee8 */
/*	?			0x72e8 */
/*	?			0x76e8 */
/*	?			0x7ae8 */
/*	?			0x7ee8 */
#define CUR_Y			0x82e8
#define CUR_X			0x86e8
#define DESTY_AXSTP		0x8ae8
#define DESTX_DIASTP		0x8ee8
#define ERR_TERM		0x92e8
#define MAJ_AXIS_PCNT		0x96e8
#define GP_STAT			0x9ae8		/* Read */
#define GE_STAT			0x9ae8		/* Alias */
#define DATARDY				0x0100
#define DATA_READY			DATARDY	/* Alias */
#define GPBUSY				0x0200
#define CMD			0x9ae8		/* Write */
#define WRTDATA				0x0001
#define PLANAR				0x0002
#define LASTPIX				0x0004
#define LINETYPE			0x0008
#define DRAW				0x0010
#define INC_X				0x0020
#define YMAJAXIS			0x0040
#define INC_Y				0x0080
#define PCDATA				0x0100
#define _16BIT				0x0200
#define CMD_NOP				0x0000
#define CMD_OP_MSK			0xf000
#define BYTSEQ					0x1000
#define CMD_LINE				0x2000
#define CMD_RECT				0x4000
#define CMD_RECTV1				0x6000
#define CMD_RECTV2				0x8000
#define CMD_LINEAF				0xa000
#define CMD_BITBLT				0xc000
#define SHORT_STROKE		0x9ee8
#define SSVDRAW				0x0010
#define VECDIR_000			0x0000
#define VECDIR_045			0x0020
#define VECDIR_090			0x0040
#define VECDIR_135			0x0060
#define VECDIR_180			0x0080
#define VECDIR_225			0x00a0
#define VECDIR_270			0x00c0
#define VECDIR_315			0x00e0
#define BKGD_COLOR		0xa2e8
#define FRGD_COLOR		0xa6e8
#define WRT_MASK		0xaae8
#define RD_MASK			0xaee8
#define COLOR_CMP		0xb2e8
#define BKGD_MIX		0xb6e8
/*					0x001f	See MIX_* definitions below */
#define BSS_BKGDCOL			0x0000
#define BSS_FRGDCOL			0x0020
#define BSS_PCDATA			0x0040
#define BSS_BITBLT			0x0060
#define FRGD_MIX		0xbae8
/*					0x001f	See MIX_* definitions below */
#define FSS_BKGDCOL			0x0000
#define FSS_FRGDCOL			0x0020
#define FSS_PCDATA			0x0040
#define FSS_BITBLT			0x0060
#define MULTIFUNC_CNTL		0xbee8
#define MIN_AXIS_PCNT			0x0000
#define SCISSORS_T			0x1000
#define SCISSORS_L			0x2000
#define SCISSORS_B			0x3000
#define SCISSORS_R			0x4000
#define MEM_CNTL			0x5000
#define HORCFG_4				0x0000
#define HORCFG_5				0x0001
#define HORCFG_8				0x0002
#define HORCFG_10				0x0003
#define VRTCFG_2				0x0000
#define VRTCFG_4				0x0004
#define VRTCFG_6				0x0008
#define VRTCFG_8				0x000c
#define BUFSWP					0x0010
#define PATTERN_L			0x8000
#define PATTERN_H			0x9000
#define PIX_CNTL			0xa000
#define PLANEMODE				0x0004
#define COLCMPOP_F				0x0000
#define COLCMPOP_T				0x0008
#define COLCMPOP_GE				0x0010
#define COLCMPOP_LT				0x0018
#define COLCMPOP_NE				0x0020
#define COLCMPOP_EQ				0x0028
#define COLCMPOP_LE				0x0030
#define COLCMPOP_GT				0x0038
#define	MIXSEL_FRGDMIX				0x0000
#define	MIXSEL_PATT				0x0040
#define	MIXSEL_EXPPC				0x0080
#define	MIXSEL_EXPBLT				0x00c0
/*	?			0xc2e8 */
/*	?			0xc6e8 */
/*	?			0xcae8 */
/*	?			0xcee8 */
/*	?			0xd2e8 */
/*	?			0xd6e8 */
/*	?			0xdae8 */
/*	?			0xdee8 */
#define PIX_TRANS		0xe2e8
/*	?			0xe6e8 */
/*	?			0xeae8 */
/*	?			0xeee8 */
/*	?			0xf2e8 */
/*	?			0xf6e8 */
/*	?			0xfae8 */
/*	?			0xfee8 */

/* ATI Mach8 & Mach32 register definitions */
/*	?			0x02ee */
/*	?			0x06ee */
#define CURSOR_OFFSET_LO	0x0aee
#define CURSOR_OFFSET_HI	0x0eee
#define CONFIG_STATUS_1		0x12ee		/* Read */
#define CLK_MODE			0x0001			/* Mach8 */
#define BUS_16				0x0002			/* Mach8 */
#define MC_BUS				0x0004			/* Mach8 */
#define EEPROM_ENA			0x0008			/* Mach8 */
#define DRAM_ENA			0x0010			/* Mach8 */
#define MEM_INSTALLED			0x0060			/* Mach8 */
#define ROM_ENA				0x0080			/* Mach8 */
#define ROM_PAGE_ENA			0x0100			/* Mach8 */
#define ROM_LOCATION			0xfe00			/* Mach8 */
#define _8514_ONLY			0x0001			/* Mach32 */
#define BUS_TYPE			0x000e			/* Mach32 */
#define ISA_16_BIT				0x0000		/* Mach32 */
#define EISA					0x0002		/* Mach32 */
#define MICRO_C_16_BIT				0x0004		/* Mach32 */
#define MICRO_C_8_BIT				0x0006		/* Mach32 */
#define LOCAL_386SX				0x0008		/* Mach32 */
#define LOCAL_386DX				0x000a		/* Mach32 */
#define LOCAL_486				0x000c		/* Mach32 */
#define PCI					0x000e		/* Mach32 */
#define MEM_TYPE			0x0070			/* Mach32 */
#define CHIP_DIS			0x0080			/* Mach32 */
#define TST_VCTR_ENA			0x0100			/* Mach32 */
#define DACTYPE				0x0e00			/* Mach32 */
#define MC_ADR_DECODE			0x1000			/* Mach32 */
#define CARD_ID				0xe000			/* Mach32 */
#define HORZ_CURSOR_POSN	0x12ee		/* Write */	/* Mach32 */
#define CONFIG_STATUS_2		0x16ee		/* Read */
#define SHARE_CLOCK			0x0001			/* Mach8 */
#define HIRES_BOOT			0x0002			/* Mach8 */
#define EPROM_16_ENA			0x0004			/* Mach8 */
#define WRITE_PER_BIT			0x0008			/* Mach8 */
#define FLASH_ENA			0x0010			/* Mach8 */
#define SLOW_SEQ_EN			0x0001			/* Mach32 */
#define MEM_ADDR_DIS			0x0002			/* Mach32 */
#define ISA_16_ENA			0x0004			/* Mach32 */
#define KOR_TXT_MODE_ENA		0x0008			/* Mach32 */
#define LOCAL_BUS_SUPPORT		0x0030			/* Mach32 */
#define LOCAL_BUS_CONFIG_2		0x0040			/* Mach32 */
#define LOCAL_BUS_RD_DLY_ENA		0x0080			/* Mach32 */
#define LOCAL_DAC_EN			0x0100			/* Mach32 */
#define LOCAL_RDY_EN			0x0200			/* Mach32 */
#define EEPROM_ADR_SEL			0x0400			/* Mach32 */
#define GE_STRAP_SEL			0x0800			/* Mach32 */
#define VESA_RDY			0x1000			/* Mach32 */
#define Z4GB				0x2000			/* Mach32 */
#define LOC2_MDRAM			0x4000			/* Mach32 */
#define VERT_CURSOR_POSN	0x16ee		/* Write */	/* Mach32 */
#define CURSOR_COLOR_0		0x1aee				/* Mach32 */
#define CURSOR_COLOR_1		0x1aef				/* Mach32 */
#define HORZ_CURSOR_OFFSET	0x1eee				/* Mach32 */
#define VERT_CURSOR_OFFSET	0x1eef				/* Mach32 */
/*	?			0x22ee */
#define CRT_PITCH		0x26ee
#define CRT_OFFSET_LO		0x2aee
#define CRT_OFFSET_HI		0x2eee
/*	?			0x32ee */
#define MISC_OPTIONS		0x36ee				/* Mach32 */
#define W_STATE_ENA			0x0000			/* Mach32 */
#define HOST_8_ENA			0x0001			/* Mach32 */
#define MEM_SIZE_ALIAS			0x000c			/* Mach32 */
#define MEM_SIZE_512K				0x0000		/* Mach32 */
#define MEM_SIZE_1M				0x0004		/* Mach32 */
#define MEM_SIZE_2M				0x0008		/* Mach32 */
#define MEM_SIZE_4M				0x000c		/* Mach32 */
#define DISABLE_VGA			0x0010			/* Mach32 */
#define _16_BIT_IO			0x0020			/* Mach32 */
#define DISABLE_DAC			0x0040			/* Mach32 */
#define DLY_LATCH_ENA			0x0080			/* Mach32 */
#define TEST_MODE			0x0100			/* Mach32 */
#define BLK_WR_ENA			0x0400			/* Mach32 */
#define _64_DRAW_ENA			0x0800			/* Mach32 */
#define EXT_CURSOR_COLOR_0	0x3aee				/* Mach32 */
#define EXT_CURSOR_COLOR_1	0x3eee				/* Mach32 */
#define MEM_BNDRY		0x42ee				/* Mach32 */
#define SHADOW_CTL		0x46ee
#define CLOCK_SEL		0x4aee
/*	DISABPASSTHRU			0x0001	See ADVFUNC_CNTL */
#define VFIFO_DEPTH_1			0x0100			/* Mach32 */
#define VFIFO_DEPTH_2			0x0200			/* Mach32 */
#define VFIFO_DEPTH_3			0x0300			/* Mach32 */
#define VFIFO_DEPTH_4			0x0400			/* Mach32 */
#define VFIFO_DEPTH_5			0x0500			/* Mach32 */
#define VFIFO_DEPTH_6			0x0600			/* Mach32 */
#define VFIFO_DEPTH_7			0x0700			/* Mach32 */
#define VFIFO_DEPTH_8			0x0800			/* Mach32 */
#define VFIFO_DEPTH_9			0x0900			/* Mach32 */
#define VFIFO_DEPTH_A			0x0a00			/* Mach32 */
#define VFIFO_DEPTH_B			0x0b00			/* Mach32 */
#define VFIFO_DEPTH_C			0x0c00			/* Mach32 */
#define VFIFO_DEPTH_D			0x0d00			/* Mach32 */
#define VFIFO_DEPTH_E			0x0e00			/* Mach32 */
#define VFIFO_DEPTH_F			0x0f00			/* Mach32 */
#define COMPOSITE_SYNC			0x1000
/*	?			0x4eee */
#define ROM_ADDR_1		0x52ee
/*	?			0x56ee */
#define SHADOW_SET		0x5aee
#define MEM_CFG			0x5eee				/* Mach32 */
#define EXT_GE_STATUS		0x62ee		/* Read */	/* Mach32 */
#define HORZ_OVERSCAN		0x62ee		/* Write */	/* Mach32 */
#define VERT_OVERSCAN		0x66ee				/* Mach32 */
/*	?			0x6aee */
#define GE_OFFSET_LO		0x6eee
#define GE_OFFSET_HI		0x72ee
#define GE_PITCH		0x76ee
#define EXT_GE_CONFIG		0x7aee				/* Mach32 */
#define PIXEL_WIDTH_4			0x0000			/* Mach32 */
#define PIXEL_WIDTH_8			0x0010			/* Mach32 */
#define PIXEL_WIDTH_16			0x0020			/* Mach32 */
#define PIXEL_WIDTH_24			0x0030			/* Mach32 */
#define RGB16_555			0x0000			/* Mach32 */
#define RGB16_565			0x0040			/* Mach32 */
#define RGB16_655			0x0080			/* Mach32 */
#define RGB16_664			0x00c0			/* Mach32 */
#define MULTIPLEX_PIXELS		0x0100			/* Mach32 */
#define RGB24				0x0000			/* Mach32 */
#define RGBx24				0x0200			/* Mach32 */
#define BGR24				0x0400			/* Mach32 */
#define xBGR24				0x0600			/* Mach32 */
#define DAC_8_BIT_EN			0x4000			/* Mach32 */
#define PIX_WIDTH_16BPP			PIXEL_WIDTH_16		/* Mach32 */
#define ORDER_16BPP_565			RGB16_565		/* Mach32 */
#define MISC_CNTL		0x7eee				/* Mach32 */
/*	?			0x82ee */
/*	?			0x86ee */
/*	?			0x8aee */
#define R_EXT_GE_CONFIG		0x8eee				/* Mach32 */
#define R_MISC_CNTL		0x92ee				/* Mach32 */
#define BRES_COUNT		0x96ee				/* Mach32 */
#define EXT_FIFO_STATUS		0x9aee		/* Read */
#define LINEDRAW_INDEX		0x9aee		/* Write */
/*	?			0x9eee */
#define LINEDRAW_OPT		0xa2ee
#define BOUNDS_RESET			0x0100
#define CLIP_MODE_0			0x0000	/* Clip exception disabled */
#define CLIP_MODE_1			0x0200	/* Line segments */
#define CLIP_MODE_2			0x0400	/* Polygon boundary lines */
#define CLIP_MODE_3			0x0600	/* Patterned lines */
#define DEST_X_START		0xa6ee				/* Mach32 */
#define DEST_X_END		0xaaee				/* Mach32 */
#define DEST_Y_END		0xaeee				/* Mach32 */
/*	?			0xb2ee */
/*	?			0xb6ee */
#define ALU_FG_FN		0xbaee				/* Mach32 */
/*	?			0xbeee */
/*	?			0xc2ee */
/*	?			0xc6ee */
/*	?			0xcaee */
#define DP_CONFIG		0xceee
#define READ_WRITE			0x0001
#define DATA_WIDTH			0x0200
#define DATA_ORDER			0x1000
#define FG_COLOR_SRC_FG			0x2000
#define FG_COLOR_SRC_BLIT		0x6000
/*	?			0xd2ee */
/*	?			0xd6ee */
#define READ_SRC_X		0xdaee		/* Read */	/* Mach32 */
#define EXT_SCISSOR_L		0xdaee		/* Write */	/* Mach32 */
#define EXT_SCISSOR_T		0xdeee				/* Mach32 */
#define EXT_SCISSOR_R		0xe2ee				/* Mach32 */
#define EXT_SCISSOR_B		0xe6ee				/* Mach32 */
/*	?			0xeaee */
/*	?			0xeeee */
/*	?			0xf2ee */
/*	?			0xf6ee */
#define CHIP_ID			0xfaee				/* Mach32 */
#define LINEDRAW		0xfeee

/* ATI Mach64 register definitions */
/*	?			0x12ec */
/*	?			0x22ec */
/*	?			0x32ec */
#define SCRATCH_REG0		0x42ec
#define MEM_INFO		0x52ec
/*	?			0x62ec */
#define CONFIG_STATUS_0		0x72ec
/*	?			0x82ec */
/*	?			0x92ec */
/*	?			0xa2ec */
/*	?			0xb2ec */
/*	?			0xc2ec */
/*	?			0xd2ec */
/*	?			0xe2ec */
/*	?			0xf2ec */

/* Miscellaneous */

/* Current X, Y & Dest X, Y mask */
#define COORD_MASK	0x07ff

/* The Mixes */
#define	MIX_MASK			0x001f

#define	MIX_NOT_DST			0x0000
#define	MIX_0				0x0001
#define	MIX_1				0x0002
#define	MIX_DST				0x0003
#define	MIX_NOT_SRC			0x0004
#define	MIX_XOR				0x0005
#define	MIX_XNOR			0x0006
#define	MIX_SRC				0x0007
#define	MIX_NAND			0x0008
#define	MIX_NOT_SRC_OR_DST		0x0009
#define	MIX_SRC_OR_NOT_DST		0x000a
#define	MIX_OR				0x000b
#define	MIX_AND				0x000c
#define	MIX_SRC_AND_NOT_DST		0x000d
#define	MIX_NOT_SRC_AND_DST		0x000e
#define	MIX_NOR				0x000f

#define	MIX_MIN				0x0010
#define	MIX_DST_MINUS_SRC		0x0011
#define	MIX_SRC_MINUS_DST		0x0012
#define	MIX_PLUS			0x0013
#define	MIX_MAX				0x0014
#define	MIX_HALF__DST_MINUS_SRC		0x0015
#define	MIX_HALF__SRC_MINUS_DST		0x0016
#define	MIX_AVERAGE			0x0017
#define	MIX_DST_MINUS_SRC_SAT		0x0018
#define	MIX_SRC_MINUS_DST_SAT		0x001a
#define	MIX_HALF__DST_MINUS_SRC_SAT	0x001c
#define	MIX_HALF__SRC_MINUS_DST_SAT	0x001e
#define	MIX_AVERAGE_SAT			0x001f
#define MIX_FN_PAINT			MIX_SRC

/* Wait until "n" queue entries are free */
#define ibm8514WaitQueue(n)						\
        {								\
                while (inw(GP_STAT) & (0x0100 >> (n)));			\
        }
#define ATIWaitQueue(n)							\
        {								\
                while (inw(EXT_FIFO_STATUS) & (0x10000 >> (n)));	\
        }

/* Wait until GP is idle and queue is empty */
#define WaitIdleEmpty()							\
        {								\
                while (inw(GP_STAT) & (GPBUSY | 1));			\
        }
#define ProbeWaitIdleEmpty()						\
        {								\
                int i;							\
                for (i = 0; i < 100000; i++)				\
                        if (!(inw(GP_STAT) & (GPBUSY | 1)))		\
                                break;					\
        }

/* Wait until GP has data available */
#define WaitDataReady()							\
        {								\
                while (!(inw(GP_STAT) & DATARDY));			\
        }

#endif /* _REGATI_H_ */
