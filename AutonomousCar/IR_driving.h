/*
 * IR_driving.h
 *
 * Created: 06-12-2018 15:36:04
 *  Author: Frederik Lund
 */ 


#ifndef IR_DRIVING_H_
#define IR_DRIVING_H_

uint16_t adc_read(uint8_t adc_channel);	//ADC Reading function
void test_function(void);	//Testing of IR-Sensors
void Driving(void);		//Value and motor change function
void Timer_init(void);	//16-bit timer for servo
void black_line(void);	//Black line follower prototype
void white_line(void);	//White line follower prototype

unsigned int IR0, IR1, IR2, IR3, IR4, IR5;	//mV values from IR-sensors
uint16_t adc_result_0, adc_result_1, adc_result_2, adc_result_3, adc_result_4, adc_result_5;	//measured data from IR-sensors
unsigned int x, y;	//limit value prototype



#endif /* IR_DRIVING_H_ */