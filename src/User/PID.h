#ifndef cxcpid
#define cxcpid
#define HAVE_NEW_VELOCITY 0X01

typedef struct PID
{
	int SetPoint;                   //目标值
        int32 sumError;                 //误差累计
	int32 P;                        //比例常数p
	int32 I;                        //积分常数I
	int32 D;                        //微分常数D
	int32 LastError;                //Error[-1]
//	int32 PrevError;                //Error[-2]
} PID;

void PID_Init(void);//PID参数初始化
int32 IncPIDCalc(int NextPoint);//增量式PID控制设计


#endif