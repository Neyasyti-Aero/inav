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

#pragma once

#define TARGET_BOARD_IDENTIFIER "STZH"

#define USBD_PRODUCT_STRING  "STRIZH"

#define LED0                    PC14
#define LED1                    PC15

#define SENSORS_SET (SENSOR_ACC|SENSOR_GYRO)

// *************** Gyro & ACC **********************
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN            PB4
#define SPI1_MISO_PIN           PA5
#define SPI1_MOSI_PIN           PA6

#define USE_IMU_BMI160
#define IMU_BMI160_ALIGN        CW0_DEG
#define BMI160_SPI_BUS          BUS_SPI1
#define BMI160_CS_PIN			PF11

// *************** Mag *****************************
/*
#define USE_I2C
#define USE_I2C_DEVICE_1
#define I2C1_SCL                PB6
#define I2C1_SDA                PB7

#define DEFAULT_I2C_BUS         BUS_I2C1

#define USE_MAG
#define MAG_I2C_BUS             BUS_I2C1
#define USE_MAG_HMC5883*/


// *************** UART ****************************
/*#define USE_VCP
#define VBUS_SENSING_PIN        PA9
#define VBUS_SENSING_ENABLED*/

#define USE_UART1
#define UART1_RX_PIN            PB7
#define UART1_TX_PIN            PB6

#define USE_UART2
#define UART2_RX_PIN            PA3
#define UART2_TX_PIN            PA2

#define USE_UART3
#define UART3_RX_PIN            PC11
#define UART3_TX_PIN            PC10

#define USE_UART4
#define UART4_RX_PIN            PA1
#define UART4_TX_PIN            PA0

#define USE_UART5
#define UART5_RX_PIN            PD2
#define UART5_TX_PIN            PC12

#define SERIAL_PORT_COUNT       5

// *************** ADC *****************************
#define USE_ADC
#define ADC_INSTANCE                ADC1
#define ADC1_DMA_STREAM             DMA2_Stream0
#define ADC_CHANNEL_1_PIN           PC5
#define VBAT_ADC_CHANNEL            ADC_CHN_1

#define DEFAULT_FEATURES (FEATURE_VBAT | FEATURE_TELEMETRY)

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         0xffff
#define TARGET_IO_PORTE         0xffff
#define TARGET_IO_PORTF         0xffff

#define USE_ESC_SENSOR

#define MAX_PWM_OUTPUT_PORTS       13
