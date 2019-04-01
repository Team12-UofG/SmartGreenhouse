#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

#define MCP342X_MODE_CONTINUOUS 0x10
#define MCP342X_CHANNEL_1      0x00
#define MCP342X_SIZE_16BIT     0x08
#define MCP342X_GAIN_1X        0x00
#define MCP342X_RDY	0x80

static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(0x68);

using namespace std;

int readData();

int main(int argc, char** argv) {

  printf("Starting up\n\n");
  printf("Configuring...\n\n");
  wiringPiI2CWrite(fd,MCP342X_MODE_CONTINUOUS);
  wiringPiI2CWrite(fd,MCP342X_CHANNEL_1);
  wiringPiI2CWrite(fd,MCP342X_SIZE_16BIT);
  wiringPiI2CWrite(fd,MCP342X_GAIN_1X);

  int configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
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
        cout << "in the loop\n";

        // read the data. . .
        int ret = readData();

        usleep(sleep_delay);
    }

}

  int readData() {

      // add the sensor stuff here
      int result;
      wiringPiI2CWriteReg8(fd, configData, MCP342X_RDY);

      printf("Result:");
      result = wiringPiI2CRead(fd);
      printf("%d \n", result);
      return 1;
  }
