/*
 * ultrasonic.h
 *
 * Created: 12/12/2018 11.21.29
 *  Author: M.A.S
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

volatile uint8_t ultChannel;
volatile uint8_t measuring;
volatile int distance;

void initTimer3();
void initUltrasonic();
uint8_t trigUltrasonic(uint8_t sensor);
void ultrasonicDriving();

#endif /* ULTRASONIC_H_ */