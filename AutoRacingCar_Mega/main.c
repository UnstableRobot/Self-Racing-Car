/*
 * AutoRacingCar_Mega.c
 *
 * Created: 12/12/2018 11.08.05
 * Author : M.A.S
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include "ultrasonic.h"
#include "usart.h"
#include "PWM.h"

void getAverage(uint8_t sensor);
void executeCMD();

int distances[5][6];
int txTime = 0;

uint8_t driveMode = 0;
uint8_t motorPower;

int main(void) {
	TCCR5B |= (1<<CS51) | (1<<CS50);
	init_motor(0);
	initServo();
    initTimer3();
	initUltrasonic();
	usart_Init();
	
	
    while (1) {
		if(driveMode == 1) {
			motorPower = 50;
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

void executeCMD() {
	switch(cmd) {
		case 0x00:
		TCNT5 = 0;
		getAverage(0);
		getAverage(1);
		getAverage(2);
		getAverage(3);
		getAverage(4);
		txTime = TCNT5;
		usart_send((uint8_t)distances[0][0]);
		usart_send((uint8_t)distances[1][0]);
		usart_send((uint8_t)distances[2][0]);
		usart_send((uint8_t)distances[3][0]);
		usart_send((uint8_t)distances[4][0]);
		usart_send(motorPower);
		
		usart_send((uint8_t)txTime);
		usart_send((uint8_t)(txTime>>8));
		break;
	case 0x01:
		driveMode = arg1;
		break;
		default:
		break;
	}
}

void getAverage(uint8_t sensor) {
	distances[sensor][5] = distances[sensor][4];
	distances[sensor][4] = distances[sensor][3];
	distances[sensor][3] = distances[sensor][2];
	distances[sensor][2] = distances[sensor][1];
	distances[sensor][1] = getDistance(sensor);
	
	distances[sensor][0] = (distances[sensor][1] + distances[sensor][2] + distances[sensor][3] + distances[sensor][4] + distances[sensor][5])/5;
}