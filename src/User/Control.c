#include "include.h"

void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);       //清中断标志位
  

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
        get_distance(i, cnt);           //计算结果为毫米级别
      }
  }
  
  }
  
  
}