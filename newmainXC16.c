/*
 * File:   newmainXC16.c
 * Author: chrissi
 *
 * Created on December 12, 2017, 12:01 PM
 */

/*
// Check for Project Settings
#ifndef __dsPIC33EP512MU810__
    #error "Wrong Controller"
#endif

/* ***********************
 * Includes
 * ***********************
 */
/*
#include "myxc.h"       //aus Projekt
#include <stdint.h>     //Standard typedefs
#include <stdbool.h>
#include <string.h> 


/* ***********************
 * Defines
 * ***********************
 */

/* Substitute for stdlib.h 
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

#define LED0   LATBbits.LATB8
#define LED1   LATBbits.LATB9
#define LED2   LATBbits.LATB10
#define LED3   LATBbits.LATB11

#define SW_0   PORTGbits.RG12
#define SW_1   PORTGbits.RG13
#define SW_2   PORTGbits.RG14
#define SW_3   PORTGbits.RG15

#define TRISB 0x0000  //set all bits of reg b as output
#define TRISG 0xF000 //set bit 12-15 of register g as inptput

##define InitAllSwitches()  TRISGbits.TRISG15=1; TRISGbits.TRISG14=11; TRISGbits.TRISG13=1; TRISGbits.TRISG112=1; ANSELDbits.ANSD7 = 0; ANSELDbits.ANSD6 = 0; ANSELAbits.ANSA7 = 0;

//#define TRISG 0b1111 0011 1100 0011 default = 11-15 turned on
#define ANSELB 0x03c0 //set 12-15 as digital i/o

char reg;

void pinMode(char pinNumber[6], bool state); //portg für buttons, latb für led

void digitalWrite(char pinNumber[6], bool state);
void initMain()  {
    }

int main(void) {
    return 0;
}
void pinMode(char pinNumber[6], bool state){ 
    char first= pinNumber [0]; 
    if (first =="P") { 
        reg = pinNumber[1];
    }   
    else if (first =="L"){
        reg = pinNumber [3];
    }
}

void digitalWrite(char pinNumber[6], bool state) {
    char reg= pinNumber  [1]; 
    switch(reg){
        case 'A': PORTA = state;
                    break; 
        case 'B': PORTB = state;
                    break;
        case 'C': PORTC = state;
                    break; 
        case 'D': PORTD = state;
                    break;
        case 'E': PORTE = state;
                    break; 
        case 'F': PORTF= state;
                    break;
        case 'G': PORTG = state;
                    break; 

        default:
            break; 
    }
}
 * */