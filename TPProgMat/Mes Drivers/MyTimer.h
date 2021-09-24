#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
	TIM_TypeDef * Timer ; // TIM1 à TIM4
	unsigned short ARR ;
	unsigned short PSC ;
} MyTimer_Struct_TypeDef ;

/*
*****************************************************************************************
* @brief
* @param -> Paramè t r e sous forme d ’ une s t r u c t u r e ( son a d re s se ) con ten an t l e s
i n f o rm a ti o n s de base
* @Note -> F onc ti on à l a n c e r s y s t ématiquement avan t d ’ a l l e r pl u s en dé t a i l dans l e s
con f pl u s f i n e s (PWM, codeur i n c . . . )
*************************************************************************************************
*/
void MyTimer_Base_Init (MyTimer_Struct_TypeDef * Timer ) ;
void MyTimer_ActiveIT (TIM_TypeDef * Timer, char prio, void (* IT_function)(void));
#define MY_TIMER_BASE_START(Timer) (Timer->CR1 |= TIM_CR1_CEN)
#define MY_TIMER_BASE_STOP(Timer) (Timer->CR1 &= ~(TIM_CR1_CEN))
#endif
