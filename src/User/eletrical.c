#include "include.h"
#include "eletrical.h"

uint16 direction=11125;

uint16 GoOrTurn =0;
uint16 dir=0;
uint16 DirecChange=0;

// 100M总线 分频 1/16后
//电机初始化
void electrical_init(){
    FTM_PWM_Init(FTM0,FTM_CH0,ELE_FREQUENCY, ELE_ONE_HZ *40);//PTC1 
    FTM_PWM_Init(FTM0,FTM_CH1,ELE_FREQUENCY, STEER_OFFSET + STEER_ONE_HZ*50);//PTC2
    FTM_PWM_Init(FTM2,FTM_CH1,STEER_FREQUENCY,direction);//PTB19
}

//电机控制
void electrical_control(){

   DirecChange=IncPIDCalc( IDC[LEFT_F] - IDC[RIGHT_F] );//传入pid算法
   if (DirecChange>=0)
      dir=direction+DirecChange*50/35;//如果转弯有反应但是程度太大或小 就改这个倍率 50/35是按旧车的比例算的 
   else
      dir=direction+DirecChange*50/35;//程度太小还有改这个 一左一右
   if(dir<STEER_MIN)
      dir=STEER_MIN;
   if(dir>STEER_MAX)
      dir=STEER_MAX;
   FTM_PWM_Duty(FTM2,FTM_CH1,dir);
}
  