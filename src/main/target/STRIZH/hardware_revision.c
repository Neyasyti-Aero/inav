/*
 * This file is part of Cleanflight.
 *
 * Cleanflight is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * Cleanflight is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with Cleanflight.  If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdbool.h>
#include <stdint.h>
#include <stdlib.h>

#include "platform.h"

#include "build/build_config.h"
#include "build/debug.h"

#include "drivers/io.h"
#include "drivers/time.h"
#include "common/log.h"

#include "hardware_revision.h"

uint8_t hardwareRevision = STRIZH_UNKNOWN;
uint32_t device_id;
uint32_t dbg_id;

// called from init() - early
void detectHardwareRevision(void)
{

}

// called from init() - later
// USB VCP can not be connected on this call (too early)
void updateHardwareRevision(void)
{

}
