#include"stm32f10x.h"
#include"MyTimer.h"
#include"Driver_GPIO.h"
#define OUT_PIN 8
#define TIMER TIM1

void Callback (void){
		
		MyGPIO_Toggle(GPIOA,OUT_PIN);
}


int main(void){
	
	MyTimer_Struct_TypeDef MyTimer = {TIMER , 719, 0};
	
	MyGPIO_Struct_TypeDef mGPIOLED = {
		GPIOA,
		OUT_PIN,
		AltOut_Ppull
	};
	
		
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	MyGPIO_Init(&mGPIOLED);
	MyGPIO_Set(GPIOA, OUT_PIN);

	MyTimer_Base_Init(&MyTimer);
	MyPWM_Enable(TIMER,1);
	MyPWM_SetRatio(TIMER,1,80);
	MY_TIMER_BASE_START(TIMER);
	//MyTimer_ActiveIT(TIMER,1, Callback);
	do{
			
	}while(1);
}
