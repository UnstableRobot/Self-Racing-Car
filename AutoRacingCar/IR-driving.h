/*
 * IR_driving.h
 *
 * Created: 06-12-2018 15:36:04
 *  Author: Frederik Lund
 */ 


#ifndef IR-DRIVING_H_
#define IR-DRIVING_H_

uint16_t adc_read(uint8_t adc_channel);	//ADC Reading function
void test_function(void);	//Testing of IR-Sensors
void Driving(void);		//Value and motor change function
void Timer_init(void);

unsigned int IR0, IR1, IR2, IR3, IR6, IR7;	//enable only for test_function
uint16_t adc_result_0, adc_result_1, adc_result_2, adc_result_3, adc_result_6, adc_result_7;	//enable only for test_function




#endif /* IR-DRIVING_H_ */