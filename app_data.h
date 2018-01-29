/*******************************************************************************


  File Name:
    app_data.h



  Description:
    Contains all the variables and functions used commonly across the application.
 *******************************************************************************/

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
 * File:    app_data.h
 * Author:  Christina Rost / team1
 * Comments:
 * Revision history: 
 */

//#include "digitalIO.h"
#include "lcd.h"
#include "timer.h"
#include "print_lcd.h"

// *****************************************************************************
//
// ***********     Variables and Functions      **********************
//
// ******************************************************************


/*

  Summary:
    Defines the data required by the timer module

  Description:
    This data structure defines the data required by timer module

 Remarks:
    None.
*/

typedef struct
{
    /* Variables used by Timer module */
    volatile unsigned char hours ;
    volatile unsigned char minutes ;
    volatile unsigned char seconds ;
    volatile unsigned char hunds ;
    volatile unsigned char tens ;
    volatile unsigned char ones ;
    volatile unsigned char rtc_lcd_update ;
    
    /* Variables used by Timer module */
    volatile unsigned char p1_hours ;
    volatile unsigned char p1_minutes ;
    volatile unsigned char p1_seconds ;
    volatile unsigned char p1_hunds ;
    volatile unsigned char p1_tens ;
    volatile unsigned char p1_ones ;
    volatile unsigned char p1_rtc_lcd_update ;
    
    /* Variables used by Timer module */
    volatile unsigned char p2_hours ;
    volatile unsigned char p2_minutes ;
    volatile unsigned char p2_seconds ;
    volatile unsigned char p2_hunds ;
    volatile unsigned char p2_tens ;
    volatile unsigned char p2_ones ;
    volatile unsigned char p2_rtc_lcd_update ;
    

    /*arrays used for Explorer 16 LCD display*/
    char messageLine1[18] ;
    char messageLine2[18]  ;
    char messageSetTime[18];

    char messageSetTime1[18];
    char messageSetTime2[18];
    char messageSetTime3[18];
    char messageSetTime4[18];

    char messageLine3[18]  ;
    char messageLine4[18]  ;
    char messageLine5[18]  ;

    char messageTime1[18] ;
    char messageTime2[18] ;
    char message1[18] ;
    
    uint16_t p1Time_currentGame; 
    uint32_t p1Time_allGames; 
    uint32_t p1Moves_currentGame;
    uint32_t p1Moves_allGame;
    uint16_t p1_score;
    
    
    
    uint16_t p2Time_currentGame; 
    uint32_t p2Time_allGames; 
    uint32_t p2Moves_currentGame;
    uint32_t p2Moves_allGame;
    uint16_t p2_score;


} APP_DATA ;

extern APP_DATA appData ;
