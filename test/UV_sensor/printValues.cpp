/**************************************************************************/
/*!
 *  @file printValues.cpp
 *  @author I. Mitchell
 *  @brief takes one reading of the soil moisture sensor and UV light UV_sensor
 * and prints the value
 *  @version 0.1
 *  @date 2019-04-07
 *  @copyright Copyright (c) 2019
 *
*/

#include "../../include/UV_sensor/VEML6075.h"
#include "../../include/UV_sensor/VEML6075.cpp"

UV_sensor lightSensor; // create sensor
int readData():


/*!
 * @brief main progam
 */
int main (){
  printf("UV light sensor Simple Test \n");
  lightSensor.uvConfigure(); // configure sensor
  
  int value = readData();
}


/*!
 * @brief Function to read data from UV light sensor and print the result
 */
int readData(){
  float UVA_calc = lightSensor.readUVA(); // additional
  float UVB_calc = lightSensor.readUVB(); // additional
  float UV_calc = lightSensor.readUVI(); // UV value - this is the desired output
  printf("UVA Index reading: %f \n", UVA_calc); 
  printf("UVB Index reading: %f \n", UVB_calc); 
  printf("UV Index reading: %f \n", UV_calc); 
  
  return 1;
}
