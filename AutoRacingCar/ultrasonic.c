/*
 * ultrasonic.c
 *
 * Created: 05/12/2018 13.25.59
 *  Author: M.A.S
 */ 

#include <avr/io.h>
#include <stdint.h>
#include "ultrasonic.h"

void initTimer2() {
	TCCR2B |= (1<<CS21);
}

void initUltrasonic() {
	DDRD |= (1<<3) | (1<<4) | (1<<5);
	PORTD &= ~((1<<3) | (1<<4) | (1<<5));
	DDRB &= ~((1<<2) | (1<<3) | (1<<4));
}

int getDistance(uint8_t sensor) {
	int overflows = 0;
	int distance = 0;
	int count = 0;
	//Send a 10µs pulse to the sensors trigger pin
	PORTD |= (4<<sensor);
	TCNT2 = 0;
	while(TCNT2 < 20);
	PORTD &= ~(4<<sensor);
	//wait for rising edge on echo pin
	while(!(PINB & (2<<sensor)));
	
	//Meassure time til falling edge
	TCNT2 = 0;
	while((PINB & (2<<sensor)) && overflows <= 45) {
		if (TIFR2 & (1<<TOV2)){
			TIFR2 |= (1<<TOV2);
			overflows++;
		}
	}
	count = TCNT2;
	if (overflows <= 45){
		distance = (((overflows * 255)+count)/2)/58;
	}
	else {
		distance = 0;
	}
	return distance;
}