/**************************************************************************/
/*!
 *  @file uv_sensor.cpp
 *  @author I. Mitchell
 *  @brief Test for checking the VEML6075 class for the UV light sensor.
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
#include "../../include/UV_sensor/VEML6075.h"
#include "../../include/UV_sensor/VEML6075.cpp"

using namespace std;
/*!
 * @brief Instantiate data configuration to zero.
 */
int configData = 0;

/*!
 * @brief Main progam will test the VEML6075 class including:
 * testing the I2C connection to the sensor, configuring the sensor,
 * and taking a reading.
 */
int main() {

  UV_sensor lightSensor; // create UV sensor object

  // Test the connection to the VEML6075
	if(lightSensor.testConnection() < 0)
  {
		throw std::exception();		// exit if unconnected
	}

  // Configure the VEML6075
  lightSensor.uvConfigure();


  // Take a UV reading from the VEML6075
  float UV_calc = lightSensor.readUVI();
  if(0 < UV_calc < 12) { // UV index range
    printf("UV reading: %f \n", UV_calc);
  }
  else if (-1 < UV_calc < 0){
    printf("No natural light. UV reading is %f \n", UV_calc);
  }
  else {
    printf("Error reading VEML6075");
    throw std::exception();
  }

  printf("SUCCESS! All tests passed \n");
  return 1;
}
