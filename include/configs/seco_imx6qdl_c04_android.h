/*
 * Copyright (C) 2014-2016 Freescale Semiconductor, Inc.
 * Copyright 2017 NXP
 * Copyright 2017 Seco
 *
 * SPDX-License-Identifier:	GPL-2.0+
 */


#ifndef __MX6DL_SECOC04_ANDROID_H
#define __MX6DL_SECOC04_ANDROID_H
#include "mx_android_common.h"

#include <asm/arch/imx-regs.h>
#include <linux/sizes.h>
#include "mx6_common.h"
#include <asm/imx-common/gpio.h>

#define CONFIG_ROM_UNIFIED_SECTIONS

/* uncomment for PLUGIN mode support */
/* #define CONFIG_USE_PLUGIN */

#ifdef CONFIG_SPL
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_MMC_SUPPORT
#include "imx6_spl.h"
#endif

#define CONFIG_OF_LOAD_MANUALLY

#define CONFIG_SYS_UBOOT_BASE		CONFIG_SYS_TEXT_BASE

/*   SPL COMMON SUPPORT */ 
#define CONFIG_SPL_RAM_SUPPORT
#define CONFIG_SPL_RAM_DEVICE
#define CONFIG_SPL_USB_HOST_SUPPORT
#define CONFIG_SPL_USB_GADGET_SUPPORT
#define CONFIG_SPL_USB_SDP_SUPPORT
#define CONFIG_SPL_LOAD_FIT_ADDRESS (0x00907400 + 0x30000)
#define CONFIG_SPL_ENV_SUPPORT
#define CONFIG_SPL_LIBCOMMON_SUPPORT
#define CONFIG_SPL_LIBGENERIC_SUPPORT
#define CONFIG_SPL_SERIAL_SUPPORT
#define CONFIG_SPL_I2C_SUPPORT
#define CONFIG_SPL_GPIO_SUPPORT
#define CONFIG_SPL_SPI_SUPPORT
#define CONFIG_ENV_SPI_BUS		0
#define CONFIG_ENV_SPI_MODE             0
#define CONFIG_ENV_SPI_MAX_HZ           10000000
#define CONFIG_ENV_SECT_SIZE           (64 * 1024)
#define CONFIG_SYS_SPI_U_BOOT_OFFS		0x12000

#define CONFIG_CMDLINE_TAG
#define CONFIG_SETUP_MEMORY_TAGS
#define CONFIG_INITRD_TAG
#define CONFIG_REVISION_TAG
#define CONFIG_SYS_GENERIC_BOARD

/* Size of malloc() pool */
#define CONFIG_SYS_MALLOC_LEN		(16 * SZ_1M)

#define CONFIG_BOARD_EARLY_INIT_F
#define CONFIG_BOARD_LATE_INIT
#define CONFIG_MXC_GPIO

#define CONFIG_MXC_UART
#define CONFIG_MXC_UART_BASE		UART2_BASE

/***********   SECO   ***************/
#define SECO_NUM_BOOT_DEV                        3
#define CONFIG_DDR_MB 			      2048
#define CONFIG_SECO_COMMON_BOARD                 1
#define CONFIG_SECO_COMMON_USDHC                 1
#define CONFIG_SECO_COMMON_RGMII                 1
#define CONFIG_SECO_COMMON_RMII                  0
#define CONFIG_SECO_COMMON_PFUZE                 1
#define CONFIG_SECO_COMMON_DISPLAY               0
/***********   SECO   ***************/

/* MMC Configuration */
#define CONFIG_FSL_ESDHC
#define CONFIG_FSL_USDHC
#define CONFIG_SYS_FSL_ESDHC_ADDR	0
#define CONFIG_SYS_FSL_USDHC_NUM	2

#define CONFIG_BOUNCE_BUFFER
#define CONFIG_CMD_EXT2
#define CONFIG_CMD_FAT
#define CONFIG_DOS_PARTITION
#undef CONFIG_SUPPORT_EMMC_BOOT /* eMMC specific */

#define CONFIG_BAUDRATE			115200

#undef CONFIG_BOOTM_NETBSD
#undef CONFIG_BOOTM_PLAN9
#undef CONFIG_BOOTM_RTEMS

/* Needed for uEnv.txt support */
/*#undef CONFIG_CMD_EXPORTENV*/
/*#undef CONFIG_CMD_IMPORTENV*/

