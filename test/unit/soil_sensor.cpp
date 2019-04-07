/**************************************************************************/
/*!
 *  @file soil_sensor.cpp
 *  @author I. Mitchell
 *  @brief test for checking the  MCP3426 ADC class for the soil moisture
 *   sensor
 *  @version 0.1
 *  @date 2019-04-07
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include "../../../include/Soil_sensor/MCP342X.h"
#include "../../../include/Soil_sensor/MCP342X.cpp"

using namespace std;
int configData = 0;

/*!
 * @brief main progam will test the MCP3426 ADC class including:
 * testing the I2C connection to the ADC, configuring the ADC, starting a data
 * conversion and getting the results.
 */
int main() {

  MCP342X mcp3426;  // create ADC object

  // Test the connection to the ADC
	if(mcp3426.testConnection() < 0)
  {
		throw std::exception();		// exit if unconnected
	}

  // Check the coniguration data for the ADC is as expected
  configData = mcp3426.configure();
  if(configData = 24){
    mcp3426.startConversion(configData); // start a data conversion
  } else {
    printf("Error configuring ADC: ADC not configured \n");
    throw std::exception();
  }

  // Read the ADC result as blocking and non-blocking function
  uint8_t value_block = mcp3426.getResult(&value_block);
  uint8_t value_noblock = mcp3426.checkforResult(&value_noblock);

  // Check that both ADC read functions give the same value and that is value is sensible
  if(value_block != value_noblock){
    printf("Error reading ADC: Mismatch between blocking and non-blocking read \n");
    throw std::exception();
  }
  else if(0 < value_block < 65536) {
    printf("Result: %d \n", value_block);
  }
  else {
    printf("Error reading ADC: value out of range \n");
    throw std::exception();
  }

  printf("SUCCESS! All tests passed \n");
  return 1;
}
