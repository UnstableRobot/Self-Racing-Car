/*
 * PWM.h
 *
 * Created: 13/12/2018 10.07.44
 *  Author: M.A.S
 */ 


#ifndef PWM_H_
#define PWM_H_

void init_motor(int duty);
void setMotor(uint8_t duty);
void initServo();
void setServo(int position);

#endif /* PWM_H_ */