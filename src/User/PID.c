#include "include.h"
#include "PID.h"

static struct PID sPID;
static struct PID *sptr = &sPID;

int32 P_DATA =500;//1000̫С
int32 I_DATA =0;//
int32 D_DATA =0; //3000  

//-----------------------------------------
//PID������ʼ��
//-----------------------------------------
void PID_Init(void)
{
	sptr->LastError = 0; //Error[-1]
	sptr->sumError;
        sptr->P =P_DATA; //��������Proportional Const
	sptr->I =I_DATA; //���ֳ���Integral Const
	sptr->D =D_DATA; //΢�ֳ���Derivative Const
	sptr->SetPoint =0; //Ŀ����0 l-r=0ʱΪ��
}

//-----------------------------------------
//����ʽPID�������
//-----------------------------------------
int32 IncPIDCalc(int NextPoint)
{
	int iError, dError; //��ǰ���
        int32 LocPid;
	iError = sptr->SetPoint - NextPoint;            //��Ŀ��ƫ��
        dError = iError - sptr->LastError;
        
        sptr->LastError = iError;
        sptr->sumError += iError;
	
        LocPid = sptr->P * iError 
                - sptr->I * sptr->sumError 
                + sptr->D * dError;       //΢����
        
        return(LocPid/100);                           //��������ֵ
}







