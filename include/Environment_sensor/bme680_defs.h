/**
 * Copyright (C) 2017 - 2018 Bosch Sensortec GmbH
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the distribution.
 *
 * Neither the name of the copyright holder nor the names of the
 * contributors may be used to endorse or promote products derived from
 * this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND
 * CONTRIBUTORS "AS IS" AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDER
 * OR CONTRIBUTORS BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY,
 * OR CONSEQUENTIAL DAMAGES(INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE
 *
 * The information provided is believed to be accurate and reliable.
 * The copyright holder assumes no responsibility
 * for the consequences of use
 * of such information nor for any infringement of patents or
 * other rights of third parties which may result from its use.
 * No license is granted by implication or otherwise under any patent or
 * patent rights of the copyright holder.
 *
 * @file	bme680_defs.h
 * @date	19 Jun 2018
 * @version	3.5.9
 * @brief 	Definitions for BME680 sensor.
 */

/*! @file bme680_defs.h
    @brief Definitions for BME680 sensor. 
*/
/*!
 * @defgroup BME680 SENSOR API
 * @brief Sensor API for BME680 environment sensor.
 * @{*/
#ifndef BME680_DEFS_H_
#define BME680_DEFS_H_

/********************************************************/
/* header includes */
#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/kernel.h>
#else
#include <stdint.h>
#include <stddef.h>
#endif

///@{
/******************************************************************************/
/*! @brief Common macros.					      */
/******************************************************************************/

#if !defined(UINT8_C) && !defined(INT8_C)
/*! @brief Common macros.					      */
#define INT8_C(x)       S8_C(x)
/*! @brief Common macros.					      */
#define UINT8_C(x)      U8_C(x)
#endif

#if !defined(UINT16_C) && !defined(INT16_C)
/*! @brief Common macros.					      */
#define INT16_C(x)      S16_C(x)
/*! @brief Common macros.					      */
#define UINT16_C(x)     U16_C(x)
#endif

#if !defined(INT32_C) && !defined(UINT32_C)
/*! @brief Common macros.					      */
#define INT32_C(x)      S32_C(x)
/*! @brief Common macros.					      */
#define UINT32_C(x)     U32_C(x)
#endif

#if !defined(INT64_C) && !defined(UINT64_C)
/*! @brief Common macros.					      */
#define INT64_C(x)      S64_C(x)
/*! @brief Common macros.					      */
#define UINT64_C(x)     U64_C(x)
#endif
///@}

/**@}*/


#ifndef NULL
#ifdef __cplusplus
#define NULL   0
#else
/** @brief C standard macros */
#define NULL   ((void *) 0)
#endif
#endif


/** BME680 configuration macros. */
/** Enable or un-comment the macro to provide floating point data output. */
#ifndef BME680_FLOAT_POINT_COMPENSATION
/* #define BME680_FLOAT_POINT_COMPENSATION */
#endif


/** @brief BME680 General configuration. */
#define BME680_POLL_PERIOD_MS		UINT8_C(10)

/**
 * @brief BME680 I2C addresses.
 */
#define BME680_I2C_ADDR_PRIMARY		UINT8_C(0x76)
/**
 * @brief BME680 I2C addresses.
 */
#define BME680_I2C_ADDR_SECONDARY	UINT8_C(0x77)

/** @brief BME680 unique chip identifier. */
#define BME680_CHIP_ID  UINT8_C(0x61)

/** @brief BME680 coefficients related defines. */
#define BME680_COEFF_SIZE		UINT8_C(41)
/** @brief BME680 coefficients related defines. */
#define BME680_COEFF_ADDR1_LEN		UINT8_C(25)
/** @brief BME680 coefficients related defines. */
#define BME680_COEFF_ADDR2_LEN		UINT8_C(16)


/** @brief BME680 field_x related defines. */
#define BME680_FIELD_LENGTH		UINT8_C(15)
/** @brief BME680 field_x related defines. */
#define BME680_FIELD_ADDR_OFFSET	UINT8_C(17)


/** @brief Soft reset command. */
#define BME680_SOFT_RESET_CMD   UINT8_C(0xb6)

