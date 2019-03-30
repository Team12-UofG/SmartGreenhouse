// Include libraries this sketch will use
#include <wiringPi.h>
#include <stdio.h>
#include "MCP342X.h"

// Instantiate objects used in this project
MCP342X myADC;

int main() {
  printf("Starting up\n\n");

  myADC.configure(MCP342X_MODE_CONTINUOUS, MCP342X_CHANNEL_1, MCP342X_SIZE_16BIT, MCP342X_GAIN_1X);
  while(1){
  static int16_t  result;
  myADC.startConversion();
  myADC.getResult(&result); // conversion takes 63568us
  printf("%d \n", result);
  }
}
