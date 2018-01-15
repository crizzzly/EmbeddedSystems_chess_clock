/*
 * File:   lcd.c
 * Author: chrissi
 *
 * Created on January 15, 2018, 3:52 AM
 */


#include "xc.h"
#include "lcd.h"
#include <stdint.h>

/* private definitions +++++++++++++++++++++++++++++++++++*/
//define fast instruction time in terms of loop time 
#define LCD_FAST_INSTR      2000

//define slow instruction time
#define LCD_SLOW_INSTR      6000

//define lcd startup time
#define LCD_STARTUP         50000

//characters per line
#define LCD_MAX_COLUMN      16

#define LCD_SendData(data) { PMADDR = 0x0001; PMDIN1 = data; LCD_Wait(LCD_F_INSTR); }
#define LCD_SendCommand(command, delay) { PMADDR = 0x0000; PMDIN1 = command; LCD_Wait(delay); }
#define LCD_COMMAND_CLEAR_SCREEN        0x01    //0000 0001
#define LCD_COMMAND_RETURN_HOME         0x02    //0000 0010
#define LCD_COMMAND_ENTER_DATA_MODE     0x06    //0000 0110
#define LCD_COMMAND_CURSOR_OFF          0x0C    //0000 1100
#define LCD_COMMAND_CURSOR_ON           0x0F    //0000 1111
#define LCD_COMMAND_MOVE_CURSOR_LEFT    0x10    //0001 0000
#define LCD_COMMAND_MOVE_CURSOR_RIGHT   0x14    //0001 0100
#define LCD_COMMAND_SET_MODE_8_BIT      0x38    //0011 1000
#define LCD_COMMAND_ROW_0_HOME          0x80    //1000 0000
#define LCD_COMMAND_ROW_1_HOME          0xC0    //1100 0000

//parallel master port mode
#define PMMODE_HOLD_DATA_AFTER_STROBE_Wait_4        0x0003  //0000 0000 0000 0011
#define PMMODE_READ_TO_BYTE_ENABLE_STROBE_WAIT_15   0x003c  //0000 0000 0011 1100
#define PMMODE_R_W_ADR_PHASE_WAIT_4                 0x00c0  //0000 0000 1100 0000
#define PMMODE_PARALLEL_MASTER_PORTMODE_1           0x0300  //0000 0011 0000 0000
#define PMMODE_PARALLEL_MASTER_PORTMODE_8_BIT       0x0000  //0000 0000 0000 0000
#define PMMODE_INCREMENT_MODE_NO_INCR               0x0000    
#define PMMODE_INTERRUPT_REQUEST_MODE_NO_INTERR     0x0000
#define PMMODE_BUSY_BIT_NOT_BUSY                    0x0000

//parallel master port control register 
 //1000 0011 1000 0011
#define PMCON_READ_STROBE_POLARITY_ENABLE_ACTIVE_HIGH       0x0001 
#define PMCON_SET_STROBE_POLARITY_IS_ACTIVE_HIGH            0x0002            
#define PMCON_BYTE_ENABLE_ACTIVE_LOW                        0x0000
#define PMCON_CHIP_SELECT_0_POLARITY_ACTIVE_LOW             0x0000
#define PMCON_CHIP_SELECT_1_POLARITY_ACTIVE_LOW             0x0000
#define PMCON_ADRESS_LATCH_POLARITY_ACTIVE_LOW              0x0000
#define PMCON_CHIP_SELECT_FUNCTION_PMC1_PMCS2_AS_CHIPSELECT 0x0080 
#define PMCON_READ_WRITE_STROBE_PORT_ENABLED                0x0100
#define PMCON_WRITE_ENABLE_STROPE_PORT_ENABLED              0x0200
#define PMCON_BYTE_ENABLE_PORT_DISABLED                     0x0000
#define PMCON_ADRESS_AND_DATA_ON_SEPERATE_PINS              0x0000
#define PMCON_PMP_CONTINUE_MODULE_OP_IN_IDLE_MODE           0X0000
#define PMCON_PARALLEL_MASTER_PORT_ENABLED                  0X8000

//parallel master port  address enable register
#define PMAEN_PMALL_STROBE_ENABLED      0x0001
#define PMAEN_PMP_ADRESS_PORT_AS_IO     0x0000
#define PMAEN_PMCS1_STROBE_AS_IO        0x0000
#define PMAEN_PMCS1_STROBE_AS_IO        0x0000


/* Private Functions *************************************************/
static void LCD_CarriageReturn ( void ) ;
static void LCD_ShiftCursorLeft ( void ) ;
static void LCD_ShiftCursorRight ( void ) ;
static void LCD_ShiftCursorUp ( void ) ;
static void LCD_ShiftCursorDown ( void ) ;
static void LCD_Wait ( unsigned long ) ;

/* Private variables ************************************************/
static uint8_t row ;
static uint8_t column ;

