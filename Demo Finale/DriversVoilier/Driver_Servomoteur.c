#include "Driver_Servomoteur.h"

extern MyTimer_Struct_TypeDef TimerE;
extern MyTimer_Struct_TypeDef TimerP;

void update_angle_servomoteur(TIM_TypeDef * timer, int teta){
	
		//mise à jour du ratio de la pwm
		float rationPwm = (2*90.0-(float)teta)*100/(20*90); //ration de la pwm
	
		PWMRatio(timer, rationPwm, 1);
	
}

void cacul_angle_servo(){
		int k = TimerE.timer -> CNT; // valeur à recuperer du encoder mode
	
		// calcul de alpha (angle du vent) à partir de k sachant que la resolution c'est arr cad 360*4
		int alpha = k/4;
		int teta=0;
		//calcul du teta (angle des voile) correspondant à la valeur de alpha
		if (alpha >= 45 && alpha <= 180 )
			teta = (90*alpha  -30*135)/135;
		else if (alpha >180 && alpha<=315)
			teta = (-90*alpha  +210*135)/135;
		else 
			teta = 0;
		update_angle_servomoteur(TimerP.timer, teta);
}
