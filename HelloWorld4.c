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
#include "melodies.h"
#include "player_data.h"
#include "digitalIO.h"

#define FCY 4000000UL
#include <libpic30.h>

#define WAIT_MS 120

#define ONE_VOLT 310
#define ONE_TENTH_VOLT 31
#define ONE_HUNDREDTH_VOLT 3

#define TIME_3_MIN  180    //s = 180 Sek ms = 10800 
#define TIME_5_MIN  300    //ms = 18000 Sek 
#define TIME_15_MIN 32400   //ms = 
#define TIME_30_MIN 64800

#define PLAYER1     0
#define PLAYER2     1

#define MOVES_MAX_VAL   1000

#define PROCESS_MENU        0
#define PROCESS_SET_TIME    1
#define PROCESS_SET_MOVES   2
#define WAIT_ON_ANY_KEY     3
#define PROCESS_GAME_PLAY   4


// *****************************************************************************
// *****************************************************************************
// Section: File Scope Variables and Functions
// *****************************************************************************
// *****************************************************************************


void Update_LCD ( void ) ;
void SYS_Initialize ( void ) ;
extern void Hex2Dec ( unsigned char ) ;
unsigned char Dec2Hex(uint16_t);
void setTime(void); 
void updateTime(void);
void wait(uint16_t);
void startGame(void);
void handleButton( void );
void showMenu(void);
void setMoves(void );
void gameOver(void);



APP_DATA appData = {
    .messageLine1    = "Chess Clock IoT3\n" ,               
    .messageSetTime  = " Set Playtime: \n",
    .messageSetTime1 = "05 min -> BTN T0\n",
    .messageSetTime2 = "15 min -> BTN T1\n",
    .messageSetTime3 = "30 min -> BTN T2\n",
    .messageSetTime4 = "custom -> BTN T3\n",           
    //.messageTime_P1 = "player 1 \n" ,
    //.messageTime_P2 = "Pl2 00: 00: 00   ",
    .message1       = "button 1 pressed\n",
    
    .menuTitle      = "  - mainMenu -  \n",
    .menuLine1      = "BTN0: set time  \n",
    .menuLine2      = "BTN1: set moves \n",
    .menuLine3      = "BTN2: speedChess\n",
    .menuLine4      = "BTN3: mainMenu  \n",
       
    .btn_pressed = 0,
    .moves_max     = MOVES_MAX_VAL
          
};

PLAYER_DATA p1 = {
    .time_current_session = 0,
    .moves_current_session = 0,
    .time_current_session = TIME_3_MIN,
    .hours = 0,
    .minutes = 3,
    .seconds = 0,
    .is_active = 0
};

PLAYER_DATA p2 = {
    .time_current_session = 0,
    .moves_current_session = 0,
    .time_current_session = TIME_3_MIN,
    .hours = 0,
    .minutes = 3,
    .seconds = 0,
    .is_active = 0
            
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
    wait(5);
    
    //shows main menu 
    showMenu(); 
    //PRINT_ClearScreen(); 
    
    setTime(); 
    
    startGame();    

    return (EXIT_SUCCESS); 
}

void showMenu(void){
    appData.btn_process = PROCESS_MENU;
    appData.btn_pressed = 0;
    while(appData.btn_pressed == 0){
        LCD_ClearScreen();

        LCD_PutString((char * ) &appData.menuTitle[0], sizeof(appData.menuTitle)-1);
        LCD_PutString((char * ) &appData.menuLine1[0], sizeof(appData.menuLine1)-1);
        wait(3);
        //LCD_ClearScreen();
        LCD_PutString((char * ) &appData.menuTitle[0], sizeof(appData.menuTitle)-1);
        LCD_PutString((char * ) &appData.menuLine2[0], sizeof(appData.menuLine2)-1);
        wait(3);
        
        LCD_PutString((char * ) &appData.menuTitle[0], sizeof(appData.menuTitle)-1);
        LCD_PutString((char * ) &appData.menuLine3[0], sizeof(appData.menuLine3)-1);
        wait(3);
        
        LCD_PutString((char * ) &appData.menuTitle[0], sizeof(appData.menuTitle)-1);
        LCD_PutString((char * ) &appData.menuLine4[0], sizeof(appData.menuLine4)-1);    
        wait(2);

    }
    handleButton();
}


