#ifndef DRIVERUSART_H
#define DRIVERUSART_H
#include "stm32f10x.h"

void USART_Base_Init(void);

void USART_ActiveReadIT(char prio, void (* IT_function)(char data));

#endif
