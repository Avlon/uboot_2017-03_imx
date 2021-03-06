/*
 * (C) Copyright 2015 Seco
 *
 * Author: Davide Cardillo <davide.cardillo@seco.com>
 * Author: Giuseppe Pagano <giuseppe.pagano@seco.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */

#include <common.h>

#include <config.h>
#include <command.h>
#include <asm/arch/sys_proto.h>
#include <malloc.h>

#include "detectboard.h"

static lvds_video_spec_t lvds_video_spec_list [] = {
	{ HDMI_1920x1080, "HDMI    [1920x1080",  "HDMI",        "RGB24",        "",         1, 160, "-hdmi" },
	{ LVDS_800x480,   "WVGA    [800x480]",   "LDB-WVGA",    "RGB666",       "",         1, 128, "-lvds" },
	{ LVDS_800x600,   "SVGA    [800x600]",   "LDB-SVGA",    "RGB666",       "",         1, 128, "-lvds" },
	{ LVDS_1024x768,  "XGA     [1024x768]",  "LDB-XGA",     "RGB666",       "",         1, 128, "-lvds" },
	{ LVDS_1368x768,  "WXGA    [1368x768]",  "LDB-WXGA",    "RGB24",        "",         1, 160, "-lvds" },
	{ LVDS_1280x800,  "WXGAP60 [1280x800]",  "LDB-1280P60", "RGB24,bpp=32", "",         1, 160, "-lvds" },
	{ LVDS_1280x1024, "SXGA    [1280x1024]", "LDB-SXGA",    "RGB24",        "",         1, 160, "-lvds" },
	{ LVDS_1680x1050, "1050P60 [1680x1050]", "LDB-1050P60", "RGB24",        "",         1, 160, "-lvds" },
	{ LVDS_1920x1080, "HD1080  [1920x1080]", "LDB-1080P60", "RGB24",        "ldb=spl0", 2, 160, "-lvds" },
	{ LVDS_HDMI,  	  "LVDS WVGA + HDMI",    "LDB-WVGA",    "RGB666",       "",         1, 128, "-lvds-hdmi" },
};

int isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\12');
}

char *trim(char *str)
{
	char *end;

	// Trim leading space
	while(isspace(*str)) str++;

	if (*str == 0)  // All spaces?
	   return str;

	// Trim trailing space
	end = str + strlen(str) - 1;
	while (end > str && isspace(*end)) end--;

	// Write new null terminator
	*(end+1) = 0;

	return str;
}

/**
 * After loading uEnv.txt, we autodetect which fdt file we need to load.
 * uEnv.txt can contain:
 *  - video_output=hdmi|lvds7|lvds15
 *    any other value (or if the variable is not specified) will default to "hdmi"
 *  - use_custom_dtb=true|false
 *    any other value (or if the variable is not specified) will default to "false"
 * 
 * Despite the signature, this command does not accept any argument.
 */
int do_secoinit(cmd_tbl_t *cmdtp, int flag, int argc, char * const argv[])
{
	char* modelfdt;
	int video_idx = 0;

	char fdt_file[100];

	char* video_part = "";
	char* dir_part   = "dts";

	char* customdtb = getenv("use_custom_dtb");
	char* video = getenv("video_output");
	char* video_args = malloc(sizeof(char) * 128);

	if (is_mx6dqp()) {
		modelfdt = "imx6qp";
	} else {
		modelfdt = "imx6q";
	}
	
	char* board_part = "";

	switch (detect_board_short()) {
		case MX6_SECO_C04:
			board_part = "seco_C04";
			break;
		case MX6_SECO_A62:
			board_part = "seco_SBC_A62";
			break;
		case MX6_SECO_A75:
			board_part = "j_A75";
			break;
		case MX6_SECO_962:
			board_part = "962";
			break;
		default:
			break;
	}

	if (video) {
		video_idx = detect_video(trim(video));

		if (video_idx == 0)
		   sprintf (video_args, "video=mxcfb0:dev=hdmi,1920x1080M@60,if=RGB24 dmfc=3 androidboot.lcd_density=160");
		else
		   sprintf (video_args, " video=mxcfb0:dev=ldb,%s,if=%s %s androidboot.lcd_density=%d",
			lvds_video_spec_list[video_idx].name,
			lvds_video_spec_list[video_idx].if_map,
			lvds_video_spec_list[video_idx].opt,
			lvds_video_spec_list[video_idx].density);

		setenv("lvds_video_args", video_args);
//		video_part = lvds_video_spec_list[video_idx].fdt_video_part;
	}
	
	if (customdtb) {
		customdtb = trim(customdtb);
		if (strcmp(customdtb, "true") == 0 || strcmp(customdtb, "yes") == 0 || strcmp(customdtb, "enabled") == 0) {
			dir_part = "dts-overlay";
		}
	}
	
	sprintf(fdt_file, "%s/%s-%s%s.dtb", dir_part, modelfdt, board_part, video_part);
//	sprintf(fdt_file, "%s/imx6qp-seco_a62.dtb", dir_part);
	
	printf("Device Tree: %s\n", fdt_file);
	setenv("fdt_file", fdt_file);
	
	return 0;
}

U_BOOT_CMD(
	secoinit,	1,	1,	do_secoinit,
	"(Seco utils) determine the device tree file to be loaded", ""
);

