/*
 *  Copyright © 2014-2015 Broadcom
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#define VC4_MASK(high, low) (((1 << ((high) - (low) + 1)) - 1) << (low))
/* Using the GNU statement expression extension */
#define VC4_SET_FIELD(value, field)                                       \
        ({                                                                \
                uint32_t fieldval = (value) << field ## _SHIFT;		  \
                WARN_ON((fieldval & ~ field ## _MASK) != 0);              \
                fieldval & field ## _MASK;                                \
         })

#define VC4_GET_FIELD(word, field) (((word)  & field ## _MASK) >> field ## _SHIFT)

#define V3D_IDENT0   0x00000
# define V3D_EXPECTED_IDENT0 \
	((2 << 24) | \
	('V' << 0) | \
	('3' << 8) | \
	 ('D' << 16))

#define V3D_IDENT1   0x00004
/* Multiples of 1kb */
# define V3D_IDENT1_VPM_SIZE_MASK                      VC4_MASK(31, 28)
# define V3D_IDENT1_VPM_SIZE_SHIFT                     28
# define V3D_IDENT1_NSEM_MASK                          VC4_MASK(23, 16)
# define V3D_IDENT1_NSEM_SHIFT                         16
# define V3D_IDENT1_TUPS_MASK                          VC4_MASK(15, 12)
# define V3D_IDENT1_TUPS_SHIFT                         12
# define V3D_IDENT1_QUPS_MASK                          VC4_MASK(11, 8)
# define V3D_IDENT1_QUPS_SHIFT                         8
# define V3D_IDENT1_NSLC_MASK                          VC4_MASK(7, 4)
# define V3D_IDENT1_NSLC_SHIFT                         4
# define V3D_IDENT1_REV_MASK                           VC4_MASK(3, 0)
# define V3D_IDENT1_REV_SHIFT                          0

#define V3D_IDENT2   0x00008
#define V3D_SCRATCH  0x00010
#define V3D_L2CACTL  0x00020
# define V3D_L2CACTL_L2CCLR                            (1 << 2)
# define V3D_L2CACTL_L2CDIS                            (1 << 1)
# define V3D_L2CACTL_L2CENA                            (1 << 0)

#define V3D_SLCACTL  0x00024
# define V3D_SLCACTL_T1CC_MASK                         VC4_MASK(27, 24)
# define V3D_SLCACTL_T1CC_SHIFT                        24
# define V3D_SLCACTL_T0CC_MASK                         VC4_MASK(19, 16)
# define V3D_SLCACTL_T0CC_SHIFT                        16
# define V3D_SLCACTL_UCC_MASK                          VC4_MASK(11, 8)
# define V3D_SLCACTL_UCC_SHIFT                         8
# define V3D_SLCACTL_ICC_MASK                          VC4_MASK(3, 0)
# define V3D_SLCACTL_ICC_SHIFT                         0

#define V3D_INTCTL   0x00030
#define V3D_INTENA   0x00034
#define V3D_INTDIS   0x00038
# define V3D_INT_SPILLUSE                              (1 << 3)
# define V3D_INT_OUTOMEM                               (1 << 2)
# define V3D_INT_FLDONE                                (1 << 1)
# define V3D_INT_FRDONE                                (1 << 0)

#define V3D_CT0CS    0x00100
#define V3D_CT1CS    0x00104
#define V3D_CTNCS(n) (V3D_CT0CS + 4 * n)
# define V3D_CTRSTA      (1 << 15)
# define V3D_CTSEMA      (1 << 12)
# define V3D_CTRTSD      (1 << 8)
# define V3D_CTRUN       (1 << 5)
# define V3D_CTSUBS      (1 << 4)
# define V3D_CTERR       (1 << 3)
# define V3D_CTMODE      (1 << 0)

#define V3D_CT0EA    0x00108
#define V3D_CT1EA    0x0010c
#define V3D_CTNEA(n) (V3D_CT0EA + 4 * (n))
#define V3D_CT0CA    0x00110
#define V3D_CT1CA    0x00114
#define V3D_CTNCA(n) (V3D_CT0CA + 4 * (n))
#define V3D_CT00RA0  0x00118
#define V3D_CT01RA0  0x0011c
#define V3D_CTNRA0(n) (V3D_CT00RA0 + 4 * (n))
#define V3D_CT0LC    0x00120
#define V3D_CT1LC    0x00124
#define V3D_CTNLC(n) (V3D_CT0LC + 4 * (n))
#define V3D_CT0PC    0x00128
#define V3D_CT1PC    0x0012c
#define V3D_CTNPC(n) (V3D_CT0PC + 4 * (n))

#define V3D_PCS      0x00130
# define V3D_BMOOM       (1 << 8)
# define V3D_RMBUSY      (1 << 3)
# define V3D_RMACTIVE    (1 << 2)
# define V3D_BMBUSY      (1 << 1)
# define V3D_BMACTIVE    (1 << 0)

#define V3D_BFC      0x00134
#define V3D_RFC      0x00138
#define V3D_BPCA     0x00300
#define V3D_BPCS     0x00304
#define V3D_BPOA     0x00308
#define V3D_BPOS     0x0030c
#define V3D_BXCF     0x00310
#define V3D_SQRSV0   0x00410
#define V3D_SQRSV1   0x00414
#define V3D_SQCNTL   0x00418
#define V3D_SRQPC    0x00430
#define V3D_SRQUA    0x00434
#define V3D_SRQUL    0x00438
#define V3D_SRQCS    0x0043c
#define V3D_VPACNTL  0x00500
#define V3D_VPMBASE  0x00504
#define V3D_PCTRC    0x00670
#define V3D_PCTRE    0x00674
#define V3D_PCTR0    0x00680
#define V3D_PCTRS0   0x00684
#define V3D_PCTR1    0x00688
#define V3D_PCTRS1   0x0068c
#define V3D_PCTR2    0x00690
#define V3D_PCTRS2   0x00694
#define V3D_PCTR3    0x00698
#define V3D_PCTRS3   0x0069c
#define V3D_PCTR4    0x006a0
#define V3D_PCTRS4   0x006a4
#define V3D_PCTR5    0x006a8
#define V3D_PCTRS5   0x006ac
#define V3D_PCTR6    0x006b0
#define V3D_PCTRS6   0x006b4
#define V3D_PCTR7    0x006b8
#define V3D_PCTRS7   0x006bc
#define V3D_PCTR8    0x006c0
#define V3D_PCTRS8   0x006c4
#define V3D_PCTR9    0x006c8
#define V3D_PCTRS9   0x006cc
#define V3D_PCTR10   0x006d0
#define V3D_PCTRS10  0x006d4
#define V3D_PCTR11   0x006d8
#define V3D_PCTRS11  0x006dc
#define V3D_PCTR12   0x006e0
#define V3D_PCTRS12  0x006e4
#define V3D_PCTR13   0x006e8
#define V3D_PCTRS13  0x006ec
#define V3D_PCTR14   0x006f0
#define V3D_PCTRS14  0x006f4
#define V3D_PCTR15   0x006f8
#define V3D_PCTRS15  0x006fc
#define V3D_BGE      0x00f00
#define V3D_FDBGO    0x00f04
#define V3D_FDBGB    0x00f08
#define V3D_FDBGR    0x00f0c
#define V3D_FDBGS    0x00f10
#define V3D_ERRSTAT  0x00f20

/* XXX: mask widths */
#define PV_CONTROL				0x00
# define PV_CONTROL_CLK_MUX_EN			(1 << 24)
# define PV_CONTROL_FORMAT_MASK			VC4_MASK(23, 21)
# define PV_CONTROL_FORMAT_SHIFT		21
# define PV_CONTROL_FORMAT_24			0
# define PV_CONTROL_FORMAT_DSIV_16		1
# define PV_CONTROL_FORMAT_DSIC_16		2
# define PV_CONTROL_FORMAT_DSIV_18		3
# define PV_CONTROL_FORMAT_DSIV_24		4

# define PV_CONTROL_FIFO_LEVEL_MASK		VC4_MASK(20, 15)
# define PV_CONTROL_FIFO_LEVEL_SHIFT		15
# define PV_CONTROL_CLR_AT_START		(1 << 14)
# define PV_CONTROL_TRIGGER_UNDERFLOW		(1 << 13)
# define PV_CONTROL_WAIT_HSTART			(1 << 12)
# define PV_CONTROL_CLK_SELECT_MASK		VC4_MASK(3, 2)
# define PV_CONTROL_CLK_SELECT_SHIFT		2
# define PV_CONTROL_FIFO_CLR			(1 << 1)
# define PV_CONTROL_EN				(1 << 0)

#define PV_V_CONTROL				0x04
# define PV_VCONTROL_CONTINUOUS			(1 << 1)
# define PV_VCONTROL_VIDEN			(1 << 0)

#define PV_VSYNCD				0x08

#define PV_HORZA				0x0c
# define PV_HORZA_HBP_MASK			VC4_MASK(31, 16)
# define PV_HORZA_HBP_SHIFT			16
# define PV_HORZA_HSYNC_MASK			VC4_MASK(15, 0)
# define PV_HORZA_HSYNC_SHIFT			0

#define PV_HORZB				0x10
# define PV_HORZB_HFP_MASK			VC4_MASK(31, 16)
# define PV_HORZB_HFP_SHIFT			16
# define PV_HORZB_HACTIVE_MASK			VC4_MASK(15, 0)
# define PV_HORZB_HACTIVE_SHIFT			0

#define PV_VERTA				0x14
# define PV_VERTA_VBP_MASK			VC4_MASK(31, 16)
# define PV_VERTA_VBP_SHIFT			16
# define PV_VERTA_VSYNC_MASK			VC4_MASK(15, 0)
# define PV_VERTA_VSYNC_SHIFT			0

#define PV_VERTB				0x18
# define PV_VERTB_VFP_MASK			VC4_MASK(31, 16)
# define PV_VERTB_VFP_SHIFT			16
# define PV_VERTB_VACTIVE_MASK			VC4_MASK(15, 0)
# define PV_VERTB_VACTIVE_SHIFT			0

#define PV_VERTA_EVEN				0x1c
#define PV_VERTB_EVEN				0x20

#define PV_INTEN				0x24
#define PV_INTSTAT				0x28
# define PV_INT_VID_IDLE			(1 << 9)
# define PV_INT_VFP_END			(1 << 8)
# define PV_INT_VFP_START			(1 << 7)
# define PV_INT_VACT_START			(1 << 6)
# define PV_INT_VBP_START			(1 << 5)
# define PV_INT_VSYNC_START			(1 << 4)
# define PV_INT_HFP_START			(1 << 3)
# define PV_INT_HACT_START			(1 << 2)
# define PV_INT_HBP_START			(1 << 1)
# define PV_INT_HSYNC_START			(1 << 0)

#define PV_STAT					0x2c
# define PV_STAT_IDLE				(1 << 8)
# define PV_STAT_RUNNING_MASK			VC4_MASK(7, 0)

#define PV_DSI_HACT				0x30

#define SCALER_DISPCTRL                         0x00000000
#define SCALER_DISPSTAT                         0x00000004
#define SCALER_DISPID                           0x00000008
#define SCALER_DISPECTRL                        0x0000000c
#define SCALER_DISPPROF                         0x00000010
#define SCALER_DISPDITHER                       0x00000014
#define SCALER_DISPEOLN                         0x00000018
#define SCALER_DISPLIST0                        0x00000020
#define SCALER_DISPLIST1                        0x00000024
#define SCALER_DISPLIST2                        0x00000028
#define SCALER_DISPLSTAT                        0x0000002c
#define SCALER_DISPLACT0                        0x00000030
#define SCALER_DISPLACT1                        0x00000034
#define SCALER_DISPLACT2                        0x00000038
#define SCALER_DISPCTRL0                        0x00000040
#define SCALER_DISPBKGND0                       0x00000044
#define SCALER_DISPSTAT0                        0x00000048
#define SCALER_DISPBASE0                        0x0000004c
#define SCALER_DISPCTRL1                        0x00000050
#define SCALER_DISPBKGND1                       0x00000054
#define SCALER_DISPSTAT1                        0x00000058
#define SCALER_DISPBASE1                        0x0000005c
#define SCALER_DISPCTRL2                        0x00000060
#define SCALER_DISPBKGND2                       0x00000064
#define SCALER_DISPSTAT2                        0x00000068
#define SCALER_DISPBASE2                        0x0000006c
#define SCALER_DISPALPHA2                       0x00000070
#define SCALER_GAMADDR                          0x00000078
#define SCALER_GAMDATA                          0x000000e0
#define SCALER_DLIST_START                      0x00002000
#define SCALER_DLIST_SIZE                       0x00004000

#define VC4_HDMI_CORE_REV			0x00
#define VC4_HDMI_SW_RESET_CONTROL		0x04
#define VC4_HDMI_HOTPLUG_INT			0x08

#define VC4_HDMI_HOTPLUG			0x0c
# define VC4_HDMI_HOTPLUG_CONNECTED		(1 << 0)

#define VC4_HDMI_HORZA				0xc4
# define VC4_HDMI_HORZA_VPOS			(1 << 14)
# define VC4_HDMI_HORZA_HPOS			(1 << 13)

#define VC4_HDMI_HORZB				0xc8
# define VC4_HDMI_HORZB_HBP_MASK		VC4_MASK(29, 20)
# define VC4_HDMI_HORZB_HBP_SHIFT		20
# define VC4_HDMI_HORZB_HSP_MASK		VC4_MASK(19, 10)
# define VC4_HDMI_HORZB_HSP_SHIFT		10

#define VC4_HDMI_FIFO_CTL			0x5c
# define VC4_HDMI_FIFO_CTL_MASTER_SLAVE_N	(1 << 0)

#define VC4_HDMI_VERTA0				0xcc
#define VC4_HDMI_VERTA1				0xd4
# define VC4_HDMI_VERTA_VSP_MASK		VC4_MASK(24, 20)
# define VC4_HDMI_VERTA_VSP_SHIFT		20
# define VC4_HDMI_VERTA_VFP_MASK		VC4_MASK(19, 13)
# define VC4_HDMI_VERTA_VFP_SHIFT		13
# define VC4_HDMI_VERTA_VAL_MASK		VC4_MASK(12, 0)
# define VC4_HDMI_VERTA_VAL_SHIFT		0

#define VC4_HDMI_VERTB0				0xd0
#define VC4_HDMI_VERTB1				0xd8
# define VC4_HDMI_VERTB_VSPO_MASK		VC4_MASK(21, 9)
# define VC4_HDMI_VERTB_VSPO_SHIFT		9
# define VC4_HDMI_VERTB_VBP_MASK		VC4_MASK(8, 0)
# define VC4_HDMI_VERTB_VBP_SHIFT		0

/* HVS display list information. */
#define HVS_BOOTLOADER_DLIST_END                32

enum hvs_pixel_format {
	/* 8bpp */
	HVS_PIXEL_FORMAT_RGB332 = 0,
	/* 16bpp */
	HVS_PIXEL_FORMAT_RGBA4444 = 1,
	HVS_PIXEL_FORMAT_RGB555 = 2,
	HVS_PIXEL_FORMAT_RGBA5551 = 3,
	HVS_PIXEL_FORMAT_RGB565 = 4,
	/* 24bpp */
	HVS_PIXEL_FORMAT_RGB888 = 5,
	HVS_PIXEL_FORMAT_RGBA6666 = 6,
	/* 32bpp */
	HVS_PIXEL_FORMAT_RGBA8888 = 7
};

/* Note: the LSB is the rightmost character shown.  Only valid for
 * HVS_PIXEL_FORMAT_RGB8888, not RGB888.
 */
#define HVS_PIXEL_ORDER_RGBA			0
#define HVS_PIXEL_ORDER_BGRA			1
#define HVS_PIXEL_ORDER_ARGB			2
#define HVS_PIXEL_ORDER_ABGR			3

#define HVS_PIXEL_ORDER_XBRG			0
#define HVS_PIXEL_ORDER_XRBG			1
#define HVS_PIXEL_ORDER_XRGB			2
#define HVS_PIXEL_ORDER_XBGR			3

#define HVS_PIXEL_ORDER_XYCBCR			0
#define HVS_PIXEL_ORDER_XYCRCB			1
#define HVS_PIXEL_ORDER_YXCBCR			2
#define HVS_PIXEL_ORDER_YXCRCB			3

#define SCALER_CTL0_END				(1 << 31)
#define SCALER_CTL0_VALID			(1 << 30)

#define SCALER_CTL0_SIZE_MASK			VC4_MASK(29, 24)
#define SCALER_CTL0_SIZE_SHIFT			24

#define SCALER_CTL0_HFLIP                       (1 << 16)
#define SCALER_CTL0_VFLIP                       (1 << 15)

#define SCALER_CTL0_ORDER_MASK			VC4_MASK(14, 13)
#define SCALER_CTL0_ORDER_SHIFT			13

/* Set to indicate no scaling. */
#define SCALER_CTL0_UNITY			(1 << 4)

#define SCALER_CTL0_PIXEL_FORMAT_MASK		VC4_MASK(3, 0)
#define SCALER_CTL0_PIXEL_FORMAT_SHIFT		0

#define SCALER_POS0_FIXED_ALPHA_MASK		VC4_MASK(31, 24)
#define SCALER_POS0_FIXED_ALPHA_SHIFT		24

#define SCALER_POS0_START_Y_MASK		VC4_MASK(23, 12)
#define SCALER_POS0_START_Y_SHIFT		12

#define SCALER_POS0_START_X_MASK		VC4_MASK(11, 0)
#define SCALER_POS0_START_X_SHIFT		0

#define SCALER_POS2_ALPHA_MODE_MASK		VC4_MASK(31,30)
#define SCALER_POS2_ALPHA_MODE_SHIFT		30
#define SCALER_POS2_ALPHA_MODE_PIPELINE		0
#define SCALER_POS2_ALPHA_MODE_FIXED		1
#define SCALER_POS2_ALPHA_MODE_FIXED_NONZERO	2
#define SCALER_POS2_ALPHA_MODE_FIXED_OVER_0x07	3

#define SCALER_POS2_HEIGHT_MASK			VC4_MASK(27, 16)
#define SCALER_POS2_HEIGHT_SHIFT		16

#define SCALER_POS2_WIDTH_MASK			VC4_MASK(11, 0)
#define SCALER_POS2_WIDTH_SHIFT			0

#define SCALER_SRC_PITCH_MASK			VC4_MASK(15, 0)
#define SCALER_SRC_PITCH_SHIFT			0
