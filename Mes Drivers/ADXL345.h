#ifndef ADXL345_H
#define ADXL345_H
#include "stm32f10x.h"

void Init_ADXL(GPIO_TypeDef * CS_GPIO, char csPin);

void Read_Acceleration(void (* Callback)(short int y, short int z)); 

#endif