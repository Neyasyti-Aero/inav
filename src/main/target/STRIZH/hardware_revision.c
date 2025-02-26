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
    // delay(1); // delay in ms

    // For STM32F405/407xx and STM32F415/417xx devices, the device ID is 0x413
    // For STM32F42xxx and STM32F43xxx devices, the device ID is 0x419
    // For STM32F401xx devices, the device ID is 0x423
    // For STM32F401xx devices, the device ID is 0x433
    // For STM32F411xx devices, the device ID is 0x431
    // For STM32F410xx devices, the device ID is 0x458
    // For STM32F412xx devices, the device ID is 0x441
    // For STM32F413xx and STM32423xx devices, the device ID is 0x463
    // For STM32F446xx devices, the device ID is 0x421
    // For STM32F469xx and STM32F479xx devices, the device ID is 0x434
    
    // Check device id
    dbg_id = *(uint32_t*)(0xE0042000); // DBG_ID / DBGMCU_IDCODE
    device_id = *(uint32_t*)(0xE0042000) & 0xFFF; // device ID
    debug[6] = *(uint32_t*)(0xE0042000); // DBG_ID / DBGMCU_IDCODE
    debug[7] = *(uint32_t*)(0xE0042000) & 0xFFF; // device ID
}

// called from init() - later
void updateHardwareRevision(void)
{
	// USB VCP can not be connected on this call (too early)
    LOG_INFO(SYSTEM, "DEBUG ID (FULL): %lu (0x%08lX)", dbg_id, dbg_id);
    LOG_INFO(SYSTEM, "DEVICE ID: %lu (0x%03lX)", device_id, device_id);
}
