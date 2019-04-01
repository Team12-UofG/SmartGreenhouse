/*
 * VEML6075.h
 *
 * Header for the Vishay VEML6075 UVA/UVB i2c sensor using the Vishay
 * VEML6075 application notes and Adafruit_VEML6075.h
 *
 * Author: Isla Mitchell
 *
 * @file Adafruit_VEML6075.h
 *
 * Designed specifically to work with the VEML6075 sensor from Adafruit
 * ----> https://www.adafruit.com/products/3964
 *
 * These sensors use I2C to communicate, 2 pins (SCL+SDA) are required
 * to interface with the breakout.
 *
 * Adafruit invests time and resources providing this open source code,
 * please support Adafruit and open-source hardware by purchasing
 * products from Adafruit!
 *
 * Written by Limor Fried/Ladyada for Adafruit Industries.
 *
 * MIT license, all text here must be included in any redistribution.
 *
 */

#ifndef _VEML6075_H
#define _VEML6075_H

/* Header includes */
#ifdef __KERNEL__
#include <linux/types.h>
#include <linux/kernel.h>
#else
#include <stdint.h>
#include <stddef.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wiringPi.h>
#endif

/* VEML6075 slave address */
#define VEML6075_ADDR                   (0x10) // I2C address
#define VEML6075_DEVID                  (0x26) // Manufacture ID

/* Register definitions */
#define VEML6075_CONF_REG               (0x00) // Configuration register
#define VEML6075_UVA_DATA_REG           (0x07) // UVA raw measurement register
#define VEML6075_REG_DUMMY              (0x08) // Dark current register
#define VEML6075_UVB_DATA_REG           (0x09) // UVB raw measurement register
#define VEML6075_UVCOMP1_DATA_REG       (0x0A) // Visible noise compensation register
#define VEML6075_UVCOMP2_DATA_REG       (0x0B) // IR noisecompensation register
#define VEML6075_ID_REG                 (0x0C) // Device ID register

/* Register value define : UV_CONF */
#define VEML6075_CONF_SD_OFF            (0x00) // Power up
#define VEML6075_CONF_SD_ON             (0x01) // Power down
#define VEML6075_CONF_UV_AF_AUTO        (0x00) // Active force mode disabled (default)
#define VEML6075_CONF_UV_AF_FORCE       (0x02) // Active force mode enabled
#define VEML6075_CONF_UV_TRIG_NO        (0x00) // No trigger
#define VEML6075_CONF_UV_TRIG_ONCE      (0x04) // Trigger measurement, clears by itself
#define VEML6075_CONF_HD                (0x08) // High dynamic setting
#define VEML6075_CONF_HD_OFF            (0x00) // Normal dynamic setting
#define VEML6075_CONF_UV_IT_MASK        (0x70) // Mask off other config bits or 0x8F
#define VEML6075_CONF_UV_IT_50MS        (0x00) // Integration time = 50ms
#define VEML6075_CONF_UV_IT_100MS       (0x10) // Integration time = 100ms (default)
#define VEML6075_CONF_UV_IT_200MS       (0x20) // Integration time = 200ms
#define VEML6075_CONF_UV_IT_400MS       (0x30) // Integration time = 400ms
#define VEML6075_CONF_UV_IT_800MS       (0x40) // Integration time = 800ms
#define VEML6075_CONF_DEFAULT           (VEML6075_CONF_UV_AF_AUTO | VEML6075_CONF_UV_TRIG_NO | VEML6075_CONF_UV_IT_100MS)

/* Definition of coefficients used to calculate UV Index */
#define VEML6075_DEFAULT_UVA_A_COEFF      2.22 // Default for no coverglass: "A"
#define VEML6075_DEFAULT_UVA_B_COEFF      1.33 // Default for no coverglass: "B"
#define VEML6075_DEFAULT_UVB_C_COEFF      2.95 // Default for no coverglass: "C"
#define VEML6075_DEFAULT_UVB_D_COEFF      1.74 // Default for no coverglass: "D"
#define VEML6075_DEFAULT_UVA_RESPONSE     0.001461 // Default for no coverglass
#define VEML6075_DEFAULT_UVB_RESPONSE     0.002591 // Default for no coverglass

enum veml6075_integrationtime {
  VEML6075_50MS, VEML6075_100MS, VEML6075_200MS, VEML6075_400MS,
  VEML6075_800MS
}

/**************************************************************************/
/*!
    @brief  Class that stores state and functions for interacting with VEML6075 sensor IC
*/
/**************************************************************************/
class UV_sensor {
 public:
  UV_sensor(); // VEML6075 becomes UV_sensor

  void setCoefficients(float UVA_A, float UVA_B, float UVA_C, float UVA_D,
		       float UVA_response, float UVB_response);

  void uvConfigure(void);

  float readUVA(void);
  float readUVB(void);
  float readUVI(void);

 private:
  float takeReading();

  uint16_t _read_delay;

  // coefficients
  float _uva_a, _uva_b, _uvb_c, _uvb_d, _uva_resp, _uvb_resp;
  float _uva_calc, _uvb_calc;
};

#endif
