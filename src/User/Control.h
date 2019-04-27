#ifndef Control
#define Control
#define FLASH_RATE 40

extern u8 pit1_f;

void view_();
void HCSR_Controller();
void pit1();
void PIT1_Interrupt();
void PORTB_Interrupt();
void PIT0_Interrupt();

#endif