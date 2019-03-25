#include <stdio.h>
#include <stdlib.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#include "VEML6075v2.h"

// I2C Linux device handle
int g_i2cFid;

// open the Linux device
void i2cOpen()
{
	g_i2cFid = open("/dev/i2c-1", O_RDWR);
if (g_i2cFid < 0) {
perror("i2cOpen");
exit(1);
	}
}

// close the Linux device
void i2cClose()
{
close(g_i2cFid);
}

// set the I2C slave address for all subsequent I2C device transfers
void i2cSetAddress(int address)
{
if (ioctl(g_i2cFid, I2C_SLAVE, address) < 0) {
perror("i2cSetAddress");
exit(1);
	}
}



int main (){
  i2cOpen();

  fprintf("VEML6075 Simple Test \n");
  i2cSetAddress(VEML6075_ADDR);

  VEML6075 uv = VEML6075();

  if (! uv.begin()) {
    fprintf("Failed to communicate with VEML6075 sensor \n");
  }
  fprintf("Found VEML6075 sensor \n");

  fprintf("UV Index reading: ");
  fprintf(uv.readUVI());
  delay(1000);

  i2cClose();
}
