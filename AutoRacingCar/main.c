/*
 * AutoRacingCar.c
 *
 * Created: 05/12/2018 10.58.53
 * Author : SPRO Team 3
 */ 

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <avr/io.h>
#include <stdint.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ultrasonic.h"
#include "PWM.h"
#include "usart.h"

void executeCMD();

uint8_t motorPower = 0;
uint8_t driveMode = 0;

int servoCenter = 250;
int servoPos = 250;

volatile int dis1 = 0;
volatile int dis2 = 0;
volatile int dis3 = 0;

int main(void) {
	
	
	initMotor();
	initServo();
	initUltrasonic();
	initTimer2();
	usart_Init();
	
    while (1) {
		//if(driveMode == 1) {
			dis1 = getDistance(1);
			//usart_send((uint8_t)dis1);
			_delay_ms(100);
			
		//}
    }
}

ISR(USART_RX_vect) {
	if (getCommand()){
		executeCMD();
	}
}

void executeCMD() {
	switch(cmd) {
		case 0x00:
		usart_send((uint8_t)dis1);
		break;
		case 0x01:
		motorPower = arg1;
		setMotor(motorPower);
		break;
		default:
		break;
	}
}

void ultrasonicDriving() {
	/*if () {
	} 
	else {
	}*/
}