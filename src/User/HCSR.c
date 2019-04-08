#include "include.h"
#include "HCSR.h"
struct HCSR_Struct sensor[5];
void HCSR_Init(void){
    //¼õµôÈýÊ®¶þÊÇÒòÎªPORTB´Ó32¿ªÊ¼
    GPIO_Init(PORTB, HCSR_1_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_1_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_2_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_2_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_3_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_3_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_4_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_4_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
    GPIO_Init(PORTB, HCSR_5_TRIG-32, GPO, 0);          //³¬Éù²¨trig 
    GPIO_Init(PORTB, HCSR_5_ECHO-32, GPI, 0);          //³¬Éù²¨echo   
   
}

//TODO
uint32 get_distance(uint8 index,uint32 cnt){
    
    
    return (uint32)cnt*(331.4+0.607*20)/2000;
}


void HCSR_pull_trig( struct HCSR_Struct s){
    GPIO_Ctrl(PORTB, s.TRIG, 1);
    LPTMR_delay_us(20);
    
    GPIO_Ctrl(PORTB, s.TRIG, 0);

}