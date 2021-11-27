#ifndef MYTIMER_H
#define MYTIMER_H
#include "stm32f10x.h"

typedef struct
{
TIM_TypeDef * timer ; // TIM1 à TIM4
unsigned short ARR;
unsigned short PSC;
} MyTimer_Struct_TypeDef;

/*
*****************************************************************************************
* @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base
* @Note -> Fonction à lancer syst ématiquement avant d’aller plus en détail dans les
configurations plus fines (PWM, codeur inc . . . )
*************************************************************************************************
*/

void MyTimer_Base_Init ( MyTimer_Struct_TypeDef * Timer );

#define MyTimer_Base_Start( Timer ) ((Timer).timer ->CR1 = (Timer).timer ->CR1 | ( 1 << 0))

#define MyTimer_Base_Stop( Timer ) (((Timer).timer-> SR & TIM_SR_UIF) ? (1) : (Timer).timer ->CR1 = (Timer).timer ->CR1 & ~( 1 << 0) )

/* **@brief
*@param-> Paramètre sous forme d’une structure ( son adresse ) contenant les
informations de base sur le timer
*@Note    Active  le mode Encoder sur le timer spécifié par la structure
*la  gestion  de  la  configuration I/O n’est pas  faite dans cette fonction*/
void MyTimer_EncoderMode( MyTimer_Struct_TypeDef * Timer );

/* **@brief
*@param -> une structure contenant les informations de base sur le timer associé à la pwm et
*le channel sur laquelle la pwm sera émise 
*@Note    Active  le mode pwm sur le timer spécifié et acitve le  channel spécifié sur ce dernier
*la  gestion  de  la  configuration I/O n’est pas  faite dans cette fonction
*ni  le  réglage de la période de la PWM (ARR, PSC)*/
void MyTimer_PWM_Enable(TIM_TypeDef* Timer ,char Channel );

/* **@brief
*@param  -> une structure contenant les informations sur le timer associé, 
* le ration de la pwm à mettre en oeuvre et le channel sur lequel la pwm sera émise
*@Note   Communique au timer le ration de la pwm à émetrre*/
void PWMRatio(TIM_TypeDef* Timer ,float ratio, char Channel);

/* **@brief
*@Note   Cette fonction initialise une external interupt servant à remettre à 0 le compteur du Timer 
*en Encoder mode*/
void init_EXIT(char prio);

#endif