/** @brief Error code definitions. */
#define BME680_OK		INT8_C(0)

/** @brief Error. */
#define BME680_E_NULL_PTR		    INT8_C(-1)
/** @brief Error. */
#define BME680_E_COM_FAIL		    INT8_C(-2)
/** @brief Error. */
#define BME680_E_DEV_NOT_FOUND		INT8_C(-3)
/** @brief Error. */
#define BME680_E_INVALID_LENGTH		INT8_C(-4)


/** @brief Warning. */
#define BME680_W_DEFINE_PWR_MODE	INT8_C(1)
/** @brief Warning. */
#define BME680_W_NO_NEW_DATA        INT8_C(2)

/** @brief Info's. */
#define BME680_I_MIN_CORRECTION		UINT8_C(1)
/** @brief Info's. */
#define BME680_I_MAX_CORRECTION		UINT8_C(2)

/**  @brief Register map other coefficient's address. */
#define BME680_ADDR_RES_HEAT_VAL_ADDR	UINT8_C(0x00)
/**  @brief Register map other coefficient's address. */
#define BME680_ADDR_RES_HEAT_RANGE_ADDR	UINT8_C(0x02)
/**  @brief Register map other coefficient's address. */
#define BME680_ADDR_RANGE_SW_ERR_ADDR	UINT8_C(0x04)
/**  @brief Register map other coefficient's address. */
#define BME680_ADDR_SENS_CONF_START	UINT8_C(0x5A)
/**  @brief Register map other coefficient's address. */
#define BME680_ADDR_GAS_CONF_START	UINT8_C(0x64)

/** @brief Field settings. */
#define BME680_FIELD0_ADDR		UINT8_C(0x1d)

/** @brief Heater settings. */
#define BME680_RES_HEAT0_ADDR		UINT8_C(0x5a)
/** @brief Heater settings. */
#define BME680_GAS_WAIT0_ADDR		UINT8_C(0x64)

/** @brief Sensor configuration registers. */
#define BME680_CONF_HEAT_CTRL_ADDR		UINT8_C(0x70)
/** @brief Sensor configuration registers. */
#define BME680_CONF_ODR_RUN_GAS_NBC_ADDR	UINT8_C(0x71)
/** @brief Sensor configuration registers. */
#define BME680_CONF_OS_H_ADDR			UINT8_C(0x72)
/** @brief Sensor configuration registers. */
#define BME680_MEM_PAGE_ADDR			UINT8_C(0xf3)
/** @brief Sensor configuration registers. */
#define BME680_CONF_T_P_MODE_ADDR		UINT8_C(0x74)
/** @brief Sensor configuration registers. */
#define BME680_CONF_ODR_FILT_ADDR		UINT8_C(0x75)

/** @brief Coefficient's address. */
#define BME680_COEFF_ADDR1	UINT8_C(0x89)
/** @brief Coefficient's address. */
#define BME680_COEFF_ADDR2	UINT8_C(0xe1)


/** @brief Chip identifier. */
#define BME680_CHIP_ID_ADDR	UINT8_C(0xd0)

/** @brief Soft reset register. */
#define BME680_SOFT_RESET_ADDR		UINT8_C(0xe0)

/** @brief Heater control settings. */
#define BME680_ENABLE_HEATER		UINT8_C(0x00)
/** @brief Heater control settings. */
#define BME680_DISABLE_HEATER		UINT8_C(0x08)

/** @brief Gas measurement settings. */
#define BME680_DISABLE_GAS_MEAS		UINT8_C(0x00)
/** @brief Gas measurement settings. */
#define BME680_ENABLE_GAS_MEAS		UINT8_C(0x01)


/** @brief Over-sampling settings. */
#define BME680_OS_NONE		UINT8_C(0)
/** @brief Over-sampling settings. */
#define BME680_OS_1X		UINT8_C(1)
/** @brief Over-sampling settings. */
#define BME680_OS_2X		UINT8_C(2)
/** @brief Over-sampling settings. */
#define BME680_OS_4X		UINT8_C(3)
/** @brief Over-sampling settings. */
#define BME680_OS_8X		UINT8_C(4)
/** @brief Over-sampling settings. */
#define BME680_OS_16X		UINT8_C(5)

