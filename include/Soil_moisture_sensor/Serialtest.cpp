// Include libraries this sketch will use
#include <wiringPi.h>
#include <wiringPiI2C.h>
#include <stdio.h>
#include "MCP342X.h"

// Instantiate objects used in this project
MCP342X myADC;

int main() {
  printf("Starting up\n\n");

  configData = myADC.configure(MCP342X_MODE_CONTINUOUS, MCP342X_CHANNEL_1, MCP342X_SIZE_16BIT, MCP342X_GAIN_1X);

  while(1){
  static int16_t  result;
  myADC.startConversion(configData);
  myADC.getResult(&result); // conversion takes 63568us
  printf("%d \n", result);
  }
}
