#include"MyTimer.h"

//checker timer1 
void (*MyCallback1)(void); 
void (*MyCallback2)(void); 
void (*MyCallback3)(void); 
void (*MyCallback4)(void); 
void MyTimer_Base_Init (MyTimer_Struct_TypeDef * Timer ) {
	Timer->Timer->ARR = Timer->ARR;
	Timer->Timer->PSC = Timer->PSC;

}

void MyTimer_ActiveIT (TIM_TypeDef * Timer, char prio, void (* IT_function)(void)){
	Timer->DIER |= (1 << 0);
	
	if (Timer==TIM1) {
		NVIC_EnableIRQ(TIM1_CC_IRQn);
		NVIC_SetPriority(TIM1_CC_IRQn,prio);
		MyCallback1=IT_function;
	}else if (Timer==TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn,prio);
		MyCallback2=IT_function;
	}else if (Timer==TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn,prio);
		MyCallback3=IT_function;
	}else{
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn,prio);
		MyCallback4=IT_function;
	}
	

	
}
void TIM1_CC_IRQHandler(void){
	TIM1->SR &= ~TIM_SR_UIF;
	MyCallback1();
}
void TIM2_IRQHandler(void){
	TIM2->SR &= ~TIM_SR_UIF;
	MyCallback2();
}
void TIM3_IRQHandler(void){
	TIM3->SR &= ~TIM_SR_UIF;
	MyCallback3();
}
void TIM4_IRQHandler(void){
	TIM4->SR &= ~TIM_SR_UIF;
	MyCallback4();
}