/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_0	UINT8_C(0)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_1	UINT8_C(1)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_3	UINT8_C(2)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_7	UINT8_C(3)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_15	UINT8_C(4)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_31	UINT8_C(5)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_63	UINT8_C(6)
/** @brief IIR filter settings. */
#define BME680_FILTER_SIZE_127	UINT8_C(7)

/** @brief Power mode settings. */
#define BME680_SLEEP_MODE	UINT8_C(0)
/** @brief Power mode settings. */
#define BME680_FORCED_MODE	UINT8_C(1)

/** @brief Delay related macro declaration. */
#define BME680_RESET_PERIOD	UINT32_C(10)

/** @brief SPI memory page settings. */
#define BME680_MEM_PAGE0	UINT8_C(0x10)
/** @brief SPI memory page settings. */
#define BME680_MEM_PAGE1	UINT8_C(0x00)


/** @brief Ambient humidity shift value for compensation. */
#define BME680_HUM_REG_SHIFT_VAL	UINT8_C(4)

/** @brief Run gas enable and disable settings. */
#define BME680_RUN_GAS_DISABLE	UINT8_C(0)
/** @brief Run gas enable and disable settings. */
#define BME680_RUN_GAS_ENABLE	UINT8_C(1)


/** @brief Buffer length macro declaration. */
#define BME680_TMP_BUFFER_LENGTH	UINT8_C(40)
/** @brief Buffer length macro declaration. */
#define BME680_REG_BUFFER_LENGTH	UINT8_C(6)
/** @brief Buffer length macro declaration. */
#define BME680_FIELD_DATA_LENGTH	UINT8_C(3)
/** @brief Buffer length macro declaration. */
#define BME680_GAS_REG_BUF_LENGTH	UINT8_C(20)


/** @brief Settings selector. */
#define BME680_OST_SEL			UINT16_C(1)
/** @brief Settings selector. */
#define BME680_OSP_SEL			UINT16_C(2)
/** @brief Settings selector. */
#define BME680_OSH_SEL			UINT16_C(4)
/** @brief Settings selector. */
#define BME680_GAS_MEAS_SEL		UINT16_C(8)
/** @brief Settings selector. */
#define BME680_FILTER_SEL		UINT16_C(16)
/** @brief Settings selector. */
#define BME680_HCNTRL_SEL		UINT16_C(32)
/** @brief Settings selector. */
#define BME680_RUN_GAS_SEL		UINT16_C(64)
/** @brief Settings selector. */
#define BME680_NBCONV_SEL		UINT16_C(128)
/** @brief Settings selector. 
* @param[in] BME680_GAS_MEAS_SEL : Settings selector for gas measurement
* @param[in] BME680_RUN_GAS_SEL : Settings selector for running the gas sensor
* @param[in] BME680_NBCONV_SEL : Settings selector for number of conversions
*/
#define BME680_GAS_SENSOR_SEL		(BME680_GAS_MEAS_SEL | BME680_RUN_GAS_SEL | BME680_NBCONV_SEL)

/** @brief Number of conversion settings. */
#define BME680_NBCONV_MIN		UINT8_C(0)
/** @brief Number of conversion settings. */
#define BME680_NBCONV_MAX		UINT8_C(10)

