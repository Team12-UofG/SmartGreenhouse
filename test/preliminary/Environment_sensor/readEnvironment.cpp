/**************************************************************************/

/*!
 *  @file readEnvironment.cpp
 *  @authors A. Saikia and I. Mitchell
 *  @brief takes one reading of the environment sensor and prints the values
 *  @version 0.1
 *  @date 2019-04-11
 *  @copyright Copyright (c) 2019
 *
*/

#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <chrono>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../../include/Environment_sensor/bme680.h"
#include "../../../include/Soil_sensor/MCP342X.h"
#include "../../../include/Soil_sensor/MCP342X.cpp"
#include "../../../include/UV_sensor/VEML6075.h"
#include "../../../include/UV_sensor/VEML6075.cpp"


using namespace std;

/*! @brief Our destination time zone */
#define     DESTZONE    "TZ=Europe/London"       // Our destination time zone

/*!
 * @brief Instantiate objects used in this project
 */
MCP342X soilSensor;
int Soil_configData = 0;;
UV_sensor lightSensor; // create sensor
int readData();

/*! @brief I2C Linux device handle.
*/
int g_i2cFid;

/*!
    @brief Open the Linux device.
*/
void i2cOpen()
{
	g_i2cFid = open("/dev/i2c-1", O_RDWR);
	if (g_i2cFid < 0) {
		perror("i2cOpen");
		exit(1);
	}
}

/*!
    @brief Close the Linux device.
*/
void i2cClose()
{
	close(g_i2cFid);
}

/*!
    @brief Set the I2C slave address for all subsequent I2C device transfers.
    @param address[in] : 12C slave address
*/
void i2cSetAddress(int address)
{
	if (ioctl(g_i2cFid, I2C_SLAVE, address) < 0) {
		perror("i2cSetAddress");
		exit(1);
	}
}


/*!
    @brief Set the user delay in milliseconds.
    @param period[in]
*/
void user_delay_ms(uint32_t period)
{
    sleep(period/1000);
}

/*!
    @brief Read I2C information.
    @param  dev_id
    @param  reg_addr
    @param  reg_data
    @param  len
*/
int8_t user_i2c_read(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */
    uint8_t reg[1];
	reg[0]=reg_addr;

 	if (write(g_i2cFid, reg, 1) != 1) {
		perror("user_i2c_read_reg");
		rslt = 1;
	}

	if (read(g_i2cFid, reg_data, len) != len) {
		perror("user_i2c_read_data");
		rslt = 1;
	}

    return rslt;
}

/*!
    @brief Write I2C information.
    @param  dev_id
    @param  reg_addr
    @param  reg_data
    @param  len
*/

int8_t user_i2c_write(uint8_t dev_id, uint8_t reg_addr, uint8_t *reg_data, uint16_t len)
{
    int8_t rslt = 0; /* Return 0 for Success, non-zero for failure */

	uint8_t reg[16];
    reg[0]=reg_addr;

    for (int i=1; i<len+1; i++)
       reg[i] = reg_data[i-1];

    if (write(g_i2cFid, reg, len+1) != len+1) {
		perror("user_i2c_write");
		rslt = 1;
	        exit(1);
	}

    return rslt;
}

/*!
 * @brief main progam
 */

int main(int argc, char *argv[] ) {

	int delay = 3;
	int nMeas = 1;
	char *outputFile = NULL;

	// Input argument parser
	if( argc == 2 ) {
		delay = strtol(argv[1], NULL, 10);

	}

	else if( argc == 3 ) {
		delay = strtol(argv[1], NULL, 10);
		nMeas = strtol(argv[2], NULL, 10);
	}

	else if( argc == 4 ) {
		delay = strtol(argv[1], NULL, 10);
		nMeas = strtol(argv[2], NULL, 10);
		outputFile = argv[3];
	}

	printf("** UofG Smartgreenhouse Environment measurements using BME680 **\n");

	time_t t = time(NULL);
	// open Linux I2C device
	i2cOpen();

	// set address of the BME680
	i2cSetAddress(0x76);

	auto start = std::chrono::high_resolution_clock::now();
	// init device
	struct bme680_dev gas_sensor;
	gas_sensor.dev_id = BME680_I2C_ADDR_SECONDARY;
	gas_sensor.intf = BME680_I2C_INTF;
	gas_sensor.read = user_i2c_read;
	gas_sensor.write = user_i2c_write;
	gas_sensor.delay_ms = user_delay_ms;

	int8_t rslt = BME680_OK;
	rslt = bme680_init(&gas_sensor);
	uint8_t set_required_settings;

	/* Set the temperature, pressure and humidity settings */
	gas_sensor.tph_sett.os_hum = BME680_OS_2X;
	gas_sensor.tph_sett.os_pres = BME680_OS_4X;
	gas_sensor.tph_sett.os_temp = BME680_OS_8X;
	gas_sensor.tph_sett.filter = BME680_FILTER_SIZE_3;

	/* Set the remaining gas sensor settings and link the heating profile */
	gas_sensor.gas_sett.run_gas = BME680_ENABLE_GAS_MEAS;

	/* Create a ramp heat waveform in 3 steps */
	gas_sensor.gas_sett.heatr_temp = 320; /* degree Celsius */
	gas_sensor.gas_sett.heatr_dur = 150; /* milliseconds */

	/* Select the power mode */
	/* Must be set before writing the sensor configuration */
	gas_sensor.power_mode = BME680_FORCED_MODE;

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL
		| BME680_GAS_SENSOR_SEL;

	/* Set the desired sensor configuration */
	rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(&gas_sensor);

	/* Get the total measurement duration so as to sleep or wait till the
	 * measurement is complete */
	uint16_t meas_period;
	bme680_get_profile_dur(&meas_period, &gas_sensor);
	user_delay_ms(meas_period + delay*1000); /* Delay till the measurement is ready */

    struct bme680_field_data data;

	struct tm tm = *localtime(&t);

	int i=0;
	int backupCounter = 0;

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	auto start = std::chrono::high_resolution_clock::now();
	while(i<nMeas && backupCounter < nMeas+3) {
		// Get sensor data
		rslt = bme680_get_sensor_data(&data, &gas_sensor);

		// Avoid using measurements from an unstable heating setup
		if(data.status & BME680_HEAT_STAB_MSK)
		{
			t = time(NULL);
			tm = *localtime(&t);
			printf("%d-%02d-%02d %02d:%02d:%02d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", data.temperature / 100.0f,
					data.pressure / 100.0f, data.humidity / 1000.0f );
			printf(", G: %d Ohms", data.gas_resistance);
			printf("\r\n");
			i++;
	}

		// Trigger a meausurement
		rslt = bme680_set_sensor_mode(&gas_sensor); /* Trigger a measurement */

		// Wait for a measurement to complete
		user_delay_ms(meas_period + delay*1000); /* Wait for the measurement to complete */
	   	backupCounter++;
	}

	auto finish = std::chrono::high_resolution_clock::now();

 	std::chrono::duration<double> elapsed = finish - start;
 	std::cout << "Elapsed time: " << elapsed.count() << " s\n";

	printf("** End of measurement **\n");

  	// close Linux I2C device
	i2cClose();

	return 0;
}
