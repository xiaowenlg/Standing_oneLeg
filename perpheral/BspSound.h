#ifndef __BSPSOUND_H
#define __BSPSOUND_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void Firstmuis();                    //���Կ�ʼ����������
void BeginSound();            //��ʼ���Բ���
//���ź���
uint8_t PlayStanceTime(double numdata);
#endif // !__BSPSOUND_H
