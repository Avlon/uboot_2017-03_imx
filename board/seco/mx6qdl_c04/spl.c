/*
 * Copyright (C) UDOO Team
 *
 * Author: Francesco Montefoschi <francesco.monte@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/clock.h>
#include <asm/arch/crm_regs.h>
#include <asm/arch/imx-regs.h>
#include <asm/arch/sys_proto.h>
#include <asm/io.h>
#include <linux/sizes.h>
#include <common.h>
#include <libfdt.h>
#include <spl.h>
#include <asm/arch/mx6-ddr.h>
#include "detectboard.h"

#include "../include/ddr/ddr_1G_2x512.h"
#include "../include/ddr/ddr_1G_4x256.h"
#ifdef CONFIG_MX6QP
#include "../include/ddr/ddr_mx6qp_2G_4x512.h"
#elif defined(CONFIG_MX6Q)
#include "../include/ddr/ddr_mx6dq_2G_4x512.h"
#else
#include "../include/ddr/ddr_mx6sdl_2G_4x512.h"
#endif
#include "../include/ddr/ddr_512M_2x256.h"
#include "../include/ddr/ddr_256M_1x256.h"

#include "../include/a75/ddr_a75dl_1G_2x512.h"
#include "../include/a75/ddr_a75dl_512M_2x256.h"
#include "../include/a75/ddr_a75dl_256M_1x256.h"
#include "../include/a75/ddr_a75solo_256M_1x256.h"

#include "../include/962/ddr_962dl_1G_4x256.h"
#include "../include/962/ddr_962dl_512M_2x256.h"

#include "../include/c04/ddr_c04_2G_4x512.h"

static void ccgr_init(void)
{
	struct mxc_ccm_reg *ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

	writel(0xFFFFFFFF, &ccm->CCGR0);
	writel(0xFFFFFFFF, &ccm->CCGR1);
	writel(0xFFFFFFFF, &ccm->CCGR2);
	writel(0xFFFFFFFF, &ccm->CCGR3);
	writel(0xFFFFFFFF, &ccm->CCGR4);
	writel(0xFFFFFFFF, &ccm->CCGR5);
	writel(0xFFFFFFFF, &ccm->CCGR6);
	writel(0xFFFFFFFF, &ccm->CCGR7);

	/* spread spectrum abilitato */
	writel(0x00108001, &ccm->analog_pll_528_ss);
}

#ifdef CONFIG_MX6Q
static void mx6dq_spl_dram_init(void)
{
	struct mx6_ddr3_cfg mem_ddr;
	struct mx6dq_iomux_ddr_regs mx6_ddr_ioregs;
	struct mx6dq_iomux_grp_regs mx6_grp_ioregs;
	struct mx6_mmdc_calibration  mx6_mmcd_calib;

	switch (detect_board()) {
	   case MX6_C04QP_2GB_4x512:
		mem_ddr = mem_ddr_2G_4x512;
		mx6_ddr_ioregs = mx6_ddr_2G_4x512_ioregs;
		mx6_grp_ioregs = mx6_grp_2G_4x512_ioregs;
		mx6_mmcd_calib = mx6_c04qp_mmcd_2G_4x512_calib;
		break;

	   case MX6_C04Q_2GB_4x512:
		mem_ddr = mem_ddr_2G_4x512;
		mx6_ddr_ioregs = mx6_ddr_2G_4x512_ioregs;
		mx6_grp_ioregs = mx6_grp_2G_4x512_ioregs;
		mx6_mmcd_calib = mx6_c04q_mmcd_2G_4x512_calib;
		break;

	   default:
		mem_ddr = mem_ddr_2G_4x512;
		mx6_ddr_ioregs = mx6_ddr_2G_4x512_ioregs;
		mx6_grp_ioregs = mx6_grp_2G_4x512_ioregs;
		mx6_mmcd_calib = mx6_c04q_mmcd_2G_4x512_calib;
		break;
	}

	struct mx6_ddr_sysinfo sysinfo = {
		.dsize = mem_ddr.width/32,
		.cs_density = 24,
		.ncs = 1,
		.cs1_mirror = 0,
		.rtt_wr = 2,
		.rtt_nom = 2,		/* RTT_Nom = RZQ/2 */
		.walat = 1,		/* Write additional latency */
		.ralat = 5,		/* Read additional latency */
		.mif3_mode = 3,		/* Command prediction working mode */
		.bi_on = 1,		/* Bank interleaving enabled */
		.sde_to_rst = 0x10,	/* 14 cycles, 200us (JEDEC default) */
		.rst_to_cke = 0x23,	/* 33 cycles, 500us (JEDEC default) */
	};
	mx6dq_dram_iocfg(mem_ddr.width, &mx6_ddr_ioregs, &mx6_grp_ioregs);
	mx6_dram_cfg(&sysinfo, &mx6_mmcd_calib, &mem_ddr);
	if (detect_board() == MX6_C04QP_2GB_4x512) {
		((struct mmdc_p_regs *)MX6_MMDC_P0_MDCTL)->mpzqhwctrl = 0xA1390003; // From calibration reg 0x021b0800
		((struct mmdc_p_regs *)MX6_MMDC_P0_MDCTL)->maarcr     = 0x14420000; // From Seco 928 board reg 0x021b0400
		((struct mmdc_p_regs *)MX6_MMDC_P0_MDCTL)->mppdcmpr2  = 0x00400C58; // From Seco 928 board reg 0x021b0890
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg3  = 0x00000000; // From Seco 928 board reg 0x00bb0008
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg4  = 0x2891E41A; // From Seco 928 board reg 0x00bb000C
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg15 = 0x00000564; // From Seco 928 board reg 0x00bb0038
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg6  = 0x00000040; // From Seco 928 board reg 0x00bb0014
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg11 = 0x00000020; // From Seco 928 board reg 0x00bb0028
		((struct noc_ddr_conf_regs *)MX6QP_NOC_CONF_BASE)->reg12 = 0x00000020; // From Seco 928 board reg 0x00bb002C
	}
}
#endif

