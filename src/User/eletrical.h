#ifndef electrical
#define electrical
#define ELE_FREQUENCY 500                      //���Ƶ�� 12.5K
#define STEER_FREQUENCY 62500                   //���1K

#define ELE_ONE_HZ 5 
#define STEER_OFFSET 9570                      
#define STEER_ONE_HZ 35
#define STEER_MIN -1715                          //������ޡ�9570��13000��
#define STEER_BALANCE 11285                     //����м�λ
#define STEER_MAX 1715


extern uint16 direction;
extern int32 dir;
extern int16 DirecChange;
extern int16 test;
extern int16 test1;
void electrical_init();
void electrical_control();

#endif