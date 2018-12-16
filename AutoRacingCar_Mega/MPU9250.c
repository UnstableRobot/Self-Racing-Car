/*
 * MPU9250.c
 *
 * Created: 16/12/2018 21.08.30
 *  Author: M.A.S
 */ 

#include <avr/io.h>
#include "MPU9250.h"
#include "i2cmaster.h"

int getWhoAmI() {
	int data;
	i2c_start(accelAddr+I2C_WRITE);
	i2c_write(WHO_AM_I);
	i2c_rep_start(accelAddr+I2C_READ);
	data = i2c_readNak();
	i2c_stop();
	return data;
}