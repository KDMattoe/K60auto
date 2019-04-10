#include "include.h"
#define FLASH_RATE 20
u8 sensor_shift_flag = 0;
u8 screen_flash_rate = 0;                               //n����������

/*******************************************

��ʾ������
scree_flash_rate:OLEDˢ��Ƶ��
5�ǳ���������������������������ʹ�õ�5�ĵط�����  

*******************************************/
void view_(){
    
    int i=0;
    if(screen_flash_rate++ <= FLASH_RATE) {
        screen_flash_rate = 0;
        LCD_CLS();
        for(i=0; i < HCSR_SENSOR_SIZE; i++) {
            char ch[5] = {'0'+i, 't', 'h', ':'};              //��ʾЧ����     'i'th:
            LCD_P6x8Str(2, i, ch);  LCD_PrintU16(25, i, sensor[i].distance);
        }
    }
  
}


void Controller(){
    uint8 i;
    sensor_shift_flag = (sensor_shift_flag)? 0: 1;
    //    ������ģ�鷢��
    for(i=sensor_shift_flag; i<HCSR_SENSOR_SIZE; i++) {
        HCSR_pull_trig(i);

       
    }
}

//TODO  �������
//void moto_cotroller(){
    
//}


//PIT 1 ���ڿ�������
void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);         //���жϱ�־λ
  view_();
  Controller();                 //���п��Ƶ�Ԫ
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
            //�յ��ߵ�ƽ
                sensor[i].flag = 1;
                sensor[i].start_time = pit_time_get_notClear(PIT0)/100;
                sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //��ȡʱ������

        } else {                                  
            //������� 
                if(sensor[i].flag){
                    sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //��ȡʱ������
                    get_distance(i);
                    sensor[i].flag = 0;
                } 
           }
   }
  }
}


//PIT0���ڳ�����ģ���ʹ��
void PIT0_Interrupt()
{
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
 
  pit_time_start(PIT0);
}


