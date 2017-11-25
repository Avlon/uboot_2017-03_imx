/*
 * Copyright (C) Seco s.r.l.
 *
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.it>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-ddr.h>

const struct mx6_mmdc_calibration mx6_a75dl_mmcd_512M_2x256_calib = {
	.p0_mpwldectrl0  = 0x002B0032,
	.p0_mpwldectrl1  = 0x00240026,
	.p0_mpdgctrl0 	 = 0x423c0238,
	.p0_mpdgctrl1 	 = 0x0234023c,
	.p0_mprddlctl 	 = 0x42444a48,
	.p0_mpwrdlctl 	 = 0x38362e36,
};
