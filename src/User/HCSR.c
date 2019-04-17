#include "include.h"
#include "HCSR.h"
struct HCSR_Struct sensor[HCSR_SENSOR_SIZE];


void HCSR_Init(void){
    //ECHO�д�ŵ���PORTB�е�˳�� HCSR_0�д�ŵĹܽŵ����
    sensor[0].ECHO = HCSR_0_ECHO-PORTB_OFFSET;
    sensor[0].TRIG = HCSR_0_TRIG-PORTB_OFFSET;
    sensor[1].ECHO = HCSR_1_ECHO-PORTB_OFFSET;
    sensor[1].TRIG = HCSR_1_TRIG-PORTB_OFFSET;
    sensor[2].ECHO = HCSR_2_ECHO-PORTB_OFFSET;
    sensor[2].TRIG = HCSR_2_TRIG-PORTB_OFFSET;
    sensor[3].ECHO = HCSR_3_ECHO-PORTB_OFFSET;
    sensor[3].TRIG = HCSR_3_TRIG-PORTB_OFFSET;
    sensor[4].ECHO = HCSR_4_ECHO-PORTB_OFFSET;
    sensor[4].TRIG = HCSR_4_TRIG-PORTB_OFFSET;
    int i; 
    
    //�����õ��ĹܽŽ��г�ʼ��
    for(i=0; i<HCSR_SENSOR_SIZE; i++){
      GPIO_Init(PORTB, sensor[i].ECHO , GPI, 0);          //������echo   
      GPIO_Init(PORTB, sensor[i].TRIG, GPO, 0);          //������trig 
  
    }
    
    
}
/********************************************
first����������ʱ��ʱ���
end���յ�������ʱ��ʱ���
cnt��ʱ����λΪus��
distance�����룬��λΪmm
********************************************/


uint32 get_distance(uint8 index){
    
    uint32 first = sensor[index].start_time;
    uint32 end = sensor[index].stop_time;
    uint32 cnt=0;
    if(first>end) {     //��ʱ��������
      cnt = ~0 - first;
      cnt = cnt + end;
    } else {            //��������
      cnt = end - first;
    }
    
    // ���� = ʱ���*���������*�¶Ȳ�*��λ�²������ٲ/������·�� * ���룩
    sensor[index].distance = (uint32)cnt*(331.4+0.607*20)/2000;
    if (sensor[index].distance > 5000) {
      
      sensor[index].distance = 0;
    }
    return sensor[index].distance;
}
/******************************************
index�����������
���Ӧ��������Trig�ܽŷ���һ���ߵ�ƽ�źţ�����20us��
******************************************/

void HCSR_pull_trig(uint8 index){
  
    GPIO_Ctrl(PORTB, sensor[index].TRIG, 1);
    LPTMR_delay_us(20);
    GPIO_Ctrl(PORTB, sensor[index].TRIG, 0);
   
}
