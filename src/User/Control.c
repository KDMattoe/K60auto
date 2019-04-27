#include "include.h"
#include "Control.h"
u8 sensor_shift_flag = 0;
u8 screen_flash_rate= 0;                    //n倍控制周期

void drew_send(){
    uint8 sum = 0;
    int16 left= IDC[LEFT_F]*2/5 + IDC[LEFT_S]*3/5;
    int16 right = IDC[RIGHT_F]*2/5 + IDC[RIGHT_S]*3/5;
    UART_Put_Char(UART4,0xAA);sum += 0xAA;
    UART_Put_Char(UART4,0xAA);sum += 0xAA;
    UART_Put_Char(UART4,0xF1);sum += 0xF1;
    UART_Put_Char(UART4,0x06);sum += 0x06;
    
//    UART_Put_Char(UART4,IDC[LEFT_F]>>8);sum+=IDC[LEFT_F]>>8;
//    UART_Put_Char(UART4,IDC[LEFT_F]);sum+=IDC[LEFT_F];
//    UART_Put_Char(UART4,IDC[LEFT_S]>>8);sum+=IDC[LEFT_S]>>8;
//    UART_Put_Char(UART4,IDC[LEFT_S]);sum+=IDC[LEFT_S];
//    UART_Put_Char(UART4,IDC[RIGHT_F]>>8);sum+=IDC[RIGHT_F]>>8;
//    UART_Put_Char(UART4,IDC[RIGHT_F]);sum+=IDC[RIGHT_F];
//    UART_Put_Char(UART4,IDC[RIGHT_S]>>8);sum+=IDC[RIGHT_S]>>8;
//    UART_Put_Char(UART4,IDC[RIGHT_S]);sum+=IDC[RIGHT_S];
//    
    
    uint16 x=(dir - STEER_MIN) / STEER_ONE_HZ;
    UART_Put_Char(UART4,x>>8);sum+=x>>8;
    UART_Put_Char(UART4,x);sum+=x;
    UART_Put_Char(UART4,test>>8);sum+=test>>8;
    UART_Put_Char(UART4,test);sum+=test;
    UART_Put_Char(UART4,test1>>8);sum+=test1>>8;
    UART_Put_Char(UART4,test1);sum+=test1;
    
    UART_Put_Char(UART4,sum);
    
}


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
            LCD_P6x8Str(2, i, ch);  LCD_PrintU16(15, i, sensor[i].distance);
        }
    LCD_P6x8Str(60, 0, "Lf:");    LCD_PrintU16(80,0, IDC[LEFT_F]);
    LCD_P6x8Str(60, 1, "Rf:");     LCD_PrintU16(80,1, IDC[RIGHT_F]);
    LCD_P6x8Str(60, 2, "Ls:");     LCD_PrintU16(80,2,IDC[LEFT_S]);            
    LCD_P6x8Str(60, 3, "Rs:");     LCD_PrintU16(80,3,IDC[RIGHT_S]);
    LCD_P6x8Str(60, 4, "dir:");     LCD_PrintU16(80,4,test);//(dir - STEER_MIN) / STEER_ONE_HZ

    }
   
  
}



void HCSR_Controller(){
    uint8 i;
    
    sensor_shift_flag = (sensor_shift_flag)? 0: 1;
    //    超声波模块发送
    for(i=sensor_shift_flag; i<HCSR_SENSOR_SIZE; i++) {
        HCSR_pull_trig(i);              //发送信号
    }
}


void pit1(){
  
  if(pit1_f){
    //if(! HCSR_detect()){                    //未阻塞
        HCSR_Controller();                 //运行控制单元
        IDC_get();
        //IDC_ap();   //当不在赛道中间时放大差值，详情见程序底部。
        electrical_control();
   //     } else {
        /*******************************/
        //被阻塞（检测到横断）的策略 TODO
   //}
  
  view_();
  drew_send();
  pit1_f = 0;
    
  }
  
}




//PIT 1 用于控制周期
void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);         //清中断标志位
  pit1_f = 1;
}



void PORTA_Interrupt()
{
    int n,i;
    i=0;
    for(i=0;i<HCSR_SENSOR_SIZE;i++ ){
        n = sensor[i].ECHO;
        if((PORTA_ISFR & (1<<n))) {
            PORTA_ISFR |= (1<<n); 
            if(GPIO_Get(sensor[i].ECHO)){                                                     
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


