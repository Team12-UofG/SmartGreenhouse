/*
 * VEML6075.cpp
 *
 * I2C communication with VEML6075, based on the example in the Vishay
 * Application Note
 *
 * Author: Isla Mitchell
 *
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <linux/i2c.h>
#include <linux/i2c-dev.h>
#include <math.h>
#include "VEML6075.h"
#include <stdio.h>

int VEML6075_read_word(int addr, short reg, int *val)
{
    int err = 0;
    int retry = 3;
    struct i2c_msg msg[2];
    short data[2];
    while (retry--)
    {
        /* Send slave address & register */
        msg[0].addr = addr >> 1;
        msg[0].flags = I2C_M_WR;
        msg[0].len = 1;
        msg[0].buf = &reg;
        /* Read word data */
        msg[1].addr = addr >> 1;
        msg[1].flags = I2C_M_RD;
        msg[1].len = 2;
        msg[1].buf = data;

        err = i2c_transfer(msg, 2);

        if (err >= 0) {
          *val = ((int)data[1] << 8) | (int)data[0];
          return err;
          }
        }
        return err;
      }


int VEML6075_write_word(int addr, short reg, int val) {
          int err = 0;
          int retry = 3;
          struct i2c_msg msg;
          short data[3];

          while (retry--)
          {
            data[0] = reg;
            data[1] = (short)(val & 0xFF);
            data[2] = (short)((val & 0xFF00) >> 8);

            /* Send slave address, register and word data */
            msg.addr = addr >> 1;
            msg.flags = I2C_M_WR;
            msg.len = 3;
            msg.buf = data;

            err = i2c_transfer(msg, 1);

            if (err >= 0)
                  return 0;
      }
      return err;
    }

int main(void)
{
    int VEML6075_conf;
    int uva_data;
    int uvb_data;
    int uvcomp1_data;
    int uvcomp2_data;


    /* Shut down VEML6075 */
    VEML6075_conf = (VEML6075_CONF_DEFAULT | VEML6075_CONF_SD_ON);
    VEML6075_write_word(VEML6075_ADDR, VEML6075_CONF_REG, VEML6075_conf);

    /* Enable VEML6075 */
    VEML6075_conf = VEML6075_CONF_DEFAULT;
    VEML6075_write_word(VEML6075_ADDR, VEML6075_CONF_REG, VEML6075_conf);

    /* Loop for polling VEML6075 data */
    while (1)
    {
      //delay(150);

      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVA_DATA_REG, &uva_data);
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVB_DATA_REG, &uvb_data);
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVCOMP1_DATA_REG,
        &uvcomp1_data);
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVCOMP2_DATA_REG,
        &uvcomp2_data);

        float uva_;
    }
}
