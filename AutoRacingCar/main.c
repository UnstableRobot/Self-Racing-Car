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
#include "IR_driving.h"
#include <avr/interrupt.h>


int main(void)
{

	//uart_init();	// open the communication to the microcontroller
	//io_redirect();	// redirect input and output to the uart (Realterm)
	
	Timer_init();
	
	while(1){
		
			
		Driving();
		
		//test_function(); //Used to test the IR-Sensors. ONLY enalbe for testing! (Enable global variable and function)
	}

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