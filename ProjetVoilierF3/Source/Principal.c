#include"stm32f10x.h"
#include"MyTimer.h"
#include"Driver_GPIO.h"
#include"Driver_USART.h"
#include "Driver_SPI.h"
#define USART_TX 9
#define USART_RX 10 //D2
#define PWM_PIN 8 //D7
#define SENS_PIN 9 //D8
#define TIMER TIM1
MyGPIO_Struct_TypeDef mGPIOsens = {
		GPIOA,
		SENS_PIN,
		Out_Ppull
	};

void Callback(char data) {
	char sens = (data & 0x80)>>7;
	char alpha = data & 0x7F;
	
	if (sens){
		alpha=128-alpha;
		MyGPIO_Set (mGPIOsens.GPIO, SENS_PIN);
	}else{
		MyGPIO_Reset (mGPIOsens.GPIO, SENS_PIN);
	}
	MyPWM_SetRatio(TIMER,1,alpha);
	
} 


int main(void){
	
	MyTimer_Struct_TypeDef MyTimer = {TIMER , 3599, 0};
	

	MyGPIO_Struct_TypeDef mGPIOUSART = {
		GPIOA,
		USART_RX,
		In_Floating
	};
	
	MyGPIO_Struct_TypeDef mGPIOPWM = {
		GPIOA,
		PWM_PIN,
		AltOut_Ppull
	};
		
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;
	USART_Base_Init();

	MyGPIO_Init(&mGPIOUSART);
	MyGPIO_Init(&mGPIOPWM);
	MyGPIO_Init(&mGPIOsens);
	
	//Comment gérer la clock ?
	//faire interruption régulières  pour Read_Acceleration
	SPI_Base_Init();

	MyTimer_Base_Init(&MyTimer);
	MyPWM_Enable(TIMER,1);
	MY_TIMER_BASE_START(TIMER);
	USART_ActiveReadIT(1, Callback);
	do{
			
	}while(1);
}
