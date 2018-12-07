/*
 * ultrasonic.h
 *
 * Created: 05/12/2018 13.25.41
 *  Author: M.A.S
 */ 



#ifndef ULTRASONIC_H_
#define ULTRASONIC_H_

void initTimer2();
void initUltrasonic();
int getDistance(uint8_t sensor);
void ultrasonicDriving();

#endif /* ULTRASONIC_H_ */