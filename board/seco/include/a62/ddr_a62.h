/*
 * Copyright (C) Seco s.r.l.
 *
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.it>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-ddr.h>


/* configure MX6Q/DUAL mmdc DDR io registers */
const struct mx6dq_iomux_ddr_regs mx6_quad_ddr_ioregs = {
        .dram_sdclk_0 =  0x00000028,
        .dram_sdclk_1 =  0x00000028,
        .dram_cas =  0x00000028,
        .dram_ras =  0x00000028,
        .dram_reset =  0x00000028,
        .dram_sdcke0 =  0x00003000,
        .dram_sdcke1 =  0x00003000,
        .dram_sdba2 =  0x00000000,
        .dram_sdodt0 =  0x00000028,
        .dram_sdodt1 =  0x00000028,
        .dram_sdqs0 =  0x00000028,
        .dram_sdqs1 =  0x00000028,
        .dram_sdqs2 =  0x00000028,
        .dram_sdqs3 =  0x00000028,
        .dram_sdqs4 =  0x00000028,
        .dram_sdqs5 =  0x00000028,
        .dram_sdqs6 =  0x00000028,
        .dram_sdqs7 =  0x00000028,
        .dram_dqm0 =  0x00000028,
        .dram_dqm1 =  0x00000028,
        .dram_dqm2 =  0x00000028,
        .dram_dqm3 =  0x00000028,
        .dram_dqm4 =  0x00000028,
        .dram_dqm5 =  0x00000028,
        .dram_dqm6 =  0x00000028,
        .dram_dqm7 =  0x00000028,
};

/* configure MX6Q/DUAL mmdc GRP io registers */
const struct mx6dq_iomux_grp_regs mx6_quad_grp_ioregs = {
        .grp_ddr_type =  0x000C0000,
        .grp_ddrmode_ctl =  0x00020000,
        .grp_ddrpke =  0x00000000,
        .grp_addds =  0x00000028,
        .grp_ctlds =  0x00000030,
        .grp_ddrmode =  0x00020000,
        .grp_b0ds =  0x00000028,
        .grp_b1ds =  0x00000028,
        .grp_b2ds =  0x00000028,
        .grp_b3ds =  0x00000028,
        .grp_b4ds =  0x00000028,
        .grp_b5ds =  0x00000028,
        .grp_b6ds =  0x00000028,
        .grp_b7ds =  0x00000028,
};

/* configure MX6SOLO/DUALLITE mmdc DDR io registers */
struct mx6sdl_iomux_ddr_regs mx6sdl_ddr_ioregs = {
	.dram_sdclk_0 = 0x00000028,
	.dram_sdclk_1 = 0x00000028,
	.dram_cas = 0x00000028,
	.dram_ras = 0x00000028,
	.dram_reset = 0x00000028,
	.dram_sdcke0 = 0x00000028,
	.dram_sdcke1 = 0x00000028,
	.dram_sdba2 = 0x00000000,
	.dram_sdodt0 = 0x00000028,
	.dram_sdodt1 = 0x00000028,
	.dram_sdqs0 = 0x00000028,
	.dram_sdqs1 = 0x00000028,
	.dram_sdqs2 = 0x00000028,
	.dram_sdqs3 = 0x00000028,
	.dram_sdqs4 = 0x00000028,
	.dram_sdqs5 = 0x00000028,
	.dram_sdqs6 = 0x00000028,
	.dram_sdqs7 = 0x00000028,
	.dram_dqm0 = 0x00000028,
	.dram_dqm1 = 0x00000028,
	.dram_dqm2 = 0x00000028,
	.dram_dqm3 = 0x00000028,
	.dram_dqm4 = 0x00000028,
	.dram_dqm5 = 0x00000028,
	.dram_dqm6 = 0x00000028,
	.dram_dqm7 = 0x00000028,
};

/* configure MX6SOLO/DUALLITE mmdc GRP io registers */
struct mx6sdl_iomux_grp_regs mx6sdl_grp_ioregs = {
	.grp_ddr_type = 0x000c0000,
	.grp_ddrmode_ctl = 0x00020000,
	.grp_ddrpke = 0x00000000,
	.grp_addds = 0x00000028,
	.grp_ctlds = 0x00000028,
	.grp_ddrmode = 0x00020000,
	.grp_b0ds = 0x00000028,
	.grp_b1ds = 0x00000028,
	.grp_b2ds = 0x00000028,
	.grp_b3ds = 0x00000028,
	.grp_b4ds = 0x00000028,
	.grp_b5ds = 0x00000028,
	.grp_b6ds = 0x00000028,
	.grp_b7ds = 0x00000028,
};


