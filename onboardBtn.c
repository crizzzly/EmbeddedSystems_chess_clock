/*
 * File:   onboardBtn.c
 * Author: chrissi
 *
 * Created on January 8, 2018, 11:22 PM
 */


#include "xc.h"
#include "onboardBtn.h"
#include <stdbool.h>

#define BTN_ONB0_PORT PORTGbits.RG12 
#define BTN_ONB1_PORT PORTGbits.RG13 
#define BTN_ONB2_PORT PORTGbits.RG14 
#define BTN_ONB3_PORT PORTGbits.RG15 

#define BTN_ONB0_TRIS TRISGbits.TRISG12 
#define BTN_ONB1_TRIS TRISGbits.TRISG13
#define BTN_ONB2_TRIS TRISGbits.TRISG14
#define BTN_ONB3_TRIS TRISGbits.TRISG15

#define BTN_PRESSED     1
#define BTN_NOT_PRESSED 0

#define PIN_INPUT   1
#define PIN_OUTPUT  0

#define PIN_DIGITAL 0
#define PIN_ANALOG  1

/*********************************************************************
* Function: bool BUTTON_IsPressed(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names 
*        of the buttons on the silkscreen on the board (as the demo 
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: TRUE if pressed; FALSE if not pressed.
*
********************************************************************/
bool BUTTON_IsPressed(BUTTON button){
    switch (button){
        case BTN_ONB0:
            return ((BTN_ONB0_PORT == BTN_PRESSED) ? true : false );
            
        case BTN_ONB1:
            return ((BTN_ONB1_PORT == BTN_PRESSED) ? true : false );
            
        case BTN_ONB2:
            return ((BTN_ONB2_PORT == BTN_PRESSED) ? true : false );
        
        case BTN_ONB3:
            return ((BTN_ONB3_PORT == BTN_PRESSED) ? true : false );
            
        case BTN_NONE:
            return false;
    }
    return false;
}

/*********************************************************************
* Function: void BUTTON_Disable(BUTTON button);
*
* Overview: Returns the current state of the requested button
*
* PreCondition: button configured via BUTTON_SetConfiguration()
*
* Input: BUTTON button - enumeration of the buttons available in
*        this demo.  They should be meaningful names and not the names
*        of the buttons on the silkscreen on the board (as the demo
*        code may be ported to other boards).
*         i.e. - ButtonIsPressed(BUTTON_SEND_MESSAGE);
*
* Output: None
*
********************************************************************/
void BUTTON_Disable(BUTTON button){
    switch (button){
        case BTN_ONB0:
            BTN_ONB0_TRIS = PIN_OUTPUT;
            break;
        case BTN_ONB1:
            BTN_ONB1_TRIS = PIN_OUTPUT;      
            break;
        case BTN_ONB2:
            BTN_ONB2_TRIS = PIN_OUTPUT;
            break;
        case BTN_ONB3:
            BTN_ONB3_TRIS = PIN_OUTPUT;
            break;
        case BTN_NONE:
            break;
    }    
}