/** @brief Mask definitions. */
#define BME680_GAS_MEAS_MSK	UINT8_C(0x30)
/** @brief Mask definitions. */
#define BME680_NBCONV_MSK	UINT8_C(0X0F)
/** @brief Mask definitions. */
#define BME680_FILTER_MSK	UINT8_C(0X1C)
/** @brief Mask definitions. */
#define BME680_OST_MSK		UINT8_C(0XE0)
/** @brief Mask definitions. */
#define BME680_OSP_MSK		UINT8_C(0X1C)
/** @brief Mask definitions. */
#define BME680_OSH_MSK		UINT8_C(0X07)
/** @brief Mask definitions. */
#define BME680_HCTRL_MSK	UINT8_C(0x08)
/** @brief Mask definitions. */
#define BME680_RUN_GAS_MSK	UINT8_C(0x10)
/** @brief Mask definitions. */
#define BME680_MODE_MSK		UINT8_C(0x03)
/** @brief Mask definitions. */
#define BME680_RHRANGE_MSK	UINT8_C(0x30)
/** @brief Mask definitions. */
#define BME680_RSERROR_MSK	UINT8_C(0xf0)
/** @brief Mask definitions. */
#define BME680_NEW_DATA_MSK	UINT8_C(0x80)
/** @brief Mask definitions. */
#define BME680_GAS_INDEX_MSK	UINT8_C(0x0f)
/** @brief Mask definitions. */
#define BME680_GAS_RANGE_MSK	UINT8_C(0x0f)
/** @brief Mask definitions. */
#define BME680_GASM_VALID_MSK	UINT8_C(0x20)
/** @brief Mask definitions. */
#define BME680_HEAT_STAB_MSK	UINT8_C(0x10)
/** @brief Mask definitions. */
#define BME680_MEM_PAGE_MSK	UINT8_C(0x10)
/** @brief Mask definitions. */
#define BME680_SPI_RD_MSK	UINT8_C(0x80)
/** @brief Mask definitions. */
#define BME680_SPI_WR_MSK	UINT8_C(0x7f)
/** @brief Mask definitions. */
#define	BME680_BIT_H1_DATA_MSK	UINT8_C(0x0F)

/** @brief Bit position definitions for sensor settings. */
#define BME680_GAS_MEAS_POS	UINT8_C(4)
/** @brief Bit position definitions for sensor settings. */
#define BME680_FILTER_POS	UINT8_C(2)
/** @brief Bit position definitions for sensor settings. */
#define BME680_OST_POS		UINT8_C(5)
/** @brief Bit position definitions for sensor settings. */
#define BME680_OSP_POS		UINT8_C(2)
/** @brief Bit position definitions for sensor settings. */
#define BME680_RUN_GAS_POS	UINT8_C(4)

/** @brief Array index to Field data mapping for calibration data. */
#define BME680_T2_LSB_REG	(1)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_T2_MSB_REG	(2)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_T3_REG		(3)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P1_LSB_REG	(5)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P1_MSB_REG	(6)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P2_LSB_REG	(7)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P2_MSB_REG	(8)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P3_REG		(9)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P4_LSB_REG	(11)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P4_MSB_REG	(12)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P5_LSB_REG	(13)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P5_MSB_REG	(14)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P7_REG		(15)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P6_REG		(16)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P8_LSB_REG	(19)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P8_MSB_REG	(20)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P9_LSB_REG	(21)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P9_MSB_REG	(22)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_P10_REG		(23)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H2_MSB_REG	(25)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H2_LSB_REG	(26)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H1_LSB_REG	(26)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H1_MSB_REG	(27)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H3_REG		(28)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H4_REG		(29)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H5_REG		(30)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H6_REG		(31)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_H7_REG		(32)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_T1_LSB_REG	(33)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_T1_MSB_REG	(34)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_GH2_LSB_REG	(35)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_GH2_MSB_REG	(36)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_GH1_REG		(37)
/** @brief Array index to Field data mapping for calibration data. */
#define BME680_GH3_REG		(38)


/** @brief BME680 register buffer index settings. */
#define BME680_REG_FILTER_INDEX		UINT8_C(5)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_TEMP_INDEX		UINT8_C(4)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_PRES_INDEX		UINT8_C(4)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_HUM_INDEX		UINT8_C(2)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_NBCONV_INDEX		UINT8_C(1)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_RUN_GAS_INDEX	UINT8_C(1)
/** @brief BME680 register buffer index settings. */
#define BME680_REG_HCTRL_INDEX		UINT8_C(0)


/** @brief BME680 pressure calculation macros. */
/*! This maximum value is used to provide precedence to multiplication or division
 * in pressure compensation equation to achieve least loss of precision and
 * avoiding overflows.
 * i.e Comparing value, BME680_MAX_OVERFLOW_VAL = INT32_C(1 << 30)
 */
#define BME680_MAX_OVERFLOW_VAL      INT32_C(0x40000000)


