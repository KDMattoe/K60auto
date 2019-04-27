#include "include.h"

int16 IDC[4];

void IDC_get(){
    IDC[LEFT_F] =(int16)(ADC_Ave(ADC0,ADC1_SE8,ADC_10bit,10)*1000/1024*5);
    IDC[RIGHT_F] =(int16)(ADC_Ave(ADC0,ADC1_SE9,ADC_10bit,10)*1000/1024*5);
    IDC[LEFT_S] =(int16)(ADC_Ave(ADC0,ADC1_SE12,ADC_10bit,10)*1000/1024*5);
    IDC[RIGHT_S] =(int16)(ADC_Ave(ADC0,ADC1_SE13,ADC_10bit,10)*1000/1024*5);
}

//∑≈¥Û≤Ó÷µ
void IDC_ap(){
    int16 ap = (IDC[LEFT_F] - IDC[RIGHT_F]);
    if(ap < 0) ap = -1 * ap;
    if(IDC[LEFT_F] - IDC[RIGHT_F] > 1000){
        IDC[LEFT_F] = IDC[LEFT_F] + ap/2;
    } else if(IDC[RIGHT_F] - IDC[LEFT_F] > 1000) {
        IDC[RIGHT_F] = IDC[RIGHT_F] +ap/2;
    }
}