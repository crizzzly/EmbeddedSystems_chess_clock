/*******************************************************************************
 Explorer 16 Demo Main File

  Company:
    Microchip Technology Inc.

  File Name:
    main.c

  Summary:
    Explorer 16 Demo Main File.

  Description: 
    This is the main file for the Explorer 16 Demo. It contains the main demo
    flow and calls processor specific files for processor specific
    implementations.
 *******************************************************************************/

// DOM-IGNORE-BEGIN
/*******************************************************************************
Copyright (c) 2013 released Microchip Technology Inc.  All rights reserved.

Microchip licenses to you the right to use, modify, copy and distribute
Software only when embedded on a Microchip microcontroller or digital signal
controller that is integrated into your product or third party product
(pursuant to the sublicense terms in the accompanying license agreement).

You should refer to the license agreement accompanying this Software for
additional information regarding your rights and obligations.

SOFTWARE AND DOCUMENTATION ARE PROVIDED "AS IS" WITHOUT WARRANTY OF ANY KIND,
EITHER EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION, ANY WARRANTY OF
MERCHANTABILITY, TITLE, NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE.
IN NO EVENT SHALL MICROCHIP OR ITS LICENSORS BE LIABLE OR OBLIGATED UNDER
CONTRACT, NEGLIGENCE, STRICT LIABILITY, CONTRIBUTION, BREACH OF WARRANTY, OR
OTHER LEGAL EQUITABLE THEORY ANY DIRECT OR INDIRECT DAMAGES OR EXPENSES
INCLUDING BUT NOT LIMITED TO ANY INCIDENTAL, SPECIAL, INDIRECT, PUNITIVE OR
CONSEQUENTIAL DAMAGES, LOST PROFITS OR LOST DATA, COST OF PROCUREMENT OF
SUBSTITUTE GOODS, TECHNOLOGY, SERVICES, OR ANY CLAIMS BY THIRD PARTIES
(INCLUDING BUT NOT LIMITED TO ANY DEFENSE THEREOF), OR OTHER SIMILAR COSTS.
 *******************************************************************************/
// DOM-IGNORE-END

// Check for Project Settings
#ifndef __dsPIC33EP512MU810__
    #error "Wrong Controller"
#endif

// *****************************************************************************
// *****************************************************************************
// Section: Included Files
// *****************************************************************************
// *****************************************************************************

#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <stdbool.h>
#include "app_data.h"
#include "digitalIO.h"

#define FCY 4000000UL
#include <libpic30.h>

#define WAIT_MS 120

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3



// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void Hex2Dec ( unsigned char ) ;
void setTime(void); 


APP_DATA appData = {
                    .messageLine1    = "Chess Clock IoT3\n" ,
         /*           
                    .messageSetTime  = "Set Playtime:\n",
                    .messageSetTime1 = "5min -> BTN T0",
                    //.messageSetTime2 = "15 min -> BTN T1\n",
                    .messageSetTime2 = "15 min -> BTN T1",
                    .messageSetTime3 = "30 min -> BTN T2",
                    .messageSetTime4 = "custom -> BTN T3",
       */        
                    //.messageTime_P1 = "player 1 \n" ,
                    //.messageTime_P2 = "Pl2 00: 00: 00   ",
                    .message1     = "button 1 pressed\n"                            
} ;



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    SYS_Initialize ( ) ;
    
//    digitalWrite(LED200, digitalRead(BTN200));
//    digitalWrite(LED201, LOW);
//    digitalWrite(LED202, LOW);
//    digitalWrite(LED203, LOW);
    
    playRandomMelody(); 
    
    //setTime(); 
    

    /*while(1){
        //digitalWrite(LED200, digitalRead(BTN200));
        digitalWrite(LED200, LOW);
        digitalWrite(LED201, LOW);
        digitalWrite(LED202, LOW);
        digitalWrite(LED203, LOW);
        
        if(digitalRead(BTN200)){
          //  digitalWrite(LED200, HIGH);
            break;
        }
        else{
          //  digitalWrite(LED200, LOW);
          break;
        }
        
        if (digitalRead(BTN201)){
            digitalWrite(LED201, HIGH);
            break;
        }
        else{
            digitalWrite(LED201, LOW);
            break;
        }

        if(digitalRead(BTN202)){
            digitalWrite(LED202,HIGH );
            break;
        }
        else{
            digitalWrite(LED202, LOW);
            break;
        }
        
        if(digitalRead(BTN203)){
            digitalWrite(LED203, HIGH);
            break;
        }
        else{
            digitalWrite(LED203, LOW);
            break; 
        }
    }*/
            return 0; 

    }

