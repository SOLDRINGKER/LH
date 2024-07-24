/*
 * buzzer.h
 *
 *  Created on: Jul 6, 2024
 *      Author: wx
 */

#ifndef INC_BUZZER_H_
#define INC_BUZZER_H_

#include "main.h"

#define MAX_PSC                 1000

#define MAX_BUZZER_PWM      20000
#define MIN_BUZZER_PWM      10000

void buzzer_on(uint16_t psc, uint16_t pwm);
void buzzer_off(void);
void buzzer();

#endif /* INC_BUZZER_H_ */
