#include"stm32f10x.h"
#include"MyTimer.h"
#include"Driver_GPIO.h"
#include"Driver_USART.h"
#include "ADXL345.h"
#define USART_RX 10 //D2
#define PWM_PIN 8 //D7
#define SENS_PIN 9 //D8
#define TIMER_PWM TIM1
#define TIMER_ADXL TIM4

MyGPIO_Struct_TypeDef mGPIOsens = {
		GPIOA,
		SENS_PIN,
		Out_Ppull
	};

void Dir_Callback(char data) {
	char sens = (data & 0x80)>>7;
	char alpha = data & 0x7F;
	
	if (sens){
		alpha = 128-alpha;
		MyGPIO_Set (mGPIOsens.GPIO, SENS_PIN);
	}else{
		MyGPIO_Reset (mGPIOsens.GPIO, SENS_PIN);
	}
	MyPWM_SetRatio(TIMER_PWM,1,alpha);
	
}

void ADXL_Callback() {
	Acceleration_TypeDef acc = Read_Acceleration();
	short int y = acc.y;
	short int z = acc.z;
}


int main(void){
	
	MyTimer_Struct_TypeDef PWM_Timer = {TIMER_PWM, 3599, 0};
	MyTimer_Struct_TypeDef ADXL_Timer = {TIMER_ADXL, 59999, 11};
	

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
		
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPBEN;
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

	MyGPIO_Init(&mGPIOUSART);
	MyGPIO_Init(&mGPIOPWM);
	MyGPIO_Init(&mGPIOsens);
	
	MyTimer_Base_Init(&PWM_Timer);
	MyPWM_Enable(TIMER_PWM,1);
	MY_TIMER_BASE_START(TIMER_PWM);
	
	USART_Base_Init();
	USART_ActiveReadIT(2, Dir_Callback);
	
	ADXL_Init();
	MyTimer_Base_Init(&ADXL_Timer);
	MyTimer_ActiveIT(TIMER_ADXL, 1, ADXL_Callback);
	MY_TIMER_BASE_START(TIMER_ADXL);	

	do{
	}while(1);
}
