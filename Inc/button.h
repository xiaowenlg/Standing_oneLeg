#ifndef __button_H
#define __button_H
#include "stdint.h"
#include "stm32f1xx_hal.h"



//备用按键
#define KEY2_Pin GPIO_PIN_8				//PA8                开始按键
#define KEY2_GPIO_Port GPIOA
#define KEY3_Pin GPIO_PIN_11			//PA11				//备用按键
#define KEY3_GPIO_Port GPIOA
//按键结构体
typedef struct K_Info
{
	GPIO_TypeDef *GPIOx; //按键端口
	uint16_t GPIO_Pin;   //按键引脚
	uint8_t Key_count;;  //注册按键数量
}Key_Message;
typedef void(*fun)(Key_Message keynum); //回调函数形式

void Key_Gpio_init();
uint16_t GetKey_Value(Key_Message *t_keymessage, uint16_t *KeyValue);
void  Decide_KeyValue(uint16_t value, uint16_t *lastvalue, Key_Message *t_keymessage, fun callback);
void ScanKeys(uint16_t *KeyValue, uint16_t *lastvalue, Key_Message *t_keymessage, fun callback);
#endif // !__button_H
