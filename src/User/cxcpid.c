#include "common.h"
#include "cxcpid.h"
//-----------------------------------------------------
//声明PID实体
//-----------------------------------------------------
typedef struct PID
{
	int SetPoint; //设定目标Desired Value 
	double Proportion; //比例常数Proportional Const 就是PID的p
	double Integral; //积分常数Integral Const i
	double Derivative; //微分常数Derivative Const
	int LastError; //Error[-1]
	int PrevError; //Error[-2]
} PID;
static PID sPID;
static PID *sptr = &sPID;


//-----------------------------------------------------
//定义相关宏
//-----------------------------------------------------
double P_DATA =0.3;// 控制转弯 p大了直线会抖 磨到调到赛道转弯也不卡死为止
double I_DATA =0;//0.3不行
double D_DATA =3.5;
double P2_DATA =0.2;// zhidao
double I2_DATA =0.006;//
double D2_DATA =0.8;

int g_CurrentVelocity; //速度
int g_Flag; //标志位
//-----------------------------------------------------
//定义全局变量
//-----------------------------------------------------
uint16 CurrentVelocity=0;
uint16 WholeVelocity=0;
uint8 flag=0;
uint8 vTmpPIT=0;
//-----------------------------------------
//PID参数初始化
//-----------------------------------------
void PID_Init(void)
{
	sptr->LastError = 0; //Error[-1]
	sptr->PrevError = 0; //Error[-2]
	sptr->Proportion =P_DATA; //比例常数Proportional Const
	sptr->Integral =I_DATA; //积分常数Integral Const
	sptr->Derivative =D_DATA; //微分常数Derivative Const
	sptr->SetPoint =0; //目标是0 l-r=0时为中
}

//-----------------------------------------
//增量式PID控制设计
//-----------------------------------------
int IncPIDCalc(int NextPoint)
{
	int iError, iIncpid; //当前误差
	iError = sptr->SetPoint - NextPoint; //增量计算
	iIncpid = sptr->Proportion * iError //E[k]项
	- sptr->Integral * sptr->LastError //E[k－1]项
	+ sptr->Derivative * sptr->PrevError; //E[k－2]项
	sptr->PrevError = sptr->LastError; //存储误差，用于下次计算
	sptr->LastError = iError; //存储误差，用于下次计算
	return(iIncpid); //返回增量值
}

int PIDChange(uint16 kpc,uint16 kic,uint16 kdc,uint16 kpc2,uint16 kic2,uint16 kdc2)
{
//	double gt;
	double kp;
	double ki;
	double kd;
	// double kp2;
	// double ki2;
	// double kd2;
//	gt=((double)gtc)/1000;
	kp=((double)kpc)/1000;
	ki=((double)kic)/1000;
	kd=((double)kdc)/1000;
	// kp2=((double)kpc2)/1000;
	// ki2=((double)kic2)/1000;
	// kd2=((double)kdc2)/1000;
        
//	if(gt=0)//pid1
//	{
		P_DATA=kp;
		I_DATA=ki;
		D_DATA=kd;
		sptr->Proportion =P_DATA; //比例常数Proportional Const
		sptr->Integral =I_DATA; //积分常数Integral Const
		sptr->Derivative =D_DATA; //微分常数Derivative Const

}





