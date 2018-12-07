/*
 * AutoRacingCar.c
 *
 * Created: 05/12/2018 10.58.53
 * Author : SPRO Team 3
 */ 

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"
#include "PWM.h"
#include "usart.h"

//uint8_t motorPower = 0;

int main(void) {
    
	initMotor();
	usart_Init();
	
    while (1) 
    {
		
    }
}

ISR(USART_RX_vect) {
	if (getCommand()){
		executeCMD();
	}
}