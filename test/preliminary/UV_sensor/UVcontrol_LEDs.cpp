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
#include "../../../include/UV_sensor/LEDMATRIX.h"
#include "../../../include/UV_sensor/LEDMATRIX.cpp"

UV_sensor lightSensor;  // create UV sensor object
LED_matrix led_panel;   // create LED matrix panel object

int LED_pin = 22;       // GPIO 22 is pin 29
int UVI_threshold = 3;  // This is the UVI value at which the LEDs will turn on

int main (){

  printf("UV Sensor with LED matrix test \n");
  lightSensor.uvConfigure();          // configure sensor
  led_panel.configurePanel(LED_pin);  // configure LED panel

  float UV_calc = lightSensor.readUVI(); // UV value
  if (UV_calc < UVI_threshold) {
    printf("UV Index is too low: %f . Turning LED Growth Matrix on \n", UV_calc);
    led_panel.on();
  }
  else {
    led_panel.off();
    printf("UV Index is %f \n", UV_calc);
  }
}
