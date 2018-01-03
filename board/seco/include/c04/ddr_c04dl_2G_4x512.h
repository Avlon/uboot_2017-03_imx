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
