/*
 * Copyright (C) Seco s.r.l.
 *
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.it>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-ddr.h>

const struct mx6_mmdc_calibration mx6_962dl_mmcd_1G_4x256_calib = {
	.p0_mpwldectrl0  = 0x001F001F,
	.p0_mpwldectrl1  = 0x001F001F,
	.p1_mpwldectrl0  = 0x001F001F,
	.p1_mpwldectrl1  = 0x001F001F,
	.p0_mpdgctrl0 	 = 0x42180217,
	.p0_mpdgctrl1 	 = 0x02050209,
	.p1_mpdgctrl0 	 = 0x42260229,
	.p1_mpdgctrl1 	 = 0x020E0224,
	.p0_mprddlctl 	 = 0x494B4C4D,
	.p0_mpwrdlctl 	 = 0x40413133,
	.p1_mprddlctl 	 = 0x4D4F5047,
	.p1_mpwrdlctl 	 = 0x31353531,
};
