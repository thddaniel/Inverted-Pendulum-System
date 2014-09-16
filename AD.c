#include"stc12c5a60s2.h"

#define ADC_POWER	0x80
#define ADC_FLAG	0x10
#define ADC_START	0x08
#define ADC_SPEEDLL	0x00
#define ADC_SPEEDL	0x20
#define ADC_SPEEDH	0x40
#define ADC_SPEEDHH	0x60

#define	ADC_F 10	//一阶低通滤波器滤波系数（取0~100），这里的系数为上一次采样结果的权。

uint8 	ADC_times = 0;			 //取均值次数
uint8 	ADC_counts = 0;			 //计算器
uint16 	ADC_Result = 0;			 //ADC累加和
uint8	ADC_ch_choose = 0;		 //ADC通道选择
uint8	ADC_speed_choose = 0;	 //ADC速度选择
uint16	ADC_DATA = 0;			 //ADC低通滤波结果
uint16	NEW_DATA = 0;			 //ADC均值

/*软件一阶低通滤波器*/
void Filter(void)
{
	uint32 count_temp = 0;
	if(NEW_DATA<ADC_DATA)
	{
		 count_temp = ADC_DATA - NEW_DATA;
		 count_temp = count_temp*ADC_F;
		 count_temp = count_temp+50;
		 count_temp = count_temp/100;
		 ADC_DATA = ADC_DATA-count_temp;
	}
	else if(ADC_DATA<NEW_DATA)
	{
		 count_temp = NEW_DATA - ADC_DATA;
		 count_temp = count_temp*ADC_F;
		 count_temp = count_temp+50;
		 count_temp = count_temp/100;
		 ADC_DATA = ADC_DATA+count_temp;
	}
}


/*****************************内部AD初始化*****************/
void Get_ADC(uint8 ch,uint8 ADC_SPEED,uint8 times)
{
	ADC_counts = times;
	ADC_Result = 0;
	ADC_DATA = 0;
	ADC_ch_choose = ch;
	ADC_speed_choose = ADC_SPEED;
	ADC_CONTR = 0x00;
	AUXR1 |= 0x04;
	P1ASF = 0xff;
	P1M1 = 0xff;
	P1M0 = 0x00;
	ADC_RES = 0;
	ADC_RESL = 0;
	ADC_CONTR = ADC_POWER|ADC_speed_choose|ADC_START|ADC_ch_choose;
	_nop_();
	_nop_();
	_nop_();
	EA = 1;
	EADC = 1;
}

void ADC_stop(void)
{
	 ADC_CONTR = 0x00;
	 EADC = 0;
}


void main(void)
{
	Get_ADC(0,ADC_SPEEDLL,30);	
}


void ADC_interrupt(void) interrupt 5		
{
	ADC_CONTR &= !ADC_FLAG;					//清除中断标志
	ADC_Result = ADC_Result + ADC_RES*256+ADC_RESL;
	ADC_counts++;
	if(ADC_counts == ADC_times)
	{
		 NEW_DATA = ADC_Result/ADC_times;
		 ADC_counts = 0;
		 ADC_Result = 0;
		 Filter();
	}
	 ADC_CONTR = ADC_POWER|ADC_speed_choose|ADC_START|ADC_ch_choose;
	_nop_();
	_nop_();
	_nop_();
}