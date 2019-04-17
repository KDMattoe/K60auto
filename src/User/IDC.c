#include "include.h"

uint16 IDC[4];

void IDC_get(){
    IDC[LEFT_F] =(uint16)(ADC_Ave(ADC0,ADC1_SE8,ADC_10bit,10)*1000/1024*5);
    IDC[RIGHT_F] =(uint16)(ADC_Ave(ADC0,ADC1_SE9,ADC_10bit,10)*1000/1024*5);
    IDC[LEFT_S] =(uint16)(ADC_Ave(ADC0,ADC1_SE12,ADC_10bit,10)*1000/1024*5);
    IDC[RIGHT_S] =(uint16)(ADC_Ave(ADC0,ADC1_SE13,ADC_10bit,10)*1000/1024*5);
}
