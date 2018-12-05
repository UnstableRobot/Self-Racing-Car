/*
 * PWM.h
 *
 * Created: 05/12/2018 13.59.23
 *  Author: M.A.S
 */ 


#ifndef PWM_H_
#define PWM_H_

void initMotor();
void initServo();

void setMotor(uint8_t power);
void setServo(uint8_t position);

#endif /* PWM_H_ */