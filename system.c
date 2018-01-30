/******************     system init file        *******************
 * 
 * File:   system.c
 * Author: chrissi
 * 
 * Summary: System Initialization File
 * 
 * Description: File contains source code necessary to initialize the system 
 *
 * Created on January 15, 2018, 4:12 PM
 */


#include <xc.h>
#include "app_data.h"
#include "myxc.h"
#include "digitalIO.h"
#include "melodies.h"
// ****************************************************************************
// ****************************************************************************
// Section: File Scope Functions
// ****************************************************************************
// ****************************************************************************

void SOSC_Configuration ( void ) ;
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _OscillatorFail ( void ) ;
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AddressError ( void ) ;
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _StackError ( void ) ;
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _MathError ( void ) ;
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _IC3Interrupt ( void ) ;

// ****************************************************************************
// ****************************************************************************
// Section: System Initialization
// ****************************************************************************
// ****************************************************************************
/*******************************************************************************
  Function:
    void SYS_Initialize ( void )

  Summary:
    Initializes the Explorer 16 board peripherals

  Description:
    This routine initializes the Explorer 16 board peripherals.
    In a bare-metal environment (where no OS is supported), this routine should
    be called almost immediately after entering the "main" routine.

  Precondition:
    The C-language run-time environment and stack must have been initialized.

  Parameters:
    None.

  Returns:
    None.

  Example:
    <code>
    SYS_INT_Initialize(NULL);
    </code>

  Remarks:
    Basic System Initialization Sequence:

    1.  Initilize minimal board services and processor-specific items
        (enough to use the board to initialize drivers and services)
    2.  Initialize all supported system services
    3.  Initialize all supported modules
        (libraries, drivers, middleware, and application-level modules)
    4.  Initialize the main (static) application, if present.

    The order in which services and modules are initialized and started may be
    important.

 */

void SYS_Initialize ( void )
{
    /* Init IO Pins for LEDs & BTNs*/
    pinMode(LED200, OUTPUT);
    pinMode(LED201, OUTPUT);
    pinMode(LED202, OUTPUT);
    pinMode(LED203, OUTPUT);
    
    pinMode(BTN200, INPUT);
    pinMode(BTN201, INPUT);
    pinMode(BTN202, INPUT);
    pinMode(BTN203, INPUT);

    /*Initialize Timer*/
    TIMER_SetConfig ( TIMER_CONFIG_RTCC ) ;

    /* Configure Secondary Ocillator for Timer 1 to work as RTC counter*/
    SOSC_Configuration ( ) ;
    
    /* Initialize LCD*/
    PRINT_SetConfiguration ( PRINT_CONFIGURATION_LCD ) ;
    
    /* Init Piezo*/
    initPiezo();
}

void SOSC_Configuration ( void )
{
    char a , b , c , *p ;

    a = 2 ;
    b = 0x46 ;
    c = 0x57 ;
    p = (char *) &OSCCON ;

    asm volatile ("mov.b %1,[%0] \n"
                "mov.b %2,[%0] \n"
                "mov.b %3,[%0] \n" : /* no outputs */ : "r"( p ) , "r"( b ) , "r"( c ) ,
                "r"( a ) ) ;
}

/*******************************************************************************
  Function:
   void __attribute__((__interrupt__)) _T1Interrupt( void ))

  Summary:
    ISR routine for the T1 Interrupt.

  Description:
    This is the raw Interrupt Service Routine (ISR) for the Timer 3 interrupt.
    This routine calls the Timer1's interrupt routine once per second

  Precondition:
    The Timer peripheral must have been initialized for Timer 3.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    This routine must not be "called" as a C-language function is called.  It
    is "vectored" to by the processor when the interrupt occurs.
 */
