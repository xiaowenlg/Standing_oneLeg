#include "BspSound.h"
#include "APPTooL.h"
#include "application.h"
#include "BspConfig.h"
#include "math.h"
#include "WTN6.h"
#include "usart.h"
uint8_t sonundArray[5] = { HUAN_YING, BEN_XIANG_MU, WO_LI, CESHI, QING_YONG_LI_WO };
//uint8_t dalaytim[4] = { 0xf3,YIN_XIAO_61,0xf8,10};				//F3H + 地址 + F8H + 10H
void Firstmuis()            //开头语音
{
	WTN6_PlayArray(5, sonundArray,5000);
	osDelay(300);
	WTN6_PlayOneByte(QING_AN_KAISHI, 5000);
	//WTN6_PlayArray(4, dalaytim);
	/**/
}
void BeginSound()
{
	WTN6_PlayOneByte(YIN_XIAO_61, 1000);
	osDelay(100);
	WTN6_PlayOneByte(CESHI_KAISHI, 1000);
}
void OverTest()					//测试结束
{
	WTN6_PlayOneByte(CESHI_JIESHU, 1000);
}

//播放站立时间
uint8_t PlayStanceTime(double numdata)//播报单脚站立时间
{
	uint8_t dat[20] = { 0 };
	uint8_t reslen = 0, templen = 0;
	uint8_t tdat[16] = { 0 };
	templen = DataSeparation(numdata, tdat);
	dat[0] = NIN_BEN_CI;
	dat[1] = DAN_JIAO_ZHAN_LI;
	dat[2] = MIAO;
	dat[3] = HUAN_ZAI_CI_YING;
	reslen = insertArray(dat, 4, tdat, templen, 2);
	WTN6_PlayArray(reslen, dat, 1000);

	return reslen;
}






