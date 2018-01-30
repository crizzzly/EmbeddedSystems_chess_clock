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

#define PROCESS_SET_TIME    1
#define WAIT_ON_ANY_KEY     2
#define PROCESS_GAME_PLAY   3


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void Hex2Dec ( unsigned char ) ;
unsigned char Dec2Hex(uint16_t);
void timeMenu(void); 
void updateTime(void);
void wait(uint16_t);
void startGame(void);
void handleButton( void ); 



APP_DATA appData = {
    .messageLine1    = "Chess Clock IoT3\n" ,               
    .messageSetTime  = " Set Playtime: \n",
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
    
    .btn_pressed = 20
};

// *****************************************************************************
// *****************************************************************************
// Section: Main Entry Point
// *****************************************************************************
// *****************************************************************************
int main ( void )
{
    SYS_Initialize ( ) ;
    
    LCD_PutString((char *) &appData.messageLine1[0], 18 );
    LCD_PutString(" ", 18);
    wait(1);
    //PRINT_ClearScreen(); 
    
    timeMenu(); 
    
    startGame();    
    /*

    
    while (1){
        Update_LCD();
        if(digitalRead(BTN200)) appData.activePlayer = 0;
        if(digitalRead(BTN203)) appData.activePlayer = 1;
    }
    
    timeMenu(); 
    //while (appData.btn_pressed > BTN203){
        LCD_ClearScreen();
        LCD_PutString("push a button to start your game\n", 34 );
        wait(3);
        appData.btn_pressed = 20;
    //}
        
    startGame();
    
    */
    
    


    return (EXIT_SUCCESS); 
}

/*******************************************************************************

  Function:
   void startGame( uint16_t gameTime )

  Summary:
 starts the timer for the chess game. 

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

void startGame(void){
//    appData.p1Time_currentGame = TIME_5_MIN; 
//    appData.p2Time_currentGame = TIME_5_MIN; 
    appData.activePlayer = 0; //sets player1 as active
    appData.p1Moves_currentGame = 1;
    appData.btn_process = PROCESS_GAME_PLAY;
        LCD_ClearScreen();
    /*
    LCD_PutString("press button to start", 22);
    wait(3);
    
    while(appData.btn_pressed < BTN203){
        wait(1);
    }
    */
    
    while (1){
        //if(digitalRead(BTN200)) appData.activePlayer = 0;
        //if(digitalRead(BTN203)) appData.activePlayer = 1;
        

        if(IFS0bits.T1IF == 1)  Update_LCD(); 

        if(appData.btn_pressed == BTN200){
            appData.btn_pressed = 20;
            appData.activePlayer = 0;
            appData.p1Moves_currentGame ++;           
        }
                
        else if(appData.btn_pressed == BTN203){
            appData.btn_pressed = 20;
            appData.activePlayer = 1;
            appData.p2Moves_currentGame ++;           
        }
        
        
        
    }
    
    
    
    
}


/*******************************************************************************

  Function:
   void setTime( void )

  Summary:
    uses appData's interrupt flag to wait for given amount of seconds. 

  Description:
    updates time until change notification on buttons is detected

    checks if the button was pressed in the meantime and aborts if so

  Precondition:
    None.

  Parameters:
    uint16_t seconds - amount of seconds to wait

  Returns:
    None.

  Remarks:

 */
/******************************************************************************/
void wait(uint16_t sec){
    LCD_PutString("Entering wait seq", 18 );
    uint8_t i = 0; 
    appData.rtc_lcd_update = 0;
    while(i<sec){
        if(appData.btn_pressed > BTN203){
            do {
               //updateTime();
            } while (!appData.rtc_lcd_update); 
            appData.rtc_lcd_update = 0; 
            i++;
        }
          
        else{
             appData.rtc_lcd_update = 0;   
            return ; 
        }
        
    }
        LCD_PutString("Leaving wait seq", 18 );   
}



