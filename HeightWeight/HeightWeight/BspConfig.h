#ifndef __BSPCONFIG_H
#define __BSPCONFIG_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "system.h"

//���贮�ڶ���
//�豸���ڲ���������
#define BLE_BAND				115200        //��������
#define DEBUG_BAND				115200        //�����ô���
#define HMI_BAND				115200		//HML������(�Ծ���)

//���ڷ���

#define  UART_BLE				&huart1			//����
#define  UART_ULTRASONIC		&huart2			//�������ӿ�	
#define  UART_TFT				&huart3			//TFT��(�人����)


//��ѹ�������
#define V_TEST_Pin GPIO_PIN_4
#define V_TEST_GPIO_Port GPIOA

//------------------------------------------ ����оƬWTN6040

//#define  CLK_2A                 PBout(13) //ʱ�������λ��������
//#define  P_DATA_2A               PBout(12) //���������λ��������


#define DIV 0.3              //��������                     ����100KG             
#define ERROR		279010     //������279423  
#define WEIGHT_MAX	4294967

#define BUTTON_SCAN_CYCLE			50      //����ɨ������


//оƬflash�ռ䶨��
#define CHIP_CAPACITY				128			//оƬflash������λKb
#define CHIP_START_ADDRESS			0x08000000

//������ַ
#define HUAN_YING					43							//��ӭʹ�����������Ŀ
#define BEN_XIANG_MU					26                        //����ĿΪ������
#define CESHI						27						  //����
#define TI_ZHI_ZHI_SHU				28						//����ָ��
#define QING_ZHAN_LI				37						//����վ���ڲ���λ�����־�ֹ�����������Ӳ��Խ��׼ȷ��
#define YIN_XIAO_61					61						//��Ч61
#define QING_AN_KAISHI				41						//�밴��ʼ����ʼ
#define CESHI_KAISHI				44						//���Կ�ʼ
#define CESHI_JIESHU				45						//���Խ���
#define NINDE						33						//����
#define SHEN_GAO					35						//���
#define TI_ZHONG					36						//����
#define SOUND_BIM					28						//����ָ��
#define GONG_JIN					16						//����
#define GONG_FEN					17						//����
#define	TI_XING						49						//����
#define PIAN_PANG					50						//ƫ��
#define PIAN_SHOU					51						//ƫ��
#define ZHENG_CHANG					52						//����
#define HUAN_ZAI_CI_YING			57						//��ӭ�ٴ�ʹ��
#define WO_LI						29						//����
#define QING_YONG_LI_WO				38						//��������ס������

//����ֵ
#define SOUND_VALUE					0xEF                  //����       0xe0-----0xef
//TFT��
#define TFT_VARIABLE_START		0x0001      //TFT��������ʼ��ַ
#define TFT_BUTTON				0x4F		//TFT���ϵİ�ť
//��ʾ���ݵ�ַ
#define TFT_INSTANTANEOUS_FORCE_ADRESS		0x0001			//˲ʱ��
#define TFT_SPEAK_GIF_ADRESS				0x0002			//���ȶ���	
#define TFT_START_GIT_ADRESS				0x0004			//���Կ�ʼ����
#define TFT_BATTERY_GIT_ADRESS				0x0003			//���ͼ��
#define TFT_RES_VAL_ADRESS					0x0005			//���Խ��
#define TFT_BACK_TIM_ADRESS					0x0006			//����ʱֵ
#define TFT_TEST_ERROR_ADRESS				0x0007			//������
//���Խ����ַ
#define TFT_SENSOR_ADRESS					0x0008			//������ֵ
#define TFT_EQUIPMENT_WEIGHT_ADRESS			0x0009			//�豸����
#define TFT_SET_OVER_ADRESS					0x000A			//������ɶ���
					
#define TEST_TIME_LONG(n)		n*1000						//���ʱ����λs	
#define SENSOR_PERIOD			100							//�������������

#define COUNT_DOWN				10							//����ʱ10����
#define WEIGHT_MIN				1000						//��С����������ֵ
#define NO_GRIP_NUM(n)			n*1000						//n����ʾһ��:"��������ס������"
#define TIP_COUNT				2							//��ʾ����
//���Կ���
#define DEBUG_PRINT					1                                
#endif // !__BSPCONFIG_H
