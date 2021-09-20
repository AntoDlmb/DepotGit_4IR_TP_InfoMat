#include"stm32f10x.h"
#include"Driver_GPIO.h"

#define NO_PIN_LED 5
#define NO_PIN_BUTTON 13

int main(void){
	MyGPIO_Struct_TypeDef mGPIOLED = {
		GPIOA,
		NO_PIN_LED,
		Out_Ppull
	};
		MyGPIO_Struct_TypeDef mGPIOButton = {
		GPIOC,
		NO_PIN_BUTTON,
		In_Floating
	};
	MyGPIO_Init(&mGPIOLED);
	MyGPIO_Init(&mGPIOButton);
	
	do{
		/*
		* Quand on appui sur le bouton bleu, la LED s'allume.
		* Quand on relâche le bouton bleu, la LED s'éteint.
		*/
		if(MyGPIO_Read(GPIOC, NO_PIN_BUTTON)) {
			MyGPIO_Reset(GPIOA, NO_PIN_LED);
		} else {
			MyGPIO_Set(GPIOA, NO_PIN_LED);
		}
	}while(1);
}