/*********************************************************************
* Function: bool LCD_Initialize(void);
*
* Overview: Initializes the LCD screen.  
*
* PreCondition: none
*
* Input: None
*
* Output: true if successful, false if not
*
********************************************************************/
bool LCD_Initialize(void){
    
    //parallel master port mode register
    PMMODE = PMMODE_HOLD_DATA_AFTER_STROBE_Wait_4 
            | PMMODE_READ_TO_BYTE_ENABLE_STROBE_WAIT_15 
            | PMMODE_R_W_ADR_PHASE_WAIT_4
            | PMMODE_PARALLEL_MASTER_PORTMODE_1
            | PMMODE_PARALLEL_MASTER_PORTMODE_8_BIT
            | PMMODE_INCREMENT_MODE_NO_INCR
            | PMMODE_INTERRUPT_REQUEST_MODE_NO_INTERR
            | PMMODE_BUSY_BIT_NOT_BUSY;
    
    //parallel master port control register 
    //PMCON = 0x8383 ; //1000 0011 1000 0011
    PMCON =  PMCON_READ_STROBE_POLARITY_ENABLE_ACTIVE_HIGH 
            | PMCON_SET_STROBE_POLARITY_IS_ACTIVE_HIGH 
            | PMCON_BYTE_ENABLE_ACTIVE_LOW 
            | PMCON_CHIP_SELECT_0_POLARITY_ACTIVE_LOW 
            | PMCON_CHIP_SELECT_1_POLARITY_ACTIVE_LOW 
            | PMCON_ADRESS_LATCH_POLARITY_ACTIVE_LOW 
            | PMCON_CHIP_SELECT_FUNCTION_PMC1_PMCS2_AS_CHIPSELECT 
            | PMCON_READ_WRITE_STROBE_PORT_ENABLED 
            | PMCON_WRITE_ENABLE_STROPE_PORT_ENABLED 
            | PMCON_BYTE_ENABLE_PORT_DISABLED 
            | PMCON_ADRESS_AND_DATA_ON_SEPERATE_PINS 
            | PMCON_PMP_CONTINUE_MODULE_OP_IN_IDLE_MODE 
            | PMCON_PARALLEL_MASTER_PORT_ENABLED;
    
    //parallel master port  address enable register

    PMAEN = PMAEN_PMALL_STROBE_ENABLED     
           | PMAEN_PMP_ADRESS_PORT_AS_IO   
           | PMAEN_PMCS1_STROBE_AS_IO      
           | PMAEN_PMCS1_STROBE_AS_IO;      
    
    
    LCD_Wait ( LCD_STARTUP ) ;

    LCD_SendCommand ( LCD_COMMAND_SET_MODE_8_BIT ,     LCD_F_INSTR + LCD_STARTUP ) ;
    LCD_SendCommand ( LCD_COMMAND_CURSOR_OFF ,         LCD_F_INSTR ) ;
    LCD_SendCommand ( LCD_COMMAND_ENTER_DATA_MODE ,    LCD_S_INSTR ) ;

    LCD_ClearScreen ( ) ;

    return true ;
}

/*********************************************************************
* Function: void LCD_PutString(char* inputString, uint16_t length);
*
* Overview: Puts a string on the LCD screen.  Unsupported characters will be
*           discarded.  If Lcd is not ready or buffer space not available 
*          characters are blocked or thrown away
*          if null terminator (0x00) is reached ir the length number of 
*          characters is printed it will terminate
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char* - string to print
*        uint16_t - length of string to print
*
* Output: None
*
********************************************************************/

void LCD_PutString(char* inputString, uint16_t length){
    while (length--){
        switch (*inputString){
            case 0x00:
                return ;

            default:
                LCD_PutChar ( *inputString++ ) ;
                break ;
        }
    }
}

/*********************************************************************
* Function: void LCD_PutChar(char);
*
* Overview: Puts a character on the LCD screen.  Unsupported characters will be
*           discarded.  May block or throw away characters is LCD is not ready
*           or buffer space is not available. Will terminate when null 
*           terminator character (0x00) is reached or the length number of 
*           characters is printed.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: char - character to print
*
* Output: None
*
********************************************************************/
void LCD_PutChar(char){
    
    switch (inputCharacter){
        case '\r':
            LCD_CarriageReturn ( ) ;
            break ;

        case '\n':
            if (row == 0) {
                LCD_ShiftCursorDown ( ) ;
            }
            else {
                LCD_ShiftCursorUp ( ) ;
            }
            break ;

        case '\b':
            LCD_ShiftCursorLeft ( ) ;
            LCD_PutChar ( ' ' ) ;
            LCD_ShiftCursorLeft ( ) ;
            break ;

        default:
            LCD_SendData ( inputCharacter ) ;
            column++ ;

            if (column == LCD_MAX_COLUMN) {
                column = 0 ;
                if (row == 0) {
                    LCD_SendCommand ( LCD_COMMAND_ROW_1_HOME , LCD_S_INSTR ) ;
                    row = 1 ;
                }
                else {
                    LCD_SendCommand ( LCD_COMMAND_ROW_0_HOME , LCD_S_INSTR ) ;
                    row = 0 ;
                }
            }
            break ;
    }
}
/*********************************************************************
* Function: void LCD_ClearScreen(void);
*
* Overview: Clears the screen, if possible.
*
* PreCondition: already initialized via LCD_Initialize()
*
* Input: None
*
* Output: None
*
********************************************************************/
void LCD_ClearScreen ( void )
{
    LCD_SendCommand ( LCD_COMMAND_CLEAR_SCREEN , LCD_S_INSTR ) ;
    LCD_SendCommand ( LCD_COMMAND_RETURN_HOME ,  LCD_S_INSTR ) ;

    row = 0 ;
    column = 0 ;
}

