#include "lcd.h"
#include "lcdgpio.h"
#include "delay.h"
#include "font.h" 




void Delay(vu32 nCount)
{
  for(; nCount != 0; nCount--);
}



void TSF8H_wcmd(unsigned char cmd)
{
	TSF8H_STB_CS_CLR;
	LCD_write_8bit_dat(cmd);
	//GPIOA->ODR=cmd;
	TSF8H_CLK_RS_CLR;//rs=0=cmd
	TSF8H_DAT_EC_SET;
	//Delay(10);
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input
	//Delay(10);
	TSF8H_STB_CS_SET;//CS =1,dis-chose LCM
}
void TSF8H_wdat(unsigned char dat)
{
	TSF8H_STB_CS_CLR;
	LCD_write_8bit_dat(dat);
	//GPIOA->ODR=dat;
	TSF8H_CLK_RS_SET;//rs=1=dat
	TSF8H_DAT_EC_SET;
	//Delay(10);
	TSF8H_DAT_EC_CLR;//EC 's fall edge enable LCM input
	//Delay(10);
	TSF8H_STB_CS_SET;//CS =1,dis-chose LCM
}
void TSF8H_set_contrast(unsigned int dat)
{
	TSF8H_wcmd(0x2a);//R_CONTRAST_CONTROL1
	TSF8H_wcmd(dat);//0-255
}

void TSF8H_init(void)
{
	delay_ms(100);//delay 100ms
	TSF8H_DAT_RST_CLR;	 // PB6/RST �͵�ƽ
	delay_ms(100);//delay 100ms
	TSF8H_DAT_RST_SET;		 // PB6/RST �ߵ�ƽ  
	delay_ms(100);//delay 100ms
	//standby mode off
	TSF8H_wcmd(0x2c);
	delay_ms(20);//delay 20ms
	//OSC ON
	TSF8H_wcmd(0x02);
	TSF8H_wcmd(0x01);//enable Internal OSC and use it
	delay_ms(20);//delay 20ms
	//DCDC1 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x01);
	delay_ms(20);//delay 20ms
	//AMP ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x09);
	delay_ms(20);//delay 20ms
	//DCDC2 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x0b);
	delay_ms(20);//delay 20ms
	//DCDC3 ON
	TSF8H_wcmd(0x26);
	TSF8H_wcmd(0x0f);
	delay_ms(20);//delay 20ms
	
	//set all other 
	 TSF8H_wcmd(0x20);//R_DCDC_Select
	 TSF8H_wcmd(0x01);
	 //b0=DC(1)=normal mode DC step up =0=1.0x =1=1.5x   
	 //b2=DC(2)=partial mode step up =0=1.0x =1=1.5x
	 TSF8H_wcmd(0x28);//R_TEMP_COMPENSATION
	 TSF8H_wcmd(0x01);
	 TSF8H_wcmd(0x10);//R_DRIVER_OUTPUT_MODE
	 TSF8H_wcmd(0x03);
	 //b5b4=DLN=set duty =00=1/132 =01=1/104 =10=1/80 =11=1/96
	 //b3=MY    =0=row address++  =1=row address--
	 //b2=MX    =0=column address++  =1=column address--
	 //b1=SWP   SEGAi?SEGCi??????
	 //b0=CDIR  COM?????????
	 TSF8H_wcmd(0x40);//R_ENTRY_MODE
	 TSF8H_wcmd(0x81);
	 //b7=16B=bus wide  =0=16bit =1=8bit
	 //b2=MDI =0
	 //b1=Y/X  =0=column address count first  =1=row address count first
	 //b0=RMW  =0
	 TSF8H_wcmd(0x34);//R_N_LINE_INVERSION  N-block inversion Set (34H)
	 TSF8H_wcmd(0x04);
	 //TSF8H_wcmd(0xfa);//?????
	 //TSF8H_wcmd(0x5f);//?????
	 TSF8H_set_contrast(0xda);
	 TSF8H_wcmd(0x53);//R_SPEC_DISPLAY_PATTERN
	 TSF8H_wcmd(0x00);
	 //b1b0=SDP =00=normal mode =01=reverse display =10=whole display pattern OFF =11=whole display pattern ON
	 TSF8H_wcmd(0x30);//R_ADDRESSING_MODE
	 TSF8H_wcmd(0x00);
	 //b7=FIR
	 //b5=GSM =0=65K color =1=4K
	 //b4=DSG : Duty Adjust Setting
	 //b3=SGF : Sub Group Frame Inversion mode setting
	 //b1=SGP : Sub Group Phase mode setting
	 TSF8H_wcmd(0x55);//R_PARTIAL_DISPLAY_MODE
	 TSF8H_wcmd(0x00);
	 //b2=PT: Partial Display ON/OFF =0=normal mode =1=Partial display ON
	 //b1=PDM: Partial Display mode set
	 //b0=PDTY: Duty selection
	 TSF8H_wcmd(0x42);//R_X_ADDR_AREA
	 TSF8H_wcmd(0x00);
	 //Y start address set (Initial Status = 00H)
	 TSF8H_wcmd(0x83);
	 //Y end address set (Initial Status = 83H)
	 TSF8H_wcmd(0x43);//R_Y_ADDR_AREA
	 TSF8H_wcmd(0x00);
	 //X start address set (Initial Status = 00H)
	 TSF8H_wcmd(0x83);
	 //X end address set (Initial Status = 83H)
	 TSF8H_wcmd(0x53);//R_SPEC_DISPLAY_PATTERN
	 TSF8H_wcmd(0x00);	
	 //b1b0=SDP =00=normal mode =01=reverse display =10=whole display pattern OFF =11=whole display pattern ON
	 delay_ms(300);//delay 300ms
	//display on
	TSF8H_wcmd(0x51);//R_DISPLAY_ON
	//delay_ms(1000);//delay 1s
}

