#ifndef _HJ12864_H_	   //HJ12864.h
#define _HJ12864_H_

///********************************12864端口定义***********////////////////////////

sbit RS  = P0^7;         //CS		LCD12864串行模式下的使能线
sbit RW  = P0^6;		 //SID		LCD12864串行模式下的数据线
sbit E   = P0^5;		 //SCLK		LCD12864串行模式下的时钟线
//sbit PSB = P1^3;			 //并行数据适用
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
