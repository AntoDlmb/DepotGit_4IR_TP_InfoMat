#ifndef DRIVERSPI_H
#define DRIVERSPI_H
#include "stm32f10x.h"

void SPI_Base_Init(void);

char SPI_ReadWrite(char address) ;  

#endif