const struct mx6_mmdc_calibration mx6qp_mmcd_4x256_calib = {
        .p0_mpwldectrl0 =  0x00710076,
        .p0_mpwldectrl1 =  0x00630059,
        .p1_mpwldectrl0 =  0x0030004E,
        .p1_mpwldectrl1 =  0x000D001A,

        .p0_mpdgctrl0 =  0x44280438,
        .p0_mpdgctrl1 =  0x04080400,
        .p1_mpdgctrl0 =  0x437C037C,
        .p1_mpdgctrl1 =  0x035C0338,

        .p0_mprddlctl =  0x423A3C3E,
        .p1_mprddlctl =  0x3C3C3646,
        .p0_mpwrdlctl =  0x383E403E,
        .p1_mpwrdlctl =  0x48364840,
};

const struct mx6_mmdc_calibration mx6qd_mmcd_4x256_calib = {
        .p0_mpwldectrl0 =  0x00710076,
        .p0_mpwldectrl1 =  0x00630059,
        .p1_mpwldectrl0 =  0x0030004E,
        .p1_mpwldectrl1 =  0x000D001A,

        .p0_mpdgctrl0 =  0x44280438,
        .p0_mpdgctrl1 =  0x04080400,
        .p1_mpdgctrl0 =  0x437C037C,
        .p1_mpdgctrl1 =  0x035C0338,

        .p0_mprddlctl =  0x423A3C3E,
        .p1_mprddlctl =  0x3C3C3646,
        .p0_mpwrdlctl =  0x383E403E,
        .p1_mpwrdlctl =  0x48364840,
};

const struct mx6_mmdc_calibration mx6qp_mmcd_4x512_calib = {
        .p0_mpwldectrl0 =  0x00690070,
        .p0_mpwldectrl1 =  0x00640059,
        .p1_mpwldectrl0 =  0x00260039,
        .p1_mpwldectrl1 =  0x000B001A,

        .p0_mpdgctrl0 =  0x4378037C,
        .p0_mpdgctrl1 =  0x03600360,
        .p1_mpdgctrl0 =  0x43500358,
        .p1_mpdgctrl1 =  0x03200300,

        .p0_mprddlctl =  0x4032383C,
        .p1_mprddlctl =  0x46304642,
        .p0_mpwrdlctl =  0x3A3A4238,
        .p1_mpwrdlctl =  0x46304642,
};

const struct mx6_mmdc_calibration mx6qd_mmcd_4x512_calib = {
        .p0_mpwldectrl0 =  0x001F001F,
        .p0_mpwldectrl1 =  0x001F001F,
        .p1_mpwldectrl0 =  0x001F0001,
        .p1_mpwldectrl1 =  0x001F001F,

        .p0_mpdgctrl0 =  0x431A0326,
        .p0_mpdgctrl1 =  0x0323031B,
        .p1_mpdgctrl0 =  0x433F0340,
        .p1_mpdgctrl1 =  0x0345031C,

        .p0_mprddlctl =  0x40343137,
        .p1_mprddlctl =  0x40372F45,
        .p0_mpwrdlctl =  0x32414741,
        .p1_mpwrdlctl =  0x4731473C,
};

static struct mx6_mmdc_calibration mx6dl_1g_mmdc_calib = {
	.p0_mpwldectrl0 = 0x002F0038,
	.p0_mpwldectrl1 = 0x001F001F,
	.p1_mpwldectrl0 = 0x001F001F,
	.p1_mpwldectrl1 = 0x001F001F,
	.p0_mpdgctrl0 = 0x425C0251,
	.p0_mpdgctrl1 = 0x021B021E,
	.p1_mpdgctrl0 = 0x021B021E,
	.p1_mpdgctrl1 = 0x01730200,
	.p0_mprddlctl = 0x45474C45,
	.p1_mprddlctl = 0x44464744,
	.p0_mpwrdlctl = 0x3F3F3336,
	.p1_mpwrdlctl = 0x32383630,
};

/* Micron MT41J256M16RE-15E */
static struct mx6_ddr3_cfg mt41j256m16re_15e = {
	.mem_speed = 1333,
	.density = 4,
	.width = 16,
	.banks = 8,
	.rowaddr = 15,
	.coladdr = 10,
	.pagesz = 2,
	.trcd = 1350,
	.trcmin = 4950,
	.trasmin = 3600,
};

/* Micron MT41J512M16RE-15E */ /* not confirmed yet*/
static struct mx6_ddr3_cfg mt41j512m16re_15e = {
	.mem_speed = 1333,
	.density = 4,
	.width = 16,
	.banks = 8,
	.rowaddr = 16,
	.coladdr = 10,
	.pagesz = 1,
	.trcd = 1350,
	.trcmin = 4950,
	.trasmin = 3600,
};

/* Micron MT41K128M16JT-125 */
static struct mx6_ddr3_cfg mt41k128m16jt_125 = {
	/* duallite */
	.mem_speed = 800,
	.density = 2,
	.width = 16,
	.banks = 8,
	.rowaddr = 14,
	.coladdr = 10,
	.pagesz = 2,
	.trcd = 1375,
	.trcmin = 4875,
	.trasmin = 3500,
	.SRT = 0,
};

