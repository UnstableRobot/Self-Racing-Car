/*
 * ultrasonic.c
 *
 * Created: 12/12/2018 11.12.08
 *  Author: M.A.S
 
 */ 

#include <avr/io.h>
#include <stdint.h>

void initTimer3() {
	TCCR3B |= (1<<CS31);
}

void initUltrasonic() {
	DDRC &= ~((1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4));
	DDRA |= (1<<0) | (1<<1) |(1<<2) | (1<<3) | (1<<4);
	PORTA &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4));
	PORTC &= ~((1<<0) | (1<<1) | (1<<2) | (1<<3) | (1<<4));
}

int getDistance(uint8_t sensor) {
	int distance = 0;
	int count = 0;
	//Send a 10µs pulse to the sensors trigger pin
	PORTA |= (1<<sensor);
	TCNT3 = 0;
	while(TCNT3 < 20);
	PORTA &= ~(1<<sensor);
	//wait for rising edge on echo pin
	TCNT3 = 0;
	while(!(PINC & (1<<sensor))) {
	}
	
	//Meassure time til falling edge
	TCNT3 = 0;
	while((PINC & (1<<sensor)) && TCNT3 < 23000) {
	}
	
	count = TCNT3;
	distance = (count/2)/58;
	return distance;
}