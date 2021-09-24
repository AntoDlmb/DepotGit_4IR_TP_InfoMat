#include"stm32f10x.h"
#include"MyTimer.h"
#include"Driver_GPIO.h"
#define NO_PIN_LED 5

void Callback (void){
		
		MyGPIO_Toggle(GPIOA,NO_PIN_LED);
}


int main(void){
	
	MyTimer_Struct_TypeDef MyTimer = {TIM2 , 59999 , 599};
	
	MyGPIO_Struct_TypeDef mGPIOLED = {
		GPIOA,
		NO_PIN_LED,
		Out_Ppull
	};
	
		
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init(&mGPIOLED);
	MyGPIO_Set(GPIOA, NO_PIN_LED);

	MyTimer_Base_Init(&MyTimer);
	MY_TIMER_BASE_START(TIM2);
	MyTimer_ActiveIT(TIM2,1, Callback);
	do{
		
	}while(1);
}
