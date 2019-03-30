// Include libraries this sketch will use
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>

// Instantiate objects used in this project
static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(0x68);

int main() {
  printf("Starting up\n\n");
  while(1){

  int result;
  result = wiringPiI2CRead(fd);
  printf("%d \n", result);
  }
}
