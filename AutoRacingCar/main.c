/*
 * AutoRacingCar.c
 *
 * Created: 05/12/2018 10.58.53
 * Author : SPRO Team 3
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "ultrasonic.h"
#include "PWM.h"
#include "i2cmaster.h"
#include "IR_driving.h"
#include <avr/interrupt.h>


int main(void)
{

	//uart_init();	// open the communication to the microcontroller
	//io_redirect();	// redirect input and output to the uart (Realterm)
	
	Timer_init();
	
	while(1)
	{
					
		//Driving();
		
		OCR1A = 200;
		_delay_ms(2000);
		OCR1A = 225;
		_delay_ms(2000);
		OCR1A = 250;
		_delay_ms(2000);
		OCR1A = 275;
		_delay_ms(2000);
		OCR1A = 300;
		_delay_ms(2000);
		
	}

}