//    
//    /* Display welcome message */
//    LCD_PutString ( (char*) &appData.messageLine1[0] , sizeof (appData.messageLine1 ) - 1  ) ;
//    LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1  ) ;
//    
//    if(BUTTON_IsPressed(BTN_ONB0)) LED_Toggle(LED_ONB0);
//    /* wait here until switch S3 is pressed */
//    while (! BUTTON_IsPressed ( BTN_ONB0 ));
//
//    /*Initialize Timer*/
//    TIMER_SetConfig ( TIMER_CONFIG_RTCC ) ;
//
//   
//    /* Display initial ADC and Timer messages */
//    LCD_PutString ( (char*) &appData.messageTime1[0] , sizeof (appData.messageTime1 ) - 1 ) ;
//    LCD_PutString ( (char*) &appData.messageTime2[0] , sizeof (appData.messageTime2 ) - 1 ) ;
//
//   
//
//
//
//        /* Infinite Loop */
//    while ( 1 )
//    {
//        LCD_PutString ( (char*) &appData.messageLine2[0] , sizeof (appData.messageLine2 ) - 1  ) ;
//        /* check if time to update LCD with Timer data */
//        if ( appData.rtc_lcd_update )
//        {
//            Hex2Dec ( appData.hours ) ;
//            Update_LCD ( ) ;
//            appData.rtc_lcd_update = 0 ;
//        }
//    } 
    


/*******************************************************************************

  Function:
   void setTime( void )

  Summary:
    Function to set the game-time

  Description:
    This function will set the time in order to the button, the user pressed
 *          Btn T0 = 3 min
 *          BTN T1 = 15 min
 *          BTN T2 = 30 min
 *          BTN T3 will load the quadratic encoder for the user so he can set time manually

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void setTime(void){
    //uint16_t sec = appData.seconds; 
    //uint16_t oldVal = sec; 
           // LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;

    
        /*
        while((oldVal-10) > sec){
           sec = appData.seconds ;
       }
        
        
        oldVal = sec; 
        sec = appData.seconds ;
        LCD_PutString ( (char*) &appData.messageSetTime1[0] , sizeof (appData.messageSetTime1 ) - 1  ) ;
        
        while((oldVal-10) > sec){
           sec = appData.seconds ;
       }
        
        
        
        oldVal = sec; 
        sec = appData.seconds ;

        //LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime2[0] , sizeof (appData.messageSetTime2 ) - 1  ) ;
        
        while((oldVal-10) > sec){
           sec = appData.seconds ;
       }
        oldVal = sec; 
        sec = appData.seconds ;

        //LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime3[0] , sizeof (appData.messageSetTime3 ) - 1  ) ;

        while((oldVal-10) > sec){
           sec = appData.seconds ;
       }
        oldVal = sec; 
        //LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime4[0] , sizeof (appData.messageSetTime4 ) - 1  ) ;
        //__delay_ms(WAIT_MS);
        
       while((oldVal-10) > sec){
           sec = appData.seconds ;
           }
        oldVal = sec; 
        sec = appData.seconds ;
        
    */
    
       
}


/*******************************************************************************

  Function:
   void Update_LCD( void )

  Summary:
    Function to update LCD

  Description:
    This function will update the time on the LCD

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void Update_LCD ( void ){
    LCD_PutChar ( 'T' ) ;
    LCD_PutChar ( 'i' ) ;
    LCD_PutChar ( 'm' ) ;
    LCD_PutChar ( 'e' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;
    LCD_PutChar ( ' ' ) ;

}


/*******************************************************************************

  Function:
   void Hex2Dec ( unsigned char )

  Summary:
    Explorer 16 Demo Hex to Decimal Conversion File

  Description:
     This is the file for the Explorer 16 Dem that converts the hexadecimal data
    into decimal format.

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void Hex2Dec ( unsigned char count )
{
    /* reset values */
    appData.hunds = 0 ;
    appData.tens  = 0 ;
    appData.ones = 0 ;

    while ( count >= 10 )
    {

        if ( count >= 200 )
        {
            count -= 200 ;
            appData.hunds = 0x02 ;
        }

        if (count >= 100)
        {
            count -= 100 ;
            appData.hunds++ ;
        }

        if (count >= 10 )
        {
            count -= 10 ;
            appData.tens++ ;
        }
    }

    appData.ones = count ;
}