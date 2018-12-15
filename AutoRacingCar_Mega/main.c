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
#include "median.h"

void smoothTurn(int target);
void hardTurn(int target);
void getAverage(uint8_t sensor);
void executeCMD();

uint8_t lastAVG = 0;
volatile int distances[5][12];
int txTime = 0;

uint8_t driveState = 0;
uint8_t motorPower = 0;
uint8_t curChannel = 4;
int turnDelay = 0;
int stateDelay = 0;

int servoPos = 250;

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
		if (TCNT5 >= 12000){
			if (trigUltrasonic(curChannel)){
				if (curChannel < 2){
					curChannel++;
				} 
				else {
					curChannel = 0;
				}
			}
		}
		
		setMotor(motorPower);
		
		if (driveState == 0) {
			if (distances[0][0] >= 40 && distances[1][0] > 100){
				smoothTurn(300);
			}
			else if(distances[0][0] >= 40 && distances[1][0] < 100) {
				smoothTurn(250);
			}
			else if (distances[0][0] <= 35/* && distances[1][3] > 100*/){
				smoothTurn(200);
			}
			else if (distances[0][0] <= 35/* && distances[1][3] < 100*/){
				smoothTurn(250);
			}
			else {
				smoothTurn(250);
			}
			if (distances[2][0] < 70){
				if (stateDelay > 5){
					driveState = 1;
				}
				else {
					stateDelay++;
				}
			}
			else {
				stateDelay = 0;
			}
		} 
		else if (driveState == 1){
			hardTurn(300);
			if (distances[1][0] >= 180 && distances[2][0] >= 180){
				if (stateDelay > 5){
					driveState = 0;
				}
				else {
					stateDelay++;
				}
			}
			else {
				stateDelay = 0;
			}
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
	}
	else {
		distance = TCNT3;
		
		
		distances[ultChannel][5] = distances[ultChannel][4];
		distances[ultChannel][4] = distances[ultChannel][3];
		distances[ultChannel][3] = distances[ultChannel][2];
		distances[ultChannel][2] = distances[ultChannel][1];
		distances[ultChannel][1] = (distance/2)/58;
		
		distances[ultChannel][0] = median5(distances[ultChannel][5], distances[ultChannel][4], distances[ultChannel][3], distances[ultChannel][2], distances[ultChannel][1]);
		
		measuring = 0;
	}
}

ISR(TIMER3_OVF_vect) {
	measuring = 0;
}

void executeCMD() {
	switch(cmd) {
		case 0x00:
		usart_send((uint8_t)distances[0][0]);
		usart_send((uint8_t)distances[1][0]);
		usart_send((uint8_t)distances[2][0]);
		usart_send((uint8_t)distances[3][0]);
		usart_send((uint8_t)distances[4][0]);
		usart_send(driveState);
		break;
	case 0x01:
		driveState = arg1;
		break;
	case 0x02:
		motorPower = arg1;
		break;
		default:
		break;
	}
}

void smoothTurn(int target) {
	if (servoPos > target){
		if (turnDelay < 600){
			turnDelay++;
		}
		else {
			servoPos--;
			turnDelay = 0;
		}
	} 
	else if (servoPos < target){
		if (turnDelay < 600){
			turnDelay++;
		} 
		else {
			servoPos++;
			turnDelay = 0;
		}
		
	}
	setServo(servoPos);
}

void hardTurn(int target) {
	servoPos = target;
	setServo(servoPos);
}