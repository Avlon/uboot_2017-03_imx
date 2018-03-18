/*
 * Copyright (C) Seco s.r.l.
 *
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.it>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-ddr.h>

const struct mx6_mmdc_calibration mx6_c04dl_mmcd_2G_4x512_calib = {
	.mpzqlp2ctl	 = 0xa1390003,
	.p0_mpwldectrl0  = 0x001F001F,
	.p0_mpwldectrl1  = 0x001F001F,
	.p0_mpdgctrl0 	 = 0x425C025C,
	.p0_mpdgctrl1 	 = 0x02340238,
	.p0_mprddlctl 	 = 0x44444848,
	.p0_mpwrdlctl 	 = 0x383A3032,
	.p1_mpdgctrl0 	 = 0x42380238,
	.p1_mpdgctrl1 	 = 0x0214021C,
	.p1_mprddlctl 	 = 0x46464640,
	.p1_mpwrdlctl 	 = 0x3836362C,
};

const struct mx6_mmdc_calibration mx6_c04q_mmcd_2G_4x512_calib = {
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

const struct mx6_mmdc_calibration mx6_c04qp_mmcd_2G_4x512_calib = {
//        .p0_mpwldectrl0 =  0x005D0063,
//        .p0_mpwldectrl1 =  0x005F004E,
//        .p1_mpwldectrl0 =  0x0021003E,
//        .p1_mpwldectrl1 =  0x000E0014,
        .p0_mpwldectrl0 =  0x001F001F,
        .p0_mpwldectrl1 =  0x001F001F,
        .p1_mpwldectrl0 =  0x001F0001,
        .p1_mpwldectrl1 =  0x001F001F,

        .p0_mpdgctrl0 =  0x436C037C,
        .p0_mpdgctrl1 =  0x034C0348,
        .p1_mpdgctrl0 =  0x433C0344,
        .p1_mpdgctrl1 =  0x031C026C,

        .p0_mprddlctl =  0x44323440,
        .p1_mprddlctl =  0x3C362E40,
        .p0_mpwrdlctl =  0x3C3A423E,
        .p1_mpwrdlctl =  0x46304A42,
};
