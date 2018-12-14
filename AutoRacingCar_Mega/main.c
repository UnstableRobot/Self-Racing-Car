/*
 * AutoRacingCar_Mega.c
 *
 * Created: 12/12/2018 11.08.05
 * Author : M.A.S
 */ 

#define F_CPU 16000000UL

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "ultrasonic.h"
#include "usart.h"
#include "PWM.h"

void getAverage(uint8_t sensor);
void executeCMD();

uint8_t lastAVG = 0;
volatile int distances[5][12];
int txTime = 0;

uint8_t driveMode = 0;
uint8_t motorPower;
uint8_t curChannel = 4;

int main(void) {
	TCCR5B |= (1<<CS51) | (1<<CS50);
	DDRB |= (1<<7);
	//PORTB &= ~(1<<7);
	
	for (int j = 0; j < 5; j++){
		for (int k = 0; k < 12; k++){
			distances[j][k] = 0;
		}
	}
	
	init_motor(0);
	initServo();
    initTimer3();
	initUltrasonic();
	usart_Init();
	sei();
	
    while (1) {
		if (TCNT5 >= 24000){
			if (trigUltrasonic(curChannel)){
				if (curChannel < 4){
					curChannel++;
				} 
				else {
					curChannel = 0;
				}
			}
		}
		
		if(driveMode == 1) {
			motorPower = 12;
		}
		else {
			motorPower = 0;
		}
		setMotor(motorPower);
		
		
		if (distances[4][0] < 20){
			setServo(300);
		} 
		else if(distances[4][0] > 30) {
			setServo(200);
		}
		else {
			setServo(250);
		}
    }
}

ISR(USART0_RX_vect) {
	if (getCommand()){
		executeCMD();
	}
}

ISR(PCINT2_vect) {
	//Check if the selected channel has gone high
	if ((PINK & (1<<ultChannel))){
		TCNT3 = 0;
		PORTB |= (1<<7);
	}
	else {
		PORTB &= ~(1<<7);
		distance = TCNT3;
		lastAVG = distances[ultChannel][1];
		if (lastAVG > 11){
			lastAVG++;
		} 
		else {
			lastAVG = 2;
		}
		
		distances[ultChannel][0] = (distance/2)/58;
		/*distances[ultChannel][1] = lastAVG;
		distance = 0;
		for (int i = 2; i < 7; i++){
			distance += distances[ultChannel][i];
		}
		distances[ultChannel][0] = distance/5;*/
		measuring = 0;
	}
}

ISR(TIMER3_OVF_vect) {
	measuring = 0;
	//PORTB |= (1<<7);
}

void executeCMD() {
	switch(cmd) {
		case 0x00:
		usart_send((uint8_t)distances[0][0]);
		usart_send((uint8_t)distances[1][0]);
		usart_send((uint8_t)distances[2][0]);
		usart_send((uint8_t)distances[3][0]);
		usart_send((uint8_t)distances[4][0]);
		usart_send(motorPower);
		break;
	case 0x01:
		driveMode = arg1;
		break;
		default:
		break;
	}
}

void getAverage(uint8_t sensor) {
	
}