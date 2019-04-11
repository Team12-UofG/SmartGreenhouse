/**************************************************************************/
/*!
 *  @file outputs.cpp
 *  @author I. Mitchell
 *  @brief turns each of the outputs on in turn to check connection
 *  @version 0.1
 *  @date 2019-04-11
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include "../../include/UV_sensor/LEDMATRIX.h"
#include "../../include/UV_sensor/LEDMATRIX.cpp"

LED_matrix led_panel;   // create LED matrix panel object

int LED_panel1 = 26;
int LED_panel2 = 27;
int heat_pad  = 29;
int water_pump = 23;

int main (){

  printf("Testing the outputs \n");
  led_panel.configurePanel(LED_panel1, LED_panel2);  // configure LED panel

  printf("Turning the LED matrix ON \n");
  led_panel.on();
  usleep(1000);

  printf("Turning the LED matrix OFF \n");
  led_panel.off();
  usleep(1000);
}
