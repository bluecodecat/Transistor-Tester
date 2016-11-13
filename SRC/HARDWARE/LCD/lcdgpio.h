#ifndef __LCDGPIO_H
#define __LCDGPIO_H
#include "stdint.h"

//�ֱ�����128x128,�������ڵĳ����õ���132x132
//LCD_1				����
//LCD_2				leda(+)
//LCD_3				ledk(-)
//LCD_4				vss
//LCD_5 6	    vdd
//LCD_7 8			����
//LCD_9				RST
//LCD_10			RS
//LCD_11			WR�ӵ͵�ƽ
//LCD_12			rd
//LCD_13-20		GPIOA��8λ
//LCD_21-28		����
//LCD_29			MPU�Ӹߵ�ƽ
//LCD_30			cs
//LCD_31			vss
//LCD_32			����

#define DataPort  GPIOA					//GPIOA��8λ//LCD_13-20

#define ControlBPort  GPIOB
//MPU�Ӹߵ�ƽ//LCD_29
#define CS_pin            GPIO_Pin_0//LCD_30


#define ControlCPort  GPIOC
#define RST_pin            GPIO_Pin_3//LCD_9
#define RS_pin             GPIO_Pin_4//LCD_10
#define wr_pin             GPIO_Pin_2//WR//LCD_11
#define rd_pin             GPIO_Pin_5//LCD_12


#define  TSF8H_STB_CS_SET     GPIO_SetBits(ControlBPort, CS_pin  )		
#define  TSF8H_STB_CS_CLR     GPIO_ResetBits(ControlBPort, CS_pin  )	 
#define  TSF8H_CLK_RS_SET     GPIO_SetBits(ControlCPort, RS_pin )		
#define  TSF8H_CLK_RS_CLR     GPIO_ResetBits(ControlCPort, RS_pin )	 
#define  TSF8H_DAT_EC_SET     GPIO_SetBits(ControlCPort, rd_pin)		
#define  TSF8H_DAT_EC_CLR     GPIO_ResetBits(ControlCPort, rd_pin)
#define  TSF8H_DAT_RST_SET     GPIO_SetBits(ControlCPort, RST_pin)		
#define  TSF8H_DAT_RST_CLR     GPIO_ResetBits(ControlCPort, RST_pin)
#define  TSF8H_DAT_WR_SET     GPIO_SetBits(ControlCPort, wr_pin)		
#define  TSF8H_DAT_WR_CLR     GPIO_ResetBits(ControlCPort, wr_pin)

void MCUGPIO_Init(void);
void LCD_write_8bit_dat(uint16_t dat);
uint16_t LCD_read_8bit_dat(void);
void LCD_gpio2IPU(void);
void LCD_gpio2OutPP(void);


#endif

