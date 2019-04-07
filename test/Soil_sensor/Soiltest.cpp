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
#include "../../include/Soil_sensor/MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project
 */
MCP342X soilSensor;
static int configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);

int readData();

/*!
 * @brief main progam
 */
int main() {
  soilSensor.configure(MCP342X_MODE_CONTINUOUS, MCP342X_CHANNEL_1, MCP342X_SIZE_16BIT, MCP342X_GAIN_1X);
  uint8_t value = readData();
}

/*!
 * @brief function to read data from soil moisture sensor
 */
int readData() {
    uint8_t result;
    soilSensor.startConversion(configData); // Start conversion
    result = soilSensor.getResult(&result); // Read converted value
    printf("Result: %d \n", result);
    return 1;
}
