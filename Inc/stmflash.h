#ifndef __STMFLASH_H__
#define __STMFLASH_H__

#include <stdint-gcc.h>
#include "stdlib.h"
//////////////////////////////////////////////////////////////////////////////////	 
//STM32 FLASH ��������	   
//Copyright(C) xiaowenlg
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////////////////////////////
//�û������Լ�����Ҫ����
#define STM32_FLASH_SIZE			CHIP_CAPACITY      //stm32flash ��С	
#define STM32_FLASH_BASE			CHIP_START_ADDRESS   //��ʼ��ַ
#define FLASH_BEGIN_BASE(n)			STM32_FLASH_BASE+(STM32_FLASH_SIZE-n)*1024    //nΪ��������           ����: EERPOM��ʼ��ַ
#define FLASH_BEGIN                 FLASH_BEGIN_BASE(2)                                   //�����ڴ濪ʼ��ַ �����ڶ�����ַ��
#define STM32_FLASH_WREN 1              //ʹ��FLASHд��(0��������;1��ʹ��)
//////////////////////////////////////////////////////////////////////////////////////////////////////

//FLASH��ʼ��ַ
//#define STM32_FLASH_BASE 0x08000000 	//STM32 FLASH����ʼ��ַ
//FLASH������ֵ
 

uint16_t STMFLASH_ReadHalfWord(uint32_t faddr);		  //��������
void STMFLASH_WriteLenByte(uint32_t WriteAddr,uint32_t DataToWrite,uint16_t Len);	//ָ����ַ��ʼд��ָ�����ȵ�����
uint32_t STMFLASH_ReadLenByte(uint32_t ReadAddr,uint16_t Len);						//ָ����ַ��ʼ��ȡָ����������
void STMFLASH_Write(uint32_t WriteAddr,uint16_t *pBuffer,uint16_t NumToWrite);		//��ָ����ַ��ʼд��ָ�����ȵ�����
void STMFLASH_Read(uint32_t ReadAddr,uint16_t *pBuffer,uint16_t NumToRead);   		//��ָ����ַ��ʼ����ָ�����ȵ�����

//����д��
void Test_Write(uint32_t WriteAddr,uint16_t WriteData);
void STMFLASH_FormatWrite(uint32_t WriteAddr, uint16_t NumToWritechar, char* fmt, ...);
#endif

















