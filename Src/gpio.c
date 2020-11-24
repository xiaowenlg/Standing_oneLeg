/**
  ******************************************************************************
  * File Name          : gpio.c
  * Description        : This file provides code for the configuration
  *                      of all used GPIO pins.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; Copyright (c) 2020 STMicroelectronics.
  * All rights reserved.</center></h2>
  *
  * This software component is licensed by ST under Ultimate Liberty license
  * SLA0044, the "License"; You may not use this file except in compliance with
  * the License. You may obtain a copy of the License at:
  *                             www.st.com/SLA0044
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "gpio.h"
/* USER CODE BEGIN 0 */
#include "BspConfig.h"
/* USER CODE END 0 */

/*----------------------------------------------------------------------------*/
/* Configure GPIO                                                             */
/*----------------------------------------------------------------------------*/
/* USER CODE BEGIN 1 */

/* USER CODE END 1 */

/** Configure pins as 
        * Analog 
        * Input 
        * Output
        * EVENT_OUT
        * EXTI
*/
void MX_GPIO_Init(void)
{

  GPIO_InitTypeDef GPIO_InitStruct = {0};

  /* GPIO Ports Clock Enable */
  __HAL_RCC_GPIOD_CLK_ENABLE();
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();

  /*Configure GPIO pin Output Level */
 // HAL_GPIO_WritePin(GPIOB, PRESSURE_SCK_Pin|WTN6040_SCK_Pin, GPIO_PIN_RESET);

  /*Configure GPIO pin Output Level */
 // HAL_GPIO_WritePin(WTN6040_DATA_GPIO_Port, WTN6040_DATA_Pin, GPIO_PIN_SET);

  /*Configure GPIO pins : PAPin PAPin PAPin PAPin */
  //************************************************************************************
  //GPIO_InitStruct.Pin = WEIGHT_RES_Pin|DISTANCE_RES_Pin|KEY2_Pin|KEY3_Pin;
  //GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  //GPIO_InitStruct.Pull = GPIO_PULLUP;
  //HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  ///*Configure GPIO pins : PBPin PBPin PBPin */
  //GPIO_InitStruct.Pin = PRESSURE_DT_Pin|KEY1_Pin;
  //GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  //GPIO_InitStruct.Pull = GPIO_PULLUP;
  //HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);

  ///*Configure GPIO pins : PBPin PBPin PBPin */
  //GPIO_InitStruct.Pin = PRESSURE_SCK_Pin;
  //GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  //GPIO_InitStruct.Pull = GPIO_PULLUP;
  //GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  //HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);


}

/* USER CODE BEGIN 2 */
void Led_Init()                      //led��ʼ��
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();
	HAL_GPIO_WritePin(LED_LEFT_PORT, LED_LEFT_PIN, 0);
	HAL_GPIO_WritePin(LED_RITHT_PORT, LED_RIGHT_PIN, 0);

	GPIO_InitStruct.Pin = LED_LEFT_PIN | LED_RIGHT_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(LED_RITHT_PORT, &GPIO_InitStruct);
}
//��翪�����ų�ʼ��
void PH_SW_Init()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOA_CLK_ENABLE();

	GPIO_InitStruct.Pin = R_PH_PIN | L_PH_PIN;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(RL_PH_PORT, &GPIO_InitStruct);
}
/* USER CODE END 2 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
