/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:        timer.h
 * Author:      Christina Rost / Team 1
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdbool.h>
#include <stdint.h>
#include <stddef.h>

#ifndef TIMER_H
#define	TIMER_H
#define TIMER_TICK_INTERVAL_MICRO_SECONDS 1000

/*Type Definitions--------------------------------------*/
typedef void (*TICK_HANDLER)(void);

typedef enum {
    TIMER_CONFIG_1MS,
    TIMER_CONFIG_RTCC,
    TIMER_CONFIG_OFF
}TIMER_CONFIGURATIONS;

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

void TIMER_CancelTICK(TICK_HANDLER handle);

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

bool TIMER_RequestTick(TICK_HANDLER handle, uint32_t rate);

/*******************************************************************************
 * Function: bool TIMER_SetConfig(TIMER_CONFIGURATIONS config)
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

bool TIMER_SetConfig(TIMER_CONFIGURATIONS config);


#endif	/* XC_HEADER_TEMPLATE_H */

