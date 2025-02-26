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

#include "config/config_master.h"
#include "config/feature.h"

#include "flight/mixer_profile.h"

#include "io/serial.h"

#include "telemetry/telemetry.h"
#include "fc/fc_msp_box.h"
#include "io/piniobox.h"

// set default settings for STRIZH target
void targetConfiguration(void)
{  
    // pinioBoxConfigMutable()->permanentId[0] = BOX_PERMANENT_ID_USER1;
    // pinioBoxConfigMutable()->permanentId[1] = BOX_PERMANENT_ID_USER2;

    mixerConfigMutable()->platformType = PLATFORM_AIRPLANE; // default mixer to Airplane
    
    serialConfigMutable()->portConfigs[0].functionMask = FUNCTION_LOG | FUNCTION_MSP;
    serialConfigMutable()->portConfigs[0].msp_baudrateIndex = BAUD_115200;

    serialConfigMutable()->portConfigs[1].functionMask = FUNCTION_TELEMETRY_MAVLINK;
    serialConfigMutable()->portConfigs[1].telemetry_baudrateIndex = BAUD_115200;
    
    serialConfigMutable()->portConfigs[2].functionMask = FUNCTION_GPS;
    serialConfigMutable()->portConfigs[2].gps_baudrateIndex = BAUD_115200;
}