void Set_show_windows(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2)//������ʾ����
{
 	  TSF8H_wcmd(0x43);  //column
	  TSF8H_wcmd(x1);  
    TSF8H_wcmd(x2);
	
		TSF8H_wcmd(0x42);
		TSF8H_wcmd(y1); 
    TSF8H_wcmd(y2);
}
void Set_Position(uint8_t x,uint8_t y)//������ʼλ��
{
	 	TSF8H_wcmd(0x43);  //column
	  TSF8H_wcmd(x);  
    TSF8H_wcmd(0x83);
	
		TSF8H_wcmd(0x42);
		TSF8H_wcmd(y); 
    TSF8H_wcmd(0x83);
}



void LCD_Write_uint16(uint16_t Data)
{
		TSF8H_wdat(((unsigned char *)&Data)[1]);
		TSF8H_wdat(((unsigned char *)&Data)[0]);
}


void TSF8H_clr(unsigned int color)
{
	unsigned int i;
	Set_Position(0,0);
	for(i=((132*132));i>0;i--)
	{
		TSF8H_wdat(((unsigned char *)&color)[1]);
		TSF8H_wdat(((unsigned char *)&color)[0]);
	}
}
void TSF8H_dis_BMP(const unsigned char *BMP)
{
	unsigned int i;
	Set_Position(0,0);
	for(i=(132*132);i>0;i--)
	{
		TSF8H_wdat(*BMP);
		BMP++;
		TSF8H_wdat(*BMP);
		BMP++;
	}
}
void Display_Gray(void)	   //����ҶȲ�����ʾ
{
  uint8_t i,j,k;
	uint16_t Rev_B=0,Rev_G=0,Rev_R,Rev_RGB=0;
	Set_show_windows(0,0,0x7f,0x83);
	
	for (i=132;i>0;i--)
	{	
	  for(k=0;k<32;k++)
		{
		 for(j=0;j<4;j++)
			{
			  Rev_R=k;
			  Rev_G=k*2;
			  Rev_B=k;
			  Rev_RGB=Rev_B+(Rev_G<<5)+(Rev_R<<11);
		    LCD_Write_uint16(Rev_RGB);
			}
		}
	}
}

