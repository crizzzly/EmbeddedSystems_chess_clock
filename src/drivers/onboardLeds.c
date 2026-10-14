/*
 * File:   onboardLEDs.c
 * Author: chrissi
 *
 * Created on January 8, 2018, 10:40 PM
 */


#include "xc.h"
#include <stdbool.h>
#include "onboardLeds.h"

#define LED_ONB0_LAT LATBbits.LATB8
#define LED_ONB1_LAT LATBbits.LATB9
#define LED_ONB2_LAT LATBbits.LATB10
#define LED_ONB3_LAT LATBbits.LATB11

#define LED_ONB0_TRIS TRISBbits.TRISB8
#define LED_ONB1_TRIS TRISBbits.TRISB9
#define LED_ONB2_TRIS TRISBbits.TRISB10
#define LED_ONB3_TRIS TRISBbits.TRISB11

#define LED_ONB0_ANSEL ANSELBbits.ANSB8
#define LED_ONB1_ANSEL ANSELBbits.ANSB9
#define LED_ONB2_ANSEL ANSELBbits.ANSB10
#define LED_ONB3_ANSEL ANSELBbits.ANSB11

#define LED_ONB0_CNEN CNENBbits.CNIEB8
#define LED_ONB1_CNEN CNENBbits.CNIEB9
#define LED_ONB2_CNEN CNENBbits.CNIEB10
#define LED_ONB3_CNEN CNENBbits.CNIEB11


#define LED_ONB0_CNPU CNPUBbits.CNPUB8
#define LED_ONB1_CNPU CNPUBbits.CNPUB9
#define LED_ONB2_CNPU CNPUBbits.CNPUB10
#define LED_ONB3_CNPU CNPUBbits.CNPUB11

#define LED_ONB0_CNPD CNPDBbits.CNPDB8 
#define LED_ONB1_CNPD CNPDBbits.CNPDB9 
#define LED_ONB2_CNPD CNPDBbits.CNPDB10
#define LED_ONB3_CNPD CNPDBbits.CNPDB11

#define LED_ON  1
#define LED_OFF 0

#define INPUT   1
#define OUTPUT  0

/*********************************************************************
* Function: void LED_On(LED led);
*
* Overview: Turns requested LED on
*
* PreCondition: LED configured via LED_Configure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LED_On(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
void LED_On(LED led){
    
    switch (led){
        case LED_ONB0:
            LED_ONB0_LAT = LED_ON;
            break;
        case LED_ONB1:
            LED_ONB1_LAT = LED_ON;
            break;
        case LED_ONB2:
            LED_ONB2_LAT = LED_ON;
            break;
        case LED_ONB3:
            LED_ONB3_LAT = LED_ON;
            break;
        case LED_NONE:
            break;
    }
          
}

/*********************************************************************
* Function: void LED_Off(LED led);
*
* Overview: Turns requested LED off
*
* PreCondition: LED configured via LED_Configure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LED_On(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/
void LED_Off(LED led){
        switch (led){
        case LED_ONB0:
            LED_ONB0_LAT = LED_OFF;
            break;
        case LED_ONB1:
            LED_ONB1_LAT = LED_OFF;
            break;
        case LED_ONB2:
            LED_ONB2_LAT = LED_OFF;
            break;
        case LED_ONB3:
            LED_ONB3_LAT = LED_OFF;
            break;
        case LED_NONE:
            break;
    }
}


/*********************************************************************
* Function: void LED_Toggle(LED led);
*
* Overview: Toggles the state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LED_Toggle(LED_CONNECTION_DETECTED);
*
* Output: none
*
********************************************************************/

void LED_Toggle(LED led){
       switch (led){
        case LED_ONB0:
            LED_ONB0_LAT ^= 1 ;
            break;
        case LED_ONB1:
            LED_ONB1_LAT ^= 1 ;
            break;
        case LED_ONB2:
            LED_ONB2_LAT ^= 1 ;
            break;
        case LED_ONB3:
            LED_ONB3_LAT ^= 1 ;
            break;
        case LED_NONE:
            break;
    }
}

/*********************************************************************
* Function: bool LED_Get(LED led);
*
* Overview: Returns the current state of the requested LED
*
* PreCondition: LED configured via LEDConfigure()
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of 
*        the LEDs on the silkscreen on the board (as the demo code may 
*        be ported to other boards).
*         i.e. - LED_Get(LED_CONNECTION_DETECTED);
*
* Output: true if on, false if off
*
********************************************************************/
bool LED_Get(LED led){
     switch (led){
        case LED_ONB0:
            return((LED_ONB0_LAT == 1) ? true : false) ;

         case LED_ONB1:
            return((LED_ONB1_LAT == 1) ? true : false) ;

         case LED_ONB2:
            return((LED_ONB2_LAT == 1) ? true : false) ;

         case LED_ONB3:
            return((LED_ONB3_LAT == 1) ? true : false) ;

         case LED_NONE:
            return false;
    }
  return false;    
}

/*********************************************************************
* Function: bool LED_Enable(LED led);
*
* Overview: Configures the LED for use by the other LED API
*
* PreCondition: none
*
* Input: LED led - enumeration of the LEDs available in this
*        demo.  They should be meaningful names and not the names of
*        the LEDs on the silkscreen on the board (as the demo code may
*        be ported to other boards).
*
* Output: none
*
********************************************************************/
void LED_Enable(LED led){
    switch (led){
        case LED_ONB0:
            LED_ONB0_TRIS = OUTPUT ;
            LED_ONB0_CNEN = 0;
            LED_ONB0_CNPU = 0;
            LED_ONB0_CNPD = 0;
            break;
        case LED_ONB1:
            LED_ONB1_TRIS = OUTPUT ;
            LED_ONB1_CNEN = 0;
            LED_ONB1_CNPU = 0;
            LED_ONB1_CNPD = 0;
            break;
        case LED_ONB2:
            LED_ONB2_TRIS = OUTPUT ;
            LED_ONB2_CNEN = 0;
            LED_ONB2_CNPU = 0;
            LED_ONB2_CNPD = 0;
            break;
        case LED_ONB3:
            LED_ONB3_TRIS = OUTPUT ;
            LED_ONB3_CNEN = 0;
            LED_ONB3_CNPU = 0;
            LED_ONB3_CNPD = 0;
            break;
        case LED_NONE:
            break;
    }
}




