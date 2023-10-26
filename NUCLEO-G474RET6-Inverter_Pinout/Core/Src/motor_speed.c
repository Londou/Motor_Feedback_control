/*
 * motor_speed.c
 *
 *  Created on: Oct 20, 2023
 *      Author: Erika
 */
#include "tim.h"
#include "usart.h"
#include <stdio.h>
#include <string.h>
#include "gpio.h"
#include <math.h>

int         alpha = 512;
int         value;
#define Speed_Max 3000 //rpm

void set_PWM(void){

	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIM_PWM_Start(&htim1, TIM_CHANNEL_2);
	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_1);
	  HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alpha);
	__HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, alpha);

}


void set_motor_speed(int speed){
	if(speed > Speed_Max) speed = Speed_Max;
	if(speed < -Speed_Max) speed = -Speed_Max;
	int alpha_target = (speed + Speed_Max)*512/Speed_Max;

    while (alpha!=alpha_target){
 	   if(alpha<alpha_target) alpha++;
	   if(alpha>alpha_target) alpha--;
       __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_1, alpha);
       __HAL_TIM_SET_COMPARE(&htim1, TIM_CHANNEL_2, (1024-alpha));
       HAL_Delay(10);
  }

}

void deactivate_PWM(void){
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIM_PWM_Stop(&htim1, TIM_CHANNEL_2);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_1);
	HAL_TIMEx_PWMN_Stop(&htim1, TIM_CHANNEL_2);

}
