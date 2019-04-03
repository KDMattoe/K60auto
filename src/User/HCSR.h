#ifndef HCSR_H
#define HCSR_H
#include "include.h"


#define HCSR_1_TRIG PTB22
#define HCSR_1_ECHO PTB23
#define HCSR_2_TRIG PTB24
#define HCSR_2_ECHO PTB25
#define HCSR_3_TRIG PTB26
#define HCSR_3_ECHO PTB27
#define HCSR_4_TRIG PTB28
#define HCSR_4_ECHO PTB29
#define HCSR_5_TRIG PTB30
#define HCSR_5_ECHO PTB31

struct HCSR_Struct {
  int distance;
  int TRIG;
  int ECHO;
  uint32 start_time;    //ms
  uint32 stop_time;     //ms
};

struct HCSR_Struct sensor[5];
void HCSR_Init();
uint32 get_distance(uint8 index,uint32 cnt);
void HCSR_pull_trig(void);

uint32 get_distance(uint8 index, uint32 cnt);


#endif