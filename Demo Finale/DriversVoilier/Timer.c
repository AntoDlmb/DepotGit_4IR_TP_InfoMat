#include "Timer.h"

extern MyTimer_Struct_TypeDef TimerE; //Timer du principal.c en mode Encoder

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> timer -> ARR = Timer ->ARR;
	Timer -> timer -> PSC = Timer ->PSC;
}

void MyTimer_EncoderMode( MyTimer_Struct_TypeDef * Timer ){

	// Counting on Tl1 and Tl2 SMS = 011
	Timer -> timer -> SMCR |= TIM_SMCR_SMS_0;
	Timer -> timer -> SMCR |=TIM_SMCR_SMS_1;
	Timer -> timer -> SMCR &= ~TIM_SMCR_SMS_2;
	
	
	//input mode
	Timer -> timer ->CCMR1 &= ~TIM_CCMR1_CC1S_1;
	Timer -> timer ->CCMR1 |= TIM_CCMR1_CC1S_0;
	
	Timer -> timer ->CCMR1 &= ~TIM_CCMR1_CC2S_1;
	Timer -> timer ->CCMR1 |= TIM_CCMR1_CC2S_0;
	
	Timer -> timer -> CCER &= ~TIM_CCER_CC1P;
	Timer -> timer -> CCER &= ~TIM_CCER_CC2P;
	
	// Enabling 
	Timer -> timer -> CR1 |= TIM_CR1_CEN;
}

void MyTimer_PWM_Enable(TIM_TypeDef* Timer ,char Channel ){
	
	//mode 1 PWM
		if (Channel == 1){
			
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
		
	Timer -> BDTR = Timer -> BDTR | (1<<15); //moe
	Timer -> BDTR = Timer -> BDTR | (1<<10); //ossi
	Timer -> BDTR = Timer -> BDTR | (1<<11); //ossR

	Timer -> CR1 = Timer -> CR1 & ~(1 << 6); // CMS edge aligned mode 
	Timer -> CR1 = Timer -> CR1 & ~(1 << 5); // CMS
}

void PWMRatio(TIM_TypeDef* Timer ,float ratio, char Channel){
	int valeur = (int)(ratio * (Timer -> ARR+1) /100);
	if (Channel == 1)
		Timer -> CCR1 = 	valeur;
	else if (Channel == 2)
		Timer -> CCR2 = 	valeur;
	else if (Channel == 3)
		Timer -> CCR3 = 	valeur;
	else if (Channel == 4)
		Timer -> CCR4 = 	valeur;
}


void init_EXIT(char prio){
	EXTI ->IMR |= EXTI_IMR_MR0; // enable interrupt request
	EXTI->RTSR |= EXTI_RTSR_TR0; //rising trigger enable (détecte le front montant)
	
	AFIO -> EXTICR[0] |= AFIO_EXTICR1_EXTI0_PB; // input interuption vient de pb0
	
	//EXTI0 line 6 of nvic
	NVIC_EnableIRQ(EXTI0_IRQn);
	NVIC_SetPriority(EXTI0_IRQn, prio);
}

void EXTI0_IRQHandler(){
	EXTI->PR |= EXTI_PR_PR0; //remise à 0 du pending bit
	TimerE.timer -> CNT = 0;
}


