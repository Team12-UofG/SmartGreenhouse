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

int LEDs = 26;
int heat_pad  = 27;
int water_pump = 23;

int main (){
  wiringPiSetup();
  printf("Testing the outputs \n");
  pinMode(heat_pad, OUTPUT);
  pinMode(water_pump, OUTPUT);
  pinMode(LEDs, OUTPUT);

  printf("Turning the LEDs ON \n");
  digitalWrite(LEDs, HIGH);
  sleep(3);

  printf("Turning the LEDs ON \n");
  digitalWrite(LEDs, LOW);

  printf("Turning the HEAT PAD ON \n");
  digitalWrite(heat_pad, HIGH);
  sleep(5);

  printf("Turning the HEAD PAD OFF \n");
  digitalWrite(heat_pad, LOW);
  sleep(1);


  printf("Turning the PUMP ON \n");
  digitalWrite(water_pump, HIGH);
  sleep(1);

  printf("Turning the PUMP OFF \n");
  digitalWrite(water_pump, LOW);
}
