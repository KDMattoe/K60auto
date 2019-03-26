/****************************************************************************************************
【平    台】龙邱K60VG核心板
【编    写】CHIUSIR
【E-mail  】chiusir@163.com
【软件版本】V1.0
【最后更新】2016年09月01日
【相关信息参考下列地址】
【网    站】http://www.lqist.cn
【淘宝店铺】http://shop36265907.taobao.com
------------------------------------------------
【dev.env.】IAR7.3
【busclock】100.000MHz
【pllclock】200.000MHz
=============================================================
接口定义：
PWM口定义：
FTM2_CH0--PTB18
FTM2_CH1--PTB19

按键定义：
KEY0--PTB20
KEY1--PTB21
KEY2--PTB22

OLED口定义：
LCD_DC --PTC19
LCD_RST--PTC18
LCD_SDA--PTC17
LCD_SCL--PTC16
=============================================================
实验现象：
按下K0，占空比恢复初值
按下K1，占空比增加
按下K2，占空比减小
并在0.96寸OLED屏上显示数值
=============================================================
******************************************************************************************************/
#include "include.h"
#define 22 HCSR_TRIG;
#define 23 HCSR_ECHO;

u8 PIT0_f=0;

void control(void);
void time_delay_ms(u32 ms)
{
  LPTMR_delay_ms(ms);
}

s16 a[8];

void drive_init(){
    PLL_Init(PLL200);         //初始化PLL为200M，总线为100MHZ  
    LCD_Init();
    UART_Init(UART4,38400);     //串口4初始化
    GPIO_Init(PORTB, HCSR_TRIG, 1, 0); //超声波trig
    GPIO_Init(PORTB, HCSR_ECHO, 0, 0); //超声波echo
    EXTI_Init(PORTB,23, either_down);//初始化外部中断
                                     //初始化DMA定时器
    
}

//主函数
void main(void)
{
    DisableInterrupts;        //关闭总中断
    
    EnableInterrupts;            //开启中断
    
    
    while(1){
    LCD_CLS();
      
      
      time_delay_ms(100);
      UART_Put_Str(UART4, "hello");
      LCD_P6x8Str(2, 3,"hello darling");
      time_delay_ms(100);
    };
   
}

void PORTB_Interrupt()
{
  int n;
  n=HCSR_ECHO;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
      /* 用户自行添加中断内程序 */
      
      
      
  } 
  n=1;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
      /* 用户自行添加中断内程序 */
  } 
}