/*
 * (C) Copyright 2015 Seco
 *
 * Author: Davide Cardillo <davide.cardillo@seco.com>
 *
 * SPDX-License-Identifier:     GPL-2.0+
 */


#include "pin_muxing_a62.h"
#include "../common/proto_seco.h"
#include "detectboard.h"

#define MX6_GPIO_BOOT_VALIDATE                   IMX_GPIO_NR(2, 4)

/* I2C1 - Embedded Controller */
struct i2c_pads_info i2c_pad_info0 = {
	.scl = {
		.i2c_mode  = MX6_PAD_EIM_D21__I2C1_SCL   | PC,
		.gpio_mode = MX6_PAD_EIM_D21__GPIO3_IO21 | PC,
		.gp        = IMX_GPIO_NR(3, 21),
	},
	.sda = {
		.i2c_mode  = MX6_PAD_EIM_D28__I2C1_SDA   | PC,
		.gpio_mode = MX6_PAD_EIM_D28__GPIO3_IO28 | PC,
		.gp        = IMX_GPIO_NR(3, 28),
	},
};


/* I2C2 - PMIC */
struct i2c_pads_info i2c_pad_info1 = {
	.scl = {
		.i2c_mode  = MX6_PAD_KEY_COL3__I2C2_SCL   | PC,
		.gpio_mode = MX6_PAD_KEY_COL3__GPIO4_IO12 | PC,
		.gp        = IMX_GPIO_NR(4, 12),
	},
	.sda = {
		.i2c_mode  = MX6_PAD_KEY_ROW3__I2C2_SDA   | PC,
		.gpio_mode = MX6_PAD_KEY_ROW3__GPIO4_IO13 | PC,
		.gp        = IMX_GPIO_NR(4, 13),
	},
};


/* I2C2 - Q7 connector */
struct i2c_pads_info i2c_pad_info2 = {
	.scl = {
		.i2c_mode  = MX6_PAD_GPIO_5__I2C3_SCL   | PC,
		.gpio_mode = MX6_PAD_GPIO_5__GPIO1_IO05 | PC,
		.gp        = IMX_GPIO_NR(1, 5),
	},
	.sda = {
		.i2c_mode  = MX6_PAD_GPIO_16__I2C3_SDA   | PC,
		.gpio_mode = MX6_PAD_GPIO_16__GPIO7_IO11 | PC,
		.gp        = IMX_GPIO_NR(7, 11),
	},
};




void ldo_mode_set(int ldo_bypass) {} 




int dram_init (void) {
	gd->ram_size = ((ulong)CONFIG_DDR_MB * 1024 * 1024);
	return 0;
}




/*  __________________________________________________________________________
 * |                                                                          |
 * |                                   UART                                   |
 * |__________________________________________________________________________|
 */

static void setup_iomux_uart (void) {
	imx_iomux_v3_setup_multiple_pads(uart_debug_pads, ARRAY_SIZE(uart_debug_pads));
}
/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */


/*  __________________________________________________________________________
 * |                                                                          |
 * |                                   SPI                                    |
 * |__________________________________________________________________________|
 */

#ifdef CONFIG_SYS_USE_SPINOR

static void setup_spinor(void) {
	SETUP_IOMUX_PADS(ecspi1_pads);
	gpio_direction_output(IMX_GPIO_NR(2, 30), 0);
}

int board_spi_cs_gpio(unsigned bus, unsigned cs)
{
	return (bus == 0 && cs == 0) ? (IMX_GPIO_NR(2, 30)) : cs >> 8;
}

#endif   /*  CONFIG_SYS_USE_SPINOR  */

/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */


/*  __________________________________________________________________________
 * |                                                                          |
 * |                               WATCHDOG APX                               |
 * |__________________________________________________________________________|
 */
static inline void setup_iomux_apx_watchdog (void) {
	imx_iomux_v3_setup_multiple_pads (wdt_trigger_pads, ARRAY_SIZE(wdt_trigger_pads));
}
/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */

#ifdef CONFIG_FSL_FASTBOOT
#ifdef CONFIG_OF_LOAD_MANUALLY

