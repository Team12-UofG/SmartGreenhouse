/**************************************************************************/
/*!
 *  @file heatmat.cpp
 *  @author A. Saikia
 *  @brief turns on heat mat
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

int heat_pad = 27;
int main (){
  wiringPiSetup();
  pinMode(heat_pad, OUTPUT);
  digitalWrite(heat_pad, HIGH);
 }
