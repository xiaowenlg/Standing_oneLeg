#ifndef __BSPSOUND_H
#define __BSPSOUND_H
#include "stdint.h"
#include "stm32f1xx_hal.h"
void Firstmuis();                    //测试开始，播放语音
void BeginSound();            //开始测试播放
//播放函数
uint8_t PlayStanceTime(double numdata);
#endif // !__BSPSOUND_H
