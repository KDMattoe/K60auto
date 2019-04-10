#ifndef HCSR_H
#define HCSR_H

#define HCSR_0_TRIG PTB0
#define HCSR_0_ECHO PTB1
#define HCSR_1_TRIG PTB2
#define HCSR_1_ECHO PTB3
#define HCSR_2_TRIG PTB4
#define HCSR_2_ECHO PTB5
#define HCSR_3_TRIG PTB6
#define HCSR_3_ECHO PTB7
#define HCSR_4_TRIG PTB8
#define HCSR_4_ECHO PTB9

#define HCSR_SENSOR_SIZE 5
struct HCSR_Struct {
  uint32 distance;
  uint8 TRIG;
  uint8 ECHO;
  uint32 start_time;    //ms
  uint32 stop_time;     //ms
  uint8 flag;
};
extern struct HCSR_Struct sensor[HCSR_SENSOR_SIZE];
void HCSR_Init(void);
uint32 get_distance(uint8 index);
void HCSR_pull_trig(uint8 index);

#endif