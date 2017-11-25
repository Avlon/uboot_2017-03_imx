/*
 * Copyright (C) Seco s.r.l.
 *
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.it>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-ddr.h>

const struct mx6_mmdc_calibration mx6_a75dl_mmcd_256M_1x256_calib = {
	.p0_mpwldectrl0  = 0x002F0037,
	.p0_mpwldectrl1  = 0x001F001F,
	.p0_mpdgctrl0 	 = 0x42400238,
	.p0_mpdgctrl1 	 = 0x00000000,
	.p0_mprddlctl 	 = 0x40404642,
	.p0_mpwrdlctl 	 = 0x40403232,
};


