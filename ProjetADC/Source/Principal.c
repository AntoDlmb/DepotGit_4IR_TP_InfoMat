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
	RCC->APB2ENR |= RCC_APB2ENR_ADC2EN;
	MyGPIO_Init(&mGPIOLED);

	MyTimer_Base_Init(&MyTimer);
	MY_TIMER_BASE_START(TIMER);
	
	ADC2->CR2 |= ADC_CR2_ADON;
	/*while(ADC2->CR2 & ADC_CR2_ADON) {
	}
	ADC2->CR2 |= ADC_CR2_ADON;*/
	ADC2->CR1 |= ADC_CR1_EOCIE;
	NVIC_EnableIRQ();
	NVIC_SetPriority(TIM1_UP_IRQn ,prio);
	do{
			
	}while(1);
}
