#include "include.h"
#include "Control.h"
u8 sensor_shift_flag = 0;
u8 screen_flash_rate= 0;                    //n倍控制周期




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
            char ch[5] = {'0'+i,':'};              //显示效果即     'i'th:
            LCD_P6x8Str(2, i, ch);  LCD_PrintU16(15, i, 11111);//sensor[i].distance
        }
    }
    LCD_P6x8Str(60, 0, "Lf:");    LCD_PrintU16(80,0, 1111);//IDC[LEFT_F]
    LCD_P6x8Str(60, 1, "Rf:");     LCD_PrintU16(80,1, IDC[RIGHT_F]);
    LCD_P6x8Str(60, 2, "Ls:");     LCD_PrintU16(80,2,IDC[LEFT_S]);            
    LCD_P6x8Str(60, 3, "Rs:");     LCD_PrintU16(80,3,IDC[RIGHT_S]);
    LCD_P6x8Str(60, 4, "dir:");     LCD_PrintU16(80,4,(dir - STEER_MIN) / STEER_ONE_HZ);

  
}



void Controller(){
    uint8 i;
    sensor_shift_flag = (sensor_shift_flag)? 0: 1;
    //    超声波模块发送
    for(i=sensor_shift_flag; i<HCSR_SENSOR_SIZE; i++) {
        HCSR_pull_trig(i);     
    }
}


void pit1(){
  
  if(pit1_f){
    view_();
    Controller();                 //运行控制单元
    electrical_control();
    pit1_f = 0;
  }
  
}




//PIT 1 用于控制周期
void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);         //清中断标志位
  pit1_f = 1;
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


