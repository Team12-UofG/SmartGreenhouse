#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include <chrono>
#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile


int main(int argc, char** argv) {
  auto start = std::chrono::high_resolution_clock::now();
  int configData = soil_sensor.configure();
  wiringPiSetup();
  pinMode (6, OUTPUT); // Setup pin 22 (GPIO 6) as output pin
  digitalWrite(6, HIGH);
  auto finish = std::chrono::high_resolution_clock::now();
}
