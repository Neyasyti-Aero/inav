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

#include <stdint.h>

#include "platform.h"

#include "drivers/bus.h"
#include "drivers/io.h"
#include "drivers/pwm_mapping.h"
#include "drivers/timer.h"
#include "drivers/pinio.h"
#include "drivers/sensor.h"

timerHardware_t timerHardware[] = {
    DEF_TIM(TIM4, CH2, PD13, TIM_USE_OUTPUT_AUTO, 0, 0), // S1 (works as Motor output in airplane with tail)
    DEF_TIM(TIM4, CH1, PD12, TIM_USE_OUTPUT_AUTO, 0, 0), // S2 (doesn't work for some reason, always 0)
    DEF_TIM(TIM3, CH2, PA7,  TIM_USE_OUTPUT_AUTO, 0, 0), // S3 (works as Servo 1 in airplane with tail for some reason)
    DEF_TIM(TIM5, CH2, PA1,  TIM_USE_OUTPUT_AUTO, 0, 0), // S4 (doesn't work for some reason, always 0)
    DEF_TIM(TIM8, CH4, PC9,  TIM_USE_OUTPUT_AUTO, 0, 0), // S5 (works as Servo 3 in airplane with tail for some reason)
    DEF_TIM(TIM3, CH4, PB1,  TIM_USE_OUTPUT_AUTO, 0, 0), // S6 (doesn't work for some reason, always 0)
    DEF_TIM(TIM8, CH2, PB0,  TIM_USE_OUTPUT_AUTO, 0, 1), // S7
    DEF_TIM(TIM8, CH1, PA5,  TIM_USE_OUTPUT_AUTO, 0, 0), // S8
    DEF_TIM(TIM2, CH1, PB8,  TIM_USE_OUTPUT_AUTO, 0, 0), // S9
    DEF_TIM(TIM1, CH4, PE14, TIM_USE_OUTPUT_AUTO, 0, 0), // S10
    DEF_TIM(TIM1, CH3, PE13, TIM_USE_OUTPUT_AUTO, 0, 0), // S11
    DEF_TIM(TIM1, CH2, PE11, TIM_USE_OUTPUT_AUTO, 0, 1), // S12
    DEF_TIM(TIM1, CH1, PE9,  TIM_USE_OUTPUT_AUTO, 0, 2), // S13
};

const int timerHardwareCount = sizeof(timerHardware) / sizeof(timerHardware[0]);