void Display_RGB(void)	   //������ɫ������ʾ
{
    int i,j,k;
	Set_Position(0,0);	
	for (i=44;i>0;i--)
	{
		for (j=132;j>0;j--)
		{
	      LCD_Write_uint16(RED);
		}
	}
    for (i=44;i>0;i--)
	{
		for (j=132;j>0;j--)
		{
	      LCD_Write_uint16(GREEN);
		}
	}
    for (k=44;k>0;k--)
	{
		for (j=132;j>0;j--)
		{
	      LCD_Write_uint16(BLUE);
		}
	}
}

void Display_FullColorline(void)	   //����ȫ�ʲ�����ʾ
{
  uint8_t i,j;
	uint16_t Rev_B=0,Rev_G=0,Rev_R,Rev_RGB=0;
	Set_show_windows(0,0,0x7f,0x83);
	for (i=132;i>0;i--)
	{
		for(j=0;j<32;j++)
		{
		  Rev_R=0x1f;
		  Rev_G=0;
		  Rev_B=0x1f-j;
		  Rev_RGB=Rev_B+(Rev_G<<5)+(Rev_R<<11);
	    LCD_Write_uint16(Rev_RGB);
		}
		for (j=0;j<32;j++)
		{
		  Rev_R=0x1f;
		  Rev_G=2*j;
		  Rev_B=0;
		  Rev_RGB=Rev_B+(Rev_G<<5)+(Rev_R<<11);
	      LCD_Write_uint16(Rev_RGB);
		}
		
		for (j=0;j<32;j++)
		{
		  Rev_R=0x1f-j;
		  Rev_G=0x3f;
		  Rev_B=0;
		  Rev_RGB=Rev_B+(Rev_G<<5)+(Rev_R<<11);
	      LCD_Write_uint16(Rev_RGB);
		}
		for (j=0;j<32;j++)
		{
		  Rev_R=0;
		  Rev_G=0x3f-2*j;
		  Rev_B=j;
		  Rev_RGB=Rev_B+(Rev_G<<5)+(Rev_R<<11);
	      LCD_Write_uint16(Rev_RGB);
		}

	}
}



void Display_Point(uint8_t x,uint8_t y,uint16_t Color)//������λ�û���
{
 	Set_Position(x,y);
	LCD_Write_uint16(Color);

}

//��ȡ��ĳ�����ɫֵ	 
//x,y:����
//����ֵ:�˵����ɫ
uint16_t LCD_ReadPoint(uint8_t x,uint8_t y)
{
 	u16 r,b;
	if(x>=Width||y>=Height)return 0;	//�����˷�Χ,ֱ�ӷ���		   
	Set_Position(x,y);	
	LCD_gpio2IPU();
	LCD_write_8bit_dat(0xff);
	
	TSF8H_STB_CS_CLR;
	TSF8H_CLK_RS_SET;//rs=1=dat
	
	TSF8H_DAT_WR_SET;
	TSF8H_DAT_EC_SET;
	LCD_read_8bit_dat();//�ٶ�
	TSF8H_DAT_EC_CLR;
	
	TSF8H_DAT_WR_SET;
	TSF8H_DAT_EC_SET;		
	r=LCD_read_8bit_dat();
	r<<=8;
	r&=0xff00;	
	TSF8H_DAT_EC_CLR;
	TSF8H_DAT_EC_SET;		
	b=LCD_read_8bit_dat();
	r+=b;
	TSF8H_DAT_EC_CLR;
	TSF8H_DAT_WR_CLR; 
	TSF8H_STB_CS_SET;
	LCD_gpio2OutPP();
	LCD_write_8bit_dat(0xff);    		//ȫ�������  
	return r;
}

