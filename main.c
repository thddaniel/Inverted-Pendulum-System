#include"includes.h"
#include"defines.h"



//1ms延时函数
//实测有极小误差 在11.0592M晶振的stc12c5a60s2单片机上
void delay_ms(uint16 n)  
{
	uint8 x,y;
	for(;n>0;n--)
		for(x=25;x>0;x--)
			for(y=108;y>0;y--);
}

//250us延时函数，用于周期摆动
void delay_250us(uint16 n)
{
	uint8 x,y;
	for(;n>0;n--)
		for(x=25;x>0;x--)
			for(y=25;y>0;y--);
}

/*
//串口1相关（使用独立波特率发生器）释放T1
void uart_init(void)		
{        
    SCON = 0x50;        
	AUXR = 0x11;
	BRT  = 0xFD;
	//EA = 1;
	//ES = 1;
}

void uart_SEND_16(uint16 dat)
{
	SBUF = dat/256;
	while(!TI);
	TI = 0;
	SBUF = dat%256;
	while(!TI);
	TI = 0;
}
void uart_SEND_8(uint8 dat)
{
	SBUF = dat;
	while(!TI);
	TI = 0;
}

void uart_SEND_str(uint8 *str)
{
	uint8 i = 0;
	while (str[i])
	{
		uart_SEND_8(str[i]);
		i++;
	}
}
*/

/*****************************内部AD初始化*****************/

