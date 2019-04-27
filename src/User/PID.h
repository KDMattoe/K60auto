#ifndef cxcpid
#define cxcpid
#define HAVE_NEW_VELOCITY 0X01

typedef struct PID
{
	int SetPoint;                   //Ŀ��ֵ
        int32 sumError;                 //����ۼ�
	int32 P;                        //��������p
	int32 I;                        //���ֳ���I
	int32 D;                        //΢�ֳ���D
	int32 LastError;                //Error[-1]
//	int32 PrevError;                //Error[-2]
} PID;

void PID_Init(void);//PID������ʼ��
int32 IncPIDCalc(int NextPoint);//����ʽPID�������


#endif