//����
//x1,y1:�������
//x2,y2:�յ�����  
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	uint16_t t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; //���õ������� 
	else if(delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;//ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )//������� 
	{  
		Display_Point(uRow,uCol,color);//���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
} 

//������	  
//(x1,y1),(x2,y2):���εĶԽ�����
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2,uint16_t color)
{
	LCD_DrawLine(x1,y1,x2,y1,color);
	LCD_DrawLine(x1,y1,x1,y2,color);
	LCD_DrawLine(x1,y2,x2,y2,color);
	LCD_DrawLine(x2,y1,x2,y2,color);
}

void LCD_Draw_Circle(uint16_t x0,uint16_t y0,uint8_t r,uint16_t color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             //�ж��¸���λ�õı�־
	while(a<=b)
	{
		Display_Point(x0+a,y0-b,color);             //5
 		Display_Point(x0+b,y0-a,color);             //0           
		Display_Point(x0+b,y0+a,color);             //4               
		Display_Point(x0+a,y0+b,color);             //6 
		Display_Point(x0-a,y0+b,color);             //1       
 		Display_Point(x0-b,y0+a,color);             
		Display_Point(x0-a,y0-b,color);             //2             
  	Display_Point(x0-b,y0-a,color);             //7     	         
		a++;
		//ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 



//��ָ��λ����ʾһ���ַ�
//x,y:��ʼ����
//num:Ҫ��ʾ���ַ�:" "--->"~"
//size:�����С 12/16/24
//mode:���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
void LCD_ShowChar(uint16_t x,uint16_t y,uint8_t num,uint8_t size,uint8_t mode,uint16_t color)
{  							  
    uint8_t temp,t1,t;
	uint16_t y0=y;
	uint8_t csize=(size/8+((size%8)?1:0))*(size/2);		//�õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';//�õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 	//����1206����
		else if(size==16)temp=asc2_1608[num][t];	//����1608����
		else if(size==24)temp=asc2_2412[num][t];	//����2412����
		else return;								//û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)Display_Point(x,y,color);
			else if(mode==0)Display_Point(x,y,BLACK);
			temp<<=1;
			y++;
			if(y>=Height)return;		//��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=Width)return;	//��������
				break;
			}
		}  	 
	}  	    	   	 	  
}

void LCD_ShowStr(uint16_t x,uint16_t y,uint8_t *str,uint8_t size,uint16_t Color)//��ʾ�ַ���
{
   while(*str!='\0')
   {
		 LCD_ShowChar(x,y,*str,size,0,Color);
	 str++;
	 x+=(size/2);
	 if(x>=(Width-(size/2)))
	 {
	  x=0;
	  y+=size;
	 }
   }
}

//m^n����
//����ֵ:m^n�η�.
u32 LCD_Pow(uint8_t m,uint8_t n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}	

//��ʾ����,��λΪ0,����ʾ
//x,y :�������	 
//len :���ֵ�λ��
//size:�����С
//color:��ɫ 
//num:��ֵ(0~4294967295);	 
void LCD_ShowNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint16_t color)
{         	
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0,color);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0,color); 
	}
}
//��ʾ����,��λΪ0,������ʾ
//x,y:�������
//num:��ֵ(0~999999999);	 
//len:����(��Ҫ��ʾ��λ��)
//size:�����С
//mode:
//[7]:0,�����;1,���0.
//[6:1]:����
//[0]:0,�ǵ�����ʾ;1,������ʾ.
void LCD_ShowxNum(uint16_t x,uint16_t y,uint32_t num,uint8_t len,uint8_t size,uint8_t mode,uint16_t color)
{  
	uint8_t t,temp;
	uint8_t enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01,color);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01,color);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01,color); 
	}
} 

//��ȡָ����ַ�İ���(16λ����)
//faddr:����ַ(�˵�ַ����Ϊ2�ı���!!)
//����ֵ:��Ӧ����.
u16 STMFLASH_ReadHalfWord(u32 faddr)
{
	return *(vu16*)faddr; 
}

