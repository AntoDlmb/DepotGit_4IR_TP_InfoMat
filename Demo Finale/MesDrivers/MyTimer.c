#include "MyTimer.h"
#include <stdio.h>

void (*pFnc) (void) = NULL;
void (* IT_function) (void);

void TIM1_UP_IRQHandler(){
		TIM1->SR = TIM1->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM2_IRQHandler(){
	TIM2->SR = TIM2->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM3_IRQHandler(){
	TIM3->SR = TIM3->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void TIM4_IRQHandler(){
	TIM4->SR = TIM4->SR & ~TIM_SR_UIF;
	
		if (pFnc != NULL)
			(*pFnc) ();
}


void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> timer -> ARR = Timer ->ARR;
	Timer -> timer -> PSC = Timer ->PSC;
}

void MyTimer_ActiveIT(TIM_TypeDef* Timer ,char Prio, void (*IT_function) (void)){
	
	//Timer -> DIER = Timer -> DIER | (1 << 0);
	//Timer -> CR1 = Timer -> CR1 | TIM1_CR1_CEN;
	Timer -> DIER = TIM_DIER_UIE;
	
	if (Timer == TIM1){ 
		NVIC_EnableIRQ(TIM1_UP_IRQn);
		NVIC_SetPriority(TIM1_UP_IRQn, (int)Prio);
	}else if (Timer == TIM2){
		NVIC_EnableIRQ(TIM2_IRQn);
		NVIC_SetPriority(TIM2_IRQn, (int)Prio);
	}else if (Timer == TIM3){
		NVIC_EnableIRQ(TIM3_IRQn);
		NVIC_SetPriority(TIM3_IRQn, (int)Prio);
	}else if (Timer == TIM4){
		NVIC_EnableIRQ(TIM4_IRQn);
		NVIC_SetPriority(TIM4_IRQn, (int)Prio);
	}
	
	pFnc = IT_function;
	
}

void MyTimer_PWM(TIM_TypeDef* Timer ,char Channel ){
	
	//mode 1 PWM
		if (Channel == 1){
			
			/*Timer -> CCMR1 = TIM_CCMR1_OC1M;
			Timer -> CCMR1 = TIM_CCMR1_CC1S;
			Timer -> CCMR1 = TIM_CCMR1_OC1PE;
			Timer -> CCER = TIM_CCER_CC1E;
			Timer -> CCER = TIM_CCER_CC1P;
			Timer -> CCER = TIM_CCER_CC1NE;
			Timer -> CR1 = TIM_CR1_ARPE;
			Timer -> EGR = TIM_EGR_UG;
			*/
			
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<6); //OC1M
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<5);//OC1M
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<4); //OC&M
			
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<0); // CC1S
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<1); // CC1S
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<3); // OCxPE
			
			
			Timer -> CR1 = Timer -> CR1 | (1 <<7); //ARPE
			Timer -> EGR = Timer -> EGR | (1 <<0); // UG bit
			
			Timer -> CCER = Timer -> CCER & ~(1<<1); // CC1P
			Timer -> CCER = Timer -> CCER | (1<<0); //CC1E
			Timer -> CCER = Timer -> CCER | (1<<2); //CC1NE
					
		} else if (Channel == 2) {
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<14); //OCxM
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<13);//OCxM
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<12); //OCxM
			
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<8); // CC1S
			Timer -> CCMR1 = Timer -> CCMR1 & ~(1 <<9); // CC1S
			Timer -> CCMR1 = Timer -> CCMR1 | (1 <<11); // OCxPE
			
			Timer -> CR1 = Timer -> CR1 | (1 <<7); //ARPE
			Timer -> EGR = Timer -> EGR | (1 <<0); // UG bit
			
			Timer -> CCER = Timer -> CCER & ~(1<<5); // CC2P
			Timer -> CCER = Timer -> CCER | (1<<4); //CC2E
			Timer -> CCER = Timer -> CCER | (1<<6); //CC2EN
			

	} else if (Channel == 3){
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<6); //OC3M
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<5); //OC3M
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<4); //OC3M
			
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<0); //CC3S
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<1); // CC3S
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<3); //OC3PE
			
			Timer -> CR1 = Timer -> CR1 | (1 <<7); //ARPE
			Timer -> EGR = Timer -> EGR | (1 <<0); // UG bit
			
			Timer -> CCER = Timer -> CCER & ~(1<<9); // CC3P
			Timer -> CCER = Timer -> CCER | (1<<8); //CC3E
			Timer -> CCER = Timer -> CCER | (1<<10); //CC3EN
			
		} else if  (Channel == 4) {
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<14); //OC4M
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<13);//OC4M
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<12);//OC4M
			
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<8); //CC3S
			Timer -> CCMR2 = Timer -> CCMR2 & ~(1 <<9);//CC3S
			Timer -> CCMR2 = Timer -> CCMR2 | (1 <<11);//OC4PE
			
			Timer -> CR1 = Timer -> CR1 | (1 <<7); //ARPE
			Timer -> EGR = Timer -> EGR | (1 <<0); // UG bit
				
			Timer -> CCER = Timer -> CCER & ~(1<<13); // CC4P
			Timer -> CCER = Timer -> CCER | (1<<12); //CC4E
			Timer -> CCER = Timer -> CCER | (1<<14); //CC4EN
		}

		

	//Timer -> BDTR = TIM_BDTR_MOE;
	//Timer -> BDTR = TIM_BDTR_OSSI;
	//Timer -> BDTR = TIM_BDTR_OSSR;
		
	Timer -> BDTR = Timer -> BDTR | (1<<15); //moe
	Timer -> BDTR = Timer -> BDTR | (1<<10); //ossi
	Timer -> BDTR = Timer -> BDTR | (1<<11); //ossR

	// edge aligned mode 
	//Timer -> CR1 = TIM_CR1_CMS_0;
	Timer -> CR1 = Timer -> CR1 & ~(1 << 6); // CMS edge aligned mode 
	Timer -> CR1 = Timer -> CR1 & ~(1 << 5); // CMS
}

void PWMRatio(TIM_TypeDef* Timer ,int ration, char Channel){
	int valeur = ration * (Timer -> ARR) /100;
	if (Channel == 1)
		Timer -> CCR1 = 	valeur;
	else if (Channel == 2)
		Timer -> CCR2 = 	valeur;
	else if (Channel == 3)
		Timer -> CCR3 = 	valeur;
	else if (Channel == 4)
		Timer -> CCR4 = 	valeur;
}

	
