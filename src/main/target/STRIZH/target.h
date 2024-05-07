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

#define TARGET_BOARD_IDENTIFIER	"STZH"

#define USBD_PRODUCT_STRING		"STRIZH"

#define LED0                    PC14
#define LED1                    PC15

#define SENSORS_SET				(SENSOR_ACC|SENSOR_GYRO|SENSOR_MAG|SENSOR_BARO)

// *************** Gyro & ACC **********************
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN            PB3
#define SPI1_MISO_PIN           PB4
#define SPI1_MOSI_PIN           PB5


#define USE_IMU_BMI088
#define IMU_BMI088_ALIGN        CW0_DEG
#define BMI088_SPI_BUS          BUS_SPI1
#define BMI088_GYRO_CS_PIN      PF12
#define BMI088_GYRO_EXTI_PIN    PG6
#define BMI088_ACC_CS_PIN       PF13
#define BMI088_ACC_EXTI_PIN     PG8


#define USE_IMU_BMI270
#define IMU_BMI270_ALIGN        CW0_DEG
#define BMI270_CS_PIN           PF10
#define BMI270_SPI_BUS          BUS_SPI1


// *************** Mag *****************************

#define USE_I2C
#define USE_I2C_DEVICE_2
#define I2C2_SCL                PF1
#define I2C2_SDA                PF0

#define DEFAULT_I2C_BUS         BUS_I2C2
#define EXTERNAL_I2C_BUS		BUS_I2C2
#define MAG_I2C_BUS				BUS_I2C2

#define USE_MAG
#define USE_MAG_QMC5883
#define QMC5883_I2C_BUS         BUS_I2C2
#define USE_MAG_ALL

// *************** Baro ****************************

#define USE_BARO
#define BARO_I2C_BUS			BUS_I2C2
#define USE_BARO_ALL

#define USE_BARO_BMP388
#define BMP388_SPI_BUS			BUS_SPI1
#define BMP388_CS_PIN			PF11

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
#define ADC_INSTANCE			ADC1
#define ADC1_DMA_STREAM			DMA2_Stream0
#define ADC_CHANNEL_1_PIN		PC5
#define VBAT_ADC_CHANNEL		ADC_CHN_1

#define DEFAULT_FEATURES		(FEATURE_VBAT|FEATURE_TELEMETRY)

#define TARGET_IO_PORTA         0xffff
#define TARGET_IO_PORTB         0xffff
#define TARGET_IO_PORTC         0xffff
#define TARGET_IO_PORTD         0xffff
#define TARGET_IO_PORTE         0xffff
#define TARGET_IO_PORTF         0xffff
#define TARGET_IO_PORTG         0xffff

#define USE_ESC_SENSOR

#define MAX_PWM_OUTPUT_PORTS	13
