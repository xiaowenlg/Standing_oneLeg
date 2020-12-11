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
#define YIN_XIAO_61					67						//��Ч61
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
#define MIAO						20						//��
#define DAN_JIAO_ZHAN_LI			58						//����վ��
#define QING_ZHAN_LI_CE_WEI			64						//��վ��������λ
#define NIN_BEN_CI					34						//������
#define ZHAN_WEI_CUO_WU				61						//վλ����
#define QING_CHONG_XIN_KAI_SHI		62						//�����¿�ʼ

//����ֵ
#define SOUND_VALUE					0xEF                  //����       0xe0-----0xef
//TFT��
#define TFT_VARIABLE_START		0x0001      //TFT��������ʼ��ַ
#define TFT_BUTTON				0x4F		//TFT���ϵİ�ť
//��ʾ���ݵ�ַ
#define TFT_LEFT_VALUE_ADRESS				0x0001			//˲ʱ��
#define TFT_RIGHT_VALUE_ADRESS				0x0002			//���ȶ���	
#define TFT_BATTERY_GIT_ADRESS				0x0003			//���ͼ��
#define TFT_ALLFEET_GIT_ADRESS				0x0004			//���Կ�ʼ����
#define TFT_LEFT_FEET_GIF_ADRESS			0x0005			//���Խ��
#define TFT_RIGHT_FEET_GIF_ADRESS			0x0006			//����ʱֵ

					
#define TEST_TIME_LONG(n)		n*1000						//���ʱ����λs	
#define SENSOR_PERIOD			500							//�������������

#define TIMER2_COUNT_T			1000						//��ʱ���������� 1Sһ��
//���Կ���
#define DEBUG_PRINT					1                                
#endif // !__BSPCONFIG_H