void board_fastboot_setup(void)
{
	switch (get_boot_device()) {
#if defined(CONFIG_FASTBOOT_STORAGE_SATA)
	case SATA_BOOT:
		if (!getenv("root_device"))
			setenv("root_device", "sata");
		if (!getenv("fastboot_dev"))
			setenv("fastboot_dev", "sata");
		if (!getenv("bootcmd"))
			setenv("bootcmd", "boota sata");
		break;
#endif /*CONFIG_FASTBOOT_STORAGE_SATA*/
#if defined(CONFIG_FASTBOOT_STORAGE_MMC)
	case SD2_BOOT:
	case MMC1_BOOT:
	case MMC2_BOOT:
	case MMC4_BOOT:
	    if (!getenv("mmc_cur"))
			setenv("mmc_cur", "0");
	    if (!getenv("root_device"))
			setenv("root_device", "emmc");
	    if (!getenv("fastboot_dev"))
			setenv("fastboot_dev", "mmc0");
	    if (!getenv("bootcmd"))
			setenv("bootcmd", "mmc dev 1; run seco_boot_init; boota mmc1 mmcsdb1");
	    break;
	case SD3_BOOT:
	case MMC3_BOOT:
	    if (!getenv("mmc_cur"))
			setenv("mmc_cur", "1");
	    if (!getenv("root_device"))
			setenv("root_device", "sd");
	    if (!getenv("fastboot_dev"))
			setenv("fastboot_dev", "mmc1");
	    if (!getenv("bootcmd"))
			setenv("bootcmd", "mmc dev 1; run seco_boot_init; boota mmc1 mmcsdb1");
	    break;
//	case MMC4_BOOT:
//	    if (!getenv("fastboot_dev"))
//			setenv("fastboot_dev", "mmc2");
//	    if (!getenv("bootcmd"))
//			setenv("bootcmd", "run seco_boot_init; boota mmc2");
//	    break;
#endif /*CONFIG_FASTBOOT_STORAGE_MMC*/
	default:
		printf("unsupported boot devices 0x%04x.\n", get_boot_device());
		break;
	}
}

#ifdef CONFIG_ANDROID_RECOVERY
// int check_recovery_cmd_file(void)
// {
// 	return recovery_check_and_clean_flag();
// }

void board_recovery_setup(void)
{
	int bootdev = get_boot_device();

	switch (bootdev) {
#if defined(CONFIG_FASTBOOT_STORAGE_SATA)
	case SATA_BOOT:
		if (!getenv("bootcmd_android_recovery"))
			setenv("bootcmd_android_recovery",
				"boota sata recovery");
		break;
#endif /*CONFIG_FASTBOOT_STORAGE_SATA*/
#if defined(CONFIG_FASTBOOT_STORAGE_MMC)
	case SD2_BOOT:
	case MMC1_BOOT:
	case MMC2_BOOT:
	case MMC4_BOOT:
	    	if (!getenv("mmc_cur"))
			setenv("mmc_cur", "0");
	    	if (!getenv("root_device"))
			setenv("root_device", "emmc");
	    	if (!getenv("fastboot_dev"))
			setenv("fastboot_dev", "mmc0");
		if (!getenv("bootcmd_android_recovery"))
			setenv("bootcmd_android_recovery",
				"boota mmc0 recovery");
		break;
	case SD3_BOOT:
	case MMC3_BOOT:
	    	if (!getenv("mmc_cur"))
			setenv("mmc_cur", "1");
	    	if (!getenv("root_device"))
			setenv("root_device", "sd");
	    	if (!getenv("fastboot_dev"))
			setenv("fastboot_dev", "mmc1");
		if (!getenv("bootcmd_android_recovery"))
			setenv("bootcmd_android_recovery",
				"boota mmc1 recovery");
		break;
//	case MMC4_BOOT:
//		if (!getenv("bootcmd_android_recovery"))
//			setenv("bootcmd_android_recovery",
//				"boota mmc2 recovery");
//		break;
#endif /*CONFIG_FASTBOOT_STORAGE_MMC*/
	default:
		printf("Unsupported bootup device for recovery: dev: %d\n",
			bootdev);
		return;
	}

	printf("setup env for recovery..\n");
	setenv("bootcmd", "run bootcmd_android_recovery");
}
#endif /*CONFIG_OF_LOAD_MANUALLY*/

#endif /*CONFIG_ANDROID_RECOVERY*/

int is_recovery_key_pressing(void)
{
	        return 0;
}

#endif /*CONFIG_FSL_FASTBOOT*/

/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */



/*  __________________________________________________________________________
 * |                                                                          |
 * |                                   ETHERNET                               |
 * |__________________________________________________________________________|
 */
inline void enable_ethernet_rail (void) {
}
/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */


/*  __________________________________________________________________________
 * |                                                                          |
 * |                                   USDHC                                  |
 * |__________________________________________________________________________|
 */
#ifdef CONFIG_FSL_ESDHC

#define USDHC3_CD_GPIO	IMX_GPIO_NR(7, 0)
#define USDHC3_PWR_GPIO IMX_GPIO_NR(2, 5)

/* USDHC map:
 * 	USDHC4  -->  eMMC  -->  FSL_SDHC: 0
 * 	USDHC3  -->  uSD   -->  FSL_SDHC: 1
 */

boot_mem_dev_t boot_mem_dev_list[SECO_NUM_BOOT_DEV] = {
	{ 0x4, 0x5, -1,   0, -1, "on board uSD" },
	{ 0x6, 0x7, -1,  -1, -1, "eMMC" },
};

