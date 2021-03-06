// SPDX-License-Identifier: BSD-3-Clause
//
// Copyright(c) 2019 Intel Corporation. All rights reserved.
//
// Author: Slawomir Blauciak <slawomir.blauciak@linux.intel.com>

#include <sof/drivers/alh.h>
#include <sof/lib/dai.h>
#include <sof/lib/dma.h>
#include <sof/lib/memory.h>
#include <sof/trace/trace.h>
#include <sof/common.h>
#include <ipc/dai.h>
#include <ipc/stream.h>
#include <user/trace.h>
#include <stdint.h>

#define trace_alh(__e, ...) trace_event(TRACE_CLASS_ALH, __e, ##__VA_ARGS__)
#define trace_alh_error(__e, ...) \
	trace_error(TRACE_CLASS_ALH, __e, ##__VA_ARGS__)
#define tracev_alh(__e, ...) tracev_event(TRACE_CLASS_ALH, __e, ##__VA_ARGS__)

static int alh_trigger(struct dai *dai, int cmd, int direction)
{
	trace_alh("alh_trigger() cmd %d", cmd);

	return 0;
}

static int alh_set_config(struct dai *dai, struct sof_ipc_dai_config *config)
{
	trace_alh("alh_set_config() config->format = 0x%4x",
		  config->format);

	return 0;
}

static int alh_context_store(struct dai *dai)
{
	trace_alh("alh_context_store()");

	return 0;
}

static int alh_context_restore(struct dai *dai)
{
	trace_alh("alh_context_restore()");

	return 0;
}

static int alh_probe(struct dai *dai)
{
	trace_alh("alh_probe()");

	return 0;
}

static int alh_remove(struct dai *dai)
{
	trace_alh("alh_remove()");

	return 0;
}

static int alh_get_handshake(struct dai *dai, int direction, int stream_id)
{
	if (stream_id >= ARRAY_SIZE(alh_handshake_map)) {
		trace_alh_error("alh_get_handshake() error: "
				"stream_id %d out of range", stream_id);

		return -1;
	}

	return alh_handshake_map[stream_id];
}

static int alh_get_fifo(struct dai *dai, int direction, int stream_id)
{
	uint32_t offset = direction == SOF_IPC_STREAM_PLAYBACK ?
		ALH_TXDA_OFFSET : ALH_RXDA_OFFSET;

	return ALH_BASE + offset + ALH_STREAM_OFFSET * stream_id;
}

const struct dai_driver alh_driver = {
	.type = SOF_DAI_INTEL_ALH,
	.dma_caps = DMA_CAP_GP_LP | DMA_CAP_GP_HP,
	.dma_dev = DMA_DEV_ALH,
	.ops = {
		.trigger		= alh_trigger,
		.set_config		= alh_set_config,
		.pm_context_store	= alh_context_store,
		.pm_context_restore	= alh_context_restore,
		.get_handshake		= alh_get_handshake,
		.get_fifo		= alh_get_fifo,
		.probe			= alh_probe,
		.remove			= alh_remove,
	},
};