//��ָ����ַ��ʼ����ָ�����ȵ�����
//ReadAddr:��ʼ��ַ
//pBuffer:����ָ��
//NumToWrite:����(16λ)��
void STMFLASH_Read(u32 ReadAddr,u16 *pBuffer,u16 NumToRead)   	
{
	u16 i;
	for(i=0;i<NumToRead;i++)
	{
		pBuffer[i]=STMFLASH_ReadHalfWord(ReadAddr);//��ȡ2���ֽ�.
		ReadAddr+=2;//ƫ��2���ֽ�.	
	}
}
void GetGBKCode_from_flash(unsigned short int* pBuffer,const unsigned char * c)
{ 
    unsigned char High8bit,Low8bit;
    u32 pos;
    High8bit=*c;     /* ȡ��8λ���� */
    Low8bit=*(c+1);  /* ȡ��8λ���� */
    pos = ((High8bit-0xa0-16)*94+Low8bit-0xa0-1)*2*16+0x08040000;//0x08040000����ģ��flash�е���ʼ��ַ
		STMFLASH_Read(pos,pBuffer,16);
   
}

/* ��ʾһ������ 
 * ��СΪ 16����ȣ�* 16���߶ȣ�����32���ֽ�
 * ȡģ˳��Ϊ����λ��ǰ����λ�ں�
 */
void LCD_DispCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color)
{
	uint8_t page , column;
	uint16_t buffer[16];		
	uint16_t tmp_char=0,tmp_char2=0;
	Set_show_windows(x,y,x+16-1,y+16-1);
	
	GetGBKCode_from_flash(buffer,pstr);	 /* ȡ��ģ���� */
	
	for(page=0; page< 16; page++)
	{
    /* ȡ�������ֽڵ����ݣ���lcd�ϼ���һ�����ֵ�һ�� */
		tmp_char=buffer[page]&0xff00;
		tmp_char2=buffer[page]&0x00ff;
		tmp_char>>=8;
		tmp_char2<<=8;
		tmp_char|=tmp_char2;
		for (column=0; column< 16; column++)
		{			
			if ( tmp_char & 0x8000 )  /* ��λ��ǰ */
			{				
					TSF8H_wdat(((unsigned char *)&color)[1]);
					TSF8H_wdat(((unsigned char *)&color)[0]);
			}
			else
			{			
				TSF8H_wdat(0x00);
				TSF8H_wdat(0x00);
			}
			tmp_char <<= 1;
		}
	}
}

/*
 * ��ʾһ������
 */
void LCD_DispStrCH(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color) 
{
	while( *pstr != '\0' )
	{
		if( x > (Width-16) )
		{
			x = 0;
			y += 16;
		}
		if( y > (Height-16) )
		{
			x = 0;
			y = 0;
		}		
		LCD_DispCH(x, y, pstr, color);
		pstr +=2;   /* һ�����������ֽ� */  
		x += 16;		
	}	   
}


/* 
 * ��Ӣ�Ļ����ʾ��������ʾ���ı�����  
 * ���Ĵ�С��16*16
 * Ӣ�Ĵ�С��12*6
 */
void LCD_DispEnCh(uint16_t x, uint16_t y, const uint8_t *pstr, uint16_t color)
{
	while(*pstr != '\0')
	{
		if(*pstr <= 126)		/* �ַ��� */
		{
			if( x > (Width-8) )
			{
				x = 0;
				y += 16;
			}
			if( y > (Height-16) )
			{
				x = 0;
				y = 0;
			}
			LCD_ShowChar(x,y,*pstr,16,0,color);
			//LCD_DispChar(x, y, *pstr, color);
			x += 8;
			pstr++;
		}
		else	/* ���� */
		{
			if( x > (Width-16) )
			{
				x = 0;
				y += 16;
			}
			if( y > (Height-16) )
			{
				x = 0;
				y = 0;
			}		
			LCD_DispCH(x, y, pstr, color);
			pstr +=2;
			x += 16;
    }
  }
} 
