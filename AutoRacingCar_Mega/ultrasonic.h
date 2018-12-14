/*
 * ultrasonic.h
 *
 * Created: 12/12/2018 11.21.29
 *  Author: skovm
 */ 


#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

void initTimer3();
void initUltrasonic();
int getDistance(uint8_t sensor);
void ultrasonicDriving();

#endif /* ULTRASONIC_H_ */