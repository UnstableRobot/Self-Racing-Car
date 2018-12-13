/*
 * PWM.c
 *
 * Created: 05/12/2018 13.59.10
 *  Author: M.A.S
 */ 
#include "avr/io.h"

void initMotor() {
	DDRH |= (1<<DDH3);
	PORTH |= (1<<PH3);
	OCR4A = 0;	//sets duty cycle 50%
	TCCR4A |= (1<<COM4A1) | (1<<WGM41) | (1<<WGM40);	//non-inverting fast pwm
	TCCR4B |= (1<<CS41);	//Set prescaler to 8 and start PWM
}

void setMotor(uint16_t power) {
	OCR4A = power;
}