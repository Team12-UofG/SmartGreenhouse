#include <stdio.h>
#include <cstdlib>
#include "VEML6075v2.h"

/**************************************************************************/
/*!
    @brief constructor initializes default configuration value
*/
/**************************************************************************/
UV_sensor::UV_sensor() {
  setCoefficients(VEML6075_DEFAULT_UVA_A_COEFF, VEML6075_DEFAULT_UVA_B_COEFF,
		  VEML6075_DEFAULT_UVB_C_COEFF, VEML6075_DEFAULT_UVB_D_COEFF,
		  VEML6075_DEFAULT_UVA_RESPONSE, VEML6075_DEFAULT_UVB_RESPONSE);

  _commandRegister.reg = 0;
}

/**************************************************************************/
/*!
    @brief  setup and initialize communication with the hardware
    @param itime The integration time to use for the data. Defaults to 100ms
    @param forcedReads True for triggered read, false for continuous (default)
    @param highDynamic Whether to read in normal or high dynamic mode - defaults to normal
    @param twoWire Optional pointer to the desired TwoWire I2C object. Defaults to &Wire
    @returns True if sensor found, false if sensor not detected
*/
/**************************************************************************/
boolean ::begin(veml6075_integrationtime_t itime, bool highDynamic,
				 bool forcedReads, TwoWire *theWire) {
  i2c_dev = new veml6075_I2CDevice(VEML6075_ADDR, theWire);

  if (!i2c_dev->begin()) {
    return false;
  }

  veml6075_I2CRegister ID_Register = veml6075_I2CRegister(i2c_dev, VEML6075_REG_ID, 2);
  uint16_t id;

  if (! ID_Register.read(&id) ) {
    return false;
  }
  if (id != 0x26) {
    return false;
  }

  Config_Register = new veml6075_I2CRegister(i2c_dev, VEML6075_REG_CONF, 2);
  // Start from scratch
  _commandRegister.reg = 0;

  shutdown(true);  // Shut down to change settings

  // Force readings
  setForcedMode(forcedReads);

  // Set integration time
  setIntegrationTime(itime);

  // Set high dynamic
  setHighDynamic(highDynamic);

  shutdown(false); // Re-enable

  return true;
}


/**************************************************************************/
/*!
    @brief Set the UVI calculation coefficients, see datasheet for some example values. We use the default "no cover glass" values if none are specified when initializing the sensor.
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
    @brief Shut down the sensor
    @param sd True if you want to shut down, false to enable
*/
/**************************************************************************/
void UV_sensor::shutdown(bool sd) {
  _commandRegister.bit.SD = sd;
  Config_Register->write(_commandRegister.reg);
}


/**************************************************************************/
/*!
    @brief Set the time over which we sample UV data per read
    @param itime How many milliseconds to integrate over
*/
/**************************************************************************/
void UV_sensor::setIntegrationTime(veml6075_integrationtime_t itime) {
  // Set integration time
  _commandRegister.bit.UV_IT = (uint8_t)itime;
  Config_Register->write(_commandRegister.reg);

  _read_delay = 0;
  switch (itime) {
    case VEML6075_50MS: _read_delay = 50; break;
    case VEML6075_100MS: _read_delay = 100; break;
    case VEML6075_200MS: _read_delay = 200; break;
    case VEML6075_400MS: _read_delay = 400; break;
    case VEML6075_800MS: _read_delay = 800; break;
  }
}

/**************************************************************************/
/*!
    @brief Get the time over which we sample UV data per read from the sensor
    @returns How many milliseconds to integrate over
*/
/**************************************************************************/
veml6075_integrationtime_t UV_sensor::getIntegrationTime(void) {
  // Get register
  Config_Register->read(&_commandRegister.reg);

  // extract and return just the integration time
  return (veml6075_integrationtime_t)_commandRegister.bit.UV_IT;
}

/**************************************************************************/
/*!
    @brief Sets whether to take readings in 'high dynamic' mode
    @param hd True if you want high dynamic readings, False for normal dynamic
*/
/**************************************************************************/
void UV_sensor::setHighDynamic(bool hd) {
  // Set HD mode
  _commandRegister.bit.UV_HD = hd;
  Config_Register->write(_commandRegister.reg);
}

