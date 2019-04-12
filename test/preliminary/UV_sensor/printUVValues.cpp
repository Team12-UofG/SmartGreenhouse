/**************************************************************************/
/*!
 *  @file printUVValues.cpp
 *  @author I. Mitchell
 *  @brief Prints the UVA, UVB and UVI reading from the VEML6075
 *  @version 0.1
 *  @date 2019-04-09
 *  @copyright Copyright (c) 2019
 *
*/
#include "../../../include/UV_sensor/VEML6075.h"
#include "../../../include/UV_sensor/VEML6075.cpp"
#include <chrono>
/*!
 * @brief UV sensor object.
 */
UV_sensor lightSensor; // create UV sensor object

/*!
 * @brief Main function for UV sensor test.
 */
int main (){

  printf("VEML6075 Simple Test \n");
  auto start1 = std::chrono::high_resolution_clock::now();
  lightSensor.uvConfigure(); // configure sensor
  auto finish1 = std::chrono::high_resolution_clock::now();

  std::chrono::duration<double> elapsed1 = finish1 - start1;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";


  auto start2 = std::chrono::high_resolution_clock::now();
  float UV_calc = lightSensor.readUVI(); // UV value - this is the output we want
  auto finish2 = std::chrono::high_resolution_clock::now();
  printf("UV Index reading: %f \n", UV_calc);
  std::chrono::duration<double> elapsed2 = finish2 - start2;
  std::cout << "Elapsed time: " << elapsed.count() << " s\n";
}
