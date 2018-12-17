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
#include "PWM.h"
#include "IR_driving.h"
#include "usart.h"
#include <avr/interrupt.h>


int main(void)
{
	OCR1A = 250; //Straighten the wheels
	//uart_init();	//Communication to microcontroller (for PC)
	//io_redirect();	//Use for Realterm on PC (debugging)
	Timer_init();	//Timer and init. for servo
	_delay_ms(5000); //Delay for motor
	init_motor();	//Start motor
	setMotor(100);	//Motor set to 100% duty
	_delay_ms(50);	//delay 50ms (motor acceleration spike)
	setMotor(10);	//Motor set to 13% duty
	
	
	while(1)
	{
					
		Driving();	//Line following function
		
		//printf("0:%u 1:%u 2:%u 3:%u 4:%u 5:%u\n\n\n", IR0, IR1, IR2, IR3, IR4, IR5);	//Print IR-values for debuging
		//_delay_ms(1000);	//delay 1sec for easy read of values
		
	}

}

