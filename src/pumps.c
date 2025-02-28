#include "stm32f0xx.h"

void togglpump(GPIO_TypeDef *port, int Curr_Pump);
void Toggle_Col(int * Curr_Pump);


// int Curr_Pump = 8; //PB8 = output connected to first pump

//Change current Pump
void Toggle_Col(int* Curr_Pump){
    *Curr_Pump += 1;
    if(*Curr_Pump == 11){
        *Curr_Pump = 8;
    }
}


void togglpump(GPIO_TypeDef *port, int Curr_Pump) {
    int temp = port->ODR & (1 << Curr_Pump);

    if(temp) { //if output is on
        GPIOB->BRR = 1 << Curr_Pump; //set pin Curr_Pump to low
    } else {    // if output is off
        GPIOB->BSRR = 1 << Curr_Pump; //set pin Curr_Pump to high
    }
}