/*
 * PWM.c
 *
 * Created: 05/12/2018 13.59.10
 *  Author: M.A.S
 */ 
#include "avr/io.h"


void setMotor(uint16_t power) 
{
	OCR4A = 655*power;
}

void init_motor(void)
{
	DDRH |= (1<<DDH3);	//enable PH3 GPIO
	
	//set fast pwm, non-inverted
	
	TCCR4A |= (1 <<WGM41) | (1<<COM4A1);
	TCCR4B |= ( 1 << WGM42) | (1 <<WGM43)|(1<<CS41);
	
	ICR4 |= 65535;	//set top limit => 16 bits
	
	OCR4A = 0;	//set duty cycle
}