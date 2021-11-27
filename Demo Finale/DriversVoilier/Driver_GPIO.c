#include "Driver_GPIO.h"

void MyGPIO_Init( MyGPIO_Struct_TypeDef * GPIOStructPtr){
	
	GPIOStructPtr -> GPIO -> CRL &= ~(0xF << (GPIOStructPtr->GPIO_Pin*4));
	
	GPIOStructPtr -> GPIO -> CRL |= (GPIOStructPtr->GPIO_Conf << GPIOStructPtr->GPIO_Pin*4);
}

int MyGPIO_Read( GPIO_TypeDef * GPIO, char GPIO_Pin){
	if (GPIO -> IDR & (0x1 << GPIO_Pin)) return 1;
	else return 0;
}

void MyGPIO_Set( GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR &= ~(0x01 << GPIO_Pin);
}

void MyGPIO_Reset( GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR |= (0x01 << GPIO_Pin);
}

void MyGPIO_Toggle( GPIO_TypeDef * GPIO, char GPIO_Pin){
	GPIO -> ODR ^= (0x01 << GPIO_Pin);
}
