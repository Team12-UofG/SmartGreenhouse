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
  wiringPiSetup():
  printf("Testing the outputs \n");
  pinMode(LED_panel1, OUTPUT);
  pinMode(LED_panel2, OUTPUT);
  //led_panel.configurePanel(LED_panel1, LED_panel2);  // configure LED panel

  printf("Turning the LED matrix ON \n");
  digitalWrite(LED_panel1, LOW);
  digitalWrite(LED_panel2, LOW);
  usleep(3000000);

  printf("Turning the LED matrix OFF \n");
  digitalWrite(LED_panel1, HIGH);
  digitalWrite(LED_panel2, HIGH);
  usleep(3000000);
}
