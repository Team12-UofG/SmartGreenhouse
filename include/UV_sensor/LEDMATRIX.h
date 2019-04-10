#ifndef _LEDMATRIX_H
#define _LEDMATRIX_H

class LED_matrix {
 public:
  void configurePanel(int LED_pin);
  
  // Turn the panel on
  void on(void);

  // Turn the panel off
  void off(void);

 private:
   int LED_pin;
};


#endif
