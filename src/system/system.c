#/******************     system init file        *******************
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
#include "../app/app_data.h"
#include "../player_data.h"
#include "../myxc.h"
#include "../drivers/digitalIO.h"
#include "../melodies.h"
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
    //piezo config
    pinMode(PZ200, OUTPUT);
    
    //Button config
    pinMode(BTN200, INPUT);
    pinMode(BTN201, INPUT);
    pinMode(BTN202, INPUT);
    pinMode(BTN203, INPUT);
    //rotary enc confoh
    pinMode(RSW204, INPUT);

    /*Initialize Timer*/
    TIMER_SetConfig ( TIMER_CONFIG_RTCC ) ;

    /* Configure Secondary Ocillator for Timer 1 to work as RTC counter*/
    SOSC_Configuration ( ) ;
    
    /* Initialize LCD*/
    PRINT_SetConfiguration ( PRINT_CONFIGURATION_LCD ) ;
    
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
    if (p2.is_active){
        /* update seconds */
        if ( p2.seconds > 0x00 )
        {
            p2.seconds-- ;
        }
            /* update minutes */
        else
        {
            p2.seconds = 0x3B ;
            if ( p2.minutes > 0x00 )
            {
                p2.minutes-- ;
            }
                /* update hours */
            else
            {
                p2.minutes = 0x3B ;
                if ( p2.hours > 0x00 )
                {
                    p2.hours -- ;
                }
                else {
                    p2.time_out = 1; 
                    p2.hours = 0x17 ;
                }
            }
        }
    }
    else if(p1.is_active)
                {
        /* update seconds */
        if ( p1.seconds > 0x00 )
        {
            p1.seconds-- ;
        }
            /* update minutes */
        else
        {
            p1.seconds = 0x3B ;
            if ( p1.minutes > 0x00 )
            {
                p1.minutes-- ;
            }
                /* update hours */
            else
            {
                p1.minutes = 0x3B ;
                if ( p1.hours > 0x00 )
                {
                    p1.hours -- ;
                }
                else
                {
                    p1.time_out = 1;
                    p1.hours = 0x17 ;
                }
            }
        }
    }
    else {
        if ( appData.seconds < 59 ){
            appData.seconds ++ ;
        }
            /* update minutes */
        else{
            appData.seconds = 0 ;
            if ( appData.minutes < 59 ){
                appData.minutes ++ ;
            }
                /* update hours */
            else{
                appData.minutes = 0 ;
                if ( appData.hours < 24 ) {
                    appData.hours ++ ;
                }
                else {
                    appData.hours = 0 ;
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
   // LCD_PutString("interrupted! ", 36);
    appData.btn_pressed = 1; 
    if(digitalRead(BTN200)){
        appData.btn200_pressed = true; 
       }
    else if(digitalRead(BTN201)){
        appData.btn201_pressed = true; 


       }
    else if(digitalRead(BTN202)){
        appData.btn202_pressed = true; 

       }
    else if(digitalRead(BTN203)){
        appData.btn203_pressed = true;
    }
    else if(digitalRead(INC_A)){
        appData.enc_inc_a = 1; 
        playIncA();
    }
    else if(digitalRead(INC_B)){
        appData.enc_inc_b = 1; 
        playIncB();
    }
    else if(digitalRead(INC_SW)){
        appData.enc_inc_sw = 1; 
        playIncSw();
    }
    playDAccord();

    //Reset change notification interrupt flag
    IFS1bits.CNIF = 0;  
}
