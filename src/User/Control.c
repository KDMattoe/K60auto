#include "include.h"

void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);       //���жϱ�־λ
  

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
      /* �û���������ж��ڳ��� */
      if(GPIO_Get(PTB23)){           //�յ��ߵ�ƽ
        //pit_close(PIT0);                     //��ն�ʱ��
        pit_time_start(PIT0);                        //�򿪶�ʱ��
      } else {                                  //������� 
        cnt = pit_time_get_us(PIT0);               //��ȡʱ������
        get_distance(i, cnt);           //������Ϊ���׼���
      }
  }
  
  }
  
  
}