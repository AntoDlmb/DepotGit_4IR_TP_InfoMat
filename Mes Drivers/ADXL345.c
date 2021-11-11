#include "Driver_SPI.h"
#include"Driver_GPIO.h"

void Init_ADXL(MyGPIO_Struct_TypeDef* GPIO_CS){
	MyGPIO_Init(GPIO_CS);
}

void Read_Acceleration(void (* Callback)(short int y, short int z)){
	//mettre le NSS � 1 et le CS � 0 pendant utilisation sinon CS � 0
	short int y, z ;
	SPI1->CR1|=SPI_CR1_SPE;
	
	y=SPI_ReadWrite(0x34);
	y+=SPI_ReadWrite(0x35)<<8;
	
	z=SPI_ReadWrite(0x36);
	z+=SPI_ReadWrite(0x37)<<8;
	Callback(y,z);
}
