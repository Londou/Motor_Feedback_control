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

#define ADC_BUFFER_LENGTH 1

float digit_Max=4095;
float plage_Dynamique=3300; //mV
float temps_echen= 0.1 ; //s
float gain=50; // mV/A
float offset_Voltage=1650; //mV
float Vitesse; // tr/s
uint16_t courant_DMA_buffer[ADC_BUFFER_LENGTH];



void  mesure_Current_U(){
	float buffer[32];
	float measured_Value;
	float courant;
	HAL_ADCEx_Calibration_Start(&hadc1, ADC_SINGLE_ENDED);

	HAL_ADC_Start_DMA(&hadc1, (uint16_t*)courant_DMA_buffer, ADC_BUFFER_LENGTH);

	HAL_TIM_Base_Start(&htim1);
	measured_Value = courant_DMA_buffer[0];
	courant=1/gain*((plage_Dynamique*measured_Value)/digit_Max-offset_Voltage);
	HAL_UART_Transmit(&huart2,(void*)buffer, sprintf((char*)buffer, "%f \r\n", (float) courant),10);

    //HAL_ADC_Start(&hadc1);
	//HAL_ADC_PollForConversion(&hadc1, HAL_MAX_DELAY);

	//measured_Value = HAL_ADC_GetValue(&hadc1);
	//courant=1/gain*((plage_Dynamique*measured_Value)/digit_Max-offset_Voltage);
	//HAL_ADC_Stop(&hadc1);
	//HAL_UART_Transmit(&huart2,(void*)buffer, sprintf((char*)buffer, "%f \r\n", (float) courant),10);
	//HAL_Delay(1000);
}


void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
	//Nouvelle valeur de l'ADC
	HAL_GPIO_WritePin(check_GPIO_Port, check_Pin, SET);
	for (int i=0; i< 100; i++);
	HAL_GPIO_WritePin(check_GPIO_Port, check_Pin, RESET);
	for (int i=0; i< 100; i++);
}

//void mesure_Speed(){
//	float buffer_vitesse[32];
	//HAL_TIM_Encoder_Start(&htim3, TIM_CHANNEL_ALL);
//	float position =__HAL_TIM_GET_COUNTER(&htim3);
//	HAL_UART_Transmit(&huart2,(void*)buffer_vitesse, sprintf((char*)buffer_vitesse, "%f \r\n", (float) position),10);
//}

void mesure_Speed(){
	float buffer_vitesse[32];

	//Partie du code qui marche mais ne donne pas la bonne réponse, car le temps ce n'est pas bon
	//float position =__HAL_TIM_GET_COUNTER(&htim3);
	//Vitesse = position/(digit_Max*temps_echen);
	//__HAL_TIM_SET_COUNTER(&htim3, 0); // Réinitialisation du compteur du Timer à 0
	//HAL_UART_Transmit(&huart2,(void*)buffer_vitesse, sprintf((char*)buffer_vitesse, "%f \r\n", (float)Vitesse),10);

	//Partie du code qui ne marche pas mais qui devrait donner la bonne réponse
	void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim) {
		if (htim->Instance == TIM2) {
			// Générer une interruption du Timer2
			float position =__HAL_TIM_GET_COUNTER(&htim3);
			Vitesse = position/(digit_Max*temps_echen);

			__HAL_TIM_SET_COUNTER(&htim3, 0); // Réinitialisation du compteur à 0
			HAL_UART_Transmit(&huart2,(void*)buffer_vitesse, sprintf((char*)buffer_vitesse, "%f \r\n", (float)Vitesse),10);
		}
  }
}

