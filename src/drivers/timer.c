/*
 * File:   timer.c
 * Author: chrissi
 *
 * Created on January 15, 2018, 2:21 AM
 */


#include <xc.h>
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>
#include <string.h>
#include "timer.h"

/* Compiler checks and configuration *******************************/
#ifndef TIMER_MAX_CLIENTS
    #define TIMER_MAX_CLIENTS 1
#endif


/* DEFINITIONS *****************************************************/
#define TIMER_ON                    0x8000  //1000 0000 0000 0000
#define STOP_TIMER_IN_IDLE_MODE     0x2000  //0010 0000 0000 0000    
#define TIMER_SOURCE_INTERNAL       0x0000
#define TIMER_SOURCE_EXTERNAL       0x0002  //0000 0000 0000 0010
#define GATED_TIME_DISABLED         0x0000  
#define TIMER_16_BIT_MODE           0X0000

#define TIMER_PRESCALER_1           0x0000
#define TIMER_PRESCALER_8           0x0010  //0000 0000 0001 0000
#define TIMER_PRESCALER_64          0x0020  //0000 0000 0010 0000
#define TIMER_PRESCALER_256         0x0030  //0000 0000 0011 0000
#define TIMER_INTERRUPT_PRIORITY    0x0001  //0000 0000 0000 0001
#define TIMER_INTERRUPT_PRIORITY_4  0x0004  //0000 0000 0000 0100

/* Type Definitions +++++++++++++++++++++++++++++++++++++++++++++++*/
typedef struct {
    TICK_HANDLER handle;
    uint32_t rate;
    uint32_t count;
} TICK_REQUEST;

/* Variables ********************************************************/
TICK_REQUEST requests[TIMER_MAX_CLIENTS];
/******************************************************************************
 * FUNCTION: void TIMER_CancelTICK(TICK_HANDLER handle)
 * 
 * Overview: cancels a tick event
 * 
 * Input: handle - the function that was handling the tick request
 * 
 * Output: none 
 * *****************************************************************************
 */

void TIMER_CancelTICK(TICK_HANDLER handle){
    uint8_t i;
    for (i = 0; i < TIMER_MAX_CLIENTS; i++){
        if(requests[i].handle == handle){
            requests[i].handle = NULL;
        }
    }
}


/*******************************************************************************
 * Function: bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate)
 * 
 * Overview: Requests to receive a periodic event
 * 
 * PreCondition: none
 * 
 * Input:   handle - the function that will be called when the time event occurs
 *          rate - the number of ticks per event
 * 
 * Output:  true if successful - false if not
 * 
 *******************************************************************************/

bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate){
    uint8_t i;
    for (i = 0; i < TIMER_MAX_CLIENTS; i++){
        if(requests[i].handle == NULL){
            requests[i].handle = handle;
            requests[i].rate = rate;
            requests[i].count = 0; 
            
            return true;
        }
    }
    return false;
}


/*******************************************************************************
 * Function: bool TIMER_SetConfig(TIMER_CONFIGURATIONS config)
 * 
 * Overview: Requests to receive a periodic event
 * 
 * PreCondition: none
 * 
 * Input:   config
 * 
 * Output:  true if successful - false if not
 * 
 *******************************************************************************/

bool TIMER_SetConfig(TIMER_CONFIGURATIONS config){
    
    switch(config){
        //set timer 3
        case TIMER_CONFIG_1MS:
            memset ( requests , 0 , sizeof (requests ) ) ;

            // Set Timer 3 Interrupt Priority Level
            IPC2bits.T3IP = TIMER_INTERRUPT_PRIORITY ;
            // Clear Timer 3 Interrupt Flag
            IFS0bits.T3IF = 0 ;

            //16-bit Timer Count register
            TMR3 = 0 ;          
            
            //16-bit Timer Period register associated with the timer
            PR3 = 2000 ;  
            
            //select internal clock source
            T3CON = TIMER_ON |
                    STOP_TIMER_IN_IDLE_MODE |
                    TIMER_SOURCE_INTERNAL |
                    GATED_TIME_DISABLED |
                    TIMER_16_BIT_MODE |
                    TIMER_PRESCALER_8 ;

            // Enable Timer1 interrupt
            IEC0bits.T3IE = 1 ;     

            return true ;
            
        //set timer 1    
        case TIMER_CONFIG_RTCC:
            memset ( requests , 0 , sizeof (requests ) ) ;

            // Set Timer 1 Interrupt Priority Level
            IPC0bits.T1IP = TIMER_INTERRUPT_PRIORITY_4 ; 
            // Clear Timer 1 Interrupt Flag
            IFS0bits.T1IF = 0 ;                          

            //16-bit Timer Count register
            TMR1 = 0 ;

            //16-bit Timer Period register associated with the timer
            PR1 = 0x8000 ;
            
            //select internal clock source
            /*If T32 = 0, when a match occurs between the 16-bit timer register 
            * (TMRx) and the respective 16-bit period register (PRx), the A/D 
            * Special Event Trigger signal is generated */
            T1CON = TIMER_ON |
                    TIMER_SOURCE_EXTERNAL |
                    GATED_TIME_DISABLED |
                    TIMER_16_BIT_MODE |
                    TIMER_PRESCALER_1 ;

            // Enable Timer1 interrupt
            IEC0bits.T1IE = 1 ; 
        
        case TIMER_CONFIG_OFF:
            
            //disable timer3 interrupt
            IEC0bits.T3IE = 0;
            return true;
    }
    return false;
}

/*******************************************************************************
 * Function: 
 *      void __attribute__ ((__interrupt__, auto psy)) __T3Interrupt (void)
 * 
 * Overview: Interrupt handler for timer3 which is connected to timer 1
 * 
 * PreCondition: none
 * 
 * Input:   none
 * 
 * Output:  none
 * 
 *******************************************************************************/
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wignored-attributes"
void __attribute__ ((__interrupt__, auto_psv)) __T3Interrupt (void){
    uint8_t i; 
    
    for(i=0; i < TIMER_MAX_CLIENTS; i++){
        if(requests[i].handle == NULL){
            requests[i].count ++;
            
            if(requests[i].count == requests[i].rate){
                requests[i].handle ();
                requests[i].count = 0;
            }
        }
    }
}

#pragma clang diagnostic pop



