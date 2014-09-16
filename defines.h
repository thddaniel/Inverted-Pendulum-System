#ifndef _DEFINES_
#define _DEFINES_


sbit CK = P0^0;
sbit CW = P0^1;
sbit EN = P0^2;
sbit LCD = P0^4;

code uint8 page1[][16] = {"2013��ȫ����ѧ��",
						  "  ������ƾ���  ",
						  "    ���ش�ѧ    ",
						  "У��ѡ����Ʒչʾ",};

code uint8 page2[][16] = {"  ���ͣ�������  ",
						  "��Ʒ01�����ɰ�  ",
						  "��Ա��  �����  ",
						  "���κ�  ���    ",};

code uint8 page3[][16] = {"����ѡ��      ",
						  "1.���ڰڶ�      ",
						  "2.Ӳ�����      ",
						  "3.�Զ����      ",};

code uint8 page4[][16] = {"���ɰ�ƽ��ϵͳ  ",
						  "ȫ���Ը��������",
						  "���ֶ�����ƽ����",
						  "ˮƽλ�ò���A ��",};

code uint8 page5[][16] = {"��ȷ��ƽ���Ƿ�Ϊ",
						  "��ֱ״̬        ",
						  "ȷ�����ƽ���ƶ�",
						  "��ĳ�ǶȺ�A ��",};

code uint8 page6[][16] = {"��ǰ�Ƕ�A ֵ��  ",
						  "                ",
						  "��ǰ�Ƕ�B ֵ��  ",
						  "                ",};

code uint8 page7[][16] = {"������������׼",
						  "��������밴A   ",
						  "                ",
						  "                ",};

code uint8 page8[][16] = {"2013��ȫ����ѧ��",
						  "  ������ƾ���  ",
						  "    ���ش�ѧ    ",
						  "У��ѡ����Ʒչʾ",};

code uint8 page9[][16] = {"2013��ȫ����ѧ��",
						  "  ������ƾ���  ",
						  "    ���ش�ѧ    ",
						  "У��ѡ����Ʒչʾ",};

code uint8 str1[] = {"�ɼ���׼......  "};
code uint8 str2[] = {"1.���ڰڶ�      "};
code uint8 str3[] = {"2.Ӳ�����      "};
code uint8 str4[] = {"3.�Զ����      "};
code uint8 str5[] = {"��ǰ�Ƕ�ֵ  ...."};
code uint8 str6[] = {"ȫ���Ը��������"};
code uint8 str7[] = {"ȫ���Ը��������"};
code uint8 str8[] = {"ȫ���Ը��������"};


#define ADC_POWER	0x80
#define ADC_FLAG	0x10
#define ADC_START	0x08
#define ADC_SPEEDLL	0x00
#define ADC_SPEEDL	0x20
#define ADC_SPEEDH	0x40
#define ADC_SPEEDHH	0x60

#define	ADC_F 10	//һ�׵�ͨ�˲����˲�ϵ����ȡ0~100���������ϵ��Ϊ��һ�β��������Ȩ��

uint8 show[7] = {"000.00\n"};  //�Ƕ���ʾ����
uint16 	ADC_times = 0;			 //ȡ��ֵ����
uint16 	ADC_counts = 0;			 //������
uint32 	ADC_Result = 0;			 //ADC�ۼӺ�
uint8	ADC_ch_choose = 0;		 //ADCͨ��ѡ��
uint8	ADC_speed_choose = 0;	 //ADC�ٶ�ѡ��
uint16	NEW_DATA = 0;			 //ADC��ֵ
uint16  pulse_now;//0.9��
uint16  pulse_count=4000;
uint16  pulse_standard = 4000;
uint8 flag = 0;				   //ȫ�ֱ�־
float angle_A = 0;
float angle_B = 0;



#define timer0_setting 500	   //
uint16 timer1_setting = 200;




#endif