/**************************************************************************/
/*!
 *  @file Soiltest.cpp
 *  @author Isla Mitchell
 *  @brief Takes one reading of the soil moisture sensor and prints the value.
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
#include "../../../include/Soil_sensor/MCP342X.h"
#include "../../../include/Soil_sensor//MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project.
 */
MCP342X soil_sensor;

/*!
 * @brief Read in data.
 */
int readData();

/*!
 * @brief Configure the data.
 */
int configData;

/*!
 * @brief Main progam.
 */
int main() {
  configData = soil_sensor.configure();
  uint8_t value = readData();
}

/*!
 * @brief Function to read data from soil moisture sensor.
 */
int readData() {
    uint8_t result;
    soil_sensor.startConversion(configData); // Start conversion
    result = soil_sensor.getResult(&result); // Read converted value
    printf("Result: %d \n", result);
    return 1;
}
