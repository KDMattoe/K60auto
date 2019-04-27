#include "include.h"
#include "Control.h"
u8 sensor_shift_flag = 0;
u8 screen_flash_rate= 0;                    //n����������

void drew_send(){
    uint8 sum = 0;
    int16 left= IDC[LEFT_F]*2/5 + IDC[LEFT_S]*3/5;
    int16 right = IDC[RIGHT_F]*2/5 + IDC[RIGHT_S]*3/5;
    UART_Put_Char(UART4,0xAA);sum += 0xAA;
    UART_Put_Char(UART4,0xAA);sum += 0xAA;
    UART_Put_Char(UART4,0xF1);sum += 0xF1;
    UART_Put_Char(UART4,0x06);sum += 0x06;
    
//    UART_Put_Char(UART4,IDC[LEFT_F]>>8);sum+=IDC[LEFT_F]>>8;
//    UART_Put_Char(UART4,IDC[LEFT_F]);sum+=IDC[LEFT_F];
//    UART_Put_Char(UART4,IDC[LEFT_S]>>8);sum+=IDC[LEFT_S]>>8;
//    UART_Put_Char(UART4,IDC[LEFT_S]);sum+=IDC[LEFT_S];
//    UART_Put_Char(UART4,IDC[RIGHT_F]>>8);sum+=IDC[RIGHT_F]>>8;
//    UART_Put_Char(UART4,IDC[RIGHT_F]);sum+=IDC[RIGHT_F];
//    UART_Put_Char(UART4,IDC[RIGHT_S]>>8);sum+=IDC[RIGHT_S]>>8;
//    UART_Put_Char(UART4,IDC[RIGHT_S]);sum+=IDC[RIGHT_S];
//    
    
    uint16 x=(dir - STEER_MIN) / STEER_ONE_HZ;
    UART_Put_Char(UART4,x>>8);sum+=x>>8;
    UART_Put_Char(UART4,x);sum+=x;
    UART_Put_Char(UART4,test>>8);sum+=test>>8;
    UART_Put_Char(UART4,test);sum+=test;
    UART_Put_Char(UART4,test1>>8);sum+=test1>>8;
    UART_Put_Char(UART4,test1);sum+=test1;
    
    UART_Put_Char(UART4,sum);
    
}


/*******************************************

��ʾ������
scree_flash_rate:OLEDˢ��Ƶ��
5�ǳ���������������������������ʹ�õ�5�ĵط�����  

*******************************************/
void view_(){
    
    int i=0;
    if(screen_flash_rate++ <= FLASH_RATE) {
        screen_flash_rate = 0;
        LCD_CLS();
        for(i=0; i < HCSR_SENSOR_SIZE; i++) {
            char ch[5] = {'0'+i,':'};              //��ʾЧ����     'i'th:
            LCD_P6x8Str(2, i, ch);  LCD_PrintU16(15, i, sensor[i].distance);
        }
    LCD_P6x8Str(60, 0, "Lf:");    LCD_PrintU16(80,0, IDC[LEFT_F]);
    LCD_P6x8Str(60, 1, "Rf:");     LCD_PrintU16(80,1, IDC[RIGHT_F]);
    LCD_P6x8Str(60, 2, "Ls:");     LCD_PrintU16(80,2,IDC[LEFT_S]);            
    LCD_P6x8Str(60, 3, "Rs:");     LCD_PrintU16(80,3,IDC[RIGHT_S]);
    LCD_P6x8Str(60, 4, "dir:");     LCD_PrintU16(80,4,test);//(dir - STEER_MIN) / STEER_ONE_HZ

    }
   
  
}



void HCSR_Controller(){
    uint8 i;
    
    sensor_shift_flag = (sensor_shift_flag)? 0: 1;
    //    ������ģ�鷢��
    for(i=sensor_shift_flag; i<HCSR_SENSOR_SIZE; i++) {
        HCSR_pull_trig(i);              //�����ź�
    }
}


void pit1(){
  
  if(pit1_f){
    //if(! HCSR_detect()){                    //δ����
        HCSR_Controller();                 //���п��Ƶ�Ԫ
        IDC_get();
        //IDC_ap();   //�����������м�ʱ�Ŵ��ֵ�����������ײ���
        electrical_control();
   //     } else {
        /*******************************/
        //����������⵽��ϣ��Ĳ��� TODO
   //}
  
  view_();
  drew_send();
  pit1_f = 0;
    
  }
  
}




//PIT 1 ���ڿ�������
void PIT1_Interrupt()
{
  PIT_Flag_Clear(PIT1);         //���жϱ�־λ
  pit1_f = 1;
}



void PORTA_Interrupt()
{
    int n,i;
    i=0;
    for(i=0;i<HCSR_SENSOR_SIZE;i++ ){
        n = sensor[i].ECHO;
        if((PORTA_ISFR & (1<<n))) {
            PORTA_ISFR |= (1<<n); 
            if(GPIO_Get(sensor[i].ECHO)){                                                     
            //�յ��ߵ�ƽ
                sensor[i].flag = 1;
                sensor[i].start_time = pit_time_get_notClear(PIT0)/100;
                sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //��ȡʱ������

        } else {                                  
            //������� 
                if(sensor[i].flag){
                    sensor[i].stop_time = pit_time_get_notClear(PIT0)/100;               //��ȡʱ������
                    get_distance(i);
                    sensor[i].flag = 0;
                } 
           }
   }
  }
}



//PIT0���ڳ�����ģ���ʹ��
void PIT0_Interrupt()
{
  PIT_Flag_Clear(PIT0);       //���жϱ�־λ
 
  pit_time_start(PIT0);
}


