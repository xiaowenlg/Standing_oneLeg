#ifndef __BSPSOUND_H
#define __BSPSOUND_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void Firstmuis();                    //���Կ�ʼ����������
void BeginSound();            //��ʼ���Բ���
//���ź���
uint8_t ProcessHeight(double numdata); //���
uint8_t ProcessWeight(double numdata);//����;
uint8_t ProcessBMI(double numdata);//bmi;
double Cal_BMI(double hei, double wei); //���/���ص�ƽ��;
void PlayHei_Wei(double height, double wei);
double Cal_BMI_TFT(uint32_t wi, uint16_t hi);
uint16_t Average_arr(uint32_t *arr, uint8_t len);//������ƽ��ֵ
uint8_t ProcessGrip(double numdata);//�ճ���
#endif // !__BSPSOUND_H