/* Network */
#define CONFIG_CMD_PING
#define CONFIG_CMD_DHCP
#define CONFIG_CMD_MII
#define CONFIG_FEC_MXC
#define CONFIG_MII
#define CONFIG_FEC_ENET_DEV 0
#define IMX_FEC_BASE			ENET_BASE_ADDR
#define CONFIG_FEC_MXC_PHYADDR          0x0
#define CONFIG_FEC_XCV_TYPE             RMII
#define CONFIG_ETHPRIME                 "FEC0"

#define CONFIG_PHYLIB
#define CONFIG_PHY_MICREL

/* allow to overwrite serial and ethaddr */
#define CONFIG_ENV_OVERWRITE
#define CONFIG_CONS_INDEX		1

/* I2C Configs */
#define CONFIG_SYS_MAX_I2C_BUS	3
#define CONFIG_CMD_I2C
#define CONFIG_SYS_I2C
#define CONFIG_SYS_I2C_MXC
#define CONFIG_SYS_I2C_MXC_I2C1    /* enable I2C bus 1 */
#define CONFIG_SYS_I2C_MXC_I2C2    /* enable I2C bus 2 */
#define CONFIG_SYS_I2C_MXC_I2C3    /* enable I2C bus 3 */
#define CONFIG_SYS_I2C_MXC_I2C4    /* enable I2C bus 4 */
#define CONFIG_SYS_I2C_SPEED		100000

/* Touchscreen for autodetect */
#define TOUCH_I2C_BUS			0

/* PMIC */
#define CONFIG_POWER
#define CONFIG_POWER_I2C
#define CONFIG_POWER_PFUZE100
#define CONFIG_POWER_PFUZE100_I2C_ADDR       0x08

#if 0
#define CONFIG_POWER_PFUZE3000
#define CONFIG_POWER_PFUZE3000_I2C_ADDR	0x08
#define PFUZE3000_I2C_BUS	0
#define PFUZE3000_SW1AB_SETP(x)    ((x - 7000) / 250)
#define PFUZE3000_SW3_SETP(x)      ((x - 9000) / 500)
#define PFUZE3000_VLDO_SETP(x)     ((x - 8000) / 500)
#endif

/* Command definition */
/* #include <config_cmd_default.h> */
/* ____________________________________________________________________________
  |                                                                            |
  |                                   WATCHDOG                                 |
  |____________________________________________________________________________|
 */
/* #define CONFIG_APX_WATCHDOG */
#define CONFIG_HW_WATCHDOG

#define APX_WDT_TRIGGER_BASE                     GPIO3_BASE_ADDR
#define APX_WDT_TRIGGER_NUM                      25

#define APX_WDT_ENABLE_BASE                      GPIO4_BASE_ADDR
#define APX_WDT_ENABLE_NUM                       11


#undef CONFIG_CMD_IMLS

#define CONFIG_SYS_AUXCORE_BOOTDATA 0x78000000 /* Set to QSPI2 B flash at default */

#ifdef CONFIG_CMD_BOOTAUX
#define M4_STARTUP_ENV \
	"m4last=/var/opt/m4/m4last.fw\0" \
	"m4fw=/m4startup.fw\0" \
	"mmcrootpart=2\0" \
	"m4last_cmd=ext2load mmc ${mmcdev}:${mmcrootpart} 0x84000000 ${m4last};\0" \
	"m4fw_cmd=fatload mmc ${mmcdev}:${mmcpart} 0x84000000 ${m4fw}; bootaux 0x84000000\0" \
	"m4boot=if run m4last_cmd ; then bootaux 0x84000000 ; else run m4fw_cmd ; fi\0" \
	"m4mmcargs=uart_from_osc clk_ignore_unused cpuidle.off=1\0"
#else
#define M4_STARTUP_ENV \
	"m4boot=\0" \
	"m4mmcargs=uart_from_osc clk_ignore_unused cpuidle.off=1\0"
#endif

