#include "include.h"
#include "PID.h"

static struct PID sPID;
static struct PID *sptr = &sPID;

int32 P_DATA =500;//1000太小
int32 I_DATA =0;//
int32 D_DATA =0; //3000  

//-----------------------------------------
//PID参数初始化
//-----------------------------------------
void PID_Init(void)
{
	sptr->LastError = 0; //Error[-1]
	sptr->sumError;
        sptr->P =P_DATA; //比例常数Proportional Const
	sptr->I =I_DATA; //积分常数Integral Const
	sptr->D =D_DATA; //微分常数Derivative Const
	sptr->SetPoint =0; //目标是0 l-r=0时为中
}

//-----------------------------------------
//增量式PID控制设计
//-----------------------------------------
int32 IncPIDCalc(int NextPoint)
{
	int iError, dError; //当前误差
        int32 LocPid;
	iError = sptr->SetPoint - NextPoint;            //与目标偏差
        dError = iError - sptr->LastError;
        
        sptr->LastError = iError;
        sptr->sumError += iError;
	
        LocPid = sptr->P * iError 
                - sptr->I * sptr->sumError 
                + sptr->D * dError;       //微分项
        
        return(LocPid/100);                           //返回增量值
}







