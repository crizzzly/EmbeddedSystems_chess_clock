/*
 * File:   onboardBtn.c
 * Author: chrissi
 *
 * Created on January 8, 2018, 11:22 PM
 */


#include <xc.h>
#include "../onboardBtn.h"
#include <stdbool.h>

#define BTN_ONB0_PORT   PORTGbits.RG12 
#define BTN_ONB1_PORT   PORTGbits.RG13 
#define BTN_ONB2_PORT   PORTGbits.RG14 
#define BTN_ONB3_PORT   PORTGbits.RG15 

#define BTN_ONB0_TRIS   TRISGbits.TRISG12 
#define BTN_ONB1_TRIS   TRISGbits.TRISG13
#define BTN_ONB2_TRIS   TRISGbits.TRISG14
#define BTN_ONB3_TRIS   TRISGbits.TRISG15

#define BTN_ONB0_CNEN   CNENGbits.CNIEG12
#define BTN_ONB1_CNEN   CNENGbits.CNIEG13
#define BTN_ONB2_CNEN   CNENGbits.CNIEG14
#define BTN_ONB3_CNEN   CNENGbits.CNIEG15

#define BTN_ONB0_CNPU  CNPUGbits.CNPUG12
#define BTN_ONB1_CNPU  CNPUGbits.CNPUG13
#define BTN_ONB2_CNPU  CNPUGbits.CNPUG14
#define BTN_ONB3_CNPU  CNPUGbits.CNPUG15

#define BTN_ONB0_CNPD  CNPDGbits.CNPDG12
#define BTN_ONB1_CNPD  CNPDGbits.CNPDG13
#define BTN_ONB2_CNPD  CNPDGbits.CNPDG14
#define BTN_ONB3_CNPD  CNPDGbits.CNPDG15


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

/*********************************************************************
 * Function: void BUTTON_Enable(BUTTON button);
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
void BUTTON_Enable ( BUTTON button )
{
     switch (button){
        case BTN_ONB0:
            BTN_ONB0_TRIS = PIN_INPUT;
            BTN_ONB0_CNEN = 0;
            BTN_ONB0_CNPU = 0;
            BTN_ONB0_CNPD = 1;
            break;
        case BTN_ONB1:
            BTN_ONB1_TRIS = PIN_INPUT; 
            BTN_ONB1_CNEN = 0;
            BTN_ONB1_CNPU = 0;
            BTN_ONB1_CNPD = 1;
            break;
        case BTN_ONB2:
            BTN_ONB2_TRIS = PIN_INPUT;
            BTN_ONB2_CNEN = 0;
            BTN_ONB2_CNPU = 0;
            BTN_ONB2_CNPD = 1;

            break;
        case BTN_ONB3:
            BTN_ONB3_TRIS = PIN_INPUT;
            BTN_ONB3_CNEN = 0;
            BTN_ONB3_CNPU = 0;
            BTN_ONB3_CNPD = 1;

            break;
        case BTN_NONE:
            break;
    } 
}