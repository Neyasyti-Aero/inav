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
#include <string.h>
#include "common/time.h"

#ifdef USE_TASK_TARGETTASK

#include "common/log.h"
#include "io/serial.h"
#include "rx/rx.h"
#include "build/debug.h"
#include "fc/runtime_config.h"
#include "drivers/pwm_output.h"
#include "flight/servos.h"

uint8_t called = 0;

// It is neccessary to configure RX and MIXER (all outputs to SERVO)
// Enable motor and servo output should be enabled

// Сигнал - функция
// 1 - зажать кнопку зажигания
// 2 - отжать кнопку зажигания
// 3 - включить фары 1 режим
// 4 - включить фары - 2 режим (дальний свет)
// 5 - выключить фары
// 6 - включить фары - 3 режим
// 7 - гудок полсекунды
// 8 - 
// 9 - зажать чёрный курок сзади (включить дальний свет)
// 10 - дальний свет мигать (выключить дальний свет)
// 11 - включить левый поворотник
// 12 - отключить поворотники
// 13 - включить правый поворотник
// 14 - насос - нажать
// 15 - насос - отжать

#define IGNITION_PRESS "1\r\n"
#define IGNITION_UNPRESS "2\r\n"
#define HEADLIGHTS_MODE_1 "3\r\n"
#define HEADLIGHTS_MODE_2 "4\r\n"
#define HEADLIGHTS_OFF "5\r\n"
#define HEADLIGHTS_MODE_3 "6\r\n"
#define HORN "7\r\n"
#define HEADLIGHTS_FAR_PRESS "9\r\n"
#define HEADLIGHTS_FAR_UNPRESS "10\r\n"
#define LEFT_TURN_SIGNAL_ON "11\r\n"
#define TURN_SIGNALS_OFF "12\r\n"
#define RIGHT_TURN_SIGNAL_ON "13\r\n"
#define PUMP_ON "14\r\n"
#define PUMP_OFF "15\r\n"

// RC CHANNELS
#define RESERVED_ALIERON 0
#define ACCELERATOR_BRAKE_CH 1
#define STEERING_CH 2

#define PUMP_STARTER_CH 4
#define RESERVER_3POS_SWITCH_SC 5
#define ARMING_CH 6
#define LIGHTS_CH 7

#define TRANSMISSION_LOWER_CH 10
#define TRANSMISSION_HIGHER_CH 11

// PWM OUTPUTS
// the nearest to USB out has id of 12
#define STEERING_PWM_OUT 0
#define ACCELERATOR_PWM_OUT 1
#define BRAKE_PWM_OUT 2
#define TRANSMISSION_PWM_OUT 3

static serialPort_t *buttons_usart_port;

// called only once
// FC was fully initialized by this moment
void firstTimeTaskCall(timeUs_t currentTimeUs)
{
	UNUSED(currentTimeUs);

	uint32_t dbg_id = *(uint32_t*)(0xE0042000); // DBG_ID / DBGMCU_IDCODE
    uint32_t device_id = *(uint32_t*)(0xE0042000) & 0xFFF; // device ID

    LOG_INFO(SYSTEM, "DEBUG ID (FULL): %lu (0x%08lX)", dbg_id, dbg_id);
    LOG_INFO(SYSTEM, "DEVICE ID: %lu (0x%03lX)", device_id, device_id);
    
    buttons_usart_port = openSerialPort(SERIAL_PORT_USART2, FUNCTION_LOG, NULL, NULL, 9600, MODE_TX, SERIAL_NOT_INVERTED);
}

bool armed = false;
uint32_t transmission_pwm_values[] = {1000, 1250, 1400, 1600, 1800};
uint8_t transmission_modes_count = sizeof(transmission_pwm_values) / sizeof(transmission_pwm_values[0]);

