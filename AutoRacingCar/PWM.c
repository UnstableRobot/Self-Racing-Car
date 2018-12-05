/*
 * PWM.c
 *
 * Created: 05/12/2018 13.59.10
 *  Author: M.A.S
 */ 

void initMotor() {
	DDRD |= (1<<DDD6);
	PORTD |= (1<<PORTD6);
	OCR0A = 0;	//sets duty cycle 50%
	TCCR0A |= (1<<COM0A1) | (1<<WGM01) | (1<<WGM00);	//non-inverting fast pwm
	TCCR0B |= (1<<CS01);	//Set prescaler to 8 and start PWM
}

void setMotor(uint8_t power) {
	OCR0A = power;
}