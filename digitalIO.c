/*
 * File:   digitalIO.c
 * Author: chrissi
 *
 * Created on January 28, 2018, 1:16 AM
 */


#include <stdint.h>
#include <stdbool.h>
#include <p33EP512MU810.h>

#include "digitalIO.h"

#define BTN200_PORT   PORTGbits.RG12 
#define BTN201_PORT   PORTGbits.RG13 
#define BTN202_PORT   PORTGbits.RG14 
#define BTN203_PORT   PORTGbits.RG15 

#define BTN200_TRIS   TRISGbits.TRISG12 
#define BTN201_TRIS   TRISGbits.TRISG13
#define BTN202_TRIS   TRISGbits.TRISG14
#define BTN203_TRIS   TRISGbits.TRISG15

#define BTN200_CNEN   CNENGbits.CNIEG12
#define BTN201_CNEN   CNENGbits.CNIEG13
#define BTN202_CNEN   CNENGbits.CNIEG14
#define BTN203_CNEN   CNENGbits.CNIEG15

#define BTN200_CNPU  CNPUGbits.CNPUG12
#define BTN201_CNPU  CNPUGbits.CNPUG13
#define BTN202_CNPU  CNPUGbits.CNPUG14
#define BTN203_CNPU  CNPUGbits.CNPUG15

#define BTN200_CNPD  CNPDGbits.CNPDG12
#define BTN201_CNPD  CNPDGbits.CNPDG13
#define BTN202_CNPD  CNPDGbits.CNPDG14
#define BTN203_CNPD  CNPDGbits.CNPDG15

#define BTN200_LAT  LATGbits.LATG12
#define BTN201_LAT  LATGbits.LATG13
#define BTN202_LAT  LATGbits.LATG14
#define BTN203_LAT  LATGbits.LATG15


#define LED200_LAT LATBbits.LATB8
#define LED201_LAT LATBbits.LATB9
#define LED202_LAT LATBbits.LATB10
#define LED203_LAT LATBbits.LATB11

#define LED200_TRIS TRISBbits.TRISB8
#define LED201_TRIS TRISBbits.TRISB9
#define LED202_TRIS TRISBbits.TRISB10
#define LED203_TRIS TRISBbits.TRISB11

#define LED200_ANSEL ANSELBbits.ANSB8
#define LED201_ANSEL ANSELBbits.ANSB9
#define LED202_ANSEL ANSELBbits.ANSB10
#define LED203_ANSEL ANSELBbits.ANSB11

#define LED200_CNEN CNENBbits.CNIEB8
#define LED201_CNEN CNENBbits.CNIEB9
#define LED202_CNEN CNENBbits.CNIEB10
#define LED203_CNEN CNENBbits.CNIEB11


#define LED200_CNPU CNPUBbits.CNPUB8
#define LED201_CNPU CNPUBbits.CNPUB9
#define LED202_CNPU CNPUBbits.CNPUB10
#define LED203_CNPU CNPUBbits.CNPUB11

#define LED200_CNPD CNPDBbits.CNPDB8 
#define LED201_CNPD CNPDBbits.CNPDB9 
#define LED202_CNPD CNPDBbits.CNPDB10
#define LED203_CNPD CNPDBbits.CNPDB11

#define BTN_PRESSED     0
#define BTN_NOT_PRESSED 1


/*
PIN pin {
             LED200 = 0,
             LED201 = 1,
             LED202 = 2,
             LED203 = 3,
             BTN200 = 4,
             BTN201 = 5,
             BTN202 = 6 ,
             BTN203 = 7
};

*/

//enabled change registers for buttons
void pinMode(uint8_t pin, uint8_t value){
    switch(pin){
        case LED200:
            LED200_ANSEL = 0;
            LED200_TRIS = value ;
            LED200_CNEN = 0;
            LED200_CNPU = 0;
            LED200_CNPD = 0;
            break;
            
        case LED201:
            LED201_ANSEL = 0;    
            LED201_TRIS = value ;
            LED201_CNEN = 0;
            LED201_CNPU = 0;
            LED201_CNPD = 0;
            break;

        case LED202:
            LED200_ANSEL = 0;
            LED202_TRIS = value ;
            LED202_CNEN = 0;
            LED202_CNPU = 0;
            LED202_CNPD = 0;
            break;
            
        case LED203:
            LED200_ANSEL = 0;
            LED203_TRIS = value ;
            LED203_CNEN = 0;
            LED203_CNPU = 0;
            LED203_CNPD = 0;
            break;


        case BTN200:
            
            BTN200_TRIS = value;
            BTN200_CNEN = 0;
            BTN200_CNPU = 1;
            BTN200_CNPD = 0;
            BTN200_LAT  = 0;
            break;
            
        case BTN201:
            BTN201_TRIS = value;
            BTN201_CNEN = 0;
            BTN201_CNPU = 1;
            BTN201_CNPD = 0;
            BTN201_LAT  = 0;
            break;

            
        case BTN202:
            BTN202_TRIS = value;
            BTN202_CNEN = 0;
            BTN202_CNPU = 1;
            BTN202_CNPD = 0;
            BTN201_LAT  = 0;
            break;

            
        case BTN203:
            BTN203_TRIS = value;
            BTN203_CNEN = 0;
            BTN203_CNPU = 1;
            BTN203_CNPD = 0;
            BTN203_LAT  = 0;
            break;
        }
                    
    }

    
uint8_t digitalRead(uint8_t pin){
    switch(pin){
        case LED200:
            return((LED200_LAT == HIGH) ? true : false) ;

        case LED201:
            return((LED201_LAT == HIGH) ? true : false) ;

        case LED202:
            return((LED202_LAT == HIGH) ? true : false) ;

        case LED203:
            return((LED203_LAT == HIGH) ? true : false) ;

        case BTN200:
            return ((BTN200_PORT == BTN_PRESSED) ? true : false );

        case BTN201:
            return ((BTN201_PORT == BTN_PRESSED) ? true : false );

        case BTN202:
            return ((BTN202_PORT == BTN_PRESSED) ? true : false );

        case BTN203:
            return ((BTN203_PORT == BTN_PRESSED) ? true : false );
    }
    return 0;
}
    
    /*********************************************************************
* Function: void digitalWrite(uint16_t pin, uint8_t value);
*
* Overview: sets the latch of requested pin to high or low
*
*
* Input: uint16_t pin - port/pin number to be set as on/off
*        uint8_t value - high to set as on, low to set as off
*
* Output: none
*
********************************************************************/
    void digitalWrite(uint8_t pin, uint8_t value){
        switch(pin){
            case LED200:
                LED200_LAT = value;
                break;
            case LED201:
                LED201_LAT = value;
                break;
            case LED202:
                LED202_LAT = value;
                break;
            case LED203:
                LED203_LAT = value;
                break;
            default:
                break;
        }
        
    }
    
    void writeAllLED(uint8_t value){
        LATB &= 0xF0FF; // clear all four LEDs
        LATB |= (value << 8); // set bits again
    }





