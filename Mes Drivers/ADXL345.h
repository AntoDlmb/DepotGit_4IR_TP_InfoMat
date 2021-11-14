#ifndef ADXL345_H
#define ADXL345_H
#include "stm32f10x.h"

typedef struct {
	short int y;
	short int z;
} Acceleration_TypeDef;

void ADXL_Init(void);

Acceleration_TypeDef Read_Acceleration(void); 

#endif