void Get_ADC(uint8 ch,uint8 ADC_SPEED,uint16 times)
{
	ADC_Result = 0;						//变量初始化
	ADC_counts = 0;
	ADC_times = times;					//形参全局化，方便中断使用
	ADC_ch_choose = ch;
	ADC_speed_choose = ADC_SPEED;
	ADC_CONTR = 0x00;					//寄存器初始化
	ADC_RES = 0;
	ADC_RESL = 0;
	AUXR1 |= 0x04;						//寄存器设置//10位ADC
	P1ASF = 0xff;
	P1M1 = 0xff;
	P1M0 = 0x00;
	ADC_CONTR = ADC_POWER|ADC_speed_choose|ADC_START|ADC_ch_choose;
	_nop_();							//延时等待数据写入ADC_CONTR
	_nop_();
	_nop_();
	EA = 1;
	EADC = 1;
}
/*****************************数据曲线拟合*****************/
void Data_optimization(uint16 Value)
{
	//static int16 angle_B_now,angle_B_last;
	if (Value>=0x02e6)		  //0~55
	{
		if (Value>=0x0382 && Value<0x03A3)       
		{angle_A = 20.0-(20.0*(Value-0x0382))/0x0021;} //0~20
		else if (Value>=0x0372 && Value<0x0382)  
		{angle_A = 25.0-(5.00*(Value-0x0372))/0x0010;angle_B = 21.4961-angle_A*0.3201;}//timer1_setting = 1600;}  //20~25
		else if (Value>=0x0362 && Value<0x0372)  
		{angle_A = 30.0-(5.00*(Value-0x0362))/0x0010;angle_B = 21.2942-angle_A*0.3120;}//timer1_setting = 1000;}  //25~30
		else if (Value>=0x034D && Value<0x0362)  
		{angle_A = 35.00-(5.00*(Value-0x034D))/0x0015;angle_B = 21.0154-angle_A*0.3027;}//timer1_setting = 1000;}  //30~35
		else if (Value>=0x0338 && Value<0x034D)  
		{angle_A = 40.00-(5.00*(Value-0x0338))/0x0015;angle_B = 20.6415-angle_A*0.2920;}//timer1_setting = 1000;}  //35~40
		else if (Value>=0x031E && Value<0x0338)  
		{angle_A = 45.00-(5.00*(Value-0x031E))/0x001a;angle_B = 20.1499-angle_A*0.2798;}//timer1_setting = 1000;}  //40~45
		else if (Value>=0x0304 && Value<0x031E)  
		{angle_A = 50.00-(5.00*(Value-0x0304))/0x001a;angle_B = 19.5131-angle_A*0.2656;}//timer1_setting = 1000;}  //45~50
		else if (Value>=0x02E6 && Value<0x0304)  
		{angle_A = 55.00-(5.00*(Value-0x02E6))/0x001e;angle_B = 18.6966-angle_A*0.2493;}//timer1_setting = 1000;}  //50~55
	}
	else if (Value>=0x01fd && Value<0x02e6)		  //55~90
	{
		if (Value>=0x02C7 && Value<0x02E6)  	 
		{angle_A = 60.00-(5.00*(Value-0x02C7))/0x001f;angle_B = 17.6575-angle_A*0.2304;}//timer1_setting = 900;}  //55~60
		else if (Value>=0x02A8 && Value<0x02C7)  
		{angle_A = 65.00-(5.00*(Value-0x02A8))/0x001f;angle_B = 16.3418-angle_A*0.2085;}//timer1_setting = 800;}  //60~65
		else if (Value>=0x0287 && Value<0x02A8)  
		{angle_A = 70.00-(5.00*(Value-0x0287))/0x0021;angle_B = 14.6813-angle_A*0.1829;}//timer1_setting = 700;}  //65~70
		else if (Value>=0x0265 && Value<0x0287)  
		{angle_A = 75.00-(5.00*(Value-0x0265))/0x0022;angle_B = 12.5895-angle_A*0.1530;}//timer1_setting = 600;}  //70~75
		else if (Value>=0x0241 && Value<0x0265)  
		{angle_A = 80.00-(5.00*(Value-0x0241))/0x0024;angle_B = 9.9567-angle_A*0.1179;}//timer1_setting = 500;}  //75~80
		else if (Value>=0x021d && Value<0x0241)  
		{angle_A = 85.00-(5.00*(Value-0x021d))/0x0024;angle_B = 6.6434-angle_A*0.0765;}//timer1_setting = 300;}  //80~85
		else if (Value>=0x01Fd && Value<0x021d)  
		{angle_A = 90.00-(5.00*(Value-0x01Fd))/0x0022;angle_B = 2.4726-angle_A*0.0274;}//timer1_setting = 300;}  //85~90
	}
	else if (Value>=0x00f5 && Value<0x01fd)		  //90~130
	{
		if (Value>=0x01D8 && Value<0x01fd)  
		{angle_A = 95.00-(5.00*(Value-0x01D8))/0x0023;angle_B = angle_A*0.0308-2.7777;}//timer1_setting = 300;}  //90~95
		else if (Value>=0x01B5 && Value<0x01D8)  
		{angle_A = 100.00-(5.00*(Value-0x01B5))/0x0023;angle_B = angle_A*0.1004-9.3823;}//timer1_setting = 300;}  //95~100
		else if (Value>=0x0192 && Value<0x01B5)  
		{angle_A = 105.00-(5.00*(Value-0x0192))/0x0023;angle_B = angle_A*0.1832-17.6697;}//timer1_setting = 500;}  //100~105
		else if (Value>=0x0171 && Value<0x0192)  
		{angle_A = 110.00-(5.00*(Value-0x0171))/0x0021;angle_B = angle_A*0.2817-28.0104;}//timer1_setting = 600;}  //105~110
		else if (Value>=0x0151 && Value<0x0171)  
		{angle_A = 115.00-(5.00*(Value-0x0151))/0x0020;angle_B = angle_A*0.3977-40.7732;}//timer1_setting = 700;} //110~115
		else if (Value>=0x0130 && Value<0x0151)  
		{angle_A = 120.00-(5.00*(Value-0x0130))/0x0020;angle_B = angle_A*0.5321-56.2245;}//timer1_setting = 800;}  //115~120
		else if (Value>=0x0111 && Value<0x0130)  
		{angle_A = 125.00-(5.00*(Value-0x0111))/0x001f;angle_B = angle_A*0.6830-74.3318;}//timer1_setting = 900;}  //120~125
		else if (Value>=0x00F5 && Value<0x0111)  
		{angle_A = 130.00-(5.00*(Value-0x00F5))/0x001c;angle_B = angle_A*0.8439-94.4508;}//timer1_setting = 1000;}  //125~130
	}
	else if (Value>=0x0060 && Value<0x00f5)		 //130~180
	{
		if (Value>=0x00DB && Value<0x00F5)  
		{angle_A = 135.00-(5.00*(Value-0x00DB))/0x001a;angle_B = angle_A*1.0016-114.9530;}//timer1_setting = 1000;}  //130~135
		else if (Value>=0x00C4 && Value<0x00DB)  
		{angle_A = 140.00-(5.00*(Value-0x00C4))/0x0017;angle_B = angle_A*1.1355-133.0269;}//timer1_setting = 1000;}  //135~140
		else if (Value>=0x00AD && Value<0x00C4)  
		{angle_A = 145.00-(5.00*(Value-0x00AD))/0x0017;angle_B = angle_A*1.2215-145.0574;}//timer1_setting = 1000;}  //140~145
		else if (Value>=0x009A && Value<0x00AD)  
		{angle_A = 150.00-(5.00*(Value-0x009A))/0x0013;angle_B = angle_A*1.2405-147.8144;}//timer1_setting = 1000;}  //145~150
		else if (Value>=0x0088 && Value<0x009A)  
		{angle_A = 155.00-(5.00*(Value-0x0088))/0x0012;angle_B = angle_A*1.1880-139.9403;}//timer1_setting = 1000;}  //150~155
		else if (Value>=0x007B && Value<0x0088)  
		{angle_A = 160.00-(5.00*(Value-0x007B))/0x000d;angle_B = angle_A*1.0763-122.6295;}//timer1_setting = 1600;}  //155~160
		else if (Value>=0x0060 && Value<0x007B)  
		{angle_A = 180.00-(20.00*(Value-0x0060))/0x001b;}  //160~180
	}
	if( angle_A >= 180.00) angle_A = 180.00;		 //防止运算溢出
	if( angle_A <= 0) angle_A = 0;
	if( angle_B >= 90.00)  angle_B = 90.00;
	if( angle_B <= 0) angle_B = 0;
   
	//angle_B_last = angle_B_now;
	//angle_B_now = angle_B;
	//angle_B = angle_B + (angle_B_now-angle_B_last);	
	
				
}

