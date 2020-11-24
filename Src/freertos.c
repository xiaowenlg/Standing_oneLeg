/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
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
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "FreeRTOS.h"
#include "task.h"
#include "main.h"
#include "cmsis_os.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */     
#include "usart.h"
#include "ultrasonic.h"
#include "BspConfig.h"
#include "button.h"
#include "stmflash.h"
#include "gpio.h"
#include "application.h"
#include "BspSound.h"
#include "adc.h"
#include "APPTooL.h"
#include "WTN6.h"
#include "tim.h"
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN Variables */
//�����ñ���
uint16_t KeyValue_t = 0xffff; uint16_t lastvalue_t = 0xffff;
Key_Message keys[2] = { 0 };
//ë������
uint32_t Weight_Skin = 0;
uint16_t Skin_arr[2] = {0};   //ëƤ�������飬Ϊ�浽mcuflash��

uint8_t L_PH_val = 0, R_PH_val = 0;
//���͵�TFT��������

//flash��
uint32_t Weight_flash = 0;
uint16_t Weight_flash_array[2] = {0};
//վ��λ��־
uint8_t Stand_OK_flag = 0;
uint8_t time_count = 0;
//�õ����ý����ֵ

//����������ַ����

//�������ΰ�״̬

//������
extern SemaphoreHandle_t xSemaphore_WTN6_TFT;//���ڣ��������Ż�����
//�߳̾��
osThreadId SensorDriveHandle;//�����������߳�
osThreadId ButtonProcessHandle;//���������߳�
/* USER CODE END Variables */
osThreadId defaultTaskHandle;

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN FunctionPrototypes */
void SensorDrive_CallBack(void const *argument);
void  ButtonProcess_CallBack(void const *argument);

//�����ص�����
void  Key_CallBack(Key_Message index);

/* USER CODE END FunctionPrototypes */

void StartDefaultTask(void const * argument);

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* Hook prototypes */
void vApplicationIdleHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook( void )
{
   /* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
   to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
   task. It is essential that code added to this hook function never attempts
   to block in any way (for example, call xQueueReceive() with a block time
   specified, or call vTaskDelay()). If the application makes use of the
   vTaskDelete() API function (as this demo application does) then it is also
   important that vApplicationIdleHook() is permitted to return to its calling
   function, because it is the responsibility of the idle task to clean up
   memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/**
  * @brief  FreeRTOS initialization
  * @param  None
  * @retval None
  */
void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
       
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* USER CODE BEGIN RTOS_TIMERS */
  /* start timers, add new ones, ... */
  /* USER CODE END RTOS_TIMERS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */

  /* Create the thread(s) */
  /* definition and creation of defaultTask */
	/////////////////////////////////////////////////////////////////////////////////////////////////////
	STMFLASH_Read(FLASH_BEGIN, Weight_flash_array, 2);
	Weight_flash = Weight_flash_array[1];
	Weight_flash = (Weight_flash << 16) + Weight_flash_array[0];
	Weight_Skin = Weight_flash;

	/////////////////////////////////////////////////////////////////////////////////////////////////////
#if DEBUG_PRINT
	Uartx_printf(&huart1, "The Weight_skin is %d\r\n", Weight_flash);
#endif
  osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 128);
  defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

}

/* USER CODE BEGIN Header_StartDefaultTask */
/**
  * @brief  Function implementing the defaultTask thread.
  * @param  argument: Not used 
  * @retval None
  */
/* USER CODE END Header_StartDefaultTask */
void StartDefaultTask(void const * argument)
{

  /* USER CODE BEGIN StartDefaultTask */
  /* Infinite loop */
	//unsigned long val = 0;
	//unsigned int  Weight_Shiwu = 0;
 // for(;;)
 // {
	//  val = Read_Weigh_1(1000);
	//  val = val / 100;
	//  Weight_Shiwu = val;
	//  Weight_Shiwu = (unsigned int)((float)Weight_Shiwu / 0.0214);
	//  printf("The Weight is:%dg", GetRealWeight(0)); fflush(stdout);//����ˢ�������**************************************
	// //printf("The Weight is:%ldg", Weight_Shiwu); fflush(stdout);//����ˢ�������
 //   osDelay(500);
	//
 // }
	taskENTER_CRITICAL();//�����ٽ���
	osDelay(500);     //�ȴ�ϵͳ�ȶ�
	//�����������߳�
	osThreadDef(SensorDrive, SensorDrive_CallBack, 4, 0, 128);
	SensorDriveHandle = osThreadCreate(osThread(SensorDrive), NULL);
	//���������߳�
	osThreadDef(ButtonProcess, ButtonProcess_CallBack, 5, 0, 128);
	ButtonProcessHandle = osThreadCreate(osThread(ButtonProcess), NULL);
#if DEBUG_PRINT
	Uart_printf(&huart1, "Start sub stask\r\n");
#endif	
	vTaskDelete(defaultTaskHandle); //ɾ������
	taskEXIT_CRITICAL();//�Ƴ��ٽ���
  /* USER CODE END StartDefaultTask */
	
}

