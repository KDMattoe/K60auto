#ifndef PID_H
#define PID_H
//-----------------------------------------------------
//����PIDʵ��
//-----------------------------------------------------
typedef struct PID
{
	int SetPoint;                   //�趨Ŀ��Desired Value
        int32 sumError;                 //����ۼ�
	int32 P;               //��������p
	int32 I;                 //���ֳ���I
	int32 D;               //΢�ֳ���D
	int32 LastError;                //Error[-1]
//	int32 PrevError;                //Error[-2]
} PID;

void PID_Init(void);//PID������ʼ��
int32 IncPIDCalc(int NextPoint);//����ʽPID�������


#endif