/**************************************************************************/
/*!
    @brief Gets whether to take readings in 'high dynamic' mode
    @returns True if set to high dynamic readings, False for normal dynamic
*/
/**************************************************************************/
bool UV_sensor::getHighDynamic(void) {
  // Get register
  Config_Register->read(&_commandRegister.reg);

  // extract and return just the HD setting
  return _commandRegister.bit.UV_HD;
}


/**************************************************************************/
/*!
    @brief Sets whether to take readings on request
    @param flag True if you want readings on request, False for continuous reads
*/
/**************************************************************************/
void UV_sensor::setForcedMode(bool flag) {
  // Set forced mode
  _commandRegister.bit.UV_AF = flag;
  Config_Register->write(_commandRegister.reg);
}

/**************************************************************************/
/*!
    @brief Gets whether to take readings on request
    @returns True if readings on request, False for continuous reads
*/
/**************************************************************************/
bool UV_sensor::getForcedMode(void) {
  // Get register
  Config_Register->read(&_commandRegister.reg);

  // extract and return just the AF setting
  return _commandRegister.bit.UV_AF;
}


/**************************************************************************/
/*!
    @brief  Perform a full reading and calculation of all UV calibrated values
*/
/**************************************************************************/
void UV_sensor::takeReading(void) {

  if (getForcedMode()) {
    // trigger one reading
    _commandRegister.bit.UV_TRIG = 1;
    Config_Register->write(_commandRegister.reg);

    // Wait until we're done, add 10% just to be sure
    delay(_read_delay * 1.1);
    //Serial.print("Delay (ms): "); Serial.println(_read_delay);
  }
  // otherwise, just take the reading immediately

  veml6075_I2CRegister UVA_Register = veml6075_I2CRegister(i2c_dev, VEML6075_REG_UVA, 2);
  veml6075_I2CRegister UVB_Register = veml6075_I2CRegister(i2c_dev, VEML6075_REG_UVB, 2);
  veml6075_I2CRegister UVCOMP1_Register = veml6075_I2CRegister(i2c_dev, VEML6075_REG_UVCOMP1, 2);
  veml6075_I2CRegister UVCOMP2_Register = veml6075_I2CRegister(i2c_dev, VEML6075_REG_UVCOMP2, 2);
  float uva = UVA_Register.read();
  float uvb = UVB_Register.read();
  float uvcomp1 = UVCOMP1_Register.read();
  float uvcomp2 = UVCOMP2_Register.read();

  /*
  Serial.print("UVA: "); Serial.print(uva);
  Serial.print(" UVB: "); Serial.println(uvb);
  Serial.print("UVcomp1: "); Serial.print(uvcomp1);
  Serial.print(" UVcomp2: "); Serial.println(uvcomp2);
  */
  // Equasion 1 & 2 in App note, without 'golden sample' calibration
  _uva_calc = uva - (_uva_a * uvcomp1) - (_uva_b * uvcomp2);
  _uvb_calc = uvb - (_uvb_c * uvcomp1) - (_uvb_d * uvcomp2);
}


/**************************************************************************/
/*!
    @brief  read the calibrated UVA band reading
    @return the UVA reading in unitless counts
*/
/*************************************************************************/
float UV_sensor::readUVA(void) {
  takeReading();
  return _uva_calc;
}

/**************************************************************************/
/*!
    @brief  read the calibrated UVB band reading
    @return the UVB reading in unitless counts
*/
/*************************************************************************/
float UV_sensor::readUVB(void) {
  takeReading();
  return _uvb_calc;
}

/**************************************************************************/
/*!
    @brief  Read and calculate the approximate UV Index reading
    @return the UV Index as a floating point
*/
/**************************************************************************/
float UV_sensor::readUVI() {
  takeReading();
  return ((_uva_calc * _uva_resp) + (_uvb_calc * _uvb_resp)) / 2;
}
