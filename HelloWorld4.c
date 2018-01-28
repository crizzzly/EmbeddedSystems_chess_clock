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

#define INPUT 1
#define OUTPUT 0

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


APP_DATA appData = {
                    .messageLine1 = "Chess Clock IoT3" ,
                    .messageLine2 = "Press Btn0 \n"  ,
                    .messageTime1 = "player 1 \n" ,
                    .messageTime2 = "Pl2 00: 00: 00   ",
                    .message1     = "button 1 pressed\n"
                            
                            
                            
} ;



// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    pinMode(LED200, OUTPUT);
    pinMode(LED201, OUTPUT);
    pinMode(LED202, OUTPUT);
    pinMode(LED203, OUTPUT);
    
    pinMode(BTN200, INPUT);
    pinMode(BTN201, INPUT);
    pinMode(BTN202, INPUT);
    pinMode(BTN203, INPUT);

    SYS_Initialize ( ) ;
    
    while (1){
            digitalWrite(LED200, !digitalRead(BTN200));
        
            digitalWrite(LED201, !digitalRead(BTN201));
        
        
            digitalWrite(LED202, !digitalRead(BTN202));
      
            digitalWrite(LED203, !digitalRead(BTN203));
        
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
//
//
//    } 
    
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