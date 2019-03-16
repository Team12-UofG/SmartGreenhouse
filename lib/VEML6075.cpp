/*
 * VEML6075.cpp
 *
 * I2C communication with VEML6075, based on the example in the Vishay
 * Application Note
 *
 * Author: Isla Mitchell
 *
 */

# include <math.h>
# include <VEML6075.h>
# include <stdio.h>

void main(void)
{
    WORD VEML6075_conf;
    WORD uva_data;
    WORD uvb_data;
    WORD uvcomp1_data;

    /* Shut down VEML6075 */
    VEML6075_conf = VEML6075_CONF_DEFAULT | VEML6075_CONF_SD;
    VEML6075_write_word(VEML6075_ADDR, VEML6075_CONF_REG, VEML6075_conf);

    /* Enable VEML6075 */
    VEML6075_conf = VEML6075_CONF_DEFAULT;
    VEML6075_write_word(VEML6075_ADDR, VEML6075_CONF_REG, VEML6075_conf);

    /* Loop for polling VEML6075 data */
    while (1)
    {
      delay(150);

      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVA_DATA_REG, &uva_data
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVB_DATA_REG, &uvb_data
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVCOMP1_DATA_REG,
        &uvcomp1_data);
      VEML6075_read_word(VEML6075_ADDR, VEML6075_UVCOMP2_DATA_REG,
        &uvcomp2_data);

        float uva_
    }
}

int VEML6075_read_word(WORD addr, BYTE reg, WORD *val)
{
    int err = 0;
    int retry = 3;
    struct i2c_msg msg[2];
    BYTE data[2];
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
          *val = ((WORD)data[1] << 8) | (WORD)data[0];
          return err;
          }
        }
        return err;
      }


      int VEML6075_write_word(WORD addr, BYTE reg, WORD val) {
          int err = 0;
          int retry = 3;
          struct i2c_msg msg;
          BYTE data[3];

          while (retry--)
          {
            data[0] = reg;
            data[1] = (BYTE)(val & 0xFF);
            data[2] = (BYTE)((val & 0xFF00) >> 8);

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
