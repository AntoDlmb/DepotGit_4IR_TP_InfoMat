#include "Driver_GPIO.h"

void MyGPIO_Init(MyGPIO_Struct_TypeDef * GPIOStructPtr) {
	GPIO_TypeDef * Port = GPIOStructPtr->GPIO;
	char pinNumber = GPIOStructPtr->GPIO_Pin;
	char config = GPIOStructPtr->GPIO_Conf;
	
	if (pinNumber < 8) {
		Port->CRL &= ~(0xF << 4*pinNumber);
		Port->CRL |= (config << 4*pinNumber);
	} else {
		Port->CRH &= ~(0xF << 4*(pinNumber%8));
		Port->CRH |= (config << 4*(pinNumber%8));
	}
	
}

int MyGPIO_Read(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	return GPIO->IDR & (0x1 << GPIO_Pin);
}

void MyGPIO_Set(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIO->ODR |= (0x1 << GPIO_Pin);
}

void MyGPIO_Reset(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	GPIOA->ODR &= ~(0x1 << GPIO_Pin);
}

void MyGPIO_Toggle(GPIO_TypeDef * GPIO, char GPIO_Pin) {
	if(MyGPIO_Read(GPIO, GPIO_Pin)) {
			MyGPIO_Reset(GPIO, GPIO_Pin);
		} else {
			MyGPIO_Set(GPIO, GPIO_Pin);
		}
}
