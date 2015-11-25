/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * Authors:
 * (C) 2015 Pengutronix, Alexander Aring <aar@pengutronix.de>
 * Eric Anholt <eric@anholt.net>
 */

#include <linux/module.h>
#include <linux/of_platform.h>
#include <linux/platform_device.h>
#include <linux/pm_domain.h>
#include <soc/bcm2835/raspberrypi-firmware.h>

#define RPI_POWER_DOMAIN(_domain, _name)			\
	[_domain] = {						\
		.domain = _domain,				\
		.enabled = true,				\
		.base = {					\
			.name = _name,				\
			.power_off = rpi_domain_off,		\
			.power_on = rpi_domain_on,		\
		},						\
	}

struct rpi_v3d_power {
	struct generic_pm_domain genpd;
};

static struct rpi_firmware *fw;

/*
 * Asks the firmware to enable or disable power on a specific power
 * domain.
 */
static int rpi_v3d_set_power(bool on)
{
	u32 packet = on;

	return rpi_firmware_property(fw, RPI_FIRMWARE_SET_ENABLE_QPU, &packet,
				     sizeof(packet));
}

static int rpi_v3d_off(struct generic_pm_domain *domain)
{
	return rpi_v3d_set_power(false);
}

static int rpi_v3d_on(struct generic_pm_domain *domain)
{
	return rpi_v3d_set_power(true);
}

static int rpi_power_probe(struct platform_device *pdev)
{
	struct device_node *fw_np;
	struct device *dev = &pdev->dev;
	struct rpi_v3d_power *v3d_power;
	int ret;

	fw_np = of_parse_phandle(pdev->dev.of_node, "firmware", 0);
	if (!fw_np) {
		dev_err(&pdev->dev, "no firmware node\n");
		return -ENODEV;
	}

	fw = rpi_firmware_get(fw_np);
	if (!fw)
		return -EPROBE_DEFER;

	v3d_power = devm_kzalloc(dev, sizeof(*v3d_power), GFP_KERNEL);
	if (!v3d_power)
		return -ENOMEM;

	v3d_power->genpd.name = "v3d";
	v3d_power->genpd.power_off = rpi_v3d_off;
	v3d_power->genpd.power_on = rpi_v3d_on;
	pm_genpd_init(&v3d_power->genpd, NULL, true);

	ret = of_genpd_add_provider_simple(dev->of_node, &v3d_power->genpd);
	return ret;
}

static int rpi_power_remove(struct platform_device *pdev)
{
	struct device *dev = &pdev->dev;

	of_genpd_del_provider(dev->of_node);

	return 0;
}

static const struct of_device_id rpi_power_of_match[] = {
	{ .compatible = "raspberrypi,bcm2835-power-v3d", },
	{},
};
MODULE_DEVICE_TABLE(of, rpi_power_of_match);

static struct platform_driver rpi_power_driver = {
	.driver = {
		.name = "raspberrypi-power",
		.of_match_table = rpi_power_of_match,
	},
	.probe		= rpi_power_probe,
	.remove		= rpi_power_remove,
};
module_platform_driver(rpi_power_driver);

MODULE_AUTHOR("Alexander Aring <aar@pengutronix.de>");
MODULE_AUTHOR("Eric Anholt <eric@anholt.net>");
MODULE_DESCRIPTION("Raspberry Pi power domain driver");
MODULE_LICENSE("GPL v2");
