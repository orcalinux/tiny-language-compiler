/**************************
 *
 * Module: HAL/Actuation/PWM
 *
 * File Name: pwm.c
 *
 * Description: Source file for the pwm peripheral
 *
 * Author: Ahmed Sanad
 *
 ***************************/

#include "pwm.h"

/***************************
 *                              Global Variables Declaration                   *
 ***************************/
static TIM_HandleTypeDef* LOC_pTimerHandler = NULL;


/***************************
 *                              Functions Definitions                           *
 ***************************/

/*
 * Description:
 * Send the pwm configuration after initization to the module.
 */
void PWM_vidInit(TIM_HandleTypeDef *pHtim)
{
  /*
   * send the timer handler declared in main to the module
   */
  LOC_pTimerHandler = pHtim;
}


/*
 * Description:
 *  the function sets the configuration for the PWM module: Duty Cycle and the frequency.
 */
void PWM_vidSetPWMConfig(uint32_t u32Channel, float fPWMDutyCycle,uint32_t u32PWMFreq)
 {
  /set the timer clock/
   uint32_t u32TimerClock = MAX_CLOCK_FREQUENCY;

   /set the prescaler value to adjust the frequency/
   uint32_t u32Prescaler = (u32TimerClock/(LOC_pTimerHandler->Init.Period * u32PWMFreq))-1;
   __HAL_TIM_SET_PRESCALER(LOC_pTimerHandler, u32Prescaler);

   /set the compare value to adjust the duty cycle/
   uint32_t u32CompareValue = ((fPWMDutyCycle * LOC_pTimerHandler->Init.Period)/100.0f) ;
   __HAL_TIM_SET_COMPARE(LOC_pTimerHandler, u32Channel, u32CompareValue);

   /start the pwm module/
   HAL_TIM_PWM_Start(LOC_pTimerHandler, u32Channel);
 }