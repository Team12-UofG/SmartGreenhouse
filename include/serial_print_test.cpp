#include "VEML6075.h"
#include "VEML6075.cpp"

UV_sensor lightSensor;

int main (){

  printf("VEML6075 Simple Test \n");
  printf("Configuring... \n");
  lightSensor.uvConfigure(); // configure
  lightSensor.UV_sensor(); // set coefficients
  int i = 0;
  for(i=1; i<10; i++){
    float UVA_calc = lightSensor.readUVA();
    float UVB_calc = lightSensor.readUVB();
	  float UV_calc = lightSensor.readUVI();
    printf("UVA Index reading: %f \n", UVA_calc);
    printf("UVB Index reading: %f \n", UVB_calc);
    printf("UV Index reading: %f \n", UV_calc);
    usleep(1);
  }
}
