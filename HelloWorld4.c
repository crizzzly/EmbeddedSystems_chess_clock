/**
 * @file   HelloWorld3.c
 * @author JS
 *
 * @date 30.11.2017, 14:36
 *
 * @brief Getting started with a simple program (blinking LED)
 */



// Check for Project Settings
#ifndef __dsPIC33EP512MU810__
    #error "Wrong Controller"
#endif

/* ***********************
 * Includes
 * ***********************
 */

#include "myxc.h"       //aus Projekt
#include "init_OnboardIO.h"
#include <stdint.h>     //Standard typedefs
#include <stdbool.h>
#include <string.h> 


/* ***********************
 * Defines
 * ***********************
 */

/* Substitute for stdlib.h */
#define	EXIT_SUCCESS	0
#define	EXIT_FAILURE	1

    #define _LED200 LATBbits.LATB8
    #define _LED201 LATBbits.LATB9
    #define _LED202 LATBbits.LATB10
    #define _LED203 LATBbits.LATB11

    #define _SW200 PORTGbits.RG12 ///*(reads from ports)*/ CNENGbits.CNIEG12 /*(detechts input change-of-state)*/
    #define _SW201 PORTGbits.RG13 //CNENGbits.CNIEG13
    #define _SW202 PORTGbits.RG14 //CNENGbits.CNIEG14
    #define _SW203 PORTGbits.RG15 //CNENGbits.CNIEG15



/* ***********************
 * Prototypes
 * ***********************
 */

void delay_ms(uint16_t u16milliseconds);      //Funktionsdeklaration

void configOnboardLed();
void configOnboardSwitches();

void configOscillator();

/* ***********************
 * Function definitions
 * ***********************
 */

/**
 * @brief Provides u16milliseconds delay
 * @param u16milliseconds Delay in milliseconds
 * @details u16milliseconds=0 causes 65536 ms delay
 * @pre 7.37 MHz (Internal Fast RC), e. g.: <br>
 * _FOSCSEL(FNOSC_FRC); //Initial Oscillator:  Internal Fast RC <br>
 * _FOSC(POSCMD_NONE);  //Primary Oscillator disabled (quartz not used) <br>
 * s. 7.37 MHz DS70216C-page 39-19 <br>
 * @attention Code has to be changed if a different oscillator frequency is used.
 */
void delay_ms(uint16_t u16milliseconds){        //Funktionsdefinition
    uint16_t ui16_i=0;
    while(u16milliseconds){
        for (ui16_i=0;ui16_i<331;ui16_i++){    //1 ms delay loop
            __asm__ volatile("nop \n\t"        //Assembler-Code
                             "nop \n\t"
                             "nop \n\t");
        }//for
        u16milliseconds--;
    }//while

}

void configOnboardLed(){
    /* Port Configurations 
     FOR ONE PIN */
    // DS70616G-page 209
    // ODCB (open drain config) unimplemented (DS70616G, Table 4-56)
    ANSELBbits.ANSB8=0;     //Digital I/O
    CNENBbits.CNIEB8=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB8=0;     //Disable weak pullup
    CNPDBbits.CNPDB8=0;     //Disable weak pulldown
    TRISBbits.TRISB8=0;     //Pin B8: Digital Output
    LATBbits.LATB8=0;       //Pin B8: Low 
    
    ANSELBbits.ANSB9=0;     //Digital I/O
    CNENBbits.CNIEB9=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB9=0;     //Disable weak pullup
    CNPDBbits.CNPDB9=0;     //Disable weak pulldown
    TRISBbits.TRISB9=0;     //Pin B8: Digital Output
    LATBbits.LATB9=0;       //Pin B8: Low   

    ANSELBbits.ANSB10=0;     //Digital I/O
    CNENBbits.CNIEB10=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB10=0;     //Disable weak pullup
    CNPDBbits.CNPDB10=0;     //Disable weak pulldown
    TRISBbits.TRISB10=0;     //Pin B8: Digital Output
    LATBbits.LATB10=0;       //Pin B8: Low
                 
  ANSELBbits.ANSB11=0;     //Digital I/O
    CNENBbits.CNIEB11=0;     //Disable change notification interrupt
    CNPUBbits.CNPUB11=0;     //Disable weak pullup      -> sw = 1
    CNPDBbits.CNPDB11=0;     //Disable weak pulldown
    TRISBbits.TRISB11=0;     //Pin B8: Digital Output   -> bei switch =1
   LATBbits.LATB11=0;       //Pin B8: Low              -> sw - löschen - port statt dessen               
    } 


    
void configOnboardSwitches(){

    CNENGbits.CNIEG12=0; //turn on change notifications
    CNPUGbits.CNPUG12=0;
    CNPDGbits.CNPDG12=0;
    TRISGbits.TRISG12=1;
    PORTGbits.RG12=0;
    LATGbits.LATG12=0; //
    
    CNENGbits.CNIEG13=0; //turn on change notifications
    CNPUGbits.CNPUG13=0;
    CNPDGbits.CNPDG13=0;
    TRISGbits.TRISG13=1;
    PORTGbits.RG13=0;
    LATGbits.LATG13=0; //
    
    CNENGbits.CNIEG14=0; //turn on change notifications
    CNPUGbits.CNPUG14=0;
    CNPDGbits.CNPDG14=0;
    TRISGbits.TRISG14=1;
    PORTGbits.RG14=0;
    LATGbits.LATG14=0; //
    
    CNENGbits.CNIEG15=0; //turn on change notifications
    CNPUGbits.CNPUG15=0;
    CNPDGbits.CNPDG15=0;
    TRISGbits.TRISG15=1;
    PORTGbits.RG15=0;
    LATGbits.LATG15=0; //
}




/* ***********************
 * Main
 * ***********************
 */


/**
 * Hello World (Blinking LED)
 * @brief Toggles LED200 with 1 Hz, 1:1 duty cycle
 * @pre CPU clock frequency = 7.37 MHz
 */
int main() {
    /*
    for (uint16_t a = 0; a < 4; a++){
        configLed(a);
    }
    */
       // _LED200=!_LED200;
    // _LED202=!_LED202;
        configOnboardLed();
        configOnboardSwitches();
  


    /* Endless Loop */
    while(1){
        
        _LED200 = !_SW200 ;
        _LED201 = !_SW201 ;
        _LED202 = !_SW202 ;
        _LED203 = !_SW203;
        

    }//while

    return (EXIT_SUCCESS);  //never reached
} //main()
