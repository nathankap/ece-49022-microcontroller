#include "stm32f0xx.h"

void togglpump(GPIO_TypeDef *port);
void Toggle_Col(void);


int Curr_Pump = 8; //PB8 = output connected to first pump

//Change current Pump
void Toggle_Col(void){
    Curr_Pump += 1;
    if(Curr_Pump == 11){
        Curr_Pump = 8;
    }
}
    
 void togglpump(GPIO_TypeDef *port) {
    int temp = port->IDR & (1 << Curr_Pump);
        //(temp == 0) means button pushed
    if(!temp) {
      GPIOB->BSRR = 1 << Curr_Pump; //set 0 to 1 at pin Curr_Pump
    } else {
      GPIOB->BRR = 1 << Curr_Pump; //set 1 to 0 at pin Curr_Pump
    }
}