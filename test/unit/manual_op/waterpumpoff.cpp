/**************************************************************************/
/*!
 *  @file waterpumpoff.cpp
 *  @author A. Saikia
 *  @brief turns water pump off
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

int water_pump = 23;
int main (){
  wiringPiSetup();
}
