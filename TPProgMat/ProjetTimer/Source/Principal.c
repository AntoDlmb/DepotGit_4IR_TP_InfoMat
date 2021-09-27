#include"stm32f10x.h"
#include"MyTimer.h"
#include"Driver_GPIO.h"
#define NO_PIN_LED 0

void Callback (void){
		
		MyGPIO_Toggle(GPIOA,NO_PIN_LED);
}


int main(void){
	
	MyTimer_Struct_TypeDef MyTimer = {TIM1 , 59999 , 599};
	
	MyGPIO_Struct_TypeDef mGPIOLED = {
		GPIOA,
		NO_PIN_LED,
		Out_Ppull
	};
	
		
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init(&mGPIOLED);
	MyGPIO_Set(GPIOA, NO_PIN_LED);

	MyTimer_Base_Init(&MyTimer);
	//MyPWM_Enable(TIM2,1);
	//MyPWM_SetRatio(TIM2,1,80);
	MY_TIMER_BASE_START(TIM1);
	MyTimer_ActiveIT(TIM1,1, Callback);
	do{
			
	}while(1);
}
