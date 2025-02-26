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

#define USBD_PRODUCT_STRING	"StrizhFC"
#define USBD_SERIALNUMBER_STRING "0x8000000" // Start of Flash

#define USE_HARDWARE_REVISION_DETECTION
#define USE_HARDWARE_PREBOOT_SETUP

/* from src/main/scheduler/scheduler.h
typedef enum {
    TASK_PRIORITY_IDLE = 0,     // Disables dynamic scheduling, task is executed only if no other task is active this cycle
    TASK_PRIORITY_LOW = 1,
    TASK_PRIORITY_MEDIUM = 3,
    TASK_PRIORITY_MEDIUM_HIGH = 4,
    TASK_PRIORITY_HIGH = 5,
    TASK_PRIORITY_REALTIME = 18,
    TASK_PRIORITY_MAX = 255    // Can never be used
} cfTaskPriority_e;
*/

#define USE_TASK_TARGETTASK
#define TARGETTASK_PERIOD TASK_PERIOD_HZ(1)
#define TARGETTASK_PRIORITY TASK_PRIORITY_LOW

#define LED0			PG0
#define LED1			PG1

#define SENSORS_SET		(SENSOR_ACC|SENSOR_GYRO|SENSOR_MAG|SENSOR_BARO)

// *************** Gyro & ACC **********************
#define USE_SPI

#define USE_SPI_DEVICE_1
#define SPI1_SCK_PIN		PA5
#define SPI1_MISO_PIN		PB4
#define SPI1_MOSI_PIN		PB5

#define USE_SPI_DEVICE_2
#define SPI2_SCK_PIN		PB10
#define SPI2_MISO_PIN		PC2
#define SPI2_MOSI_PIN		PC1

#define USE_IMU_BMI088
#define IMU_BMI088_ALIGN	CW0_DEG
#define BMI088_SPI_BUS		BUS_SPI1
#define BMI088_GYRO_CS_PIN	PG11
//#define BMI088_GYRO_EXTI_PIN	PG6 // not used
#define BMI088_ACC_CS_PIN	PA4
//#define BMI088_ACC_EXTI_PIN	PG8 // not used


#define USE_IMU_BMI270
#define IMU_BMI270_ALIGN	CW90_DEG_FLIP
#define BMI270_CS_PIN		PG8
#define BMI270_SPI_BUS		BUS_SPI1


// *************** Mag *****************************

#define USE_I2C
#define USE_I2C_DEVICE_2
#define I2C2_SCL		PF1
#define I2C2_SDA		PF0

#define DEFAULT_I2C_BUS		BUS_I2C2
#define EXTERNAL_I2C_BUS	BUS_I2C2
#define MAG_I2C_BUS		BUS_I2C2

/* ERRATA: SCL and SDA mixed up on QMC's side
#define USE_MAG
#define USE_MAG_QMC5883
#define QMC5883_I2C_BUS		BUS_I2C2
*/
#define USE_MAG_ALL

// *************** Baro ****************************

#define USE_BARO
#define BARO_I2C_BUS			BUS_I2C2
#define USE_BARO_ALL

#define USE_BARO_BMP388
#define BMP388_SPI_BUS			BUS_SPI1
#define BMP388_CS_PIN			PG10

// *************** UART ****************************
#define USE_VCP

#define USE_UART1
#define UART1_RX_PIN		PB7
#define UART1_TX_PIN		PB6

#define USE_UART2
#define UART2_RX_PIN		PA3
#define UART2_TX_PIN		PA2

#define USE_UART3
#define UART3_RX_PIN		PB11
#define UART3_TX_PIN		PD8

/* ERRATA: double TX pins PA0 and PC10
#define USE_UART4
#define UART4_RX_PIN		PA1
#define UART4_TX_PIN		PA0
*/

#define USE_UART5
#define UART5_RX_PIN		PD2
#define UART5_TX_PIN		PC12

/* ERRATA: NO TX pin ON PG15, PG14 should be used
#define USE_UART6
#define UART6_RX_PIN		PG9
#define UART6_TX_PIN		PG14
*/

#define SERIAL_PORT_COUNT	5

// *************** OSD *****************************

#define USE_OSD
#define USE_MAX7456
#define MAX7456_SPI_BUS	BUS_SPI2
#define MAX7456_CS_PIN	PF2

// *************** ADC *****************************
#define USE_ADC
#define ADC_INSTANCE			ADC3

#define ADC_CHANNEL_1_PIN		PF6
#define ADC_CHANNEL_2_PIN		PF5
#define VBAT_ADC_CHANNEL		ADC_CHN_1
#define CURRENT_METER_ADC_CHANNEL	ADC_CHN_2

#define VBAT_SCALE_DEFAULT      1100
#define CURRENT_METER_SCALE     5

// ************** PINIO ****************************
#define USE_PINIO
#define USE_PINIOBOX
#define PINIO1_PIN		PE0
#define PINIO2_PIN		PE1
#define PINIO3_PIN		PE2
#define PINIO4_PIN		PE3

// ************** SDIO *****************************
#define USE_SDCARD
#define USE_SDCARD_SDIO
#define SDCARD_SDIO_DMA		DMA_TAG(2,3,4)
#define SDCARD_SDIO_4BIT
#define ENABLE_BLACKBOX_LOGGING_ON_SDCARD_BY_DEFAULT

#define DEFAULT_FEATURES	(FEATURE_VBAT|FEATURE_TELEMETRY|FEATURE_CURRENT_METER|FEATURE_BLACKBOX/*|FEATURE_OSD*/)

#define TARGET_IO_PORTA		0xffff
#define TARGET_IO_PORTB		0xffff
#define TARGET_IO_PORTC		0xffff
#define TARGET_IO_PORTD		0xffff
#define TARGET_IO_PORTE		0xffff
#define TARGET_IO_PORTF		0xffff
#define TARGET_IO_PORTG		0xffff

#define MAX_PWM_OUTPUT_PORTS	13
