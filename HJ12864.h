#ifndef _HJ12864_H_	   //HJ12864.h
#define _HJ12864_H_

///********************************12864�˿ڶ���***********////////////////////////

sbit RS  = P0^7;         //CS		LCD12864����ģʽ�µ�ʹ����
sbit RW  = P0^6;		 //SID		LCD12864����ģʽ�µ�������
sbit E   = P0^5;		 //SCLK		LCD12864����ģʽ�µ�ʱ����
//sbit PSB = P1^3;			 //������������
//sbit REST = P1^4;

void delay_12864(uint8 x);
void read_BF(void);
void SendByteLCD(uint8 WData);
void w_com(uint8 com);
void w_dat(uint8 dat);
void LCD_init(void);
void show_str16(uint8 addr,uint8 *str,uint8 count);
void show_page(uint8 (*page)[16]);
void show_NUM_10(uint8 addr,uint8 number);



#endif
