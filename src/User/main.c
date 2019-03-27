/****************************************************************************************************
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
#define HCSR_TRIG 22
#define HCSR_ECHO 23

void control(void);
void HCSR_pull_trig();
uint32 get_distance(uint32 cnt);



u8 PIT0_f=0;
uint32 distance=0;


void time_delay_ms(u32 ms)
{
  LPTMR_delay_ms(ms);
}

s16 a[8];

void drive_init(){
    PLL_Init(PLL200);         //初始化PLL为200M，总线为100MHZ  
    LCD_Init();
    UART_Init(UART4,38400);     //串口4初始化
    GPIO_Init(PORTB, HCSR_TRIG, GPO, 0);          //超声波trig
    GPIO_Init(PORTB, HCSR_ECHO, GPI, 0);          //超声波echo
    EXTI_Init(PTB, HCSR_ECHO, either_down);   //初始化外部中断
    // gpio_init (PORTA, 17, 1,0);
}

//主函数
void main(void)
{
    DisableInterrupts;        //关闭总中断
    drive_init();
    EnableInterrupts;            //开启中断
    
    
    while(1){
      LCD_CLS();
      time_delay_ms(100);
      UART_Put_Str(UART4, "hello");
      LCD_PrintU16(2, 3,distance);
      HCSR_pull_trig();
      time_delay_ms(100);
    };
   
}



uint32 get_distance(uint32 cnt){
    return (uint32)cnt*(331.4+0.607*20)/2000;
}
void HCSR_pull_trig(void){
    GPIO_Ctrl(PORTB, HCSR_TRIG, 1);
    LPTMR_delay_us(20);
}


void PORTB_Interrupt()
{
  int n,cnt;
  n=HCSR_ECHO;
  if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
      /* 用户自行添加中断内程序 */
      if(GPIO_Get(PTB23)){           //收到高电平
        pit_time_get(PIT0);                     //清空定时器
        pit_time_start(PIT0);                        //打开定时器
      } else {                                  //结束测距 
        cnt = pit_time_get_us(PIT0);               //获取时钟周期
        distance = get_distance(cnt);           //计算结果为毫米级别
      }

  }
  
}