//角度计算与传送
void angle_count(void)
{ 
	 static uint16 pulse_count_now,pulse_count_last=4000;
	 uint32 a_temp = 0;
	 EADC = 0; 
	 Data_optimization(NEW_DATA);
	 if(flag == 0)
	 {
		 if(angle_A>90.00)
		 {
		 	  pulse_count = (uint16)((angle_A-90.00)/0.225*2) + pulse_standard;
			  CW = 1;
		 }
		 else if(angle_A<90.00)
		 {
		 	  pulse_count = (uint16)((90.00-angle_A)/0.225*2) + pulse_standard;
			  CW = 0;
		 }
	 }
	 if(flag == 2)
	 {
	 	if(angle_A>=90.00)//(angle_A>=90.50)
		{
			 pulse_count_now = ((uint16)((angle_A+angle_B-89.775)/0.225*2)) + pulse_standard;
		}
		else//(angle_A<=89.50)
		{
			 pulse_count_now = pulse_standard - ((uint16)((90.225-angle_A-angle_B)/0.225*2));
		}
		pulse_count = 2*pulse_count_now-pulse_count_last;
		pulse_count_last = pulse_count_now;
	 }
	 a_temp = (uint32)(angle_A*100);
	 show[0] = a_temp/10000+'0';		   //12864显示
	 show[1] = a_temp/1000%10+'0';
	 show[2] = a_temp/100%10+'0';
	 show[4] = a_temp/10%10+'0';
	 show[5] = a_temp%10+'0'; 
	 show_str16(0x90,show,3);
	 a_temp = (uint32)(angle_B*100);
	 show[0] = a_temp/10000+'0';		   //12864显示
	 show[1] = a_temp/1000%10+'0';
	 show[2] = a_temp/100%10+'0';
	 show[4] = a_temp/10%10+'0';
	 show[5] = a_temp%10+'0'; 
	 show_str16(0x98,show,3);
	 //delay_ms(5);
	 //puts(show);
   	 				   //刷新12864
	 //uart_SEND_16(NEW_DATA);
	 //uart_SEND_8(P2);
	 EADC = 1;

}

uint8 type_choose(void)							//功能选择
{
	P2 = 0xff;
	while(P2 != 0xff);
	if(P2 == 0x7f) return 1;
	else if(P2 == 0xbf) return 2;
	else if(P2 == 0xdf) return 3;
	else return 4;
}


//系统初始化
void system_init(void)
{
	EN = 1;
	CW = 1;
	CK = 1;
	show_page(page1);
	delay_ms(1000);
	show_page(page2);
	delay_ms(1000);
	show_page(page3);
}

void Mode_1(void)	   //周期摆动模式
{
	uint8 i;
	w_com(0x01);show_str16(0x90,str2,8);
	delay_ms(500);w_com(0x01);
	show_page(page4);
	while(P2 != 0xef);
	EN = 0;CW = 1;
	for(i=200;i>0;i--)
	{
		delay_250us(5);CK = ~CK;
		delay_250us(5);CK = ~CK;
	}
	show_page(page5);
	delay_ms(1000);
	while(P2 != 0xef);
	EN = 0;
	while(1)
	{
		delay_250us(5);CK = ~CK;	
	}
}

