#ifndef electrical
#define electrical
#define ELE_FREQUENCY 6250                      //电机频率
#define STEER_FREQUENCY 62500                   //舵机频率

#define ELE_ONE_HZ 63 
#define STEER_OFFSET 9570                      
#define STEER_ONE_HZ 35
#define STEER_MIN 9570                          //舵机极限【9570，13000】 
#define STEER_MAX 13000


extern uint16 direction;
extern uint16 GoOrTurn;
extern uint16 dir;
extern uint16 DirecChange;

void electrical_init();
void electrical_control();

#endif