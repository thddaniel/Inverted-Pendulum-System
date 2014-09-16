#include"stc12c5a60s2.h"
#include"HJ12864.h"

sbit EN = P0^2;
sbit CW = P0^1;
sbit CK = P0^0;


#define timer0_setting 300


//1ms延时函数
//实测有极小误差 在11.0592M晶振的stc12c5a60s2单片机上
void delay_ms(uint16 n)  
{
	uint8 x,y;
	for(;n>0;n--)
		for(x=25;x>0;x--)
			for(y=100;y>0;y--)
			;
}

/*
void main(void)
{
	EN = 0;
	CW = 1;
	CK = 0;
	TH0 = (65536-timer0_setting)/256;
	TL0 = (65536-timer0_setting)%256;
	TMOD = 0x01;
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	while(1)
	{
		delay_ms(200);
		CW = ~CW;
	}
}

void timer0_interrupt(void)	interrupt 1
{
	TH0 = (65536-timer0_setting)/256;
	TL0 = (65536-timer0_setting)%256;
	CK = ~CK;
}
*/


void main(void)
{
	ufloat a=0,i;
	for(i=0;i<10;i++)
	{
		a++;
	}
	while(1);

}