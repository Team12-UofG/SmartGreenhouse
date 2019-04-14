/**************************************************************************/

/*!
 *  @file example.cpp
 *  @authors I.Mitchell and A. Saikia
 *  @brief Takes readings from the sensors and updates the website with the values.
 *  @version 0.1
 *  @date 2019-04-11
 *  @copyright Copyright (c) 2019
 *
*/

#include <wiringPi.h>
#include <wiringPiI2C.h> // add "-lwiringPi" to compile
#include <stdio.h>
#include <iostream>      // add "-lstdc++" to compile
#include <unistd.h>
#include <mysql/mysql.h> // add "-lmysqlclient" to compile
#include <stdlib.h>
#include <time.h>
#include <linux/i2c-dev.h>
#include <fcntl.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "../../include/Environment_sensor/bme680.h"
#include "../../include/Soil_sensor/MCP342X.h"
#include "../../include/Soil_sensor/MCP342X.cpp"
#include "../../include/UV_sensor/VEML6075.h"
#include "../../include/UV_sensor/VEML6075.cpp"




/*! @brief Our destination time zone. */
#define     DESTZONE    "TZ=Europe/London"       // Our destination time zone

/*!
 * @brief Instantiate objects used in this project.
 */
MCP342X soilSensor;

/*!
 * @brief Initiate the Soil_configData variable to zero.
 */
int Soil_configData = 0;
int water_pump = 23;
int LED_pin = 26;
int heat_pin = 27;

int dry_threshold = 60;
int UV_threshold = 3;   	// UVI of 3
int temp_threshold = 20; 	// 20 deg C

/*!
 * @brief Sensor variable.
 */
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
    @param address[in] : I2C slave address
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
    @param period[in] :
*/
void user_delay_ms(uint32_t period)
{
    sleep(period/1000);
}

/*!
    @brief Read I2C information.
    @param  dev_id :
    @param  reg_addr :
    @param  reg_data :
    @param  len :
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
 * @brief Main progam.
 * @param argc[in] :
 * @param argv[in] :
 */

int main(int argc, char *argv[] ) {

	printf("System is configuring ...\n");
	lightSensor.uvConfigure(); // configure sensor
	Soil_configData = soilSensor.configure();

	// initialize connection to MySQL database
  MYSQL *mysqlConn;
  MYSQL_RES result;
  MYSQL_ROW row;
  mysqlConn = mysql_init(NULL);
	char buff[1024];

	int delay = 3;
	int nMeas = 1;

	time_t t = time(NULL);

	/* Setup water pump, LEDs and heat mat */
  wiringPiSetup();
  pinMode(water_pump, OUTPUT);
  pinMode(LED_pin, OUTPUT);
  pinMode(heat_pin, OUTPUT);

	/* Configure BME680 */
	i2cOpen(); 						// open Linux I2C device
	i2cSetAddress(0x76);	// set address of the BME680

	struct bme680_dev gas_sensor;			// init device
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
	gas_sensor.power_mode = BME680_FORCED_MODE;

	/* Set the required sensor settings needed */
	set_required_settings = BME680_OST_SEL | BME680_OSP_SEL | BME680_OSH_SEL | BME680_FILTER_SEL
		| BME680_GAS_SENSOR_SEL;

	/* Set the desired sensor configuration */
	rslt = bme680_set_sensor_settings(set_required_settings,&gas_sensor);

	/* Set the power mode */
	rslt = bme680_set_sensor_mode(&gas_sensor);


	/* The main loop means that the system will run continuously */
	while(1){
		mysql_real_connect(mysqlConn,"localhost", "UOG_SGH", "test", "SGH_TPAQ", \
				0, NULL, 0)!=NULL;

		/* Get the total measurement duration for the BME680 so as to sleep or
	 	* wait until the measurement is complete
		*/
		uint16_t meas_period;
		bme680_get_profile_dur(&meas_period, &gas_sensor);
		user_delay_ms(meas_period + delay*1000); /* Delay till the measurement is ready */

  	struct bme680_field_data data;
		struct tm tm = *localtime(&t);
		int i=0;
		int backupCounter = 0;


		/*
		* Read the soil sensor data
		*/
		uint8_t soilData;
		soilSensor.startConversion(Soil_configData); // Start conversion
		soilData = soilSensor.getResult(&soilData); // Read converted value
		printf("Soil moisture: %d ", soilData);
		if(soilData > dry_threshold){
			digitalWrite(water_pump, HIGH);
			sleep(1);
		}

		/*
		* Read the UV sensor data
		*/
		float UV_calc = lightSensor.readUVI(); // UV value - this is the output we want
		printf("UV Index reading: %f \n", UV_calc);
		if(UV_calc < UV_threshold){
			digitalWrite(LED_pin, HIGH);
		}
		else {
			digitalWrite(LED_pin, LOW);
		}

		/*
		 * Read the Environment sensor
		*/
		while(i<nMeas && backupCounter < nMeas+3) {
			rslt = bme680_get_sensor_data(&data, &gas_sensor); // Get sensor data
			if(data.status & BME680_HEAT_STAB_MSK) // Don't use measurements from an unstable heating setup
			{
				t = time(NULL);
				tm = *localtime(&t);
				printf("%d-%02d-%02d %02d:%02d:%02d ", tm.tm_year + 1900, tm.tm_mon + 1,\
				 tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
				printf("T: %.2f degC, P: %.2f hPa, H: %.2f %%rH", data.temperature / 100.0f,
					data.pressure / 100.0f, data.humidity / 1000.0f );
					printf(", G: %d Ohms", data.gas_resistance);
					printf("\r\n");
					i++;
			}
			rslt = bme680_set_sensor_mode(&gas_sensor); /* Trigger a measurement */
			user_delay_ms(meas_period); /* Wait for the measurement to complete */
	  	backupCounter++;
		}

		if (data.temperature / 100.0f < temp_threshold){
		  digitalWrite(heat_pin, HIGH);
		}
		else {
		  digitalWrite(heat_pin, LOW);
		}

		/*
		* Send measurement to MYSQL database
		*/
			printf("Updating website \n");
			snprintf(buff, sizeof buff, "INSERT INTO TPAQ VALUES ('', '%d', '%f', \
			'%02d', '%02d', '%02d', '%02d', '%02d', '%02d', '%.2f','%.2f','%.2f', \
			'%d');", soilData, UV_calc, tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, \
			tm.tm_hour, tm.tm_min, tm.tm_sec, data.temperature / 100.0f, \
			 data.pressure / 100.0f, data.humidity / 1000.0f, data.gas_resistance );
			mysql_query(mysqlConn, buff);

			mysqlConn = mysql_init(NULL);
	}
	printf("** End of measurements **\n");
	mysql_close(mysqlConn); // close MySQL
	i2cClose(); // close Linux I2C device

	return 0;
}
