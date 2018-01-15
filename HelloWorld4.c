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
#include "onboardLeds.h"
#include "onboardBtn.h"
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

    



/* ***********************
 * Prototypes
 * ***********************
 */

void delay_ms(uint16_t u16milliseconds);      //Funktionsdeklaration


/* ***********************
 * Function definitions
 * ***********************
 */

/**
 * @brief Provides u16milliseconds delay
 * @param u16milliseconds Delay in milliseconds
 * @details u16milliseconds=0 causes 65536 ms delay
 * @pre 8.00 MHz (External Oscillator without PLL), e. g.: <br>
 * _FOSCSEL(FNOSC_PRI); //External Oscillator: Primary  <br>
 * _FOSC(POSCMD_XT);  //Primary Oscillator Enabled: XT Crystal Oscillator Mode  <br>
 * s. 8.00 MHz DS70216C-page 39-19 <br>
 * @attention Code has to be changed if a different oscillator frequency is used.
 
void delay_ms(uint16_t u16milliseconds){        //Funktionsdefinition
    uint16_t ui16_i=0;
    while(u16milliseconds){
        for (ui16_i=0;ui16_i<358;ui16_i++){    //1 ms delay loop
            __asm__ volatile("nop \n\t"        //Assembler-Code
                             "nop \n\t"
                             "nop \n\t");
        }//for
        u16milliseconds--;
    }//while

}
 * */

/* ***********************
 * Main
 * ***********************
 */


/**
 * Hello World (Blinking LED)
 * @brief Toggles LED200 with 1 Hz, 1:1 duty cycle
 * @pre CPU clock frequency = 8.00« MHz
 */
int main() {
    
  
    LED_On(LED_ONB1);
    LED_On(LED_ONB3);

    /* Endless Loop */
    while(1){
        
        LED_Toggle(LED_ONB0);
        LED_Toggle(LED_ONB1);
        LED_Toggle(LED_ONB2);
        LED_Toggle(LED_ONB3);
        
        delay_ms(500); 
        

    }//while

    return (EXIT_SUCCESS);  //never reached
} //main()