/** @brief Macro to combine two 8 bit datas to form a 16 bit data. 
* @param[in] msb : Data
* @param[in] lsb : Data */
#define BME680_CONCAT_BYTES(msb, lsb)	(((uint16_t)msb << 8) | (uint16_t)lsb)


/** @brief Macro to SET BITS of a register. 
* @param[in] reg_data : Data array to read/write  
* @param[in] bitname : Identifier  
* @param[in] data : Structure instance to hold the data  
* @param[in] bitname ##_MSK : Mask identifier  
* param[in] bitname ##_POS : Position identifier  */
#define BME680_SET_BITS(reg_data, bitname, data) \
		((reg_data & ~(bitname##_MSK)) | \
		((data << bitname##_POS) & bitname##_MSK))
/** @brief Macro to GET BITS of a register. 
* @param[in] reg_data : Data array to read/write
* @param[in] bitname : Identifier
* @param[in] bitname ##_MSK : Mask identifier 
* param[in] bitname ##_POS : Position identifier */
#define BME680_GET_BITS(reg_data, bitname)	((reg_data & (bitname##_MSK)) >> \
	(bitname##_POS))


/** @brief Macro variant to set the bitname position if it is zero. 
* @param[in] reg_data : Data array to read/write
* @param[in] bitname : Identifier  
* @param[in] data : Structure instance to hold the data  
* @param[in] bitname ##_MSK : Mask identifier */
#define BME680_SET_BITS_POS_0(reg_data, bitname, data) \
				((reg_data & ~(bitname##_MSK)) | \
				(data & bitname##_MSK))

/** @brief Macro variant to get the bitname position if it is zero.
* @param[in] reg_data : Data array to read/write
* @param[in] bitname : Identifier
* @param[in] bitname ##_MSK : Mask identifier  */
#define BME680_GET_BITS_POS_0(reg_data, bitname)  (reg_data & (bitname##_MSK))

/** Type definitions. */
/*!
 * @brief Generic communication function pointer.
 * @param[in] dev_id : Place holder to store the ID of the device structure,
 *                    can be used to store the index of the chip select or
 *                    I2C address of the device
 * @param[in] reg_addr :	Used to select the register the where data needs to
 *                      be read from or written to
 * @param[in,out] reg_data : Data array to read/write
 * @param[in] len : Length of the data array
 */
typedef int8_t (*bme680_com_fptr_t)(uint8_t dev_id, uint8_t reg_addr, uint8_t *data, uint16_t len);

/*!
 * @brief Delay function pointer with given period.
 * @param[in] bme680_delay_fptr_t : Delay function pointer
 * @param[in] period : Time period in milliseconds
 */
typedef void (*bme680_delay_fptr_t)(uint32_t period);

/*!
 * @brief Interface selection enumerations.
 */
enum bme680_intf {
	/*! SPI interface */
	BME680_SPI_INTF,
	/*! I2C interface */
	BME680_I2C_INTF
};

/* structure definitions. */
/*!
 * @brief Sensor field data structure.
 */
struct	bme680_field_data {
	/*! Contains new_data, gasm_valid & heat_stab */
	uint8_t status;
	/*! The index of the heater profile used */
	uint8_t gas_index;
	/*! Measurement index to track order */
	uint8_t meas_index;

#ifndef BME680_FLOAT_POINT_COMPENSATION
	/*! Temperature in degree celsius x100 */
	int16_t temperature;
	/*! Pressure in Pascal */
	uint32_t pressure;
	/*! Humidity in % relative humidity x1000 */
	uint32_t humidity;
	/*! Gas resistance in Ohms */
	uint32_t gas_resistance;
#else
	/*! Temperature in degree celsius */
	float temperature;
	/*! Pressure in Pascal */
	float pressure;
	/*! Humidity in % relative humidity x1000 */
	float humidity;
	/*! Gas resistance in Ohms */
	float gas_resistance;

#endif

};

/*!
 * @brief Structure to hold the calibration data.
 */
struct	bme680_calib_data {
	/*! Variable to store calibrated humidity data */
	uint16_t par_h1;
	/*! Variable to store calibrated humidity data */
	uint16_t par_h2;
	/*! Variable to store calibrated humidity data */
	int8_t par_h3;
	/*! Variable to store calibrated humidity data */
	int8_t par_h4;
	/*! Variable to store calibrated humidity data */
	int8_t par_h5;
	/*! Variable to store calibrated humidity data */
	uint8_t par_h6;
	/*! Variable to store calibrated humidity data */
	int8_t par_h7;
	/*! Variable to store calibrated gas data */
	int8_t par_gh1;
	/*! Variable to store calibrated gas data */
	int16_t par_gh2;
	/*! Variable to store calibrated gas data */
	int8_t par_gh3;
	/*! Variable to store calibrated temperature data */
	uint16_t par_t1;
	/*! Variable to store calibrated temperature data */
	int16_t par_t2;
	/*! Variable to store calibrated temperature data */
	int8_t par_t3;
	/*! Variable to store calibrated pressure data */
	uint16_t par_p1;
	/*! Variable to store calibrated pressure data */
	int16_t par_p2;
	/*! Variable to store calibrated pressure data */
	int8_t par_p3;
	/*! Variable to store calibrated pressure data */
	int16_t par_p4;
	/*! Variable to store calibrated pressure data */
	int16_t par_p5;
	/*! Variable to store calibrated pressure data */
	int8_t par_p6;
	/*! Variable to store calibrated pressure data */
	int8_t par_p7;
	/*! Variable to store calibrated pressure data */
	int16_t par_p8;
	/*! Variable to store calibrated pressure data */
	int16_t par_p9;
	/*! Variable to store calibrated pressure data */
	uint8_t par_p10;

#ifndef BME680_FLOAT_POINT_COMPENSATION
	/*! Variable to store t_fine size */
	int32_t t_fine;
#else
	/*! Variable to store t_fine size */
	float t_fine;
#endif
	/*! Variable to store heater resistance range */
	uint8_t res_heat_range;
	/*! Variable to store heater resistance value */
	int8_t res_heat_val;
	/*! Variable to store error range */
	int8_t range_sw_err;
};

/*!
 * @brief BME680 sensor settings structure which comprises of ODR,
 * over-sampling and filter settings.
 */
struct	bme680_tph_sett {
	/*! Humidity oversampling */
	uint8_t os_hum;
	/*! Temperature oversampling */
	uint8_t os_temp;
	/*! Pressure oversampling */
	uint8_t os_pres;
	/*! Filter coefficient */
	uint8_t filter;
};

/*!
 * @brief BME680 gas sensor; which comprises of gas settings
 *  and status parameters.
 */
struct	bme680_gas_sett {
	/*! Variable to store nb conversion */
	uint8_t nb_conv;
	/*! Variable to store heater control */
	uint8_t heatr_ctrl;
	/*! Run gas enable value */
	uint8_t run_gas;
	/*! Heater temperature value */
	uint16_t heatr_temp;
	/*! Duration profile value */
	uint16_t heatr_dur;
};

/*!
 * @brief BME680 sensor device structure.
 */
struct	bme680_dev {
	/*! Chip Id */
	uint8_t chip_id;
	/*! Device Id */
	uint8_t dev_id;
	/*! SPI/I2C interface */
	enum bme680_intf intf;
	/*! Memory page used */
	uint8_t mem_page;
	/*! Ambient temperature in Degree C */
	int8_t amb_temp;
	/*! Sensor calibration data */
	struct bme680_calib_data calib;
	/*! Sensor settings */
	struct bme680_tph_sett tph_sett;
	/*! Gas Sensor settings */
	struct bme680_gas_sett gas_sett;
	/*! Sensor power modes */
	uint8_t power_mode;
	/*! New sensor fields */
	uint8_t new_fields;
	/*! Store the info messages */
	uint8_t info_msg;
	/*! Bus read function pointer */
	bme680_com_fptr_t read;
	/*! Bus write function pointer */
	bme680_com_fptr_t write;
	/*! delay function pointer */
	bme680_delay_fptr_t delay_ms;
	/*! Communication function result */
	int8_t com_rslt;
};



#endif /* BME680_DEFS_H_ */
/** @}*/
/** @}*/