void __attribute__ ( ( __interrupt__ , auto_psv ) ) _T1Interrupt ( void )
{
    if (appData.activePlayer == 1){
        /* update seconds */
        if ( appData.p2_seconds > 0x00 )
        {
            appData.p2_seconds-- ;
        }
            /* update minutes */
        else
        {
            appData.p2_seconds = 0x3B ;
            if ( appData.p1_minutes > 0x00 )
            {
                appData.p2_minutes-- ;
            }
                /* update hours */
            else
            {
                appData.p2_minutes = 0x3B ;
                if ( appData.p1_hours > 0x00 )
                {
                    appData.p2_hours -- ;
                }
                else
                {
                    appData.p2_hours = 0x17 ;
                }
            }
        }
    }
    else{
        /* update seconds */
        if ( appData.p1_seconds > 0x00 )
        {
            appData.p1_seconds-- ;
        }
            /* update minutes */
        else
        {
            appData.p1_seconds = 0x3B ;
            if ( appData.p1_minutes > 0x00 )
            {
                appData.p1_minutes-- ;
            }
                /* update hours */
            else
            {
                appData.p1_minutes = 0x3B ;
                if ( appData.p1_hours > 0x00 )
                {
                    appData.p1_hours -- ;
                }
                else
                {
                    appData.p1_hours = 0x17 ;
                }
            }
        }
    }

    /* set flag to update LCD */
    appData.rtc_lcd_update = 1 ;

    /* reset Timer 1 interrupt flag */
    IFS0bits.T1IF = 0 ;
}

// *****************************************************************************
// *****************************************************************************
// Section: Primary Exception Vector handlers
// *****************************************************************************
// *****************************************************************************

// *****************************************************************************
/*  void __attribute__((__interrupt__,auto_psv)) _OscillatorFail(void)

  Summary:
    Provides the required exception vector handlers for Oscillator trap

  Description:
   This routine is used if INTCON2bits.ALTIVT = 0 and it handles the oscillator
 trap.

  Remarks:
   All trap service routines in this file simply ensure that device
   continuously executes code within the trap service routine. Users
   may modify the basic framework provided here to suit to the needs
   of their application.
 */

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _OscillatorFail ( void )
{
    LCD_PutString("OSC FAIL", 18);
    INTCON1bits.OSCFAIL = 0 ;        //Clear the trap flag
    while (1) ;
}

// *****************************************************************************
/*  void __attribute__((__interrupt__,auto_psv)) _AddressError(void)

  Summary:
    Provides the required exception vector handlers for Address Error trap

  Description:
   This routine is used if INTCON2bits.ALTIVT = 0 and it handles the address
 error trap.

  Remarks:
   All trap service routines in this file simply ensure that device
   continuously executes code within the trap service routine. Users
   may modify the basic framework provided here to suit to the needs
   of their application.
 */

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _AddressError ( void )
{
    LCD_PutString("ADDR ERR", 18);
    INTCON1bits.ADDRERR = 0 ;        //Clear the trap flag
    while (1) ;
}

// *****************************************************************************
/*  void __attribute__((__interrupt__,auto_psv)) _StackError(void))

  Summary:
    Provides the required exception vector handlers for Stack Error trap

  Description:
   This routine is used if INTCON2bits.ALTIVT = 0 and it handles the stack
 error trap.

  Remarks:
   All trap service routines in this file simply ensure that device
   continuously executes code within the trap service routine. Users
   may modify the basic framework provided here to suit to the needs
   of their application.
 */

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _StackError ( void )
{
        LCD_PutString("STACK ERR", 18);

    INTCON1bits.STKERR = 0 ;         //Clear the trap flag
    while (1) ;
}

// *****************************************************************************
/*  void __attribute__((__interrupt__,auto_psv)) _MathError(void))

  Summary:
    Provides the required exception vector handlers for Math Error trap

  Description:
   This routine is used if INTCON2bits.ALTIVT = 0 and it handles the math
 error trap.

  Remarks:
   All trap service routines in this file simply ensure that device
   continuously executes code within the trap service routine. Users
   may modify the basic framework provided here to suit to the needs
   of their application.
 */

void __attribute__ ( ( __interrupt__ , auto_psv ) ) _MathError ( void )
{
    INTCON1bits.MATHERR = 0 ;        //Clear the trap flag
    while (1) ;
}


void __attribute__ ( ( __interrupt__ , auto_psv ) ) _CNInterrupt (void) 
{     
    LCD_PutString("interrupted! ", 36);
    if(digitalRead(BTN200)){
        appData.btn_pressed = BTN200; 
       }
    else if(digitalRead(BTN201)){
        appData.btn_pressed = BTN201; 

       }
    else if(digitalRead(BTN202)){
        appData.btn_pressed = BTN202; 

       }
    else if(digitalRead(BTN203)){
        appData.btn_pressed = BTN203;
    }

    //Reset change notification interrupt flag
    IFS1bits.CNIF = 0; 

    playDAccord();

    handleButton(); 
}