void handleButton( ){
   
    if(appData.btn_process == PROCESS_SET_TIME){
        if(appData.btn_pressed == BTN200) {
            LCD_PutString("handle Button?\t\n", 18); 
            LCD_PutString("btn0 \t\n", 18);

             appData.btn_pressed= 20;    



            appData.p1Time_currentGame = TIME_5_MIN;
            appData.p1_hours = 0x0; 
            appData.p1_minutes = 0x05; 
            appData.p1_seconds = 0x0; 
            
            appData.p2Time_currentGame = TIME_5_MIN;
            appData.p2_hours = 0x0; 
            appData.p2_minutes = 0x05; 
            appData.p2_seconds = 0x0; 
            startGame(); 
        }
        else if (appData.btn_pressed == BTN201){
            LCD_PutString("handle Button\n", 18);
            LCD_PutString("btn1 \n", 18);
            appData.btn_pressed= 20;    

            appData.p1Time_currentGame = TIME_15_MIN;
            appData.p1_hours = 0; //x0; 
            appData.p1_minutes = 0xf; //0xf; 
            appData.p1_seconds = 0; //x0;

            appData.p2Time_currentGame = TIME_15_MIN;
            appData.p2_hours = 0; //x0; 
            appData.p2_minutes = 0xf; //0xf; 
            appData.p2_seconds = 0; //x0;

                        startGame(); 

        }

        else if (appData.btn_pressed == BTN202){
              LCD_PutString("handle Button\n", 18);
                LCD_PutString("btn2 \n", 18);

            appData.btn_pressed= 20;    

            appData.p1Time_currentGame = TIME_30_MIN;
            appData.p1_hours = 0; //0x0; 
            appData.p1_minutes = 0x1e; //0x1e; 
            appData.p1_seconds = 0; //0x0;

            appData.p2Time_currentGame = TIME_30_MIN;
            appData.p2_hours = 0; 
            appData.p2_minutes = 0x1e; //0x1e; 
            appData.p2_seconds = 0;
            startGame(); 

        }


        else if (appData.btn_pressed == BTN203){
              LCD_PutString("handle Button\n", 18);
                LCD_PutString("btn3 \n", 18);
               appData.btn_pressed= 20;    

            timeMenu();
        }
        
    }
}

/*******************************************************************************

  Function:
   void TimeMenu (void)

  Summary:
    shows menu to setup GameTime
 *  
  Description:
    

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
    /*give btn_pressed a value greater than the highest value of the buttons
     actually:  4-9 (uint16_t) */
    
    appData.btn_pressed = 20;
    //LCD_ClearScreen();
    LCD_PutString("entering timeMenu", 18);
    appData.btn_process = PROCESS_SET_TIME;
    while (appData.btn_pressed > BTN203){
        
        appData.rtc_lcd_update = 0; 
        LCD_ClearScreen();
        //PRINT_ClearScreen(); 
        LCD_SetPosition(0, 0);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
          LCD_PutString ( (char*) &appData.messageSetTime1[0] , sizeof (appData.messageSetTime1 ) - 1  ) ;
 
        wait(2);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime2[0] , sizeof (appData.messageSetTime2 ) - 1  ) ;        

        wait(2);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime3[0] , sizeof (appData.messageSetTime3 ) - 1  ) ;
        
        wait(2);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
          LCD_PutString ( (char*) &appData.messageSetTime4[0] , sizeof (appData.messageSetTime4 ) - 1  ) ;       
      wait(2);
    }
        handleButton(); 
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
      //}
    Hex2Dec ( appData.p2_hours ) ;
    LCD_PutChar ( 'P' ) ;
    LCD_PutChar ( 'l' ) ;
    LCD_PutChar ( '.' ) ;
    LCD_PutChar ( '2' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.p2_minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.p2_seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;
    LCD_PutChar ( ' ' ) ;
    
    
    Hex2Dec ( appData.p1_hours ) ;
    LCD_PutChar ( 'P' ) ;
    LCD_PutChar ( 'l' ) ;
    LCD_PutChar ( '.' ) ;
    LCD_PutChar ( '1' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.p1_minutes ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;

    Hex2Dec ( appData.p1_seconds ) ;
    LCD_PutChar ( ':' ) ;
    LCD_PutChar ( ' ' ) ;
    LCD_PutChar ( appData.tens + 0x30 ) ;
    LCD_PutChar ( appData.ones + 0x30 ) ;
    LCD_PutChar ( ' ' ) ;
    //}

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



unsigned char Dec2Hex(uint16_t no){
  //decimal passed should be in range 0 to 153
   // char hex [] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, A, B, C, D, E, F}; 
    int hex=0;
    if(!no)
        return 0;
    else {
        hex=no%16;
        Dec2Hex(no/16);
    }
    if(hex>9)
        return ('A'+(hex-10));
    else
        return (hex);
  


}