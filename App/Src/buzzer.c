/*
 * buzz.c
 *
 *  Created on: Jul 6, 2024
 *      Author: wx
 */
#include "buzzer.h"
#include "main.h"




extern TIM_HandleTypeDef htim4;
void buzzer_on(uint16_t psc, uint16_t pwm)
{

    __HAL_TIM_PRESCALER(&htim4, psc);
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, pwm);

}

void buzzer()
{
	uint16_t psc = 0;
	uint16_t pwm = MIN_BUZZER_PWM;
	for(int i=0;i<200;i++)
	{
		pwm++;
		psc++;

		if(pwm > MAX_BUZZER_PWM)
		{
		    pwm = MIN_BUZZER_PWM;
		}
		if(psc > MAX_PSC)
		{
		    psc = 0;
		}
		buzzer_on(psc, pwm);
		HAL_Delay(5);
	}
}

void buzzer_off(void)
{
    __HAL_TIM_SetCompare(&htim4, TIM_CHANNEL_3, 0);
}


