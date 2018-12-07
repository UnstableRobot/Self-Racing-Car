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

void usart_Init();

volatile char cmd;
volatile char arg1;
volatile char arg2;
volatile char argIndex;

int main(void) {
    
	initMotor();
	//usart_Init();
	
    while (1) 
    {
		
    }
}

ISR(USART_RX_vect) {
	if (argIndex == 0){
		cmd = UDR0;
		arg1 = 0;
		arg2 = 0;
		argIndex++;
	}
	else {
		arg1 = UDR0;
		argIndex = 0;
	}
	
	if (argIndex == 0){
		if (cmd) {
			setMotor(arg1);
		} 
		else {
			
		}
	}
}

void usart_Init() {
	//Set the USART prescaler
	UBRR0H = (uint8_t)(BAUD_PRESCALER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALER);
	
	//Enable RX, TX and interrupts
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	sei();
}