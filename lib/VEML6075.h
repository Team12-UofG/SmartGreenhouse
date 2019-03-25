/*
 * VEML6075.h
 *
 * Header for the Vishay VEML6075 UVA/UVB i2c sensor using the Vishay
 * VEML6075 application notes
 *
 * Author: Isla Mitchell
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
#include <math.h>
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

/* I2C message, used for I2C transaction */
struct i2c_msg {
  int addr;
  int flags;
#define I2C_M_TEN                       0x0010
#define I2C_M_RD                        0x0001
#define I2C_M_NOSTART                   0x4000
#define I2C_M_REV_DIR_ADDR              0x2000
#define I2C_M_IGNORE_NAK                0x1000
#define I2C_M_NO_RD_ACK                 0x0800
#define I2C_M_RECV_LEN                  0x0400
  int len;
  short *buf;
};

extern int i2c_transfer(struct i2c_msg *msgs, int num);

#endif
