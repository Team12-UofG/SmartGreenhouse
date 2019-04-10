#include <stdio.h>
#include <cstdlib>
#include <wiringPi.h>
#include <wiringPiI2C.h>

/**************************************************************************/
/*!
    @brief Sets up the wiringPi to communicate with GPIO pins
*/
/**************************************************************************/
static int setup_ledpanel = wiringPiSetup();

/**************************************************************************/
/*!
    @brief Set the GPIO pin of the LED panel
    @param LED_pin The GPIO pin used to turn the panel on/off
*/
/**************************************************************************/
void LED_matrix::configurePanel(int LED_pin) {
  pinMode(LED_pin, OUTPUT);  // Setup LED growth matrix panel
  digitalWrite(LED_pin, HIGH); // 'LOW' turns the panel on
}

/**************************************************************************/
/*!
    @brief Turns the LED growth matrix on
*/
/**************************************************************************/
void LED_matrix::on(void){
  digitalWrite(LED_pin, LOW);
}

/**************************************************************************/
/*!
    @brief Turns the LED growth matrix off
*/
/**************************************************************************/
void LED_matrix::off(void){
  digitalWrite(LED_pin, HIGH);
}