struct fsl_esdhc_cfg usdhc_cfg[CONFIG_SYS_FSL_USDHC_NUM] = {
	{USDHC4_BASE_ADDR, 0, 8},
	{USDHC3_BASE_ADDR, 0, 4},
};

struct usdhc_l usdhc_list[CONFIG_SYS_FSL_USDHC_NUM] = {
	{usdhc4_pads, ARRAY_SIZE(usdhc4_pads), -1},
	{usdhc3_pads, ARRAY_SIZE(usdhc3_pads), USDHC3_CD_GPIO},
};

enum mxc_clock usdhc_clk[CONFIG_SYS_FSL_USDHC_NUM] = {
	MXC_ESDHC4_CLK,
	MXC_ESDHC3_CLK,
};

/* map the usdhc controller id to the devno given to the board device */
int usdhc_devno[4] = { -1, -1, 1, 0};

int board_mmc_getcd (struct mmc *mmc) {
	struct fsl_esdhc_cfg *cfg = (struct fsl_esdhc_cfg *)mmc->priv;
	int ret = 0;

	switch (cfg->esdhc_base) {
		case USDHC3_BASE_ADDR:
			ret = !gpio_get_value(USDHC3_CD_GPIO);
			break;
		case USDHC4_BASE_ADDR:
			ret = 1; /* eMMC/uSDHC4 is always present */
			break;
	}

	return ret;
}

#endif  /*  CONFIG_FSL_ESDHC  */

/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */



/*  __________________________________________________________________________
 * |                                                                          |
 * |                                    USB                                   |
 * |__________________________________________________________________________|
 */
#ifdef CONFIG_USB_EHCI_MX6

#define USB_HOST1_PWR     IMX_GPIO_NR(7, 12)
#define USB_OTG_PWR       IMX_GPIO_NR(3, 22)


int board_ehci_hcd_init (int port) {
	switch (port) {
	case 0:
		imx_iomux_v3_setup_multiple_pads(usb_otg_pads,
			ARRAY_SIZE(usb_otg_pads));

		/*set daisy chain for otg_pin_id on 6q. for 6dl, this bit is reserved*/
		imx_iomux_set_gpr_register(1, 13, 1, 0);
		break;
	case 1:
		imx_iomux_v3_setup_multiple_pads(usb_hc1_pads,
			ARRAY_SIZE(usb_hc1_pads));
		break;
	default:
		printf("MXC USB port %d not yet supported\n", port);
		return 1;
	}
	return 0;
}

int board_ehci_power (int port, int on) {
	switch (port) {
	case 0:
		if (on)
			gpio_direction_output(USB_OTG_PWR, 1);
		else
			gpio_direction_output(USB_OTG_PWR, 0);
		break;
	case 1:
		if (on)
			gpio_direction_output(USB_HOST1_PWR, 1);
		else
			gpio_direction_output(USB_HOST1_PWR, 0);
		break;
	default:
		printf("MXC USB port %d not yet supported\n", port);
		return 1;
	}
	return 0;
}

#endif  /*  CONFIG_USB_EHCI_MX6  */
/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */


/*  __________________________________________________________________________
 * |                                                                          |
 * |                            DISPLAY INFO - INIT                           |
 * |__________________________________________________________________________|
 */
/*
 * Do not overwrite the console
 * Use always serial for U-Boot console
 */
int overwrite_console (void) {
	return 1;
}


#ifdef CONFIG_SECO_BOARD_NAME
char *board_name = CONFIG_SECO_BOARD_NAME;
#else
char *board_name = "Seco i.mx6 Board - A62";
#endif


int board_early_init_f (void) {

	setup_iomux_uart();

#if defined(CONFIG_VIDEO_IPUV3)
	setup_display();
#endif

	return 0;
}

#define I2C_PMIC                                 0x1

int board_init (void) {

#ifdef CONFIG_SYS_I2C_MXC
	int s, i;
	unsigned char *boardrev = NULL;
#endif

#ifdef CONFIG_SYS_USE_SPINOR
	setup_spinor();
#endif

#ifdef CONFIG_CMD_SATA
	setup_sata();
#endif


	print_boot_device ();

	return 0;
}

#ifdef CONFIG_CMD_BMODE
static const struct boot_mode board_boot_modes[] = {
	/* 4 bit bus width */
	{"sd3",	 MAKE_CFGVAL(0x40, 0x30, 0x00, 0x00)},
	/* 8 bit bus width */
	{"emmc", MAKE_CFGVAL(0x60, 0x58, 0x00, 0x00)},
	{NULL,	 0},
};
#endif

int board_late_init (void) {
	int ret = 0;

#ifdef CONFIG_CMD_BMODE
	add_board_boot_modes(board_boot_modes);
#endif

#ifdef CONFIG_ENV_IS_IN_MMC
	board_late_mmc_env_init();
#endif

	return ret;
}
/*  __________________________________________________________________________
 * |__________________________________________________________________________|
 */


