/**************************************************************************/
/*!
 *  @file heatmatoff.cpp
 *  @author A. Saikia
 *  @brief Turns off heat mat.
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

/** @brief GPIO pin of heat mat. */
int heat_pad = 27;
/** @brief Main function. */
int main (){
  wiringPiSetup();
  pinMode(heat_pad, OUTPUT);
  digitalWrite(heat_pad, LOW);
 }
