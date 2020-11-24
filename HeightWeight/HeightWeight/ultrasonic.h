#ifndef __ULTRASONIC_H
#define __ULTRASONIC_H
#include "stdint.h"
#include "stm32f1xx_hal.h"

//ѹ������������
#define PRESSURE_DT_Pin GPIO_PIN_0			//��������         ʵ���GPIO_PIN_0                         ������GPIO_PIN_8
#define PRESSURE_DT_GPIO_Port GPIOB
#define PRESSURE_SCK_Pin GPIO_PIN_1			//ʱ������		   ʵ���GPIO_PIN_1						������GPIO_PIN_9	
#define PRESSURE_SCK_GPIO_Port GPIOB

#define PRE_SCK		PBout(1)   //ʱ��
#define PRE_DT		PBin(0);   //����

void Hx711_Sck_Out();
void Hx711_Data_In();
void Hx711_Data_Out();
unsigned long Read_Weigh(uint32_t timout);
uint32_t GetRealWeight(unsigned long skin);
unsigned long Read_Weigh_1(uint32_t timout);
double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R);//�������˲�
#endif // !__ULTRASONIC_H