/* Linux only */
#ifndef CONFIG_ANDROID_SUPPORT
#define CONFIG_MFG_ENV_SETTINGS \
	"mfgtool_args=setenv bootargs console=${console},${baudrate} " \
		"rdinit=/linuxrc " \
		"g_mass_storage.stall=0 g_mass_storage.removable=1 " \
		"g_mass_storage.idVendor=0x066F g_mass_storage.idProduct=0x37FF "\
		"g_mass_storage.iSerialNumber=\"\" "\
		"\0" \
	"initrd_addr=0x83800000\0" \
	"initrd_high=0xffffffff\0" \
	"bootcmd_mfg=run mfgtool_args;bootz ${loadaddr} ${initrd_addr} ${fdt_addr};\0" \

#define CONFIG_BOOTCOMMAND \
	"mmc dev ${mmcdev}; " \
	"if mmc rescan; then " \
		"if run loadbootscript; then " \
			"run bootscript; " \
		"fi; " \
		"secoinit; " \
		"run m4boot; " \
		"if run loadimage; then " \
			"run mmcboot; " \
		"else run netboot; " \
		"fi; " \
	"else run netboot; fi"
#endif /* ifndef CONFIG_ANDROID_SUPPORT*/

/* Miscellaneous configurable options */
#define CONFIG_SYS_LONGHELP
#define CONFIG_SYS_PROMPT		"=> "
#define CONFIG_AUTO_COMPLETE

#define CONFIG_SYS_BARGSIZE CONFIG_SYS_CBSIZE

#define CONFIG_CMD_MEMTEST
#define CONFIG_SYS_MEMTEST_START	0x80000000
#define CONFIG_SYS_MEMTEST_END		(CONFIG_SYS_MEMTEST_START + 0x10000)

#define CONFIG_SYS_LOAD_ADDR		CONFIG_LOADADDR
#define CONFIG_SYS_HZ			1000

#define CONFIG_CMDLINE_EDITING
#define CONFIG_STACKSIZE		SZ_128K

/* Physical Memory Map */
#define CONFIG_NR_DRAM_BANKS		1
#define PHYS_SDRAM			MMDC0_ARB_BASE_ADDR
#define PHYS_SDRAM_SIZE			SZ_1G

#define CONFIG_SYS_SDRAM_BASE		PHYS_SDRAM
#define CONFIG_SYS_INIT_RAM_ADDR	IRAM_BASE_ADDR
#define CONFIG_SYS_INIT_RAM_SIZE	IRAM_SIZE

#define CONFIG_SYS_INIT_SP_OFFSET \
	(CONFIG_SYS_INIT_RAM_SIZE - GENERATED_GBL_DATA_SIZE)
#define CONFIG_SYS_INIT_SP_ADDR \
	(CONFIG_SYS_INIT_RAM_ADDR + CONFIG_SYS_INIT_SP_OFFSET)

/* FLASH and environment organization */

#define CONFIG_ENV_SIZE			SZ_8K

#ifdef CONFIG_SYS_AUXCORE_FASTUP
/*#define CONFIG_MXC_RDC*/   /* Disable the RDC temporarily, will enable it in future */
#define CONFIG_ENV_IS_IN_MMC  /* Must disable QSPI driver, because M4 run on QSPI */
#elif defined CONFIG_SYS_BOOT_QSPI
#define CONFIG_FSL_QSPI
#define CONFIG_ENV_IS_IN_SPI_FLASH
#else
#define CONFIG_ENV_IS_IN_MMC
#endif

/* ____________________________________________________________________________
  |                                                                            |
  |                                       SPI                                  |
  |____________________________________________________________________________|
*/

#define CONFIG_SYS_BOOT_SPINOR	

#ifdef CONFIG_SYS_BOOT_SPINOR
	#define CONFIG_SPI_FLASH
	#define CONFIG_SPI_FLASH_SPANSION
	#define CONFIG_MXC_SPI
	#define CONFIG_SF_DEFAULT_BUS        	0
	#define CONFIG_SF_DEFAULT_CS         	(0|(IMX_GPIO_NR(2, 30)<<8))
	#define CONFIG_SF_DEFAULT_SPEED         20 * 1000 * 1000
	#define	CONFIG_SF_DEFAULT_MODE		SPI_MODE_0
	#define CONFIG_SYS_MAX_FLASH_BANKS 	1    /* max number of memory banks */
#endif

#ifdef CONFIG_CMD_SF
	#define CONFIG_SPI_FLASH_SST
	/* #define CONFIG_MXC_SPI_CSHOLD */
	#define CONFIG_SF_DEFAULT_BUS  	0
	#define CONFIG_SF_DEFAULT_CS   	(0|(IMX_GPIO_NR(2, 30)<<8))
