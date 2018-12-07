/*
 * usart.c
 *
 * Created: 07/12/2018 09.53.05
 *  Author: M.A.S
 */ 


#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include "usart.h"
#include "PWM.h"

uint8_t motorPower = 0;

void usart_Init() {
	//Set the USART prescaler
	UBRR0H = (uint8_t)(BAUD_PRESCALER>>8);
	UBRR0L = (uint8_t)(BAUD_PRESCALER);
	
	//Enable RX, TX and interrupts
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0);
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01);
	sei();
}

void usart_send(unsigned char data) {
	//Wait for transmit buffer to empty before sending next message
	while (!(UCSR0A & (1<<UDRE0)));
	UDR0 = data;
}

int getCommand() {
	if (argIndex == 0){
		cmd = UDR0;
		arg1 = 0;
		arg2 = 0;
		argIndex++;
	}
	else if(argIndex == 1){
		arg1 = UDR0;
		argIndex++;
	}
	else {
		arg2 = UDR0;
		argIndex = 0;
	}
	
	return !argIndex;
}

void executeCMD() {
	switch(cmd) {
		case 0:
			usart_send(motorPower);
			break;
		case 1:
			motorPower = arg1;
			setMotor(motorPower);
			break;
		default:
			break;
	}
}