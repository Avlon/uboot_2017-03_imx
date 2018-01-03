/*
 * Copyright (C) UDOO Team
 *
 * Author: Francesco Montefoschi <francesco.monte@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#include <asm/arch/mx6-pins.h>
#include <i2c.h>
#include <asm/gpio.h>
#include <asm/imx-common/iomux-v3.h>
#include "detectboard.h"

/**
 * Detects board revision.
 * Rev_B = 0x0
 * Rev_C = 0x1
 * Rev_D = 0x2
 * Rev_E = 0x3
 * Rev_F = 0x4
 * Rev_G = 0x5
 * Rev_H = 0x6
 * Rev_I = 0x7
 */
int detect_revision(void)
{
    return 0;
}

/**
 * Detects the board model.
 */

int detect_board(void)
{
    return MX6_C04DL_2GB_4x512;
}

int detect_board_short(void)
{
    return MX6_SECO_A75;
}

/**
 * Autodetect video output searching for connected I2C touchsreen address
 * 0x14 = RGB 7''
 * 0x55 = LVDS 7''
 */
int detect_video(char *video)
{
	if (strcmp(video, "auto") == 0)
		return HDMI_1920x1080;
	else if (strcmp(video, "hdmi") == 0)
		return HDMI_1920x1080;
	else if (strcmp(video, "lvds-hdmi") == 0)
		return LVDS_HDMI;
	else if (strcmp(video, "lvdsCTM") == 0)
		return LVDS_1280x800;
	else if (strcmp(video, "lvds800x480") == 0)
		return LVDS_800x480;
	else if (strcmp(video, "lvds800x600") == 0)
		return LVDS_800x600;
	else if (strcmp(video, "lvds1024x768") == 0)
		return LVDS_1024x768;
	else if (strcmp(video, "lvds1368x768") == 0)
		return LVDS_1368x768;
	else if (strcmp(video, "lvds1280x800") == 0)
		return LVDS_1280x800;
	else if (strcmp(video, "lvds1280x1024") == 0)
		return LVDS_1280x1024;
	else if (strcmp(video, "lvds1680x1050") == 0)
		return LVDS_1680x1050;
	else if (strcmp(video, "lvds1920x1080") == 0)
		return LVDS_1920x1080;
	else
		return HDMI_1920x1080;
	
/*
        I2C_SET_BUS(TOUCH_I2C_BUS);
        int j = 0, ret = 0;

        for (j = 128; j > 0; j--) {
           ret = i2c_probe(j);
           if (ret == 0) {
                switch(j) {
                   case 0x14:
                        printf("Auto-select RGB 7'' video output.\n");
                        return 0x14;
                   case 0x55:
                        printf("Auto-select LVDS 7'' video output.\n");
                        return 0x55;
                }
           }
        }
        return 0;
*/
}

