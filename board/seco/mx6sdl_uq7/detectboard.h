/*
 * Copyright (C) UDOO Team
 *
 * Author: Francesco Montefoschi <francesco.monte@gmail.com>
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */

#define MX6_A75SOLO_256MB_1x256	0x0000
#define MX6_A75DL_256MB_1x256	0x0001
#define MX6_A75DL_512MB_2x256	0x0002
#define MX6_A75DL_1GB_2x512	0x0003
#define MX6_962DL_512MB_2x256	0x0004
#define MX6_962DL_1GB_4x256	0x0005
#define MX6_962DL_2GB_4x512	0x0006

#define MX6_SECO_A75		0x0000
#define MX6_SECO_962		0x0001

typedef struct lvds_video_spec {
	int  idx;
	char *label;
	char *name;
	char *if_map;
	char *opt;
	int  num_channel;
	int  density;
	char *fdt_video_part;
} lvds_video_spec_t;

enum {
	HDMI_1920x1080 = 0,
	LVDS_800x480,
	LVDS_800x600,
	LVDS_1024x768,
	LVDS_1368x768,
	LVDS_1280x800,
	LVDS_1280x1024,
	LVDS_1680x1050,
	LVDS_1920x1080,
	LVDS_HDMI
};

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

int detect_board(void);
int detect_board_short(void);
int detect_video(char *video);
int detect_revision(void);
