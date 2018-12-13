/*
 * IR_driving.c
 *
 * Created: 06-12-2018 15:36:24
 *  Author: Frederik Lund
 */ 

#include <avr/io.h>
#include "IR_driving.h"


uint16_t adc_read(uint8_t adc_channel){
	ADMUX &= 0xf0;	// clear any previously used channel, but keep internal reference
	ADMUX |= adc_channel;	// set the desired channel
	ADCSRA |= (1<<ADSC); //start a conversion
	
	while ( (ADCSRA & (1<<ADSC)) );	// now wait for the conversion to complete
	
	return ADC; // now we have the result, so we return it to the calling function as a 16 bit unsigned int
}

void Driving(void)
{
	adc_result_0 = adc_read(0);	//Get mV value for Pin A0
	adc_result_1 = adc_read(1);	//Get mV value for Pin A1
	adc_result_2 = adc_read(2);	//Get mV value for Pin A2
	adc_result_3 = adc_read(3);	//Get mV value for Pin A3
	adc_result_4 = adc_read(4);	//Get mV value for Pin A4
	adc_result_5 = adc_read(5);	//Get mV value for Pin A5
	
	IR0 = ((adc_result_0*4.84)/1024.0)*1000; // Function get value for IR0
	IR1 = ((adc_result_1*4.84)/1024.0)*1000; // Function get value for IR1
	IR2 = ((adc_result_2*4.84)/1024.0)*1000; // Function get value for IR2
	IR3 = ((adc_result_3*4.84)/1024.0)*1000; // Function get value for IR3
	IR4 = ((adc_result_4*4.84)/1024.0)*1000; // Function get value for IR4
	IR5 = ((adc_result_5*4.84)/1024.0)*1000; // Function get value for IR5
	
	if (IR0 >= 4000)
	{
		OCR1A = 300;	//PWM Max right (Precaution for turning)
	}
	if (IR1 && IR0 >= 4000)
	{
		OCR1A = 300;	//PWM Max right
	}
	if (IR1 && IR2 >= 4000)
	{
		OCR1A = 275;	//PWM medium right
	}
	if (IR2 && IR3 >= 4000)
	{
		OCR1A = 250;	//PWM straight (straight forward)
	}
	if (IR4 && IR3 >= 4000)
	{
		OCR1A = 225;	//PWM medium left
	}
	if (IR5 && IR4 >= 4000)
	{
		OCR1A = 200;	//PWM Max left
	}
	if (IR5 >= 4000)
	{
		OCR1A = 200;	//PWM Max left (Precaution for turning)
	}
}

void Timer_init(void)
{
	ADMUX = (1<<REFS0);	 // Select Vref = AVcc
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN); //set prescaler to 128 and turn on the ADC module
	
	DDRB = 0xFF;	// I/O board:PB1...7 as outputs, for for servo
	DDRF = 0x00;	// I/O board PF0...7 as inputs, for IR-sensor
	DDRB = (1<<5);
	
	TCCR1A = (1<<COM1A1)|(1<<WGM11);	//Timer 1 count/compare mode
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);	//Fast PWM, non-inverting
	ICR1 = 5000;	//TOP count
}