#endif

#define CONFIG_SYS_MMC_ENV_DEV		1  /*USDHC4*/
#define CONFIG_SYS_MMC_ENV_PART		0	/* user area */
#define CONFIG_MMCROOT			"/dev/mmcblk1p5"  /* USDHC2 */

#if defined(CONFIG_ENV_IS_IN_MMC)
#define CONFIG_ENV_OFFSET		(8 * SZ_64K)
#elif defined(CONFIG_ENV_IS_IN_SPI_FLASH)
#define CONFIG_ENV_OFFSET		(768 * 1024)
#define CONFIG_ENV_SECT_SIZE		(64 * 1024)
#define CONFIG_ENV_SPI_BUS		CONFIG_SF_DEFAULT_BUS
#define CONFIG_ENV_SPI_CS		CONFIG_SF_DEFAULT_CS
#define CONFIG_ENV_SPI_MODE		CONFIG_SF_DEFAULT_MODE
#define CONFIG_ENV_SPI_MAX_HZ		CONFIG_SF_DEFAULT_SPEED
#endif

#define CONFIG_CMD_BOOTZ

#define CONFIG_CMD_BMODE

#ifndef CONFIG_SYS_DCACHE_OFF
#define CONFIG_CMD_CACHE
#endif

#ifdef CONFIG_VIDEO
#define	CONFIG_CFB_CONSOLE
#define	CONFIG_VIDEO_MXS
#define	CONFIG_VIDEO_LOGO
#define	CONFIG_VIDEO_SW_CURSOR
#define	CONFIG_VGA_AS_SINGLE_DEVICE
#define	CONFIG_SYS_CONSOLE_IS_IN_ENV
#define	CONFIG_SPLASH_SCREEN
#define CONFIG_SPLASH_SCREEN_ALIGN
#define	CONFIG_CMD_BMP
#define	CONFIG_BMP_16BPP
#define	CONFIG_VIDEO_BMP_RLE8
#define CONFIG_VIDEO_BMP_LOGO
#ifdef CONFIG_VIDEO_GIS
#define CONFIG_VIDEO_CSI
#define CONFIG_VIDEO_PXP
#define CONFIG_VIDEO_VADC
#endif
#endif

#define CONFIG_USB_EHCI
#define CONFIG_USB_EHCI_MX6
#define CONFIG_USB_STORAGE
#define CONFIG_EHCI_HCD_INIT_AFTER_RESET
#define CONFIG_USB_HOST_ETHER
#define CONFIG_USB_ETHER_ASIX
#define CONFIG_MXC_USB_PORTSC  (PORT_PTS_UTMI | PORT_PTS_PTW)
#define CONFIG_MXC_USB_FLAGS   0
#define CONFIG_USB_MAX_CONTROLLER_COUNT 2

#define CONFIG_CMD_FUSE
#ifdef CONFIG_CMD_FUSE
#define CONFIG_MXC_OCOTP
#endif

#if defined(CONFIG_ANDROID_SUPPORT)
#define CONFIG_CMD_BOOTI
#include "mx6sxsabresdandroid.h"
#endif

#if defined(CONFIG_ANDROID_SUPPORT)
#undef CONFIG_EXTRA_ENV_SETTINGS
#define CONFIG_EXTRA_ENV_SETTINGS \
	"kernel_loadaddr=0x10800000\0" \
	"fdt_loadaddr=0x14f00000\0" \
	"script_file=uEnvC04.txt\0" \
	"usb_test=usb start; mw.b 10600000 0 1600; setenv recoveryboot 0; if fatload usb 0 10600000 /boot/${script_file}; then env import -t 10600000 1600; boot; fi; \0" \
	"seco_boot_init=if itest.l *0x80000000 != 0x551177AA; then run usb_test; fi; secoinit; ext2load mmc ${mmc_cur}:5 ${fdt_loadaddr} ${fdt_file}; \0" \
	"splashpos=m,m\0" \
	"fdt_high=0xffffffff\0" \
	"initrd_high=0xffffffff\0" \
	"recoverycmd=run seco_boot_init; boota mmc1 recovery\0"
#endif

#define CONFIG_CMD_TIME

#endif				/* __CONFIG_H */
