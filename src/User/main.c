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

HCSR(超声波测距模块定义（待定）：
HCSR_1_TRIG PTB22
HCSR_1_ECHO PTB23
HCSR_2_TRIG PTB24
HCSR_2_ECHO PTB25
HCSR_3_TRIG PTB26
HCSR_3_ECHO PTB27
HCSR_4_TRIG PTB28
HCSR_4_ECHO PTB29
HCSR_5_TRIG PTB30
HCSR_5_ECHO PTB31
=============================================================
******************************************************************************************************/
#include "include.h"



u8 PIT0_f=0;


void time_delay_ms(u32 ms)
{
  LPTMR_delay_ms(ms);
}

void drive_init(){
    PLL_Init(PLL200);         //初始化PLL为200M，总线为100MHZ  
    LCD_Init();
    UART_Init(UART4,38400);     //串口4初始化
    int i=0;
    HCSR_Init();                //超声波传感器初始化 
    for(i=0; i<5; i++){
      EXTI_Init(PTB, sensor[i].ECHO, either_down);   //初始化外部中断
    }
    
    PIT_Init(PIT1, 20);
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
      
      
    };
   
}
void PORTB_Interrupt()
{
  int n,cnt,i;
  i=0;
  for(i=0;i<5;i++ ){
    n = sensor[i].ECHO;
    if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
      /* 用户自行添加中断内程序 */
      if(GPIO_Get(PTB23)){           //收到高电平
        //pit_close(PIT0);                     //清空定时器
        pit_time_start(PIT0);                        //打开定时器
      } else {                                  //结束测距 
        cnt = pit_time_get_us(PIT0);               //获取时钟周期
      }
  }
  }
  
  
}

