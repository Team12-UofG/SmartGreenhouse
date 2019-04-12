/******************************************/
/*!
 *  @file printSoilValues.cpp
 *  @author I. Mitchell
 *  @brief Prints output sensor readings.
 *  @brief Test of soil mositure sensor with the sampling rate and sampling
 *    frequency set by the user. Samples the sensor and prints the values.
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include <time.h> // -lrt
#include <chrono>
#include "../../../include/Soil_sensor/MCP342X.h"
#include "../../../include/Soil_sensor/MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project.
 */
MCP342X soil_sensor;
using namespace std;

/*!
 * @brief Instantiate data configuration to zero.
 */
int configData = 0;

int readData();


/*!
 * @brief Main progam configures the sensor and calls function to read data from
 * the soil moisture sensor.
 * @param argc
 * @param argv
 */
int main(int argc, char** argv) {

  auto t1 = std::chrono::high_resolution_clock::now();

   configData = soil_sensor.configure();

   auto t2 = std::chrono::high_resolution_clock::now();

   std::chrono::duration<double> t = t2 - t1;
   std::cout << "Elapsed time: " << t.count() << " s\n";


   int counter = 0;

  // decode arguments
    if(argc < 3) {
        printf("You must provide at least two arguments \n First, the number of samples to take,\n then the delay (in sec) between each reading\n \n ");
        exit(0);
    }
    int c = atoi(argv[1]);

    // now we have the correct number of args
    int sleep_delay = atoi(argv[2]) * 1000 ; // convert to millisecs

  for (int i = 1; i < c; ++i)
  {
        // read the data. . .
        uint8_t result = readData();
        usleep(sleep_delay);
    }

}


/*!
 * @brief Function to read data from soil moisture sensor
 */
int readData() {

auto start = std::chrono::high_resolution_clock::now();



    uint8_t result;
    soil_sensor.startConversion(configData); // Start conversion
    result = soil_sensor.getResult(&result); // Read converted value

    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;
    std::cout << "Elapsed time: " << elapsed.count() << " s\n";

    printf("Result: %d \n", result);
    return 1;
}
