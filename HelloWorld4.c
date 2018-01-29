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
//#include <player_data.h>
#include "digitalIO.h"

#define FCY 4000000UL
#include <libpic30.h>

#define WAIT_MS 120

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

#define TIME_5_MIN  1080    //ms = 180 Sek
#define TIME_15_MIN 32400   //ms = 
#define TIME_30_MIN 64800
#define CUSTOM_TIME

#define PLAYER1     0
#define PLAYER2     1


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void Hex2Dec ( unsigned char ) ;
void timeMenu(void); 
void updateTime(void);
void waitOneSec(void);
bool checkButton(uint8_t returnString); 
void startGame(uint16_t time);



APP_DATA appData = {
    .messageLine1    = "Chess Clock IoT3\n" ,               
    .messageSetTime  = "Set Playtime:  \n",
    .messageSetTime1 = "05 min -> BTN T0\n",
    .messageSetTime2 = "15 min -> BTN T1\n",
    .messageSetTime3 = "30 min -> BTN T2\n",
    .messageSetTime4 = "custom -> BTN T3\n",           
    //.messageTime_P1 = "player 1 \n" ,
    //.messageTime_P2 = "Pl2 00: 00: 00   ",
    .message1     = "button 1 pressed\n",
    
    .p1Time_currentGame = TIME_5_MIN, 
    .p1Time_allGames =0, 
    .p1Moves_currentGame = 0,
    .p1Moves_allGame = 0,
    .p1_score = 0,
    
    .p2Time_currentGame = TIME_5_MIN, 
    .p2Time_allGames = 0, 
    .p2Moves_currentGame = 0,
    .p2Moves_allGame = 0,
    .p2_score = 0,
};

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    SYS_Initialize ( ) ;
    
     
   
    timeMenu(); 
    


    return (EXIT_SUCCESS); 
}


void startGame(uint16_t gameTime){
    appData.p1Time_currentGame = gameTime; 
    appData.p2Time_currentGame = gameTime; 
    
    
    
}

/*******************************************************************************

  Function:
   void setTime( void )

  Summary:
 updates the time whenever it is colled... will prpbably not count as it should but
 * won't be called when it's really up to counting seconds

  Description:
    

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/

void updateTime(void){
    appData.tens - 0x30; 
    appData.ones - 0x30; 
    Hex2Dec(appData.minutes);

    appData.tens - 0x30; 
    appData.ones - 0x30; 
    Hex2Dec(appData.seconds);
    
    appData.tens - 0x30; 
    appData.ones - 0x30;
}

/*******************************************************************************

  Function:
   void setTime( void )

  Summary:
 uses appData's interrupt flag to wait about one second. 

  Description:
    

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void waitOneSec(void){
    do {
        updateTime();
     } while (!appData.rtc_lcd_update);
}


bool checkButton(uint8_t returnString){
    PRINT_ClearScreen(); 
    if (returnString == 1) LCD_PutString("user set time\n", 15 );
    else {
        waitOneSec();
            waitOneSec();
    }
    if( digitalRead(BTN200)){
        LCD_PutString ( "Time set to 5 min" , 18  ) ;
        startGame(TIME_5_MIN);
        return true;
    }
         
    else if (digitalRead(BTN201)){
        LCD_PutString ( "Time set to 15 min" , 18  ) ;
        startGame(TIME_15_MIN);
        return true;
    }
    else if (digitalRead(BTN202)){
        LCD_PutString ( "Time set to 30 min" , 18  ) ;
        startGame(TIME_30_MIN);
        return true; 
    }
    else if (digitalRead(BTN203)){
        LCD_PutString ( "custom time:     " , 18  ) ;

        return true; 
    }
    return false; 
}



/*******************************************************************************

  Function:
   void TimeMenu (void)

  Summary:
    shows menu to setup GameTime

  Description:
    This function will update time so the interrupt handler can tell 
 * when it's time to update lcd so the user can see his options. 
 * waits for user interaction and sets up the gameTime the user has chosen

  Precondition:
    None.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
 * CR on Jan/17

 */
/******************************************************************************/

void timeMenu(void){
    
    bool timeSet = false;
    uint16_t buttonPressed; 
    while (!timeSet){
        
        appData.rtc_lcd_update = 0; 
        //PRINT_ClearScreen(); 
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime1[0] , sizeof (appData.messageSetTime1 ) - 1  ) ;

        waitOneSec();
        timeSet = checkButton(1); 
        
        waitOneSec();
        waitOneSec();
        
        appData.rtc_lcd_update = 0; 
        //PRINT_ClearScreen(); 
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime2[0] , sizeof (appData.messageSetTime2 ) - 1  ) ;
        waitOneSec();
        timeSet = checkButton(1); 

        waitOneSec();
        waitOneSec();
        
        appData.rtc_lcd_update = 0; 
        //PRINT_ClearScreen(); 
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime3[0] , sizeof (appData.messageSetTime3 ) - 1  ) ;
        
        waitOneSec();
                timeSet = checkButton(1); 

        waitOneSec();
        waitOneSec();
        
        appData.rtc_lcd_update = 0; 
        //PRINT_ClearScreen(); 
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime4[0] , sizeof (appData.messageSetTime4 ) - 1  ) ;
        
        timeSet = checkButton(1);         
    }

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
    LCD_PutChar ( appData.tens - 0x30 ) ;
    LCD_PutChar ( appData.ones - 0x30 ) ;

    Hex2Dec ( appData.minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens - 0x30 ) ;
    LCD_PutChar ( appData.ones - 0x30 ) ;

    Hex2Dec ( appData.seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens - 0x30 ) ;
    LCD_PutChar ( appData.ones - 0x30 ) ;
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