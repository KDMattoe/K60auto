#include "include.h"
#include "eletrical.h"

uint16 direction=11125;

uint16 GoOrTurn =0;
uint16 dir=0;
uint16 DirecChange=0;

// 100M���� ��Ƶ 1/16��
//�����ʼ��
void electrical_init(){
    FTM_PWM_Init(FTM0,FTM_CH0,ELE_FREQUENCY, ELE_ONE_HZ *40);//PTC1 
    FTM_PWM_Init(FTM0,FTM_CH1,ELE_FREQUENCY, STEER_OFFSET + STEER_ONE_HZ*50);//PTC2
    FTM_PWM_Init(FTM2,FTM_CH1,STEER_FREQUENCY,direction);//PTB19
}

//�������
void electrical_control(){

   DirecChange=IncPIDCalc( IDC[LEFT_F] - IDC[RIGHT_F] );//����pid�㷨
   if (DirecChange>=0)
      dir=direction+DirecChange*50/35;//���ת���з�Ӧ���ǳ̶�̫���С �͸�������� 50/35�ǰ��ɳ��ı������ 
   else
      dir=direction+DirecChange*50/35;//�̶�̫С���и���� һ��һ��
   if(dir<STEER_MIN)
      dir=STEER_MIN;
   if(dir>STEER_MAX)
      dir=STEER_MAX;
   FTM_PWM_Duty(FTM2,FTM_CH1,dir);
}
  