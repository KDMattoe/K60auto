#ifndef Control
#define Control
#define FLASH_RATE 20

extern u8 pit1_f;
void view_();
void Controller();
void pit1();
void PIT1_Interrupt();
void PORTB_Interrupt();
void PIT0_Interrupt();

#endif