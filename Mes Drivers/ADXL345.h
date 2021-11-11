#ifndef ADXL345_H
#define ADXL345_H
#include "stm32f10x.h"

void Read_Acceleration(void (* Callback)(short int y, short int z)); 

#endif