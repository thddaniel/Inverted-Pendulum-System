/*�澧HJ12864ZW��ظ�����*/
/*���ĺ���:	void LCD_init(void)									 ��ʼ��
			void show_str16(uint8 addr,uint8 *str,uint8 count)	 д�ַ���
			void show_page(uint8 (*page)[16])					 дҳ��
			void show_NUM(uint8 addr,uint NUM)					 д��λ����
*/

#include "includes.h"

/*****************************����ʱ**********************/
//������stc12c5a60s2��11.0592M�����¡�
void delay_12864(uint8 x)	   //����ʱָ�������֮�����ʱ
{					   //������
	uint8 k,j;
	for(k=0;k<x;k++)
		for(j=0;j<10;j++);
}

/*
///////////////////////////////////////////////////////////////////////////
///////////��������ģʽ�µĺ���////////////////////////////////////////////
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
////////////////////////////����ģʽ�µĳ���ע��ģ���ϵ�PSB����û�к��ӣ�////
void SendByteLCD(uint8 WData)		 //�����д�����ݻ�ָ��
{
	uint8 i;
	for(i=0;i<8;i++)
	{
		if((WData<<i)&0x80)	RW = 1;	   //�������ƣ���λ����
		else RW = 0;
		E = 0;						   //����ʱ��
		delay_12864(4);					   //ʱ��������Сʱ��ֵ
		E = 1;
	}
}

void w_com(uint8 Wdata)		          //�����д������
{
	RS=0;
	RS=1;
	SendByteLCD(0xf8);
	SendByteLCD(Wdata&0xf0);
	SendByteLCD((Wdata<<4)&0xf0);
	delay_12864(50);				               //������ʱ
}

void w_dat(uint8 Wdata)
{
	RS = 0;
	RS = 1;
	SendByteLCD(0xfa);
	SendByteLCD(Wdata&0xf0);
	SendByteLCD((Wdata<<4)&0xf0);
	delay_12864(50);							   //������ʱ
}

///////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////


void LCD_init(void)
{
	//PSB = 1;							 //���������д���
	//REST = 1;REST = 0;REST = 1;		 //���������д���
	w_com(0x30);//�����趨   8-bit ����ָ��
	w_com(0x06);//������趨
	w_com(0x01);//����
	w_com(0x0c);//��ʾ״̬��������ʾ���α겻��ʾ�����ס�
	w_com(0x02);//��ַ��λ
}

//����ʾ�����ֽ���ʾ
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
//10����������ʾ
void show_NUM_10(uint8 addr,uint8 number)
{
	uint8 num[2];
	num[0] = number/10+'0';
	num[1] = number%10+'0';
	show_str16(addr,num,1);
	
}
*/
	

////////////////////��ҳ��ʾ//////////////////////////
void show_page(uint8 (*page)[16])
{
	show_str16(0x80,*page,8);
	show_str16(0x90,*(page+1),8);
	show_str16(0x88,*(page+2),8);
	show_str16(0x98,*(page+3),8);
}