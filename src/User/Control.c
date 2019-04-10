#include "include.h"
#define FLASH_RATE 20
u8 sensor_shift_flag = 0;
u8 screen_flash_rate = 0;                               //n倍控制周期

/*******************************************

显示屏控制
scree_flash_rate:OLED刷新频率
5是超声波传感器的数量，下面所有使用到5的地方都是  

*******************************************/
void view_(){
    
    int i=0;
    if(screen_flash_rate++ <= FLASH_RATE) {
        screen_flash_rate = 0;
        LCD_CLS();
        for(i=0; i < HCSR_SENSOR_SIZE; i++) {
            char ch[5] = {'0'+i, 't', 'h', ':'};              //显示效果即     'i'th:
            LCD_P6x8Str(2, i, ch);  LCD_PrintU16(25, i, sensor[i].distance);
        }
    }
  
}


void Controller(){
    uint8 i;
    sensor_shift_flag = (sensor_shift_flag)? 0: 1;
    //    超声波模块发送
    for(i=sensor_shift_flag; i<HCSR_SENSOR_SIZE; i++) {
        HCSR_pull_trig(i);

       
    }
}

//TODO  电机控制
//void moto_cotroller(){
    
//}


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
    for(i=0;i<HCSR_SENSOR_SIZE;i++ ){
        n = sensor[i].ECHO;
        if((PORTB_ISFR & (1<<n))) {
            PORTB_ISFR |= (1<<n); 
            if(GPIO_Get(sensor[i].ECHO+PORTB_OFFSET)){                                                     
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