/*******************************************************************************

  Function:
   void setTime (void)

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

void setTime(void){
    /*give btn_pressed a value greater than the highest value of the buttons
     actually:  4-9 (uint16_t) */
    
    appData.btn_pressed = 0;
    //LCD_ClearScreen();
    LCD_PutString("entering timeMenu", 18);
    appData.btn_process = PROCESS_SET_TIME;
    while (appData.btn_pressed == 0){
        
        appData.rtc_lcd_update = 0; 
        LCD_ClearScreen();
        //PRINT_ClearScreen(); 
        LCD_SetPosition(0, 0);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime1[0] , sizeof (appData.messageSetTime1 ) - 1  ) ;
 
        wait(3);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime2[0] , sizeof (appData.messageSetTime2 ) - 1  ) ;        

        wait(3);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime3[0] , sizeof (appData.messageSetTime3 ) - 1  ) ;
        
        wait(3);
        LCD_PutString ( (char*) &appData.messageSetTime[0] , sizeof (appData.messageSetTime ) - 1  ) ;
        LCD_PutString ( (char*) &appData.messageSetTime4[0] , sizeof (appData.messageSetTime4 ) - 1  ) ;       
        wait(3);
    }
    handleButton(); 
}

/*******************************************************************************

  Function:
   void setMoves (void)

  Summary:
    sets the amount of moves a user can take until game is over
  Description:
    uses rotary encoder to set the amount of moves

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

void setMoves(void ){
    appData.btn_process = PROCESS_SET_MOVES;
    
    
}/*******************************************************************************

  Function:
   void gameOver (void)

  Summary:
  handles the final things that have been done after gameplay
  Description:
    uses rotary encoder to set the amount of moves

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
void gameOver(void){
    
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
    appData.btn_process = PROCESS_GAME_PLAY;

    p1.is_active = 1; //sets player1 as active
    p1.moves_current_session = 0; 
    
    p2.is_active = 0; 
    p2.moves_current_session= 0; 
    
    
    LCD_ClearScreen();
    
    LCD_PutString("press button to start", 22);
    wait(2);
    if(appData.btn_pressed ==0){}
        
    handleButton();    
    
    while (1){

        if(appData.rtc_lcd_update == 1){
           LCD_ClearScreen();
            Update_LCD(); 
            appData.rtc_lcd_update =0;
            handleButton();
        }
    }   
}


/*******************************************************************************

  Function:
   void wait( uint16_t seconds )

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
    //LCD_ClearScreen();
   // LCD_PutString("Entering wait seq", 18 );
    uint8_t i = 0; 
    appData.rtc_lcd_update = 0;
    while(i<sec){
        if(appData.btn_pressed == 0){
            do {
               //nothing :) 
            } while (!appData.rtc_lcd_update); 
            //appData.rtc_lcd_update = 0; 
            i++;
        }
          
        else{
             handleButton();   
            return ; 
        }
        
    }
        //LCD_ClearScreen();

      //  LCD_PutString("Leaving wait seq", 18 );   
}


void handleButton( ){
    appData.btn_pressed = 0; 
    switch(appData.btn_process){
        case PROCESS_GAME_PLAY: 
            if(appData.btn200_pressed == 1){
                if(appData.btn200_pressed  && appData.btn201_pressed ){


                    //how to score schach & schach matt??

                }
                appData.btn200_pressed = 0;
                p1.is_active = 0;
                p1.moves_current_session ++; 
                if(p1.moves_current_session >= appData.moves_max){
                    gameOver();
                }
                p2.is_active = 1; 
            }
            else if(appData.btn203_pressed == 1){
                if(appData.btn203_pressed == 1 && appData.btn202_pressed == 1){
                    /*btn 203 & 202 must stay set true if it is so. will be 
                    handled next */
                    
                    
                    //how to score Schach & Schach Matt?? 


                }
                appData.btn203_pressed = 0;
                p2.is_active = 0;
                p2.moves_current_session ++; 
             
                if(p2.moves_current_session >= appData.moves_max){

                    LCD_PutString("reached max moves\n", 18);
                    gameOver();
                }
                p1.is_active = 1; 
            }

            else if (appData.btn201_pressed && appData.btn202_pressed ){
                appData.btn201_pressed =0; 
                appData.btn202_pressed = 0;
                LCD_PutString("aborted by user\n", 18); 
                LCD_PutString("Leaving game ...\n", 18); 
            }
            break; 
            
            
        case PROCESS_MENU:
            if(appData.btn200_pressed){
                appData.btn200_pressed =0; 
                setTime();
            }
            else if (appData.btn201_pressed){
                appData.btn201_pressed = 0; 
                setMoves(); 
            }
            else if (appData.btn202_pressed){
                appData.btn202_pressed = 0; 
                startGame();
            }
            else if (appData.btn203_pressed){
                appData.btn203_pressed = 0; 
                showMenu(); 
            }
            break; 
            
        case PROCESS_SET_TIME: 
            if(appData.btn200_pressed == true) {

                appData.btn200_pressed= 0;    
                p1.time_current_session = TIME_5_MIN;
                p1.hours = 0x0; 
                p1.minutes = 0x05; 
                p1.seconds = 0x0; 

                p2.time_current_session = TIME_5_MIN;
                p2.hours = 0x0; 
                p2.minutes = 0x05; 
                p2.seconds = 0x0; 
                startGame(); 
            }
            else if (appData.btn201_pressed == true){
                appData.btn201_pressed= 0;    

                p1.time_current_session = TIME_15_MIN;
                p1.hours = 0; //x0; 
                p1.minutes = 0xf; //0xf; 
                p1.seconds = 0; //x0;

                p2.time_current_session = TIME_15_MIN;
                p2.hours = 0; //x0; 
                p2.minutes = 0xf; //0xf; 
                p2.seconds = 0; //x0;

                startGame(); 
            }

            else if (appData.btn202_pressed == true){
                LCD_PutString("handle Button\n", 18);
                LCD_PutString("btn2 \n", 18);

                appData.btn202_pressed= 0;    

                p1.time_current_session = TIME_30_MIN;
                p1.hours = 0; //0x0; 
                p1.minutes = 0x1e; //0x1e; 
                p1.seconds = 0; //0x0;

                p2.time_current_session = TIME_30_MIN;
                p2.hours = 0; 
                p2.minutes = 0x1e; //0x1e; 
                p2.seconds = 0;
                startGame(); 
            }

            else if (appData.btn203_pressed == true){
                  LCD_PutString("handle Button\n", 18);
                    LCD_PutString("btn3 \n", 18);
                   appData.btn203_pressed= 0;    

                setTime();
            }
        break; 
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
      //}
     
    if (appData.btn_process == PROCESS_GAME_PLAY){
        
        //prints player1 time in first row
        Hex2Dec ( p1.hours ) ;
        LCD_PutChar ( 'P' ) ;
        LCD_PutChar ( 'l' ) ;
        LCD_PutChar ( '.' ) ;
        LCD_PutChar ( '1' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;

        Hex2Dec ( p1.minutes ) ;
        LCD_PutChar ( ':' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;

        Hex2Dec ( p1.seconds ) ;
        LCD_PutChar ( ':' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;
        LCD_PutChar ( ' ' ) ;

        //prints player2 time in 2nd row
        Hex2Dec ( p2.hours ) ;
        LCD_PutChar ( 'P' ) ;
        LCD_PutChar ( 'l' ) ;
        LCD_PutChar ( '.' ) ;
        LCD_PutChar ( '2' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;

        Hex2Dec ( p2.minutes ) ;
        LCD_PutChar ( ':' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;

        Hex2Dec ( p2.seconds ) ;
        LCD_PutChar ( ':' ) ;
        LCD_PutChar ( ' ' ) ;
        LCD_PutChar ( appData.tens + 0x30 ) ;
        LCD_PutChar ( appData.ones + 0x30 ) ;
        LCD_PutChar ( ' ' ) ;
    }
    
    /* coints upwards while the updates in 
     * gameplay are counting downwards */
    
    if(appData.btn_process == PROCESS_SET_TIME){
        Hex2Dec ( appData.hours ) ;
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
            if ( count >= 200 ){
                count -= 200 ;
                appData.hunds = 0x02 ;
            }

            if (count >= 100){
                count -= 100 ;
                appData.hunds++ ;
            }

            if (count >= 10 ){
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