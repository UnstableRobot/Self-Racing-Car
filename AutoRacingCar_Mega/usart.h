/*
 * usart.h
 *
 * Created: 12/12/2018 11.33.33
 *  Author: M.A.S
 */ 


#ifndef USART_H_
#define USART_H_

#define F_CPU 16000000UL
#define BAUDRATE 9600
#define BAUD_PRESCALER (((F_CPU / (BAUDRATE * 16UL))) - 1)

volatile char cmd;
volatile char arg1;
volatile char arg2;
volatile char argIndex;

void usart_Init();
void usart_send(unsigned char data);
int getCommand();

#endif /* USART_H_ */