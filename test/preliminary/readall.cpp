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
int readData();
int sample_no = 100;

/*!
 * @brief Main progam.
 */
int main (){

  printf("Reading the soil moisture sensor and UV light sensor \n");
  lightSensor.uvConfigure(); // configure sensor
  Soil_configData = soilSensor.configure();
  uint8_t value = readData();
}

/*!
 * @brief Function to read data from soil moisture sensor and average 100 samples
 */
int readData() {
  uint8_t soilSum = 0;
  float UVsum = 0;
    for(int i=0;i<sample_no;i++){
      int soilData = 0;
      soilSensor.startConversion(Soil_configData); // Start conversion
      soilData = soilSensor.getResult(&soilData); // Read converted value
      soilSum += soilData;
      printf("Soil Sum = %d \n", soilSum);
    }

    int averageSoil = soilSum / sample_no;
    printf("Average soil moisture reading: %d \n", averageSoil);

    for(int i=0;i<sample_no;i++){
      float UV_calc = 0;
      UV_calc = lightSensor.readUVI();  // Read converted value
      UVsum += UV_calc;
    }

    float averageUV = UVsum / sample_no;
    printf("Average UV Index reading: %f \n", averageUV);

    return 1;
}
