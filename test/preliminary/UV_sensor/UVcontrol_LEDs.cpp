/**************************************************************************/
/*!
 *  @file UVcontrol_LEDs.cpp
 *  @author I. Mitchell
 *  @brief Calculates the UV Index from the VEML6075, if below the threshold of
 *   '2' then the LED growth matrix will be illuminated.
 *  @version 0.1
 *  @date 2019-04-09
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include "../../../include/UV_sensor/VEML6075.h"
#include "../../../include/UV_sensor/VEML6075.cpp"

LED_matrix led_panel;   // create LED matrix panel object

int LED_pin = 26;       // GPIO 27 is pin 32
int UVI_threshold = 3;  // This is the UVI value at which the LEDs will turn on

int main (){

  printf("UV Sensor with LED matrix test \n");
  wiringPiSetup();
  pinmode(LED_pin, OUTPUT);

  float UV_calc = lightSensor.readUVI(); // UV value
  if (UV_calc < UVI_threshold) {
    printf("UV Index is too low: %f . Turning LED Growth Matrix on \n", UV_calc);
    digitalWrite(LED_pin, HIGH);
  }
  else {
    led_panel.off();
    printf("UV Index is %f \n", UV_calc);
    digitalWrite(LED_pin, LOW);
  }
}
