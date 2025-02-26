/*
 * This file is part of INAV.
 *
 * INAV is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * INAV is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with INAV.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <platform.h>
#include "common/time.h"

#ifdef USE_TASK_TARGETTASK

#include "common/log.h"
#include "build/debug.h"

void targetTaskCall(timeUs_t currentTimeUs)
{
#ifdef USE_64BIT_TIME
    LOG_DEBUG(SYSTEM, "Target task call, currentTimeUs: %llu", currentTimeUs);
#else
    LOG_DEBUG(SYSTEM, "Target task call, currentTimeUs: %lu", currentTimeUs);
#endif

    uint32_t dbg_id = *(uint32_t*)(0xE0042000); // DBG_ID / DBGMCU_IDCODE
    uint32_t device_id = *(uint32_t*)(0xE0042000) & 0xFFF; // device ID

    LOG_INFO(SYSTEM, "DEBUG ID (FULL): %lu (0x%08lX)", dbg_id, dbg_id);
    LOG_INFO(SYSTEM, "DEVICE ID: %lu (0x%03lX)", device_id, device_id);
}

#endif
