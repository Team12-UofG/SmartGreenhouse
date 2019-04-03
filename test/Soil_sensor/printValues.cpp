/**************************************************************************/
/*!
 *  @file printValues.cpp
 *  @author I. Mitchell
 *  @brief test of soil mositure sensor with the sampling rate and samplifng
 *    frequency set by the user. Samples the sensor and prints the values.
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
#include "../include/MCP342X.h"
#include "../include/MCP342X.cpp"

/*!
 * @brief Instantiate objects used in this project
 */
MCP342X myADC;
static int configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
using namespace std;

int readData();


/*!
 * @brief main progam configures the sensor and calls function to read data from
 * the soil moisture sensor
 */
int main(int argc, char** argv) {
  myADC.configure(MCP342X_MODE_CONTINUOUS, MCP342X_CHANNEL_1, MCP342X_SIZE_16BIT, MCP342X_GAIN_1X);

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
    myADC.startConversion(configData); // Start conversion
    result = myADC.getResult(&result); // Read converted value
    printf("Result: %d \n", result);
    return 1;
}
