/*
 * AutoRacingCar.c
 *
 * Created: 05/12/2018 10.58.53
 * Author : SPRO Team 3
 */ 

#define F_CPU 16E6

#include <avr/io.h>
#include <stdio.h>
#include <util/delay.h>
#include "IR_driving.h"
#include "i2cmaster.h"
#include "ds1621.h"
#include "lcd.h"
#include "usart.h"
#include "ultrasonic.h"
#include "PWM.h"
#include <avr/interrupt.h>

void IR_sensor_read(void);	//Print values to Realterm function


int main(void) {
    
	
	uart_init();
	io_redirect();
	
	Timer_init();
	
    while (1) 
    {	
			Driving();
			IR_sensor_read();
			_delay_ms(1000);
    }
}

void IR_sensor_read(void)
{
	printf("IR0: %u  IR1: %u  IR2: %u IR3: %u  IR6: %u  IR7: %u\n\n\n" ,IR0, IR1, IR2, IR3, IR6, IR7);
}
