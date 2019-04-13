/**************************************************************************/

/*!
 *  @file ledoff.cpp
 *  @author A. Saikia
 *  @brief Turns off the LED matrix.
 *  @version 0.1
 *  @date 2019-04-12
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>

/** @brief GPIO pin of LED panels. */
int LEDs = 26;
/** Main function. */
int main (){
  wiringPiSetup();
  pinMode(LEDs, OUTPUT);
  digitalWrite(LEDs, LOW);
}
