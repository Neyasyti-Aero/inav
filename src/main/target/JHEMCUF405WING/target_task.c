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

// Command - function (check ASCII table)
// 1 - Starter On
// 2 - Starter Off
// 3 - Headlights Mode 1
// 4 - Headlights Mode 2 (far)
// 5 - Headlights Off
// 6 - Headlights Mode 3
// 7 - Horn 0.5 sec
// 8 - 
// 9 - Black curok szadi (turn on far headlights)
// 10 - Far headlights blink (turn off far headlights)
// 11 - left turn signal ON
// 12 - turn signals OFF
// 13 - right turn signal ON
// 14 - Pump - press
// 15 - Pump - unpress

#define IGNITION_PRESS "1"
#define IGNITION_UNPRESS "2"
#define HEADLIGHTS_MODE_1 "3"
#define HEADLIGHTS_MODE_2 "4"
#define HEADLIGHTS_OFF "5"
#define HEADLIGHTS_MODE_3 "6"
#define HORN "7"
#define HEADLIGHTS_FAR_PRESS "9"
#define HEADLIGHTS_FAR_UNPRESS ":"
#define LEFT_TURN_SIGNAL_ON ";"
#define TURN_SIGNALS_OFF "<"
#define RIGHT_TURN_SIGNAL_ON "="
#define PUMP_ON ">"
#define PUMP_OFF "?"

// RC CHANNELS
#define RESERVED_ALIERON 0
#define ACCELERATOR_BRAKE_CH 1
#define STEERING_CH 2

#define PUMP_STARTER_CH 4
#define RESERVED_3POS_SWITCH_SC 5
#define ARMING_CH 6
#define LIGHTS_CH 7

#define TRANSMISSION_LOWER_CH 10
#define TRANSMISSION_HIGHER_CH 11

// PWM OUTPUTS
// the nearest to USB out has id of 12
#define STEERING_PWM_OUT 4
#define ACCELERATOR_PWM_OUT 5
#define BRAKE_PWM_OUT 6
#define TRANSMISSION_PWM_OUT 7

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
    
    buttons_usart_port = openSerialPort(SERIAL_PORT_USART3, FUNCTION_LOG, NULL, NULL, 9600, MODE_TX, SERIAL_NOT_INVERTED);
    
    // zero initial state
    for (int i = 0; i < 11; i++)
	{
		pwmWriteServo(i, 100);
	}
}

bool armed = false;

// parking, reverse, neutral, pov, pon
const uint32_t transmission_pwm_values[] = {950, 1200, 1400, 1600, 2000};
uint8_t transmission_modes_count = sizeof(transmission_pwm_values) / sizeof(transmission_pwm_values[0]);
int8_t transmission_current_gear = 0;
bool lower_button_pressed = false;
bool higher_button_pressed = false;

bool waseverrecieving = false;

