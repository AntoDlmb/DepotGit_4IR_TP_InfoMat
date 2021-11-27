#include "stm32f10x.h"
#include "Timer.h"
#include "Driver_GPIO.h"
#include "Driver_Servomoteur.h"
#include "Driver_USART.h"

#define USART_RX 10 //D2
#define PWM_CAP_PIN 8 //D7
#define SENS_CAP_PIN 9 //D8
#define TIMER_CAP_PWM TIM1

MyGPIO_Struct_TypeDef mGPIO_sens = {
		GPIOA,
		SENS_CAP_PIN,
		Out_Ppull
};

MyGPIO_Struct_TypeDef mGPIO_USART = {
		GPIOA,
		USART_RX,
		In_Floating
};
	
MyGPIO_Struct_TypeDef mGPIO_cap_PWM = {
		GPIOA,
		PWM_CAP_PIN,
		AltOut_Ppull
};

void Callback_USART(char data) {
	char sens = (data & 0x80)>>7;
	char alpha = data & 0x7F;
	
	if (sens){
		alpha=128-alpha;
		MyGPIO_Set (mGPIO_sens.GPIO, SENS_CAP_PIN);
	}else{
		MyGPIO_Reset (mGPIO_sens.GPIO, SENS_CAP_PIN);
	}
	PWMRatio(TIMER_CAP_PWM,alpha,1);
}

MyTimer_Struct_TypeDef mTimer_cap_PWM = {TIMER_CAP_PWM , 3599, 0};

MyTimer_Struct_TypeDef TimerE; // Timer qui sera en encoder mode, le nom de cette variable n'est pas à modifier par l'utilisateur
															// car elle est utilisé par le driver Timer.c
														
MyTimer_Struct_TypeDef TimerP; //timer permettant d'emettre la pwm pour le servomoteur

MyGPIO_Struct_TypeDef inputEncoderA; // Port de gpio pour le signal A de la girouette
MyGPIO_Struct_TypeDef inputEncoderB; // port gpio pour le signal B de la girouette
MyGPIO_Struct_TypeDef inputEncoderI; // Port gpio pour le signal I de la girouette


MyGPIO_Struct_TypeDef outputPwm; // port de gpio sortant la pwm

int k=0; // valeur pour calculer 'a (correspond au cnt du timer en encoder mode
int alpha=0; //angle de la girouette
int teta = 0; // angle des voiles

int main (){
	
	//enable des gpio, des timers et des afio
	RCC->APB2ENR |= (0x01 << 2) | (0x01 << 3) | (0x01 << 4) ;
	RCC->APB2ENR |= RCC_APB2ENR_TIM1EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	RCC->APB1ENR |= RCC_APB1ENR_TIM3EN;
	RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;
	
	//config des gpio pour le encoder mode
	inputEncoderA.GPIO = GPIOA;
	inputEncoderA.GPIO_Conf = In_Floating;
	inputEncoderA.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoderA);
	
	inputEncoderB.GPIO = GPIOA;
	inputEncoderB.GPIO_Conf = In_Floating;
	inputEncoderB.GPIO_Pin = 0x01;
	MyGPIO_Init(&inputEncoderB);
	
	inputEncoderI.GPIO = GPIOB;
	inputEncoderI.GPIO_Conf = In_Floating;
	inputEncoderI.GPIO_Pin = 0x00;
	MyGPIO_Init(&inputEncoderI);
	
	//config gpio cap
	MyGPIO_Init(&mGPIO_USART);
	MyGPIO_Init(&mGPIO_cap_PWM);
	MyGPIO_Init(&mGPIO_sens);
	
	//config timer & USART cap
	USART_Base_Init();
	MyTimer_Base_Init(&mTimer_cap_PWM);
	MyTimer_PWM_Enable(TIMER_CAP_PWM,1);
	MyTimer_Base_Start(mTimer_cap_PWM);
	USART_ActiveReadIT(2, Callback_USART);
	
	//config timer pour le encoder mode
	TimerE.timer = TIM2;
	TimerE.ARR = 360*4; // resolution
	TimerE.PSC = 0;
	MyTimer_Base_Init(&TimerE);
	MyTimer_Base_Start(TimerE);
	MyTimer_EncoderMode(&TimerE);
	
	//config des gpio pour la pwm
	outputPwm.GPIO = GPIOA;
	outputPwm.GPIO_Conf = AltOut_Ppull;
	outputPwm.GPIO_Pin = 0x06;
	MyGPIO_Init(&outputPwm);
	
	//config timer pour la pwm
	TimerP.timer = TIM3;
	// periode de 20ms = psc * arr / 72MHz => psc = 20ms * 72 MHz / arr
	TimerP.ARR = 65454; // resolution
	TimerP.PSC = 20 * 72000000 / (65454 * 1000);
	MyTimer_Base_Init(&TimerP);
	MyTimer_Base_Start(TimerP);
	
	
	//config pwm
	MyTimer_PWM_Enable(TimerP.timer ,1);
	PWMRatio(TimerP.timer, 10.0, 1); //ratio de 10 par défault correspondant à un angle de 0°
	
	//init interrution pour remettre à 0 l'angle après un tour complet
	init_EXIT(1); 

	while(1){
		
		k = TimerE.timer -> CNT; // valeur à recuperer du encoder mode
		
		// calcul de alpha à partir de k sachant que la resolution c'est arr
		alpha = k/4;
	
		//calcul du teta correspondant à la valeur de alpha
		if (alpha >= 45 && alpha <= 180 )
			teta = (90*alpha  -30*135)/135;
		else if (alpha >180 && alpha<=315)
			teta = (-90*alpha  +210*135)/135;
		else 
			teta = 0;
		
		update_angle_servomoteur(TimerP.timer, teta);
	}
	
}

