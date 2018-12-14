/*
 * ultrasonic.c
 *
 * Created: 12/12/2018 11.12.08
 *  Author: M.A.S
 
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "ultrasonic.h"

volatile uint8_t ultChannel = 0;
volatile uint8_t measuring = 0;
volatile int distance = 0;

void initTimer3() {
	TCCR5B |= (1<<CS51);
	TCCR3B |= (1<<CS31);
	TIMSK3 |= (1<<TOIE3);
}

void initUltrasonic() {
	DDRK &= ~((1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4));
	DDRA |= (1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4);
	PORTA &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4));
	PORTC &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4));
	
	PCICR |= (1<<PCIE2);
	PCMSK2 = 0x3F;
}

uint8_t trigUltrasonic(uint8_t sensor) {
	//Check if a measurement is ongoing
	if (measuring){
		return 0;
	} 
	else {
		//PORTB |= (1<<7);
		ultChannel = sensor;
		measuring = 1;
		//Send a 10µs pulse to the sensors trigger pin
		PORTA |= (1<<sensor);
		TCNT5 = 0;
		while(TCNT5 < 20);
		PORTA &= ~(1<<sensor);
		//PORTB &= ~(1<<7);
		return 1;
	}

}