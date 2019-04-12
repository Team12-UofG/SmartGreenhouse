/**************************************************************************/
/*!
 *  @file readall.cpp
 *  @author Isla Mitchell
 *  @brief Takes one reading of the soil moisture sensor and UV light UV_sensor
 *   and prints the value.
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
#include <thread>
#include "../../include/Soil_sensor/MCP342X.h"
#include "../../include/Soil_sensor/MCP342X.cpp"
#include "../../include/UV_sensor/VEML6075.h"
#include "../../include/UV_sensor/VEML6075.cpp"

using namespace std;
/*!
 * @brief Instantiate objects used in this project.
 */
MCP342X soilSensor;
UV_sensor lightSensor; // create sensor

/*!
 * @brief Initialise variables to be used
 */
int Soil_configData = 0;
int water_pump = 23;
int LED_pin = 26;

int dry_threshold = 60;
int UV_threshold = 3;
int temp_threshold = 15;
/*!
 * @brief Funxtions to read the sensors
 */
int checkSoil();
int checkUV();

/*!
 * @brief Main progam.
 */
int main (){

  printf("Reading the soil moisture sensor and UV light sensor \n");
  lightSensor.uvConfigure(); // configure sensor
  Soil_configData = soilSensor.configure();

  wiringPiSetup();
  pinMode (water_pump, OUTPUT); // Setup pin 22 (GPIO 6) as output pin

  while(1){
  std::thread soil (checkSoil);
  std::thread light (checkUV);

  soil.join();
  light.join();
  }
}

/*!
 * @brief Function to read data from soil moisture sensor and check against threshold
 */

int checkSoil() {
  uint8_t soilData = 0;
  soilSensor.startConversion(Soil_configData); // Start conversion
  soilData = soilSensor.checkforResult(&soilData); // Read converted value
  printf("Soil reading = %d \n", soilData);

  if(soilData < dry_threshold){
    digitalWrite(water_pump, HIGH);
    sleep(5);
  }

  return 1;
}

/*!
 * @brief Function to read data from UV sensor and check against the threshold
 */
int checkUV() {
  float UV_calc = 0;
  UV_calc = lightSensor.readUVI();  // Read converted value
  printf("UV Index reading: %f \n", UV_calc);

  if(UV_calc < UV_threshold){
    digitalWrite(LED_pin, HIGH);
  }
  else {
    digitalWrite(LED_pin, LOW);
  }
  return 1;
}



/*
void foo()
{
  // do stuff...
}

void bar(int x)
{
  // do stuff...
}

int main()
{
  std::thread first (foo);     // spawn new thread that calls foo()
  std::thread second (bar,0);  // spawn new thread that calls bar(0)

  std::cout << "main, foo and bar now execute concurrently...\n";

  // synchronize threads:
  first.join();                // pauses until first finishes
  second.join();               // pauses until second finishes

  std::cout << "foo and bar completed.\n";

  return 0;
}
*/
