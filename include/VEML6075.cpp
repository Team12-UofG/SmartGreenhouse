#include <stdio.h>
#include <cstdlib>
#include <wiringPi.h>
#include "VEML6075.h"

/**************************************************************************/
/*!
    @brief Sets up the wiringPi I2C comms to the VEML6075 device
*/
/**************************************************************************/
static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(VEML6075_DEVID);

UV_sensor::uvConfigure() {
  wiringPiI2CWriteReg8(fd,VEML6075_CONF_DEFAULT);
}

/**************************************************************************/
/*!
    @brief Constructor initializes default configuration value
*/
/**************************************************************************/
UV_sensor::UV_sensor() {
  setCoefficients(VEML6075_DEFAULT_UVA_A_COEFF, VEML6075_DEFAULT_UVA_B_COEFF,
		  VEML6075_DEFAULT_UVB_C_COEFF, VEML6075_DEFAULT_UVB_D_COEFF,
		  VEML6075_DEFAULT_UVA_RESPONSE, VEML6075_DEFAULT_UVB_RESPONSE);
}

/**************************************************************************/
/*!
    @brief Set the UVI calculation coefficients
    @param UVA_A  the UVA visible coefficient
    @param UVA_B  the UVA IR coefficient
    @param UVB_C  the UVB visible coefficient
    @param UVB_D  the UVB IR coefficient
    @param UVA_response the UVA responsivity
    @param UVB_response the UVB responsivity
*/
/**************************************************************************/
void UV_sensor::setCoefficients(float UVA_A, float UVA_B, float UVB_C, float UVB_D,
					float UVA_response, float UVB_response) {
  _uva_a = UVA_A;
  _uva_b = UVA_B;
  _uvb_c = UVB_C;
  _uvb_d = UVB_D;
  _uva_resp = UVA_response;
  _uvb_resp = UVB_response;
}

/**************************************************************************/
/*!
    @brief Perform a reading and calculated UV value
*/
/**************************************************************************/
void UV_sensor::takeReading() {

  float uva = wiringPiI2CReadReg8(fd, VEML6075_REG_UVA);
  float uvb = wiringPiI2CReadReg8(fd, VEML6075_REG_UVB);
  float uvcomp1 = wiringPiI2CReadReg8(fd, VEML6075_REG_UVCOMP1);
  float uvcomp2 = wiringPiI2CReadReg8(fd, VEML6075_REG_UVCOMP2);

  /*
  Serial.print("UVA: "); Serial.print(uva);
  Serial.print(" UVB: "); Serial.println(uvb);
  Serial.print("UVcomp1: "); Serial.print(uvcomp1);
  Serial.print(" UVcomp2: "); Serial.println(uvcomp2);
  */
  // Equation 1 & 2 in App note, without 'golden sample' calibration
  float _uva_calc = uva - (_uva_a * uvcomp1) - (_uva_b * uvcomp2);
  float _uvb_calc = uvb - (_uvb_c * uvcomp1) - (_uvb_d * uvcomp2);
  float _uvi_calc = ((_uva_calc * _uva_resp) + (_uvb_calc * _uvb_resp)) / 2;
}

/**************************************************************************/
/*!
    @brief  Read the calibrated UVA band reading
    @return the UVA reading in unitless counts
*/
/*************************************************************************/
float UV_sensor::readUVA(void) {
  takeReading();
  return _uva_calc;
}

/**************************************************************************/
/*!
    @brief  Read the calibrated UVB band reading
    @return the UVB reading in unitless counts
*/
/*************************************************************************/
float UV_sensor::readUVB(void) {
  takeReading();
  return _uvb_calc;
}

/**************************************************************************/
/*!
    @brief  read and calculate the approximate UV Index reading
    @return the UV Index as a floating point
*/
/**************************************************************************/
float UV_sensor::readUVI() {
  takeReading();
  return _uvi_calc;
}
