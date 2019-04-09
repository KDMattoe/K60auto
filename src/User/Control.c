#include "include.h"
#define FLASH_RATE 10
u8 screen_flash_rate = 0;                               //n倍控制周期

void Controller(){
  uint8 i;
  //    超声波模块发送
  for(i=0; i<1; i++){
    HCSR_pull_trig(i);
  }
}

void view_(){
  //if(screen_flash_rate++ <= FLASH_RATE) {
    screen_flash_rate == 0;
    LCD_CLS();
    LCD_P6x8Str(2, 0, "0th:"); LCD_PrintU16(20, 0, sensor[0].distance);
    LCD_P6x8Str(2, 1, "1th:");        
    LCD_P6x8Str(2, 2, "2th:");
    LCD_P6x8Str(2, 3, "3th:");
    LCD_P6x8Str(2, 4, "4th:");

  //}
  
}

//PIT 1 用于控制周期
void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);         //清中断标志位
  view_();
  Controller();                 //运行控制单元
}

void PORTB_Interrupt()
{
  int n,i;
  i=0;
  for(i=0;i<1;i++ ){
    n = sensor[i].ECHO;
    if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
     
      if(GPIO_Get(HCSR_0_ECHO)){           
        //收到高电平
        sensor[i].flag = 1;
        sensor[i].start_time = pit_time_get_notClear(PIT0)/100;
        sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //获取时钟周期

      } else {                                  
        //结束测距 
        if(sensor[i].flag){
          sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //获取时钟周期
          get_distance(i);
          sensor[i].flag = 0;
        }
        
      }
    }
  }

}


//PIT0用于超声波模块的使用
void PIT0_Interrupt()
{
  PIT_Flag_Clear(PIT0);       //清中断标志位
 
  pit_time_start(PIT0);
}



void moto_cotroller(){

}