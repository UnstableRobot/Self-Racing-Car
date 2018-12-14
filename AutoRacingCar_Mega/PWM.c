/*
 * PWM.c
 *
 * Created: 13/12/2018 10.07.16
 *  Author: M.A.S
 */ 

#include <avr/io.h>

void init_motor(int duty) {
	DDRH |= (1<<3);	//enable PH3 GPIO
	//PORTH |= (1<<3);
	
	//set fast pwm, non-inverted
	
	TCCR4A |= (1<<WGM41) | (1<<COM4A1);
	TCCR4B |= (1<< WGM42) | (1<<WGM43) | (1<<CS41);
	
	ICR4 = 65535;	//set top limit => 16 bits
	
	OCR4A = 0;	//set duty cycle
	
}

void setMotor(uint8_t duty) {
	OCR4A = 655*duty;
}

void initServo() {
	//Set servo pin as outut
	DDRB |= (1<<5);
	
	TCCR1A = (1<<COM1A1)|(1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
	ICR1 = 5000;
	OCR1A = 250;
}

void setServo(int position) {
	OCR1A = position;
}