/*
 * capteurs.c
 *
 *  Created on: Oct 26, 2023
 *      Author: Erika
 */


#include "tim.h"
#include "usart.h"
#include "gpio.h"
#include "stdio.h"
#include "adc.h"

float digit_Max=4095;
float plage_Dynamique=3300; //mV
float gain=50; // mV/A
float offset_Voltage=5; //mV



void  mesure_Current_U(){
	float buffer[32];
	float measured_Value;
	float courant;
	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);
	measured_Value = HAL_ADC_GetValue(&hadc1);
	courant=1/gain*((plage_Dynamique*measured_Value)/digit_Max-offset_Voltage);
	HAL_ADC_Stop(&hadc1);
	HAL_UART_Transmit(&huart2,(void*)buffer, sprintf((char*)buffer, "%f \r\n", (float) courant),10);
	HAL_Delay(1000);
}
