#include "lcdgpio.h"        
#include "stm32f10x_gpio.h"

void MCUGPIO_Init(void)
{
  GPIO_InitTypeDef GPIO_InitStructure;
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC| RCC_APB2Periph_GPIOD , ENABLE  );
  
  GPIO_InitStructure.GPIO_Pin =0xff00  ;	//��8λ		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(DataPort, &GPIO_InitStructure);				 // ѡ��A�˿�
	
  GPIO_InitStructure.GPIO_Pin = CS_pin ;		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(ControlBPort, &GPIO_InitStructure);				 // ѡ��B�˿�	

	GPIO_InitStructure.GPIO_Pin = RST_pin|RS_pin|rd_pin|wr_pin  ;		
  GPIO_InitStructure.GPIO_Mode =  GPIO_Mode_Out_PP;		   // �������
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		 // ����������50MHz
  GPIO_Init(ControlCPort, &GPIO_InitStructure);				 // ѡ��C�˿�	
	TSF8H_DAT_WR_CLR;
}

void LCD_write_8bit_dat(uint16_t dat)
{
	DataPort->ODR &= 0x00ff;
	DataPort->ODR |= (uint16_t)((dat<<8) & 0x00ff);
}

uint16_t LCD_read_8bit_dat(void)//ʵ���Ƿ��ص�8λ
{
	uint16_t dat;
	dat=GPIO_ReadInputData(DataPort);
	dat&=0x00ff;
	return dat;
}

void LCD_gpio2IPU(void)
{
DataPort->CRL=0X88888888; //PB0-7  ��������
}

void LCD_gpio2OutPP(void)
{
	DataPort->CRL=0X33333333; 		//PB0-7  �������
}






