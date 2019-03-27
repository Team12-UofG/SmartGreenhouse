#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <wiringPi.h>

#include "VEML6075.h"

static int intial_setup = wiringPiSetup();
static int fd = wiringPiI2CSetup(VEML6075_DEVID);

int main (){
  fprintf("VEML6075 Simple Test \n");

	float UV_calc = UV_sensor::readUVI();

  fprintf("UV Index reading: ");
  fprintf(uv.readUVI());
  wait(1);
}
