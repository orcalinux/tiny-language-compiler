/**************************
 *
 * Module: HAL/Actuation/PWM
 *
 * File Name: pwm.h
 *
 * Description: Header file for the pwm peripheral
 *
 * Author: Ahmed Sanad
 *
 ***************************/

#ifndef SOURCES_HAL_PWM_PWM_H_
#define SOURCES_HAL_PWM_PWM_H_

#include "stm32f4xx_hal.h"

/***************************
 *                                Definitions                                  *
 ***************************/
#define PWM_CHANNEL_1 TIM_CHANNEL_1
#define PWM_CHANNEL_2 TIM_CHANNEL_2
#define PWM_CHANNEL_3 TIM_CHANNEL_3
#define PWM_CHANNEL_4 TIM_CHANNEL_4
#define MAX_CLOCK_FREQUENCY 84000000

/***************************
 *                              Functions Prototypes                           *
 ***************************/

/*
 * Description:
 * the function sets the configuration for the PWM module: Duty Cycle and the frequency.
 */
void PWM_vidSetPWMConfig(uint32_t u32Channel, float fPWMDutyCycle, uint32_t u32PWMFreq);

/*
 * Description:
 * Send the i2c configuration after initization to the module.
 */
void PWM_vidInit(TIM_HandleTypeDef *pHtim);

#endif /* SOURCES_HAL_PWM_PWM_H_ */