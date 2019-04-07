/**************************************************************************/
/*!
 *  @file readall.cpp
 *  @author I. Mitchell
 *  @brief takes one reading of the soil moisture sensor and UV light UV_sensor
 * and prints the value
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
#include "../../include/Soil_sensor/MCP342X.h"
#include "../../include/Soil_sensor/MCP342X.cpp"
#include "../../include/UV_sensor/VEML6075.h"
#include "../../include/UV_sensor/VEML6075.cpp"

/*!
 * @brief Instantiate objects used in this project
 */
MCP342X soilSensor;
static int Soil_configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
UV_sensor lightSensor; // create sensor
int readData();

/*!
 * @brief main progam
 */
int main (){

  printf("Simple Test \n");
  lightSensor.uvConfigure(); // configure sensor

  soilSensor.configure(MCP342X_MODE_CONTINUOUS, MCP342X_CHANNEL_1, MCP342X_SIZE_16BIT, MCP342X_GAIN_1X);
  uint8_t value = readData();
}

/*!
 * @brief function to read data from soil moisture and UV light sensor
 */
int readData() {
    uint8_t result;
    soilSensor.startConversion(configData); // Start conversion
    result = soilSensor.getResult(&result); // Read converted value
    printf("Soil moisture reading: %d \n", result);

    float UV_calc = lightSensor.readUVI(); // UV value - this is the output we want
    printf("UV Index reading: %f \n", UV_calc);

    return 1;
}
