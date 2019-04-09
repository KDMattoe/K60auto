/****************************************************************************************************
��dev.env.��IAR7.3
��busclock��100.000MHz
��pllclock��200.000MHz
=============================================================
�ӿڶ��壺
PWM�ڶ��壺
FTM2_CH0--PTB18
FTM2_CH1--PTB19

�������壺
KEY0--PTB20
KEY1--PTB21
KEY2--PTB22

OLED�ڶ��壺
LCD_DC --PTC19
LCD_RST--PTC18
LCD_SDA--PTC17
LCD_SCL--PTC16

HCSR(���������ģ�鶨�壨��������
HCSR_1_TRIG PTB22
HCSR_1_ECHO PTB23
HCSR_2_TRIG PTB24
HCSR_2_ECHO PTB25
HCSR_3_TRIG PTB26
HCSR_3_ECHO PTB27
HCSR_4_TRIG PTB28
HCSR_4_ECHO PTB29
HCSR_5_TRIG PTB30
HCSR_5_ECHO PTB31

��ʱ��ʹ�������
PIT0���ڳ��������ģ��
PIT1���ڿ�������
LPTMR�͹��Ķ�ʱ�����ڳ��ö�ʱ
=============================================================
******************************************************************************************************/
#include "include.h"



void time_delay_ms(u32 ms)
{
  LPTMR_delay_ms(ms);
}

void drive_init(){
    PLL_Init(PLL200);                                   //��ʼ��PLLΪ200M������Ϊ100MHZ  
    LCD_Init();
    UART_Init(UART4,38400);                             //����4��ʼ��
    int i=0;
    HCSR_Init();                                        //��������������ʼ�� 
    for(i=0; i<5; i++){
      EXTI_Init(PTB, sensor[i].ECHO, either_down);       //��ʼ���ⲿ�ж�
    }
    
    PIT_Init(PIT1, 60);                                 //��ʱ��1���ڿ�������
    // gpio_init (PORTA, 17, 1,0);
}

//������
void main(void)
{
    DisableInterrupts;        //�ر����ж�
    drive_init();
    EnableInterrupts;            //�����ж�
    pit_time_start(PIT0);                        //�򿪶�ʱ��
    
    while(1){
      

    };
   
}

