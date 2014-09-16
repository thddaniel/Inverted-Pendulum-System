#ifndef _DEFINES_
#define _DEFINES_


sbit CK = P0^0;
sbit CW = P0^1;
sbit EN = P0^2;
sbit LCD = P0^4;

code uint8 page1[][16] = {"2013年全国大学生",
						  "  电子设计竞赛  ",
						  "    五邑大学    ",
						  "校内选拔作品展示",};

code uint8 page2[][16] = {"  类型：控制类  ",
						  "作品01：自由摆  ",
						  "成员：  王华杲  ",
						  "刘嘉豪  唐昊    ",};

code uint8 page3[][16] = {"功能选择：      ",
						  "1.周期摆动      ",
						  "2.硬币随摆      ",
						  "3.自动瞄靶      ",};

code uint8 page4[][16] = {"自由摆平板系统  ",
						  "全力以赴做到最好",
						  "请手动调整平板至",
						  "水平位置并按A 键",};

code uint8 page5[][16] = {"请确定平板是否为",
						  "垂直状态        ",
						  "确认请把平板推动",
						  "到某角度后按A 键",};

code uint8 page6[][16] = {"当前角度A 值：  ",
						  "                ",
						  "当前角度B 值：  ",
						  "                ",};

code uint8 page7[][16] = {"请调整激光笔瞄准",
						  "调整完毕请按A   ",
						  "                ",
						  "                ",};

code uint8 page8[][16] = {"2013年全国大学生",
						  "  电子设计竞赛  ",
						  "    五邑大学    ",
						  "校内选拔作品展示",};

code uint8 page9[][16] = {"2013年全国大学生",
						  "  电子设计竞赛  ",
						  "    五邑大学    ",
						  "校内选拔作品展示",};

code uint8 str1[] = {"采集基准......  "};
code uint8 str2[] = {"1.周期摆动      "};
code uint8 str3[] = {"2.硬币随摆      "};
code uint8 str4[] = {"3.自动瞄靶      "};
code uint8 str5[] = {"当前角度值  ...."};
code uint8 str6[] = {"全力以赴做到最好"};
code uint8 str7[] = {"全力以赴做到最好"};
code uint8 str8[] = {"全力以赴做到最好"};


#define ADC_POWER	0x80
#define ADC_FLAG	0x10
#define ADC_START	0x08
#define ADC_SPEEDLL	0x00
#define ADC_SPEEDL	0x20
#define ADC_SPEEDH	0x40
#define ADC_SPEEDHH	0x60

#define	ADC_F 10	//一阶低通滤波器滤波系数（取0~100），这里的系数为上一次采样结果的权。

uint8 show[7] = {"000.00\n"};  //角度显示数组
uint16 	ADC_times = 0;			 //取均值次数
uint16 	ADC_counts = 0;			 //计算器
uint32 	ADC_Result = 0;			 //ADC累加和
uint8	ADC_ch_choose = 0;		 //ADC通道选择
uint8	ADC_speed_choose = 0;	 //ADC速度选择
uint16	NEW_DATA = 0;			 //ADC均值
uint16  pulse_now;//0.9度
uint16  pulse_count=4000;
uint16  pulse_standard = 4000;
uint8 flag = 0;				   //全局标志
float angle_A = 0;
float angle_B = 0;



#define timer0_setting 500	   //
uint16 timer1_setting = 200;




#endif