/* Private application code --------------------------------------------------*/
/* USER CODE BEGIN Application */

void SensorDrive_CallBack(void const *argument)             //�����������߳�---------�������
{ 
	xSemaphoreTake(xSemaphore_WTN6_TFT, portMAX_DELAY);
	{
		WTN6_PlayOneByte(SOUND_VALUE, 1000);//��������
		HAL_Delay(20);
		//Firstmuis();					//���ſ�ʼ����
		//����
		write_variable_store_82_1word(TFT_RES_VAL_ADRESS, 0);//
		write_variable_store_82_1word(TFT_INSTANTANEOUS_FORCE_ADRESS, 0);
	}
	xSemaphoreGive(xSemaphore_WTN6_TFT);

	for (;;)
	{
		
		if (Stand_OK_flag==1)//���վλ׼ȷ
		{
			Uart_printf(&huart1, "for++++++++++++++++++\r\n");
			 L_PH_val = HAL_GPIO_ReadPin(RL_PH_PORT, L_PH_PIN);//���翪��
			 R_PH_val = HAL_GPIO_ReadPin(RL_PH_PORT, R_PH_PIN);//�ҹ�翪��
			if (L_PH_val==1&R_PH_val==0)						//���̧��
			{

				if (time_count <= 0)
				{
					HAL_TIM_Base_Start_IT(&htim2);//������ʱ����ʱ
					time_count++;
				}
			}
			else if (L_PH_val == 0 & R_PH_val == 1)						//�ҽ�̧��
			{
				if (time_count <= 0)
				{
					HAL_TIM_Base_Start_IT(&htim2);//������ʱ����ʱ
					time_count++;
				}
			}
			else
			{ 
				Stand_OK_flag = 0;//������
				HAL_TIM_Base_Stop_IT(&htim2); //�رն�ʱ���ж�
				//����ʱ��
				Uart_printf(&huart1, "Beging playing!**************====%d\r\n");
			}
			
		}
		osDelay(SENSOR_PERIOD);                                                             //����T=100ms Ƶ��F = 10Hz
	}
}
void  ButtonProcess_CallBack(void const *argument)
{
	uint16_t battery_i = 0;
	for (;;)
	{
	
		ScanKeys(&KeyValue_t, &lastvalue_t, keys, Key_CallBack);
		HAL_GPIO_TogglePin(LED_RITHT_PORT, LED_RIGHT_PIN);                  //�̻߳ָʾ��
		if (battery_i++>TEST_TIME_LONG(1) / BUTTON_SCAN_CYCLE)
		{
			battery_i = 0;
			xSemaphoreTake(xSemaphore_WTN6_TFT, portMAX_DELAY);
			{
				write_variable_store_82_1word(TFT_BATTERY_GIT_ADRESS, ADC_GetValue(&hadc1, 10));//��TFT�������������
			}
			xSemaphoreGive(xSemaphore_WTN6_TFT);

		}
		///Uart_printf(&huart1, "Task2\r\n");
		osDelay(BUTTON_SCAN_CYCLE);

	}
}
void Key_Regist()
{
	
	//��ʼ����
	keys[0].GPIOx = KEY2_GPIO_Port;
	keys[0].GPIO_Pin = KEY2_Pin;
	keys[0].Key_count = 2;
	//���ð���PA11
	keys[1].GPIOx = KEY3_GPIO_Port;
	keys[1].GPIO_Pin = KEY3_Pin;
	keys[1].Key_count = 2;
}

void  Key_CallBack(Key_Message index)
{

	if (index.GPIO_Pin == KEY2_Pin) //��ʼ����
	{
		Uart_printf(&huart1,"The KEY_START is passed_pin8!\r\n");
		BeginSound();
		uint8_t L_Val = HAL_GPIO_ReadPin(RL_PH_PORT, L_PH_PIN);//���翪��
		uint8_t R_Val = HAL_GPIO_ReadPin(RL_PH_PORT, R_PH_PIN);//�ҹ�翪��
		time_count = 0;											//���
		if (L_Val == R_Val)
		{
			if (L_Val == 0 && R_Val == 0)
			{
				//����ͬʱվ��λ
				Stand_OK_flag = 1;
			}
			else if (L_Val == 1 && R_Val == 1)
			{
				//��û��վλ
				HAL_TIM_Base_Stop_IT(&htim2); //�رն�ʱ���ж�
				Stand_OK_flag = 0;
				Uart_printf(&huart1, "L_Val==R_Val***********\r\n");
			}

		}
		else   //վλ�����        ��һ����̧����
		{
			HAL_TIM_Base_Stop_IT(&htim2); //�رն�ʱ���ж�
			Stand_OK_flag = 0;
		}
	}
	if (index.GPIO_Pin == KEY3_Pin) //���ð���
	{
	
		
		//pi = 0;
	}

	//Uartx_printf(&huart1, "Key===%d\r\n", index);
}

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/