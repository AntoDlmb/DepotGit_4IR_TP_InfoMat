#include "Driver_Servomoteur.h"

void update_angle_servomoteur(TIM_TypeDef * timer, int teta){
	
		//mise à jour du ratio de la pwm
		float rationPwm = (2*90.0-(float)teta)*100/(20*90); //ration de la pwm
	
		PWMRatio(timer, rationPwm, 1);
	
}
