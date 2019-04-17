#ifndef cxcpid
#define cxcpid
#define HAVE_NEW_VELOCITY 0X01


void PID_Init(void);//PID参数初始化
int IncPIDCalc(int NextPoint);//增量式PID控制设计
int PIDChange(uint16 kpc,uint16 kic,uint16 kdc,uint16 kpc2,uint16 kic2,uint16 kdc2);


#endif