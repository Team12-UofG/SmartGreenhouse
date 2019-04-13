/**************************************************************************/
/*!
 *  @file SensorPump.cpp
 *  @author I. Mitchell
 *  @brief Soil moisture sensor is read and water pump is controlled using GPIO pins.
 *  @version 0.1
 *  @date 2019-04-11
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include <chrono>

#include "../../../include/Soil_sensor/MCP342X.h"
#include "../../../include/Soil_sensor/MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project.
 */
MCP342X soil_sensor;
using namespace std;
/** @brief Reset data configuration. */
int configData = 0;
/** @brief GPIO pin of water pump. */
int water_pump = 23;
/** @brief The soil moisture value at which the motor will turn on.*/
int dry_threshold = 60;


/*!
 * @brief Main progam configures the sensor and reads data from the soil
 * moisture sensor. If the reading falls below the threshold then the plant is
 * watered.
 * @param[in]  argc : Used in input arguement parser, determines output file
 * @param[in]  argv : Used input arguement parser, to specify output file

 */
int main(int argc, char** argv) {
  printf("Testing the soil moisture sensor and water pump together \n");
   configData = soil_sensor.configure();
   wiringPiSetup();
   pinMode (water_pump, OUTPUT); // Setup pin 22 (GPIO 6) as output pin

   soil_sensor.startConversion(configData); // Start conversion
   uint8_t result;
   result = soil_sensor.getResult(&result); // Read converted value

   if (result > dry_threshold){
     printf("Soil is too dry: %d. Water pump is turning on \n", result);
     digitalWrite(water_pump, HIGH);
     sleep(2);
     digitalWrite(water_pump, LOW);
     printf("Water pump is off \n");
   }

}
