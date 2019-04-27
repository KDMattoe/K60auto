#include "include.h"
#include "eletrical.h"

uint16 direction=11125;

int32 dir=0;
int16 test;
int16 DirecChange=0;
int16 test1; 

// 100M���� ��Ƶ 1/16��
//�����ʼ��
void electrical_init(){
    FTM_PWM_Init(FTM0,FTM_CH1,ELE_FREQUENCY, ELE_ONE_HZ *45);//PTC1 
    FTM_PWM_Init(FTM0,FTM_CH0,ELE_FREQUENCY, 0);//PTC2
    FTM_PWM_Init(FTM2,FTM_CH1,STEER_FREQUENCY,STEER_OFFSET + STEER_ONE_HZ*50);//PTB19
}

//�������
void electrical_control(){
   int32 idc_now = IDC[LEFT_F]/3+ IDC[LEFT_S]/2 - IDC[RIGHT_F]/3- IDC[RIGHT_S]/2;
   test1 = (int16)idc_now;
   DirecChange=IncPIDCalc( idc_now );//����ƫת�Ƕ�
   
   dir = DirecChange;
   test = (int16)dir;
   if(dir<STEER_MIN)
      dir=STEER_MIN;            //����ת
   if(dir>STEER_MAX)
      dir=STEER_MAX;            //����ת
   //FTM_PWM_Duty(FTM2,FTM_CH1,STEER_BALANCE+dir);
   FTM_PWM_Duty(FTM2,FTM_CH1,STEER_OFFSET+dir);

}


  