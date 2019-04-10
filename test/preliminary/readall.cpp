/**************************************************************************/
/*!
 *  @file readall.cpp
 *  @author Isla Mitchell
 *  @brief Takes one reading of the soil moisture sensor and UV light UV_sensor
 * and prints the value.
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
 * @brief Instantiate objects used in this project.
 */
MCP342X soilSensor;
int Soil_configData = 0;
<<<<<<< HEAD
=======

>>>>>>> master
UV_sensor lightSensor; // create sensor
int readData();

/*!
 * @brief Main progam.
 */
int main (){

  printf("Simple Test \n");
  lightSensor.uvConfigure(); // configure sensor
<<<<<<< HEAD
=======

>>>>>>> master
  Soil_configData = soilSensor.configure();
  uint8_t value = readData();
}

/*!
 * @brief Function to read data from soil moisture and UV light sensor.
 */
int readData() {
    uint8_t result;
    soilSensor.startConversion(Soil_configData); // Start conversion
    result = soilSensor.getResult(&result); // Read converted value
    printf("Soil moisture reading: %d \n", result);

    float UV_calc = lightSensor.readUVI(); // UV value - this is the output we want
    printf("UV Index reading: %f \n", UV_calc);

    return 1;
}
