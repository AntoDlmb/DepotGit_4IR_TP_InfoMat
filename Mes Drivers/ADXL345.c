#include "Driver_SPI.h"
#include "Driver_GPIO.h"
#include "ADXL345.h"

#define MISO_PIN 6
#define MOSI_PIN 7
#define CLOCK_PIN 5
#define NSS_PIN 4
#define CS_PIN 2

MyGPIO_Struct_TypeDef GPIO_MISO = {
		GPIOA,
		MISO_PIN,
		AltOut_Ppull
	};
MyGPIO_Struct_TypeDef GPIO_MOSI = {
		GPIOA,
		MOSI_PIN,
		AltOut_Ppull
	};
MyGPIO_Struct_TypeDef GPIO_Clock = {
		GPIOA,
		CLOCK_PIN,
		AltOut_Ppull
	};
MyGPIO_Struct_TypeDef GPIO_CS = {
		GPIOB,
		CS_PIN,
		Out_Ppull
	};
	
void ADXL_Init(){
	SPI_Base_Init();
	MyGPIO_Init(&GPIO_MISO);
	MyGPIO_Init(&GPIO_MOSI);
	MyGPIO_Init(&GPIO_Clock);
	MyGPIO_Init(&GPIO_CS);
}

Acceleration_TypeDef Read_Acceleration(){
	Acceleration_TypeDef acc;
	//mettre le NSS à 1 et le CS à 0 pendant utilisation sinon CS à 1
	SPI1->CR1|= SPI_CR1_SPE;
	MyGPIO_Reset(GPIOB, CS_PIN);
	
	acc.y = SPI_ReadWrite(0x34);
	acc.y += SPI_ReadWrite(0x35)<<8;
	
	acc.z = SPI_ReadWrite(0x36);
	acc.z += SPI_ReadWrite(0x37)<<8;
	
	MyGPIO_Set(GPIOB, CS_PIN);
	SPI1->CR1 &= ~SPI_CR1_SPE;
	return acc;
}
