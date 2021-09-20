#include"stm32f10x.h"
#include"MyTimer.h"

int main(void){
		
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	
	TIM2->ARR = 59999;
	TIM2->PSC = 599;
//	TIM2->CR1 = TIM2->CR1 | TIM_CR1_CEN;
	
	MyTimer_Base_Start TIM2;
	
	do{
		
	}while(1);
}