void regularTaskCall(timeUs_t currentTimeUs)
{
	UNUSED(currentTimeUs);
	
	// disable default inav servo processing
	setServoOutputEnabled(false);
	
	// disable default inav arming
	DISABLE_ARMING_FLAG(ARMED);
	
	// check if inav was armed
	// if (ARMING_FLAG(ARMED))
	
	// Handle ARMING
	if (rxGetChannelValue(ARMING_CH) > 1700)
	{
		// Разрешение управления бензонасосом и стартером
		if (rxGetChannelValue(PUMP_STARTER_CH) > 1700)
		{
			// Стартер включен, бензонасос включен
			serialWriteBuf(buttons_usart_port, IGNITION_PRESS, strlen(IGNITION_PRESS));
			serialWriteBuf(buttons_usart_port, PUMP_ON, strlen(PUMP_ON));
		}
		else if (rxGetChannelValue(PUMP_STARTER_CH) > 1300)
		{
			// Стартер выключен, бензонасос включен
			serialWriteBuf(buttons_usart_port, IGNITION_UNPRESS, strlen(IGNITION_UNPRESS));
			serialWriteBuf(buttons_usart_port, PUMP_ON, strlen(PUMP_ON));	
		}
		else
		{
			// Стартер выключен, бензонасос выключен
			serialWriteBuf(buttons_usart_port, IGNITION_UNPRESS, strlen(IGNITION_UNPRESS));
			serialWriteBuf(buttons_usart_port, PUMP_OFF, strlen(PUMP_OFF));
		}
		armed = true;
	}
	else if (rxGetChannelValue(ARMING_CH) > 1300)
	{
		// Можно управлять всем, кроме бензонасоса и стартера
		armed = true;
	}
	else
	{
		// Не управлять ничем
		armed = false;
	}
	
	// Handle Buttons Control
	// Handle headlights
	if (rxGetChannelValue(LIGHTS_CH) > 1700)
	{
		serialWriteBuf(buttons_usart_port, HEADLIGHTS_MODE_2, strlen(HEADLIGHTS_MODE_2));
	}
	else if (rxGetChannelValue(LIGHTS_CH) > 1300)
	{
		serialWriteBuf(buttons_usart_port, HEADLIGHTS_MODE_1, strlen(HEADLIGHTS_MODE_1));
	}
	else
	{
		// Turn headlights off
		serialWriteBuf(buttons_usart_port, HEADLIGHTS_OFF, strlen(HEADLIGHTS_OFF));
	}
	
	// Handle Motion Control (arming required)
	if (armed && rxIsReceivingSignal() && rxAreFlightChannelsValid())
	{
		// Steering
		pwmWriteServo(STEERING_PWM_OUT, rxGetChannelValue(STEERING_CH));
		
		// Accelerator & Brake
		if (rxGetChannelValue(ACCELERATOR_BRAKE_CH) > 1550)
		{
			pwmWriteServo(ACCELERATOR_PWM_OUT, (rxGetChannelValue(ACCELERATOR_BRAKE_CH) - 1550) * 2 + 1000);
			pwmWriteServo(BRAKE_PWM_OUT, 1000);
		}
		else if (rxGetChannelValue(ACCELERATOR_BRAKE_CH) < 1450)
		{
			pwmWriteServo(ACCELERATOR_PWM_OUT, 1000);
			pwmWriteServo(BRAKE_PWM_OUT, (1450 - rxGetChannelValue(ACCELERATOR_BRAKE_CH)) * 2 + 1000);
		}
		else
		{
			pwmWriteServo(ACCELERATOR_PWM_OUT, 1000);
			pwmWriteServo(BRAKE_PWM_OUT, 1000);
		}
		
		// Transmission
	}
	else
	{
		// управление полностью запрещено
		for (int i = 0; i < 13; i++)
		{
			pwmWriteServo(i, 0);
		}
	}
}

void targetTaskCall(timeUs_t currentTimeUs)
{
#ifdef USE_64BIT_TIME
    //LOG_DEBUG(SYSTEM, "Target task call, currentTimeUs: %llu", currentTimeUs);
#else
    //LOG_DEBUG(SYSTEM, "Target task call, currentTimeUs: %lu", currentTimeUs);
#endif

    if (!called)
    {
        called = 1;
        firstTimeTaskCall(currentTimeUs);
    }

    regularTaskCall(currentTimeUs);
}

#endif /* USE_TASK_TARGETTASK */
