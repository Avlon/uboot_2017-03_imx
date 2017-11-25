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

int detect_board(void);
int detect_board_short(void);
int detect_video(void);
int detect_revision(void);
