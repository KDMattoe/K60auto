/******************** LQ_K60_������ v1.0 ********************
 * �ļ���           ��ADC.c
 * ����             ������DAC����ģʽ
 * ��ע             ���ٷ��������޸�
 * ����             ��2016-09-01
 * ʵ��ƽ̨         ������ K60VG���İ� 
 * ��������         ��IAR 7.3
 * ����             �������� 006
 * �Ա���           ��https://longqiu.taobao.com
 * �����������ܿƼ�������Ⱥ ��202949437
*************************************************************/
#include "include.h" 

DAC_MemMapPtr DACN[2] = {DAC0_BASE_PTR, DAC1_BASE_PTR}; //��������ָ�����鱣�� DACN �ĵ�ַ


void DAC_Init(DACn_e dacn)
{
    /* ʹ��ʱ�� */
    SIM_SCGC2 |= (SIM_SCGC2_DAC0_MASK << dacn) ;    //ʹ��DACģ��

    /*  ����DAC�Ĵ���  */

    //����DAC_C0�Ĵ���
    DAC_C0_REG(DACN[dacn])  = ( 0
                                |  DAC_C0_DACTRGSEL_MASK                //ѡ����������
                                |  DAC_C0_DACRFS_MASK                   //ѡ��ο�VDD��ѹ(3.3V)
                                |  DAC_C0_DACEN_MASK                    //ʹ��DACģ��
                              );

    //����DAC_C1�Ĵ���
    DAC_C1_REG(DACN[dacn]) = ( 0
                             ) ;
    //����DAC_C2�Ĵ���
    DAC_C2_REG(DACN[dacn]) = ( 0
                               | DAC_C2_DACBFRP(0)             //���û�������ָ��ָ��0
                             );

    DAC_DATH_REG(DACN[dacn], 0) = 0;   //Ĭ�������͵�ѹ
    DAC_DATL_REG(DACN[dacn], 0) = 0;
}

void DAC_Out(DACn_e dacn, uint16 val)
{
    ASSERT(val < 0x1000);               //val Ϊ 12bit

    DAC_DATH_REG(DACN[dacn], 0) = (val >> 8);   //�����ѹ
    DAC_DATL_REG(DACN[dacn], 0) = (val & 0xFF);
}