/*********************************************************************
* Function: void LCD_CursorEnable(bool enable)
*
* Overview: Enables/disables cursor
*
* PreCondition: None
*
* Input: bool - specifies if the cursor should be on or off
*
* Output: None
*
********************************************************************/
void LCD_CursorEnable ( bool enable ) {
    if (enable == true) {
        LCD_SendCommand ( LCD_COMMAND_CURSOR_ON , LCD_S_INSTR ) ;
    }
    else {
        LCD_SendCommand ( LCD_COMMAND_CURSOR_OFF , LCD_S_INSTR ) ;
    }
}


/****************************************************************************
 * 
 *                    private functions 
 *  
 ****************************************************************************/

/*********************************************************************
 * Function: static void LCD_CarriageReturn(void)
 *
 * Overview: Handles a carriage return
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_CarriageReturn ( void )
{
    if (row == 0) {
        LCD_SendCommand ( LCD_COMMAND_ROW_0_HOME , LCD_S_INSTR ) ;
    }
    else {
        LCD_SendCommand ( LCD_COMMAND_ROW_1_HOME , LCD_S_INSTR ) ;
    }
    column = 0 ;
}
/*********************************************************************
 * Function: static void LCD_ShiftCursorLeft(void)
 *
 * Overview: Shifts cursor left one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_ShiftCursorLeft ( void )
{
    uint8_t i ;

    if (column == 0) {
        if (row == 0) {
            LCD_SendCommand ( LCD_COMMAND_ROW_1_HOME , LCD_S_INSTR ) ;
            row = 1 ;
        }
        else {
            LCD_SendCommand ( LCD_COMMAND_ROW_0_HOME , LCD_S_INSTR ) ;
            row = 0 ;
        }

        //Now shift to the end of the row
        for (i = 0 ; i < ( LCD_MAX_COLUMN - 1 ) ; i++) {
            LCD_ShiftCursorRight ( ) ;
        }
    }
    else {
        column-- ;
        LCD_SendCommand ( LCD_COMMAND_MOVE_CURSOR_LEFT , LCD_F_INSTR ) ;
    }
}
/*********************************************************************
 * Function: static void LCD_ShiftCursorRight(void)
 *
 * Overview: Shifts cursor right one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_ShiftCursorRight ( void ) {
    LCD_SendCommand ( LCD_COMMAND_MOVE_CURSOR_RIGHT , LCD_F_INSTR ) ;
    column++ ;

    if (column == LCD_MAX_COLUMN) {
        column = 0 ;
        if (row == 0) {
            LCD_SendCommand ( LCD_COMMAND_ROW_1_HOME , LCD_S_INSTR ) ;
            row = 1 ;
        }
        else {
            LCD_SendCommand ( LCD_COMMAND_ROW_0_HOME , LCD_S_INSTR ) ;
            row = 0 ;
        }
    }
}
/*********************************************************************
 * Function: static void LCD_ShiftCursorUp(void)
 *
 * Overview: Shifts cursor up one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_ShiftCursorUp ( void ) {
    uint8_t i ;

    for (i = 0 ; i < LCD_MAX_COLUMN ; i++) {
        LCD_ShiftCursorLeft ( ) ;
    }
}
/*********************************************************************
 * Function: static void LCD_ShiftCursorDown(void)
 *
 * Overview: Shifts cursor down one spot (wrapping if required)
 *
 * PreCondition: already initialized via LCD_Initialize()
 *
 * Input: None
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_ShiftCursorDown ( void ) {
    uint8_t i ;

    for (i = 0 ; i < LCD_MAX_COLUMN ; i++) {
        LCD_ShiftCursorRight ( ) ;
    }
}
/*********************************************************************
 * Function: static void LCD_Wait(unsigned int B)
 *
 * Overview: A crude wait function that just cycle burns
 *
 * PreCondition: None
 *
 * Input: unsigned int - artibrary delay time based on loop counts.
 *
 * Output: None
 *
 ********************************************************************/
static void LCD_Wait ( unsigned long delay ) {
    while (delay) {
        Nop();
        delay-- ;
    }
}