#ifdef CONFIG_MX6DL
static void mx6sdl_spl_dram_init(void)
{
	struct mx6_ddr3_cfg mem_ddr;
	struct mx6sdl_iomux_ddr_regs mx6_ddr_ioregs;
	struct mx6sdl_iomux_grp_regs mx6_grp_ioregs;
	struct mx6_mmdc_calibration  mx6_mmcd_calib;

	switch (detect_board()) {

	   case MX6_C04DL_2GB_4x512:
		mem_ddr = mem_ddr_2G_4x512;
		mx6_ddr_ioregs = mx6_ddr_2G_4x512_ioregs;
		mx6_grp_ioregs = mx6_grp_2G_4x512_ioregs;
		mx6_mmcd_calib = mx6_c04dl_mmcd_2G_4x512_calib;
		break;

	   case MX6_A75DL_1GB_2x512:
		mem_ddr = mem_ddr_1G_2x512;
		mx6_ddr_ioregs = mx6_ddr_1G_2x512_ioregs;
		mx6_grp_ioregs = mx6_grp_1G_2x512_ioregs;
		mx6_mmcd_calib = mx6_a75dl_mmcd_1G_2x512_calib;
		break;

	   case MX6_A75DL_512MB_2x256:
		mem_ddr = mem_ddr_512M_2x256;
		mx6_ddr_ioregs = mx6_ddr_512M_2x256_ioregs;
		mx6_grp_ioregs = mx6_grp_512M_2x256_ioregs;
		mx6_mmcd_calib = mx6_a75dl_mmcd_512M_2x256_calib;
		break;

	   case MX6_A75DL_256MB_1x256:
		mem_ddr = mem_ddr_256M_1x256;
		mx6_ddr_ioregs = mx6_ddr_256M_1x256_ioregs;
		mx6_grp_ioregs = mx6_grp_256M_1x256_ioregs;
		mx6_mmcd_calib = mx6_a75dl_mmcd_256M_1x256_calib;
		break;

	   case MX6_A75SOLO_256MB_1x256:
		mem_ddr = mem_ddr_256M_1x256;
		mx6_ddr_ioregs = mx6_ddr_256M_1x256_ioregs;
		mx6_grp_ioregs = mx6_grp_256M_1x256_ioregs;
		mx6_mmcd_calib = mx6_a75solo_mmcd_256M_1x256_calib;
		break;

	   case MX6_962DL_512MB_2x256:
		mem_ddr = mem_ddr_512M_2x256;
		mx6_ddr_ioregs = mx6_ddr_512M_2x256_ioregs;
		mx6_grp_ioregs = mx6_grp_512M_2x256_ioregs;
		mx6_mmcd_calib = mx6_962dl_mmcd_512M_2x256_calib;
		break;

	   case MX6_962DL_1GB_4x256:
		mem_ddr = mem_ddr_1G_4x256;
		mx6_ddr_ioregs = mx6_ddr_1G_4x256_ioregs;
		mx6_grp_ioregs = mx6_grp_1G_4x256_ioregs;
		mx6_mmcd_calib = mx6_962dl_mmcd_1G_4x256_calib;
		break;

	   default:
		mem_ddr = mem_ddr_1G_2x512;
		mx6_ddr_ioregs = mx6_ddr_1G_2x512_ioregs;
		mx6_grp_ioregs = mx6_grp_1G_2x512_ioregs;
		mx6_mmcd_calib = mx6_a75dl_mmcd_1G_2x512_calib;
		break;
	}

	struct mx6_ddr_sysinfo sysinfo = {
		.dsize = mem_ddr.width/32,
		.cs_density = 24,
		.ncs = 1,
		.cs1_mirror = 0,
		.rtt_wr = 2,
		.rtt_nom = 2,		/* RTT_Nom = RZQ/2 */
		.walat = 1,		/* Write additional latency */
		.ralat = 5,		/* Read additional latency */
		.mif3_mode = 3,		/* Command prediction working mode */
		.bi_on = 1,		/* Bank interleaving enabled */
		.sde_to_rst = 0x10,	/* 14 cycles, 200us (JEDEC default) */
		.rst_to_cke = 0x23,	/* 33 cycles, 500us (JEDEC default) */
	};
	mx6sdl_dram_iocfg(mem_ddr.width, &mx6_ddr_ioregs, &mx6_grp_ioregs);
	mx6_dram_cfg(&sysinfo, &mx6_mmcd_calib, &mem_ddr);
}
#endif

void board_boot_order(u32 *spl_boot_list)
{
	spl_boot_list[0] = spl_boot_device();
	spl_boot_list[1] = BOOT_DEVICE_MMC2;
	spl_boot_list[2] = BOOT_DEVICE_BOARD;
}

void board_init_f(ulong dummy)
{
	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	ccgr_init();

	/* iomux and setup of i2c */
	board_early_init_f();

	/* setup GP timer */
	timer_init();

	/* UART clocks enabled and gd valid - init serial console */
	preloader_console_init();

	/* DDR initialization */
#ifdef CONFIG_MX6Q
	mx6dq_spl_dram_init();
#endif
#ifdef CONFIG_MX6DL
	mx6sdl_spl_dram_init();
#endif

	/* Clear the BSS. */
	memset(__bss_start, 0, __bss_end - __bss_start);

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}

void reset_cpu(ulong addr)
{
}

