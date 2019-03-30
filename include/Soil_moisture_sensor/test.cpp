// Include libraries this sketch will use
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

#define CP342X_MODE_CONTINUOUS 0x10
#define MCP342X_CHANNEL_1      0x00
#define MCP342X_SIZE_16BIT     0x08
#define MCP342X_GAIN_1X        0x00
#define MCP342X_RDY	0x80

// Instantiate objects used in this project
static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(0x68);

int main() {
  printf("Starting up\n\n");

  printf("Configuring...\n\n");
  wiringPiI2CWrite(fd,CP342X_MODE_CONTINUOUS);
  wiringPiI2CWrite(fd,MCP342X_CHANNEL_1);
  wiringPiI2CWrite(fd,MCP342X_SIZE_16BIT);
  wiringPiI2CWrite(fd,MCP342X_GAIN_1X);

  int configData = (MCP342X_MODE_CONTINUOUS | MCP342X_CHANNEL_1 | MCP342X_SIZE_16BIT | MCP342X_GAIN_1X);
  while(1){
  int result;
  printf("Start conversion \n");
  wiringPiI2CWriteReg8(fd, configData, MCP342X_RDY);

  printf("Get result \n");
  result = wiringPiI2CRead(fd);
  printf("%d \n", result);
  }
}
