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
	
	uart_init();
	io_redirect();
	Timer_init();
	/*_delay_ms(10000);
	initMotor();
	setMotor(255);
	_delay_ms(50);
	setMotor(140);*/
	
	while(1)
	{
					
		Driving();
		printf("0:%u 1:%u 2:%u 3:%u 4:%u 5:%u\n\n\n", IR0, IR1, IR2, IR3, IR4, IR5);
		_delay_ms(1000);
		
		/*OCR1A = 200;
		_delay_ms(2000);
		OCR1A = 225;
		_delay_ms(2000);
		OCR1A = 250;
		_delay_ms(2000);
		OCR1A = 275;
		_delay_ms(2000);
		OCR1A = 300;
		_delay_ms(2000);*/
		
	}

}

