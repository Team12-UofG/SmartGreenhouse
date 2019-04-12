/**
 * @file SGH_TPAQ.c
 *
 * @brief I2C communication with Bosch BME680 Temperature, Humidity and Air Quality Sensor
 *
 *
 * Sensor Data is exported to MySQL database
 * Application Note
 *
 * @author Anton Saikia (based on example by twartzek and Boschsensortech)
 *
 **/
#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include "../../../include/Environment_Sensor/bme680.h"

/*! @brief Our destination time zone */
#define     DESTZONE    "TZ=Europe/London"       // Our destination time zone

/*! @brief I2C Linux device handle.
*/
static int setupI2C_BME680 = wiringPiSetup();
static int fd_env = wiringPiI2CSetup(0x76);

/*!
    @brief Set the user delay in milliseconds.
    @param period[in]
*/
void user_delay_ms(uint32_t period)
{
    sleep(period/1000);
}


/*!
    @brief Writes measurements to output file specified.
    @param outputFile
    @param tm
    @param bme680_field_data
*/
void write2file(char *outputFile, struct tm tm, struct bme680_field_data data)
{
	// Write measurement to output file if specified.
	if(outputFile != NULL)
	{
		FILE *f = fopen(outputFile, "a");
		if (f == NULL)
		{
			printf("Error opening file!\n");
			//exit(1);
		}
		else
		{
			fprintf(f,"%d-%02d-%02d %02d:%02d:%02d ", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			fprintf(f,"T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", data.temperature / 100.0f,
					data.pressure / 100.0f, data.humidity / 1000.0f );
			fprintf(f,", G: %d Ohms", data.gas_resistance);
			fprintf(f,"\r\n");
			fclose(f);
		}

	}
}

/*!
    @brief Main function.
    @param argc
    @param argv
*/
int main(int argc, char *argv[] )
{
	char buff[1024];
	int j;

	// create lock file first
	FILE *f = fopen("~bme680i2c.lock", "w");
	if (f == NULL)
	{
		printf("Error opening file!\n");
		exit(1);
	}
	fprintf(f,"I2C locked by BME680 readout. \r\n");
	fclose(f);

	int delay = 3;
	int nMeas = 3;
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
	else {
	}


	printf("** UofG Smartgreenhouse Environment measurements using BME680 **\n");

	time_t t = time(NULL);
    putenv(DESTZONE);               // Switch to destination time zone


  // init device
	struct bme680_dev gas_sensor;

	gas_sensor.dev_id = BME680_I2C_ADDR_SECONDARY;
	gas_sensor.intf = BME680_I2C_INTF;
	gas_sensor.read = wiringPiI2CRead(fd_env);
	gas_sensor.write = wiringPiI2CWrite(fd_env);
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

	while(i<nMeas && backupCounter < nMeas+5) {

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
			write2file(outputFile, tm, data);
			i++;
		}

		// Trigger a meausurement
		rslt = bme680_set_sensor_mode(&gas_sensor); /* Trigger a measurement */

		// Wait for a measurement to complete
		user_delay_ms(meas_period + delay*1000); /* Wait for the measurement to complete */

		backupCounter++;
	}


	printf("** End of measurement **\n");

	// delete lock file
	remove("~bme680i2c.lock");

	return 0;
}
