#include "Driver_SPI.h"


void Read_Acceleration(void (* Callback)(short int y, short int z)){
	short int y, z ;
	SPI1->CR1|=SPI_CR1_SPE;
	
	y=SPI_ReadWrite(0x34);
	y+=SPI_ReadWrite(0x35)<<8;
	
	z=SPI_ReadWrite(0x36);
	z+=SPI_ReadWrite(0x37)<<8;
	Callback(y,z);
}
