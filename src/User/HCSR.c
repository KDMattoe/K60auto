#include "include.h"
#include "HCSR.h"
struct HCSR_Struct sensor[5];
void HCSR_Init(void){
    //¼õµôÈıÊ®¶şÊÇÒòÎªPORTB´Ó32¿ªÊ¼
    GPIO_Init(PORTB, HCSR_0_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_0_ECHO-32, GPI, 0);          //³¬Éù²¨echo     
    GPIO_Init(PORTB, HCSR_1_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_1_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_2_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_2_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_3_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_3_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_4_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_4_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    sensor[0].ECHO = 21;
    sensor[0].TRIG = 20;
    sensor[1].ECHO = 2;
    sensor[1].TRIG = 3;
    sensor[2].ECHO = 4;
    sensor[2].TRIG = 5;
    sensor[3].ECHO = 6;
    sensor[3].TRIG = 7;
    sensor[4].ECHO = 8;
    sensor[4].TRIG = 9;
    sensor[0].flag = 0;
}

uint32 get_distance(uint8 index){
    uint32 first = sensor[index].start_time;
    uint32 end = sensor[index].stop_time;
    uint32 cnt=0;
    if(first>end) {     //¶¨Ê±Æ÷ÖØÆô¹ı
      cnt = ~0 - first;
      cnt = cnt + end;
    } else {            //Õı³£¹¤×÷
      cnt = end - first;
    }
   // if(cnt < 23000)
    sensor[index].distance = (uint32)cnt*(331.4+0.607*20)/2000;
    return sensor[index].distance;
}


void HCSR_pull_trig(uint8 index){
  
    GPIO_Ctrl(PORTB, sensor[index].TRIG, 1);
    LPTMR_delay_us(20);
    GPIO_Ctrl(PORTB, sensor[index].TRIG, 0);

}
