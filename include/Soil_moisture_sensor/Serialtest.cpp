// Include libraries this sketch will use
#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream> // add "-lstdc++" to compile
#include <unistd.h>

#include "MCP342X.h"
#include "MCP342X.cpp"

// Instantiate objects used in this project
MCP342X myADC;
static int configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
using namespace std;

int readData();

int main(int argc, char** argv) {
  printf("Starting up\n\n");
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

int readData() {
    // add the sensor stuff here
    uint8_t result;
    myADC.startConversion(configData);
    printf("Result:");
    result = myADC.getResult(&result); // conversion takes 63568us
    printf("%d \n", result);
    return 1;
}
