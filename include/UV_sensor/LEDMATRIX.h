/**
* @file  LEDMATRIX.h
* @brief  Header for control of LED panels.
*/

#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

/*! 
* @brief Control of LED panels.
*/
class LED_matrix {
 public:
  void configurePanel(int LED_pin1, int LED_pin2);

  // Turn the panel on
  void on(void);

  // Turn the panel off
  void off(void);

 private:
 /*! 
 @brief Control of LED panel at pin 1.
 */
   int LED_pin1;
 /*! 
 @brief Control of LED panel at pin 2.
 */
   int LED_pin2;
};


#endif
