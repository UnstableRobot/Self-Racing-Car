/*
 * AutoRacingCar.c
 *
 * Created: 05/12/2018 10.58.53
 * Author : SPRO Team 3
 */ 

#define F_CPU 16E6
#include <avr/io.h>
#include <stdio.h>
#include <stdint.h>
#include <util/delay.h>
#include "ultrasonic.h"
#include "PWM.h"
#include "i2cmaster.h"
#include <avr/interrupt.h>

uint16_t adc_read(uint8_t adc_channel);	//ADC Reading function
void test_function(void);	//Testing of IR-Sensors

//unsigned int IR0, IR1, IR2, IR3, IR6, IR7;	//enable only for test_function
//uint16_t adc_result_0, adc_result_1, adc_result_2, adc_result_3, adc_result_6, adc_result_7;	//enable only for test_function

int main(void)
{

	//uart_init();	// open the communication to the microcontroller
	//io_redirect();	// redirect input and output to the uart (Realterm)
	
	uint16_t adc_result_0, adc_result_1, adc_result_2, adc_result_3, adc_result_6, adc_result_7;	//16-bit Value
	ADMUX = (1<<REFS0);	 // Select Vref = AVcc
	ADCSRA = (1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN); //set prescaler to 128 and turn on the ADC module
	
	DDRD = 0xFF;	// I/O board:PD4...7 as outputs, for LEDs
	DDRC = 0x00;	// I/O board PC0...3 as inputs, for buttons
	DDRB = (1<<1);
		
	TCCR1A = (1<<COM1A1)|(1<<WGM11);
	TCCR1B = (1<<WGM13)|(1<<WGM12)|(1<<CS11)|(1<<CS10);
	ICR1 = 5000;
	
	unsigned int IR0, IR1, IR2, IR3, IR6, IR7;
	
	while(1){
			
		adc_result_0 = adc_read(0);	//Get mV value for Pin A0
		adc_result_1 = adc_read(1);	//Get mV value for Pin A1
		adc_result_2 = adc_read(2);	//Get mV value for Pin A2
		adc_result_3 = adc_read(3);	//Get mV value for Pin A3
		adc_result_6 = adc_read(6);	//Get mV value for Pin A6
		adc_result_7 = adc_read(7);	//Get mV value for Pin A7
		
		IR0 = ((adc_result_0*4.84)/1024.0)*1000; // Function get value for IR0
		IR1 = ((adc_result_1*4.84)/1024.0)*1000; // Function get value for IR1
		IR2 = ((adc_result_2*4.84)/1024.0)*1000; // Function get value for IR2
		IR3 = ((adc_result_3*4.84)/1024.0)*1000; // Function get value for IR3
		IR6 = ((adc_result_6*4.84)/1024.0)*1000; // Function get value for IR6
		IR7 = ((adc_result_7*4.84)/1024.0)*1000; // Function get value for IR7
		
		OCR1A = 375;
		
		//test_function(); //Used to test the IR-Sensors. ONLY enalbe for testing!
		if (IR0 >= 3500)
		{
			OCR1A = 100;
		}
		if (IR1 && IR0 >= 3500)
		{
			//PWM medium right 
		}
		if (IR2 && IR3 >= 3500)
		{
			//PWM straight (straight out)
		}

		if (IR6 && IR3 >= 3500)
		{
			//PWM medium right
		}
		if (IR7 >= 3500)
		{
			//PWM Max right
		}
		
	}

}

uint16_t adc_read(uint8_t adc_channel){
	ADMUX &= 0xf0;	// clear any previously used channel, but keep internal reference
	ADMUX |= adc_channel;	// set the desired channel
	ADCSRA |= (1<<ADSC); //start a conversion
	
	// now wait for the conversion to complete
	while ( (ADCSRA & (1<<ADSC)) );
	
	// now we have the result, so we return it to the calling function as a 16 bit unsigned int
	return ADC;
}

/*void test_function(void)
{
	adc_result_0 = adc_read(0);	//Get mV value for Pin A0
	adc_result_1 = adc_read(1);	//Get mV value for Pin A1
	adc_result_2 = adc_read(2);	//Get mV value for Pin A2
	adc_result_3 = adc_read(3);	//Get mV value for Pin A3
	adc_result_6 = adc_read(6);	//Get mV value for Pin A6
	adc_result_7 = adc_read(7);	//Get mV value for Pin A7
	
	IR0 = ((adc_result_0*4.84)/1024.0)*1000;
	IR1 = ((adc_result_1*4.84)/1024.0)*1000;
	IR2 = ((adc_result_2*4.84)/1024.0)*1000;
	IR3 = ((adc_result_3*4.84)/1024.0)*1000;
	IR6 = ((adc_result_6*4.84)/1024.0)*1000;
	IR7 = ((adc_result_7*4.84)/1024.0)*1000;

	printf("A0:%u mV  A1:%u mV  A2:%u mV  A3:%u mV  A6:%u mV  A7:%u mV\n", IR0, IR1, IR2, IR3, IR6, IR7);
}*/