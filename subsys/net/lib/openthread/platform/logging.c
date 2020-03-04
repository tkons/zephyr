/*
 * Copyright (c) 2018 Nordic Semiconductor ASA
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <kernel.h>
#include <stdarg.h>
#include <stdio.h>

#include <openthread/platform/logging.h>
#include "openthread-core-zephyr-config.h"

#define LOG_MODULE_NAME net_openthread
#define LOG_LEVEL LOG_LEVEL_DBG
#include <logging/log.h>
LOG_MODULE_REGISTER(LOG_MODULE_NAME);

#include "platform-zephyr.h"


void otPlatLog(otLogLevel aLogLevel, otLogRegion aLogRegion,
	       const char *aFormat, ...)
{
	const bool do_strdup = true;

#ifdef OPENTHREAD_CONFIG_PLAT_LOG_FUNCTION__COUNT_ARGS
	u32_t argsNum = (int) aLogRegion;
#else
	u32_t argsNum = log_count_args(aFormat);
#endif

	va_list paramList;
	va_start(paramList, aFormat);

	switch (aLogLevel) {
	case OT_LOG_LEVEL_CRIT:
		Z_LOG_VA(LOG_LEVEL_ERR, aFormat, paramList, argsNum,
			do_strdup);
		break;
	case OT_LOG_LEVEL_WARN:
		Z_LOG_VA(LOG_LEVEL_WRN, aFormat, paramList, argsNum,
			do_strdup);
		break;
	case OT_LOG_LEVEL_INFO:
		Z_LOG_VA(LOG_LEVEL_INF, aFormat, paramList, argsNum,
			do_strdup);
		break;
	case OT_LOG_LEVEL_DEBG:
		Z_LOG_VA(LOG_LEVEL_DBG, aFormat, paramList, argsNum,
			do_strdup);
		break;
	default:
		break;
	}
	va_end(paramList);

}
