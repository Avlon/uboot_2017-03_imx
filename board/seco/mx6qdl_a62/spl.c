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
#include <asm/arch/iomux.h>
#include "detectboard.h"

#include <spl.h>
#include <asm/arch/mx6-ddr.h>

#ifdef CONFIG_APX_WATCHDOG
#include <watchdog.h>
#endif

#include "../include/ddr/ddr_1G_2x512.h"
#include "../include/ddr/ddr_1G_4x256.h"
#include "../include/ddr/ddr_2G_4x512.h"
#include "../include/ddr/ddr_512M_2x256.h"
#include "../include/ddr/ddr_256M_1x256.h"

#include "../include/a75/ddr_a75dl_1G_2x512.h"
#include "../include/a75/ddr_a75dl_512M_2x256.h"
#include "../include/a75/ddr_a75dl_256M_1x256.h"
#include "../include/a75/ddr_a75solo_256M_1x256.h"

#include "../include/962/ddr_962dl_1G_4x256.h"
#include "../include/962/ddr_962dl_512M_2x256.h"

#include "../include/a62/ddr_a62.h"

static void ccgr_init(void)
{
	struct mxc_ccm_reg *ccm = (struct mxc_ccm_reg *)CCM_BASE_ADDR;

	writel(0x00C03F3F, &ccm->CCGR0);
	writel(0x0030FC03, &ccm->CCGR1);
	writel(0x0FFFC000, &ccm->CCGR2);
	writel(0x3FF00000, &ccm->CCGR3);
	writel(0x00FFF300, &ccm->CCGR4);
	writel(0x0F0000F3, &ccm->CCGR5);
	writel(0x000003FF, &ccm->CCGR6);
	/* Enable USB HUB Clock on A62 Board */
	writel(0x010E0000, &ccm->ccosr);
}

static void gpr_init(void)
{
	struct iomuxc *iomux = (struct iomuxc *)IOMUXC_BASE_ADDR;

	/* enable AXI cache for VDOA/VPU/IPU */
	writel(0xF00000FF, &iomux->gpr[4]);
	/* set IPU AXI-id0 Qos=0xf(bypass) AXI-id1 Qos=0x7 */
	if (is_mx6dqp()) {
		writel(0xFFFFFFFF, &iomux->gpr[6]);
		writel(0xFFFFFFFF, &iomux->gpr[7]);
	} else {
		writel(0x007F007F, &iomux->gpr[6]);
		writel(0x007F007F, &iomux->gpr[7]);
	}
}

#ifdef CONFIG_MX6Q
static void mx6dq_spl_dram_init(void)
{
	struct mx6_ddr3_cfg mem_ddr;
	struct mx6dq_iomux_ddr_regs mx6_ddr_ioregs;
	struct mx6dq_iomux_grp_regs mx6_grp_ioregs;
	struct mx6_mmdc_calibration  mx6_mmcd_calib;
	u32 mdctl;

        struct mx6_ddr_sysinfo sysinfo = {
                .dsize = 2,             /* total bus width/32, i.e 4x16/32 */
                .cs_density = 32,
                .ncs = 1,
                .cs1_mirror = 0,
                .rtt_wr = 1,
                .rtt_nom = 2,           /* RTT_Nom = RZQ/2 */
                .walat = 1,             /* Write additional latency */
                .ralat = 5,             /* Read additional latency */
                .mif3_mode = 3,         /* Command prediction working mode */
                .bi_on = 1,             /* Bank interleaving enabled */
                .sde_to_rst = 0x10,     /* 14 cycles, 200us (JEDEC default) */
                .rst_to_cke = 0x23,     /* 33 cycles, 500us (JEDEC default) */
        };

	switch (detect_board()) {
	   case MX6_A62Q_2GB_4x512:
		mem_ddr = mt41j512m16re_15e;
		mx6_ddr_ioregs = mx6_quad_ddr_ioregs;
		mx6_grp_ioregs = mx6_quad_grp_ioregs;
		mx6_mmcd_calib = mx6qd_mmcd_4x512_calib;
		mdctl = 0x841A0000;
		puts("Setting 2048MB RAM calibration data\n");
		break;

	   case MX6_A62QP_1GB_4x256:
		mem_ddr = mt41j256m16re_15e;
		mx6_ddr_ioregs = mx6_quad_ddr_ioregs;
		mx6_grp_ioregs = mx6_quad_grp_ioregs;
		mx6_mmcd_calib = mx6qp_mmcd_4x256_calib;
		mdctl = 0x831A0000;
		puts("Setting 1024MB RAM calibration data\n");
		break;

	   case MX6_A62Q_1GB_4x256:
		mem_ddr = mt41j256m16re_15e;
		mx6_ddr_ioregs = mx6_quad_ddr_ioregs;
		mx6_grp_ioregs = mx6_quad_grp_ioregs;
		mx6_mmcd_calib = mx6qd_mmcd_4x256_calib;
		mdctl = 0x831A0000;
		puts("Setting 1024MB RAM calibration data\n");
		break;

	   default:
		mem_ddr = mt41j256m16re_15e;
		mx6_ddr_ioregs = mx6_ddr_ioregs;
		mx6_grp_ioregs = mx6_grp_ioregs;
		mx6_mmcd_calib = mx6qd_mmcd_4x256_calib;
		mdctl = 0x831A0000;
		puts("Setting 1024MB RAM calibration data\n");
		break;
	}

	if (is_mx6dq() || is_mx6dqp()) {
		mx6dq_dram_iocfg(64, &mx6_ddr_ioregs, &mx6_grp_ioregs);
		mx6_dram_cfg(&sysinfo, &mx6qd_mmcd_4x256_calib, &mt41j256m16re_15e);
		((struct mmdc_p_regs *)MX6_MMDC_P0_MDCTL)->mdctl = 0x831A0000;
	} else { /*MXC_CPU_MX6SOLO*/
		/* TODO */
		puts("CPU ELSE\n");
	}	

	if (is_mx6dqp()) {
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

	switch (detect_board()) {

	   default:
		mem_ddr = mem_ddr_1G_2x512;
		mx6_ddr_ioregs = mx6_ddr_1G_2x512_ioregs;
		mx6_grp_ioregs = mx6_grp_1G_2x512_ioregs;
		mx6_mmcd_calib = mx6_a75dl_mmcd_1G_2x512_calib;
		break;
	}
	mx6sdl_dram_iocfg(mem_ddr.width, &mx6_ddr_ioregs, &mx6_grp_ioregs);
	mx6_dram_cfg(&sysinfo, &mx6_mmcd_calib, &mem_ddr);

}
#endif

#ifdef CONFIG_APX_WATCHDOG
static void init_func_watchdog_init(void)
{
	hw_watchdog_init();
	WATCHDOG_RESET();
}
#endif /* CONFIG_APX_WATCHDOG */


void board_init_f(ulong dummy)
{
	/* setup AIPS and disable watchdog */
	arch_cpu_init();

	ccgr_init();
	gpr_init();

	/* iomux and setup of i2c */
	board_early_init_f();

#ifdef CONFIG_APX_WATCHDOG
	init_func_watchdog_init();
#endif

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

#ifdef CONFIG_APX_WATCHDOG
	WATCHDOG_RESET();
#endif

	/* load/boot image from boot device */
	board_init_r(NULL, 0);
}

