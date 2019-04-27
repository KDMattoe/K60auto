#include "include.h"
#include "HCSR.h"
struct HCSR_Struct sensor[HCSR_SENSOR_SIZE];
uint8 blocked = 0;


void HCSR_Init(void){
    //ECHO中存放的是PORTB中的顺序， HCSR_0中存放的管脚的序号
    sensor[0].ECHO = HCSR_0_ECHO;
    sensor[0].TRIG = HCSR_0_TRIG;
//    sensor[1].ECHO = HCSR_1_ECHO-PORTB_OFFSET;
//    sensor[1].TRIG = HCSR_1_TRIG-PORTB_OFFSET;
//    sensor[2].ECHO = HCSR_2_ECHO-PORTB_OFFSET;
//    sensor[2].TRIG = HCSR_2_TRIG-PORTB_OFFSET;
//    sensor[3].ECHO = HCSR_3_ECHO-PORTB_OFFSET;
//    sensor[3].TRIG = HCSR_3_TRIG-PORTB_OFFSET;
//    sensor[4].ECHO = HCSR_4_ECHO-PORTB_OFFSET;
//    sensor[4].TRIG = HCSR_4_TRIG-PORTB_OFFSET;
   int i; 
//    
//    //对所用到的管脚进行初始化
    for(i=0; i<HCSR_SENSOR_SIZE; i++){
     GPIO_Init(PORTA, sensor[i].ECHO , GPI, 0);          //超声波echo   
      GPIO_Init(PORTA, sensor[i].TRIG, GPO, 0);          //超声波trig 
  
    }
//    
    
}
/********************************************
first：发超声波时的时间戳
end：收到超声波时的时间戳
cnt：时间差（单位为us）
distance：距离，单位为mm
********************************************/


uint32 get_distance(uint8 index){
    
    uint32 first = sensor[index].start_time;
    uint32 end = sensor[index].stop_time;
    uint32 cnt=0;
    if(first>end) {     //定时器重启过
      cnt = ~0 - first;
      cnt = cnt + end;
    } else {            //正常工作
      cnt = end - first;
    }
    
    // 距离 = 时间差*（零度音速*温度差*单位温差下音速差）/（两倍路程 * 毫秒）
    sensor[index].distance = (uint32)cnt*(331.4+0.607*20)/2000;
    if (sensor[index].distance > 5000) {
      
      sensor[index].distance = 0;
    }
    return sensor[index].distance;
}
/******************************************
index：传感器序号
向对应传感器的Trig管脚发送一个高电平信号，持续20us。
******************************************/

void HCSR_pull_trig(uint8 index){
  
    GPIO_Ctrl(PORTA, sensor[index].TRIG, 1);
    LPTMR_delay_us(20);
    GPIO_Ctrl(PORTA, sensor[index].TRIG, 0);
   
}


uint8 HCSR_detect(){
  if(sensor[3].distance > 700 && sensor[3].distance < 1600){
    blocked ++;                         //距离在1.6m到0.7米之内，视作有效计数
  }
  if(blocked < 10){                     //检测到十次以上，确认前方被阻塞   
    return 0;
  }
  return 1;
}

void HCSR_release(){
  blocked = 0;
}