void Mode_2(void)	   //硬币随摆模式
{
	uint8 a=1;
	w_com(0x01);show_str16(0x88,str3,8);
	delay_ms(500);w_com(0x01);
	show_page(page4);
	P2 = 0xff;
	while(P2 != 0xf3);
	delay_ms(1000);
	LCD = 1;
	EN = 0;CW = 1;
	pulse_now = pulse_standard;
	show_page(page6);
	TH0 = (65536-timer0_setting)/256;
	TL0 = (65536-timer0_setting)%256;
	TMOD = 0x01;
	Get_ADC(0,ADC_SPEEDHH,100);
	delay_ms(40);
	EA = 1;
	ET0 = 1;
	TR0 = 1;
	PT0 = 1;
	while(a)
	{
		if(angle_A>=11000||angle_A<=7000) {ET0 = 1;TR0 = 1;a=0;}
	}
	while(1);
}

void Mode_3(void)	   //自动瞄靶模式
{
	w_com(0x01);show_str16(0x98,str4,8);
	delay_ms(500);w_com(0x01);
	show_page(page7);
	while(P2 != 0xef);
	delay_ms(20);
	flag = 2;
	EN = 0;CW = 1;
	pulse_now = pulse_standard;
	show_page(page6);
	TH1 = (65536-timer1_setting)/256;
	TL1 = (65536-timer1_setting)%256;
	TMOD = 0x10;
	Get_ADC(0,ADC_SPEEDHH,100);
	delay_ms(30);
	EA = 1;
	ET1 = 1;
	TR1 = 1;
	PT1 = 1;
	while(1);
}

///主函数

void main(void)
{
	uint8 type = 4;
	LCD = 0;
	LCD_init();
	//uart_init();
	system_init();
	while(1)
	{
		type = type_choose();
		switch(type)				 //功能选择
		{
			case 1:Mode_1();break;
			case 2:Mode_2();break;
			case 3:Mode_3();break;
			case 4:break;
		}
	}
}

void timer0_interrupt(void)	interrupt 1
{
	TH0 = (65536-timer0_setting)/256;
	TL0 = (65536-timer0_setting)%256;
	if(P2 != 0xf3&&flag==0)	{flag = 1;flag = 1;flag = 1;flag = 1;CW = ~CW;EADC=0;}
	if(flag == 0)
	{	
		if(pulse_now < pulse_count) {CK = ~CK;pulse_now++;}//校正电机
	}
	else
	{
		CK = ~CK;
		if(--pulse_now == pulse_standard) {ET0 = 0;LCD = 0;EADC=1;}//电机归零
	}
}

void timer1_interrupt(void)	interrupt 3
{
	//static uint8 cnt = 40;
	uint8 i = 30;
	TH1 = (65536-timer1_setting)/256;
	TL1 = (65536-timer1_setting)%256;
	//if(P2 == 0xef&&flag==0)	{flag = 1;CW = ~CW;}
	if(flag == 2)
	{/*	
		if(pulse_now < (pulse_count)) 
		{
			cnt++;
			if(cnt>145)
			{
				CW = 1;for(;i>0;i--);CK = ~CK;pulse_now++;
				cnt = 145;
			}
		}//校正电机
		if(pulse_now > (pulse_count))	
		{			
			cnt--;
			if(cnt<5)
			{
				CW = 0;for(;i>0;i--);CK = ~CK;pulse_now--;
				cnt = 5;
			}
		} */
			
		if(pulse_now < (pulse_count)) 
		{
				CW = 1;for(;i>0;i--);CK = ~CK;pulse_now++;
		
		}//校正电机
	if(pulse_now > (pulse_count))	
		{
				CW = 0;for(;i>0;i--);CK = ~CK;pulse_now--;

		} 
	}
}


void ADC_interrupt(void) interrupt 5		
{
	ADC_CONTR &= !ADC_FLAG;					//清除中断标志
	ADC_Result = ADC_Result + ADC_RES*256+ADC_RESL;		  //数据累加
	ADC_counts++;
	if(ADC_counts == ADC_times)
	{
		 NEW_DATA = (ADC_Result+ADC_times/2)/ADC_times;	  //ADC计算
		 ADC_counts = 0;
		 ADC_Result = 0;
		 angle_count();
	}
	 ADC_CONTR = ADC_POWER|ADC_speed_choose|ADC_START|ADC_ch_choose;
	_nop_();
	_nop_();
	_nop_();
}


