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
 * File:        print_lcd.h
 * Author:         christina rost / team1
 * Comments:        type &function definitions to print on lcd and set print configs
 * Revision history: 
 */



#ifndef PRINT_LCD_H
#define PRINT_LCD_H

#include <stdbool.h>
#include "lcd.h"

/* Type Definitions *************************************************/
typedef enum
{
    PRINT_CONFIGURATION_LCD
} PRINT_CONFIGURATION;

/*********************************************************************
* Function: bool PRINT_SetConfiguration(PRINT_CONFIGURATION led);
*
* Overview: Configures the print configuration
*
* PreCondition: none
*
* Input: configuration - the print configuration to use.  Some boards
*         may have more than one print configuration enabled
*
* Output: TRUE if successful, FALSE if LED not configured or doesn?t 
*         exist for this board.
*
********************************************************************/
bool PRINT_SetConfiguration(PRINT_CONFIGURATION configuration);
#define PRINT_SetConfiguration(configuration) LCD_Initialize()

/*********************************************************************
* Function: void PRINT_String(char* string, uint16_t length)
*
* Overview: Prints a string until a null terminator is reached or the
*           specified string length is printed.
*
* PreCondition: none
*
* Input: char* string - the string to print.
*        uint16_t length - the length of the string.
*
* Output: None
*
********************************************************************/
void PRINT_String(char* string, uint16_t length);
#define PRINT_String(string, length) LCD_PutString(string, length)

/*********************************************************************
* Function: void PRINT_Char(char charToPrint)
*
* Overview: Prints a character
*
* PreCondition: none
*
* Input: char charToPrint - the character to print
*
* Output: None
*
********************************************************************/
void PRINT_Char(char charToPrint);
#define PRINT_Char(charToPrint) LCD_PutChar(charToPrint)

/*********************************************************************
* Function: void PRINT_ClearStreen()
*
* Overview: Clears the screen, if possible
*
* PreCondition: none
*
* Input: None
*
* Output: None
*
********************************************************************/
void PRINT_ClearScreen(void);
#define PRINT_ClearScreen() LCD_ClearScreen()

/*********************************************************************
* Function: void PRINT_CursorEnable(bool enable)
*
* Overview: Enables/disables the cursor
*
* PreCondition: None
*
* Input: bool - specifies if the cursor should be on or off
*
* Output: None
*
********************************************************************/
void PRINT_CursorEnable(bool);
#define PRINT_CursorEnable(enabled) LCD_CursorEnable(enabled)

#endif //PRINT_LCD_H
