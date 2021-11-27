#ifndef DRIVER_GPIO_H
#define DRIVER_GPIO_H

#include "stm32f10x.h"

typedef struct
{
GPIO_TypeDef * GPIO ;
char GPIO_Pin ; //numero de 0 a 15
char GPIO_Conf ; // voir ci dessous
} MyGPIO_Struct_TypeDef ;


#define In_Floating 0x4
#define In_PullDown 0x8
#define In_PullUp 0x8
#define In_Analog 0x0
#define Out_Ppull 0x2
#define Out_OD 0x6
#define AltOut_Ppull 0xA
#define AltOut_OD 0xE

/* * @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base sur le gpio
* @Note -> Fonction à lancer syst ématiquement pour initaliser et mettre en place les configurations
* spécifiées dans la structure en paramètre
*/
void MyGPIO_Init ( MyGPIO_Struct_TypeDef * GPIOStructPtr ) ;

/* * @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base sur le gpio et le port sur lequel le read se fera
* @Note -> cette fonction fait une lecture de la valeur contenue dans le bit du Input Data Register correspondant à la pin de gpio spécifiée
*/
int MyGPIO_Read(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

/* * @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base sur le gpio et le port sur lequel le set se fera
* @Note -> cette fonction écrit 0 dans le bit du Output Data Degister correspondant à la pin de gpio spécifiée
*/
void MyGPIO_Set(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

/* * @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base sur le gpio et le port sur lequel le reset se fera
* @Note -> cette fonction écrit 1 dans le bit du Output Data Degister correspondant à la pin de gpio spécifiée
*/
void MyGPIO_Reset(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

/* * @brief
* @param -> Paramètre sous forme d ’ une structure ( son adresse ) contenant les
informations de base sur le gpio et le port sur lequel le toggle se fera
* @Note -> cette fonction écrit 0 dans le bit du Output Data Degister correspondant à la pin de gpio spécifiée 
* si un 1 y était et 1 si c'etait un 0
*/
void MyGPIO_Toggle(GPIO_TypeDef * GPIO , char GPIO_Pin ) ;

#endif
