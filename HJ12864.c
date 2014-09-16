/*绘晶HJ12864ZW相关各函数*/
/*核心函数:	void LCD_init(void)									 初始化
			void show_str16(uint8 addr,uint8 *str,uint8 count)	 写字符串
			void show_page(uint8 (*page)[16])					 写页面
			void show_NUM(uint8 addr,uint NUM)					 写两位数字
*/

#include "includes.h"

/*****************************短延时**********************/
//适用于stc12c5a60s2的11.0592M环境下。
void delay_12864(uint8 x)	   //串口时指令和数据之间的延时
{					   //大致量
	uint8 k,j;
	for(k=0;k<x;k++)
		for(j=0;j<10;j++);
}

/*
///////////////////////////////////////////////////////////////////////////
///////////并行数据模式下的函数////////////////////////////////////////////
void read_BF(void)
{
	 uint8 temp;
	 RS = 0;
	 RW = 1;
	 while(1)
	 {
	 	P0 = 0xFF;
		E  = 1;
		temp = P0;
		E  = 0;
		if((temp&0x80)==0) break;
	 }
}


void w_com(uint8 com)
{
	read_BF();
	RS = 0;
	RW = 0;
	P0 = com;
	E = 1;
	E = 0;
}


void w_dat(uint8 dat)
{
	read_BF();
	RS = 1;
	RW = 0;
	P0 = dat;
	E = 1;
	E = 0;
}
*/
//////////////////////////////////////////////////////////////
////////////////////////////串行模式下的程序（注意模块上的PSB端有没有焊接）////
void SendByteLCD(uint8 WData)		 //输入待写的数据或指令
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		if((WData<<i)&0x80)	RW = 1;	   //数据左移，高位上线
		else RW = 0;
		E = 0;						   //产生时钟
		delay_12864(4);					   //时钟所需最小时间值
		E = 1;
	}
}

void w_com(uint8 Wdata)		          //输入待写的数据
{
	RS=0;
	RS=1;
	SendByteLCD(0xf8);
	SendByteLCD(Wdata&0xf0);
	SendByteLCD((Wdata<<4)&0xf0);
	delay_12864(50);				               //缓冲延时
}

void w_dat(uint8 Wdata)
{
	RS = 0;
	RS = 1;
	SendByteLCD(0xfa);
	SendByteLCD(Wdata&0xf0);
	SendByteLCD((Wdata<<4)&0xf0);
	delay_12864(50);							   //缓冲延时
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void LCD_init(void)
{
	//PSB = 1;							 //并行下运行此行
	//REST = 1;REST = 0;REST = 1;		 //并行下运行此行
	w_com(0x30);//功能设定   8-bit 基本指令
	w_com(0x06);//进入点设定
	w_com(0x01);//清屏
	w_com(0x0c);//显示状态。整体显示，游标不显示不反白。
	w_com(0x02);//地址归位
}

//行显示、多字节显示
void show_str16(uint8 addr,uint8 *str,uint8 count)   
{
	uint8 i = 0;
	w_com(addr);
	for(i=0;i<count;i++)
	{
		w_dat(str[i*2]);
		w_dat(str[i*2+1]);
	}
}
/*
//10进制数字显示
void show_NUM_10(uint8 addr,uint8 number)
{
	uint8 num[2];
	num[0] = number/10+'0';
	num[1] = number%10+'0';
	show_str16(addr,num,1);
	
}
*/
	

////////////////////整页显示//////////////////////////
void show_page(uint8 (*page)[16])
{
	show_str16(0x80,*page,8);
	show_str16(0x90,*(page+1),8);
	show_str16(0x88,*(page+2),8);
	show_str16(0x98,*(page+3),8);
}