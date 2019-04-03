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

#define VEML6075_ADDR                   (0x10) // I2C address
#define VEML6075_DEVID                  (0x26) // Manufacture ID
#define VEML6075_CONF_UV_AF_AUTO        (0x00)
#define VEML6075_CONF_UV_TRIG_NO        (0x00) // No trigger
#define VEML6075_CONF_UV_IT_100MS       (0x10) // Integration time = 100ms (default)
#define VEML6075_CONF_DEFAULT           (VEML6075_CONF_UV_AF_AUTO | VEML6075_CONF_UV_TRIG_NO | VEML6075_CONF_UV_IT_100MS)

#define VEML6075_UVA_DATA_REG           (0x07) // UVA raw measurement register
#define VEML6075_UVB_DATA_REG           (0x09) // UVB raw measurement register
#define VEML6075_UVCOMP1_DATA_REG       (0x0A) // Visible noise compensation register
#define VEML6075_UVCOMP2_DATA_REG       (0x0B) // IR noisecompensation register

/* Definition of coefficients used to calculate UV Index */
float _uva_a = 2.22; // Default for no coverglass: "A"
float _uva_b = 1.33; // Default for no coverglass: "B"
float _uva_c = 2.95; // Default for no coverglass: "C"
float _uva_d = 1.74; // Default for no coverglass: "D"
float _uva_resp = 0.001461; // Default for no coverglass
float _uvb_resp = 0.002591; // Default for no coverglass

static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(VEML6075_ADDR);

int takeReading();

int main() {
  printf("Starting up\n\n");

  printf("Configuring...\n\n");
  wiringPiI2CWrite(fd,VEML6075_CONF_UV_AF_AUTO);
  wiringPiI2CWrite(fd,VEML6075_CONF_UV_TRIG_NO);
  wiringPiI2CWrite(fd,VEML6075_CONF_UV_IT_100MS);
  int configData = VEML6075_CONF_DEFAULT;

  printf("Get result \n");
  int result = takeReading();
}

int takeReading(){
  float uva = wiringPiI2CReadReg8(fd, VEML6075_UVA_DATA_REG, &uva);
  float uvb = wiringPiI2CReadReg8(fd, VEML6075_UVB_DATA_REG, &uvb);
  float uvcomp1 = wiringPiI2CReadReg8(fd, VEML6075_UVCOMP1_DATA_REG, &uvcomp1);
  float uvcomp2 = wiringPiI2CReadReg8(fd, VEML6075_UVCOMP2_DATA_REG, &uvcomp2);

  printf("UVA: %f ", uva);
  printf("UVB: %f ", uvb);
  printf("UVcomp1: %f ", uvcomp1);
  printf(" UVcomp2: %f \n", uvcomp2);

// Equation 1 & 2 in App note, without 'golden sample' calibration
  float _uva_calc = uva - (_uva_a * uvcomp1) - (_uva_b * uvcomp2);
  float _uvb_calc = uvb - (_uva_c * uvcomp1) - (_uva_d * uvcomp2);
  float _uvi_calc = ((_uva_calc * _uva_resp) + (_uvb_calc * _uvb_resp)) / 2;

  printf("UVA Index reading: %f \n", _uva_calc);
  printf("UVB Index reading: %f \n", _uvb_calc);
  printf("UV Index reading: %f \n", _uvi_calc);
  return 1;
}