void regularTaskCall(timeUs_t currentTimeUs)
{
	UNUSED(currentTimeUs);
	
	// disable default inav servo processing
	setServoOutputEnabled(false);
	
	// disable default inav arming
	DISABLE_ARMING_FLAG(ARMED);
	
	// check if inav was armed
	// if (ARMING_FLAG(ARMED))
	
	if (rxIsReceivingSignal() && rxAreFlightChannelsValid() && !waseverrecieving && rxGetChannelValue(ARMING_CH) < 1300)
	{
		waseverrecieving = true;
		
		// enable parking
		transmission_current_gear = 0;
		pwmWriteServo(TRANSMISSION_PWM_OUT, transmission_pwm_values[transmission_current_gear]);
	}
	
	// if never recieved => do nothing
	if (!waseverrecieving)
	{
		return;
	}
	
	// Here we are sure that Rx is OK or failsafe
	
	bool oldarmed = armed;
	
	// Handle ARMING
	if (rxGetChannelValue(ARMING_CH) > 1700)
	{
		// Starter and pump can be controlled
		if (rxGetChannelValue(PUMP_STARTER_CH) > 1700)
		{
			// Starter on, pump on
			serialWriteBuf(buttons_usart_port, IGNITION_PRESS, strlen(IGNITION_PRESS));
			serialWriteBuf(buttons_usart_port, PUMP_ON, strlen(PUMP_ON));
		}
		else if (rxGetChannelValue(PUMP_STARTER_CH) > 1300)
		{
			// Starter off, pump on
			serialWriteBuf(buttons_usart_port, IGNITION_UNPRESS, strlen(IGNITION_UNPRESS));
			serialWriteBuf(buttons_usart_port, PUMP_ON, strlen(PUMP_ON));	
		}
		else
		{
			// Starter off, pump off
			serialWriteBuf(buttons_usart_port, IGNITION_UNPRESS, strlen(IGNITION_UNPRESS));
			serialWriteBuf(buttons_usart_port, PUMP_OFF, strlen(PUMP_OFF));
		}
		armed = true;
	}
	else if (rxGetChannelValue(ARMING_CH) > 1300)
	{
		// everything except pump and starter can be controlled
		armed = true;
	}
	else
	{
		// do not control anything
		armed = false;
	}
	
	// armed right now - parking needed
	if (!oldarmed && armed)
	{
		// enable parking
		transmission_current_gear = 0;
		pwmWriteServo(TRANSMISSION_PWM_OUT, transmission_pwm_values[transmission_current_gear]);
	}
	
	// Handle Control (arming required)
	if (armed && rxIsReceivingSignal() && rxAreFlightChannelsValid())
	{
		// Handle Buttons Control
		// Handle headlights
		if (rxGetChannelValue(LIGHTS_CH) > 1700)
		{
			serialWriteBuf(buttons_usart_port, HEADLIGHTS_MODE_1, strlen(HEADLIGHTS_MODE_2));
		}
		else if (rxGetChannelValue(LIGHTS_CH) > 1300)
		{
			serialWriteBuf(buttons_usart_port, HEADLIGHTS_MODE_2, strlen(HEADLIGHTS_MODE_1));
		}
		else
		{
			// Turn headlights off
			serialWriteBuf(buttons_usart_port, HEADLIGHTS_OFF, strlen(HEADLIGHTS_OFF));
		}
	
		// Steering
		pwmWriteServo(STEERING_PWM_OUT, rxGetChannelValue(STEERING_CH));
		
		// Accelerator & Brake
		if (rxGetChannelValue(ACCELERATOR_BRAKE_CH) > 1550)
		{
			// calculate accel (proportional), spin brake to minimum
			pwmWriteServo(ACCELERATOR_PWM_OUT, 2000 - (rxGetChannelValue(ACCELERATOR_BRAKE_CH) - 1550) * 2);
			pwmWriteServo(BRAKE_PWM_OUT, 2000);
		}
		else if (rxGetChannelValue(ACCELERATOR_BRAKE_CH) < 1450)
		{
			// minimum accel, spin brake to maximum
			pwmWriteServo(ACCELERATOR_PWM_OUT, 2000);
			pwmWriteServo(BRAKE_PWM_OUT, 1000);
		}
		else
		{
			// minimum accel, do not spin brake
			pwmWriteServo(ACCELERATOR_PWM_OUT, 2000);
			pwmWriteServo(BRAKE_PWM_OUT, 1500);
		}
		
		// Transmission
		// allow hear switch only if acc < 1200
		if (rxGetChannelValue(ACCELERATOR_BRAKE_CH) < 1200)
		{
			if (higher_button_pressed && !lower_button_pressed && rxGetChannelValue(TRANSMISSION_LOWER_CH) < 1400 && rxGetChannelValue(TRANSMISSION_HIGHER_CH) < 1400)
			{
				// higher gear required
				transmission_current_gear++;
				if (transmission_current_gear > transmission_modes_count - 1)
					transmission_current_gear = transmission_modes_count - 1;
			
				pwmWriteServo(TRANSMISSION_PWM_OUT, transmission_pwm_values[transmission_current_gear]);
			}
			else if (lower_button_pressed && !higher_button_pressed && rxGetChannelValue(TRANSMISSION_LOWER_CH) < 1400 && rxGetChannelValue(TRANSMISSION_HIGHER_CH) < 1400)
			{
				// lower gear required
				transmission_current_gear--;
				if (transmission_current_gear < 0)
					transmission_current_gear = 0;
			
				pwmWriteServo(TRANSMISSION_PWM_OUT, transmission_pwm_values[transmission_current_gear]);
			}
			
			if (rxGetChannelValue(TRANSMISSION_LOWER_CH) > 1700 && rxGetChannelValue(TRANSMISSION_HIGHER_CH) < 1400)
			{
				lower_button_pressed = true;
				higher_button_pressed = false;
			}
			else if (rxGetChannelValue(TRANSMISSION_HIGHER_CH) > 1700 && rxGetChannelValue(TRANSMISSION_LOWER_CH) < 1400)
			{
				lower_button_pressed = false;
				higher_button_pressed = true;
			}
			else
			{
				lower_button_pressed = false;
				higher_button_pressed = false;
			}
		}
	}
	else if (!armed)
	{
		// fully prevent any control output
		for (int i = 0; i < 11; i++)
		{
			pwmWriteServo(i, 100);
		}
	}
	
	// lost signal
	if (waseverrecieving && !(rxIsReceivingSignal() && rxAreFlightChannelsValid()))
	{
		if (armed)
		{
			// failsafe - spin brake to maximum, minimum accel, stop ignition and pump
			pwmWriteServo(ACCELERATOR_PWM_OUT, 2000);
			pwmWriteServo(BRAKE_PWM_OUT, 1000);
			serialWriteBuf(buttons_usart_port, IGNITION_UNPRESS, strlen(IGNITION_UNPRESS));
			serialWriteBuf(buttons_usart_port, PUMP_OFF, strlen(PUMP_OFF));
		}
		else
		{
			// reset to initial state
			waseverrecieving = false;
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
