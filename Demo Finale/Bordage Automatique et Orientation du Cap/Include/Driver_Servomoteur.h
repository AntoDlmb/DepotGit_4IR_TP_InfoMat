#ifndef DRIVER_SERVOMOTEUR_H
#define DRIVER_SERVOMOTEUR_H
#include "stm32f10x.h"
#include "Timer.h"
/* **@brief
*@param -> addresse du timer associé à la pwm et l'angle des voiles à communiquer au servomoteur
*@Note -> Communique au servomoteur l'angle des voiles en émettant une pwm avec le ratio correspondant*/
void update_angle_servomoteur(TIM_TypeDef * timer, int teta);

/* **@brief
*@Note -> calcul l'angle des voiles correspondant à la direction du vent et mets à jour le servomoteur*/
void cacul_angle_servo(void);
#endif
