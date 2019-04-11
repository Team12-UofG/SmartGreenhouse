/**************************************************************************/
/*!
 *  @file SensorPump.cpp
 *  @author I. Mitchell
 *  @brief Soil moisture sensor is read and water pump is controlled using GPIO pins
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
 * @brief Instantiate objects used in this project
 */
MCP342X soil_sensor;
using namespace std;
int configData = 0;
int water_pump = 23;
int dry_threshold = 60;


/*!
 * @brief main progam configures the sensor and reads data from the soil
 * moisture sensor. If the reading falls below the threshold then the plant is
 * watered.
 */
int main(int argc, char** argv) {
  printf("Testing the soil moisture sensor and water pump together \n");
   configData = soil_sensor.configure();
   wiringPiSetup();
   pinMode (water_pump, OUTPUT); // Setup pin 22 (GPIO 6) as output pin

   soil_sensor.startConversion(configData); // Start conversion
   int result
   result = soil_sensor.getResult(&result); // Read converted value

   if (result > dry_threshold){
     printf("Soil is too dry, pump is turning on");
     digitalWrite(water_pump, HIGH);
     sleep(2);
     digitalWrite(water_pump, LOW);
     printf("Pump is off");
   }

}
