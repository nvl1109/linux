/*
 * Copyright (C) 2015 Broadcom
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include "drm_crtc.h"
#include "drm_atomic_helper.h"
#include "drm_crtc_helper.h"
#include "drm_plane_helper.h"
#include "drm_fb_cma_helper.h"
#include "vc4_drv.h"

static void vc4_output_poll_changed(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);

	if (vc4->fbdev)
		drm_fbdev_cma_hotplug_event(vc4->fbdev);
}

static const struct drm_mode_config_funcs vc4_mode_funcs = {
	.output_poll_changed = vc4_output_poll_changed,
	.atomic_check = drm_atomic_helper_check,
	.atomic_commit = drm_atomic_helper_commit,
	.fb_create = drm_fb_cma_create,
};

/*
 * Calls out to initialize all of the VC4 KMS objects.
 */
static int
vc4_init_modeset_objects(struct drm_device *dev)
{
	struct drm_encoder *encoder;
	struct drm_connector *connector;
	int ret = 0;

	encoder = vc4_hdmi_encoder_init(dev);
	if (IS_ERR(encoder)) {
		dev_err(dev->dev, "failed to construct HDMI encoder\n");
		ret = PTR_ERR(encoder);
		goto fail;
	}

	connector = vc4_hdmi_connector_init(dev, encoder);
	if (IS_ERR(connector)) {
		ret = PTR_ERR(connector);
		dev_err(dev->dev, "failed to initialize HDMI connector\n");
		goto fail;
	}

fail:
	return ret;
}

int
vc4_kms_load(struct drm_device *dev)
{
	struct vc4_dev *vc4 = to_vc4_dev(dev);
	int ret;

	ret = drm_vblank_init(dev, dev->mode_config.num_crtc);
	if (ret < 0) {
		dev_err(dev->dev, "failed to initialize vblank\n");
		return ret;
	}

	dev->mode_config.max_width = 2048;
	dev->mode_config.max_height = 2048;
	dev->mode_config.funcs = &vc4_mode_funcs;
	dev->mode_config.preferred_depth = 24;

	ret = vc4_init_modeset_objects(dev);
	if (ret)
		goto fail;

	drm_mode_config_reset(dev);

	vc4->fbdev = drm_fbdev_cma_init(dev, 32,
					dev->mode_config.num_crtc,
					dev->mode_config.num_connector);
	if (IS_ERR(vc4->fbdev))
		vc4->fbdev = NULL;

	drm_kms_helper_poll_init(dev);

fail:
	return ret;
}
