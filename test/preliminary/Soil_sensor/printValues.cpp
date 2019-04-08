/******************************************/
/*!
 *  @file printValues.cpp
 *
 *
 *  @brief Test of soil mositure sensor with the sampling rate and sampling frequency set by the user. Samples the sensor and prints the values.
 *  @author Isla Mitchell
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
#include "../../../include/MCP342X.h"
#include "../../../include/MCP342X.cpp"

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
   configData = soil_sensor.configure();

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
    uint8_t result;
    soil_sensor.startConversion(configData); // Start conversion
    result = soil_sensor.getResult(&result); // Read converted value
    printf("Result: %d \n", result);
    return 1;
}
