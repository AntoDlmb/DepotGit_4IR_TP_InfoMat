#include "Timer.h"

void (*MyCallback)(char); 

void USART_Base_Init(){
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    USART1->CR1 |= USART_CR1_UE; // Activation de l'USART
    USART1->CR1 &= ~USART_CR1_M; // Choix d'une taille de 8 bits de données
    USART1->CR2 &= USART_CR2_STOP; // Choix d'un seul bit de stop
    USART1->BRR |= 468 << 4; // Fixe le baud rate à 9600bps
		USART1->CR1 |= USART_CR1_RE;
		USART1->CR1 |= USART_CR1_RXNEIE;
	
}

void USART_ActiveReadIT(char prio, void (* IT_function)(char data)) {
	NVIC_EnableIRQ(USART1_IRQn);
	NVIC_SetPriority(USART1_IRQn, prio);
	MyCallback=IT_function;
}

void USART1_IRQHandler(void) {
	char data;
	
	data =USART1->DR ;
	MyCallback(data);
}
