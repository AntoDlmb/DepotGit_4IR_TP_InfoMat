#include "MyTimer.h"
#include "Driver_GPIO.h"
#include <stdio.h>

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer ){
	Timer -> timer -> ARR = Timer ->ARR;
	Timer -> timer -> PSC = Timer ->PSC;
}
void MyTimer_EncoderMode( MyTimer_Struct_TypeDef * Timer ){

	// Counting on Tl1 and Tl2 SMS = 011
	Timer -> timer -> TIM_SMCR_SMS_0 = 0;
	Timer -> timer -> TIM_SMCR_SMS_1 = 1;
	Timer -> timer -> TIM_SMCR_SMS_2 = 1;
	
	// Enabling 
	Timer -> timer -> TIM_CR1_CEN = 1;
	
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