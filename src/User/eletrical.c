#include "include.h"
#include "eletrical.h"

uint16 direction=11125;

int32 dir=0;
int16 test;
int16 DirecChange=0;
int16 test1; 

// 100M总线 分频 1/16后
//电机初始化
void electrical_init(){
    FTM_PWM_Init(FTM0,FTM_CH1,ELE_FREQUENCY, ELE_ONE_HZ *45);//PTC1 
    FTM_PWM_Init(FTM0,FTM_CH0,ELE_FREQUENCY, 0);//PTC2
    FTM_PWM_Init(FTM2,FTM_CH1,STEER_FREQUENCY,STEER_OFFSET + STEER_ONE_HZ*50);//PTB19
}

//电机控制
void electrical_control(){
   int32 idc_now = IDC[LEFT_F]/3+ IDC[LEFT_S]/2 - IDC[RIGHT_F]/3- IDC[RIGHT_S]/2;
   test1 = (int16)idc_now;
   DirecChange=IncPIDCalc( idc_now );//计算偏转角度
   
   dir = DirecChange;
   test = (int16)dir;
   if(dir<STEER_MIN)
      dir=STEER_MIN;            //向右转
   if(dir>STEER_MAX)
      dir=STEER_MAX;            //向左转
   //FTM_PWM_Duty(FTM2,FTM_CH1,STEER_BALANCE+dir);
   FTM_PWM_Duty(FTM2,FTM_CH1,STEER_OFFSET+dir);

}


  