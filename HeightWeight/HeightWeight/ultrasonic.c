#include "ultrasonic.h"
#include "BspConfig.h"
#include "dwt_stm32_delay.h"
#include "stm32f1xx_hal.h"
#include "usart.h"
void Hx711_Data_Out() //���ó����
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);
}
void Hx711_Data_In()//���ó�����
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	GPIO_InitStruct.Pin = PRESSURE_DT_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	HAL_GPIO_Init(PRESSURE_DT_GPIO_Port, &GPIO_InitStruct);


}
//************************************
// ����:    Ultrasonic_Init
// ����ȫ��:  Ultrasonic_Init
// ��������:    public 
// ����ֵ:   uint8_t
// Qualifier:
// ����: uint8_t gpioIndex   gpio�˿�����
// ����: uint16_t sk_pin	//ʱ������
// ����: uint16_t dt_pin	//���ݽ�������
//************************************
void Hx711_Sck_Out()
{
	GPIO_InitTypeDef GPIO_InitStruct = { 0 };
	__HAL_RCC_GPIOB_CLK_ENABLE();
	//ʱ�����ų�ʼ��
	GPIO_InitStruct.Pin = PRESSURE_SCK_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(PRESSURE_SCK_GPIO_Port, &GPIO_InitStruct);

	//�������ų�ʼ��
	
}

uint8_t is_ready() {
	uint8_t val = PRE_DT;
	return val == 0;
}
unsigned long Read_Weigh(uint32_t timout)
{
	uint32_t i = 0;
	unsigned long Count = 0;//�޷���4���ֽ�
	Hx711_Data_Out(); //����IO���
	HAL_GPIO_WritePin(PRESSURE_DT_GPIO_Port,PRESSURE_DT_Pin,1);
	HAL_GPIO_WritePin(PRESSURE_SCK_GPIO_Port, PRESSURE_SCK_Pin, 0);
	Hx711_Data_In(); //����IO����

	long tim = HAL_GetTick();
	while (HAL_GetTick()-tim<timout)
	{
		if (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin)==0)
		{
			//Uart_printf(&huart1, "Test0==%d\r\n", HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8));
			break;
		}
	}
	//while (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin));
	
	for (i = 0; i < 24; i++)
	{
		PRE_SCK = 1;
		DWT_Delay_us(1);
		Count = Count << 1;
		PRE_SCK = 0;
		if (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin))
			Count++;
		DWT_Delay_us(1);
	}
	PRE_SCK = 1;
	DWT_Delay_us(1);
	Count = Count ^ 0x800000;//^��������,λֵ��ͬΪ0,��ͬΪ1
	PRE_SCK = 0;
	DWT_Delay_us(1);
	return(Count);
}
///ȡʵ������=����-ë��
uint32_t GetRealWeight(unsigned long skin)
{
	unsigned long val = 0,valsum = 0;
	uint32_t res_temp = 0,res = 0;
	uint8_t i = 0;
	val = Read_Weigh(1000);
	val = val / 100;
	res_temp = (val / DIV - ERROR) - skin;
	
	/*if (abs(res_temp) < 30000)
	{
		res = res_temp;
	}
	else
		res = 0;*/
	
	return res_temp;
}

unsigned long Read_Weigh_1(uint32_t timout)
{
	uint8_t i = 0;
	unsigned long Count = 0;//�޷���4���ֽ�
	Hx711_Data_Out(); //����IO���
	HAL_GPIO_WritePin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin, 1);
	HAL_GPIO_WritePin(PRESSURE_SCK_GPIO_Port, PRESSURE_SCK_Pin, 0);
	Hx711_Data_In(); //����IO����

	long tim = HAL_GetTick();
	while (HAL_GetTick() - tim < timout)
	{
		if (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin) == 0)
		{
			//Uart_printf(&huart1, "Test0==%d\r\n", HAL_GPIO_ReadPin(GPIOB, GPIO_PIN_8));
			break;
		}
	}
	//while (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin));

	for (i = 0; i < 24; i++)
	{
		PRE_SCK = 1;
		DWT_Delay_us(1);
		Count = Count << 1;
		PRE_SCK = 0;
		if (HAL_GPIO_ReadPin(PRESSURE_DT_GPIO_Port, PRESSURE_DT_Pin))
			Count++;
		DWT_Delay_us(1);
	}
	PRE_SCK = 1;
	DWT_Delay_us(1);
	Count = Count ^ 0x800000;//^��������,λֵ��ͬΪ0,��ͬΪ1
	PRE_SCK = 0;
	DWT_Delay_us(1);
	return(Count);
}

double KalmanFilter(const double ResrcData, double ProcessNiose_Q, double MeasureNoise_R)
{
	double R = MeasureNoise_R;
	double Q = ProcessNiose_Q;

	static        double x_last;

	double x_mid = x_last;
	double x_now;

	static        double p_last;

	double p_mid;
	double p_now;
	double kg;

	x_mid = x_last; //x_last=x(k-1|k-1),x_mid=x(k|k-1)
	p_mid = p_last + Q; //p_mid=p(k|k-1),p_last=p(k-1|k-1),Q=����
	kg = p_mid / (p_mid + R); //kgΪkalman filter��RΪ����
	x_now = x_mid + kg*(ResrcData - x_mid);//���Ƴ�������ֵ

	p_now = (1 - kg)*p_mid;//����ֵ��Ӧ��covariance        

	p_last = p_now; //����covarianceֵ
	x_last = x_now; //����ϵͳ״ֵ̬

	return x_now;
}