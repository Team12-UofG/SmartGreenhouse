/**************************************************************************/
/*!
 *  @file Soiltest.cpp
 *  @author I. Mitchell
 *  @brief takes one reading of the soil moisture sensor and prints the value
 *  @version 0.1
 *  @date 2019-04-03
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include "../../include/Soil_sensor/MCP342X.h"
#include "../../include/Soil_sensor//MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project
 */
MCP342X soil_sensor;
int readData();

/*!
 * @brief main progam
 */
int main() {
  int configData = soil_sensor.configure();
  uint8_t value = readData();
}

/*!
 * @brief function to read data from soil moisture sensor
 */
int readData() {
    uint8_t result;
    soil_sensor.startConversion(configData); // Start conversion
    result = soil_sensor.getResult(&result); // Read converted value
    printf("Result: %d \n", result);
    return 1;
}
