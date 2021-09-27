#include"MyTimer.h"
#define PWM_MODE_1 0x6

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
		NVIC_EnableIRQ(TIM1_UP_IRQn );
		NVIC_SetPriority(TIM1_UP_IRQn ,prio);
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
void TIM1_UP_IRQHandler(void){
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

void MyPWM_Enable (TIM_TypeDef * Timer ,char Channel){
	
	if (Channel==1) {
		Timer->CCER |= TIM_CCER_CC1E;
		Timer->CCMR1 &= ~TIM_CCMR1_OC1M;
		Timer->CCMR1 |= TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1M_2;
		
	}else if (Channel==2){
		Timer->CCER |= TIM_CCER_CC2E;
		Timer->CCMR1 &= ~TIM_CCMR1_OC2M;
		Timer->CCMR1 |= TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2M_2;
	}else if (Channel==3){
		Timer->CCER |= TIM_CCER_CC3E;
		Timer->CCMR2 &= ~TIM_CCMR2_OC3M;
		Timer->CCMR2 |= TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3M_2;
	}else{
		Timer->CCER |= TIM_CCER_CC4E;
		Timer->CCMR2 &= ~TIM_CCMR2_OC4M;
		Timer->CCMR2 |= TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4M_2;
		
	}
}


void MyPWM_SetRatio(TIM_TypeDef * Timer ,char Channel, char ratio){
	if (Channel==1) {
		Timer->CCR1=ratio*(Timer->ARR+1)/100;
	}else if (Channel==2){
		Timer->CCR2=ratio*(Timer->ARR+1)/100;
	}else if (Channel==3){
		Timer->CCR3=ratio*(Timer->ARR+1)/100;
	}else{
		Timer->CCR4=ratio*(Timer->ARR+1)/100;
	}
	
}


























