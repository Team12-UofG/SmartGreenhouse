/**************************************************************************/
/*!
    @file     MCP342X.cpp
    @author   C. Schnarel, I. Mitchell
		@license  BSD (see license.txt)

    This is part of an Arduino library to interface with the Microchip
    MCP47X6 series of Analog-to-Digital converters which are connected
    via the I2C bus.

    MCP342X I2C device class
    Based on Microchip datasheets for the following part numbers
        MCP3421, MCP3422, MCP3423, MCP3424, MCP3425, MCP3426, MCP3427, MCP3428
    These parts share a common programming interface

    (c) Copyright 2013 by Chip Schnarel <schnarel@hotmail.com>
    Updates should (hopefully) always be available at
        https://github.com/uchip/MCP342X

	@section  HISTORY

    2013-Dec-24  - First release, C. Schnarel
		2019-Apr-01  - Second release, I. Mitchell
*/
/**************************************************************************/

#include "MCP342X.h"

/**************************************************************************/
/*!
    @brief Sets up the wiringPi I2C comms to the MCP3426 device
*/
/**************************************************************************/
static int setupI2C_MCP3426 = wiringPiSetup();
static int fd_soil = wiringPiI2CSetup(MCP342X_DEFAULT_ADDRESS);

/******************************************
 *!
 * @brief  Default constructor, uses default I2C address.
 * @see MCP342X_DEFAULT_ADDRESS
 */
MCP342X::MCP342X() {
    devAddr = MCP342X_DEFAULT_ADDRESS;
}

/******************************************
 *!
 * @brief Specific address constructor.
 * @param address I2C address
 * @see MCP342X_DEFAULT_ADDRESS
 * @see MCP342X_A0GND_A1GND, etc.
 */
MCP342X::MCP342X(uint8_t address) {
    devAddr = address;
}

/******************************************
 *!
 * @brief Set the configuration shadow register
 */
uint8_t MCP342X::configure(uint16_t mode, uint16_t channel, uint16_t size, uint16_t gain) {
	wiringPiI2CWrite(fd_soil, mode);
  wiringPiI2CWrite(fd_soil, channel);
  wiringPiI2CWrite(fd_soil, size);
  wiringPiI2CWrite(fd_soil, gain);
	configData = (mode | channel | size | gain);
  return configData;
}

/******************************************
*!
* @brief Start a conversion using configuration settings from
 *   the shadow configuration register
 */
bool MCP342X::startConversion(uint8_t configData) {
  wiringPiI2CWriteReg8(fd_soil, configData, MCP342X_RDY);
}

/******************************************
*!
* @brief Read the conversion value (12, 14 or 16 bit)
 *  Spins reading status until ready then
 *  fills in the supplied location with the 16-bit (two byte)
 *  conversion value and returns the status byte
 *  Note: status of -1 "0xFF' implies read error
 */
uint8_t MCP342X::getResult(uint8_t *dataPtr) {
	uint8_t adcStatus;
	adcStatus = wiringPiI2CRead(fd_soil);

  return adcStatus;
}


/******************************************
*!
* @brief Check to see if the conversion value (12, 14 or 16 bit)
 *  is available.  If so, then
 *  fill in the supplied location with the 16-bit (two byte)
 *  conversion value and status the config byte
 *  Note: status of -1 "0xFF' implies read error
 */
uint8_t MCP342X::checkforResult(uint8_t *dataPtr) {
  uint8_t adcStatus;

	adcStatus = wiringPiI2CRead(fd_soil);

  return adcStatus;
}
