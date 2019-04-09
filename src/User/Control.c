#include "include.h"
#define FLASH_RATE 10
u8 screen_flash_rate = 0;                               //n����������

void Controller(){
  uint8 i;
  //    ������ģ�鷢��
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
  for(i=0;i<1;i++ ){
    n = sensor[i].ECHO;
    if((PORTB_ISFR & (1<<n)))
  {
      PORTB_ISFR |= (1<<n); 
     
      if(GPIO_Get(HCSR_0_ECHO)){           
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



void moto_cotroller(){

}