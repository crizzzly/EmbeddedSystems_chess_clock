

/* 
 * File:  digitalIO.h 
 * Author:  CR
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  

#ifndef DIGITALIO_H
#define	DIGITALIO_H

#include <xc.h> // include processor files - each processor file is guarded.
#include <stdint.h>
#include <stdio.h>

#define LED_ON  1
#define LED_OFF 0

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define LED200  0
#define LED201  1
#define LED202  2
#define LED203  3

#define BTN200  4
#define BTN201  5
#define BTN202  6
#define BTN203  7

#define PZ200   9
#define RSW204   10

#define INC_A   11 //incrementing in Dir A
#define INC_B   12 //incrementing in Dir B
#define INC_SW  13 //switching directions


#define LED_COUNT 4
#define BTN_COUNT 4

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

//piezo
#define PIEZ_ANS    ANSELGbits.ANSG8
#define PIEZ_TRIS   TRISGbits.TRISG8
#define PIEZ_CNEN   CNENGbits.CNIEG8
#define PIEZ_PORT   PORTGbits.RG8
#define PIEZ_LAT    LATGbits.LATG9


//rotary encoder
#define RSW204_INC_A    PORTGbits.RG0
#define RSW204_INC_B    PORTGbits.RG1
#define RSW204_INC_SW   PORTGbits.RG9
#define RSW204_ANS      ANSELGbits.ANSG9
//IO select
#define RSW204_TRIS0    TRISGbits.TRISG0
#define RSW204_TRIS1    TRISGbits.TRISG1
#define RSW204_TRIS9    TRISGbits.TRISG9
//enable/disable weak PullUp
#define RSW204_CNPUG0   CNPUGbits.CNPUG0
#define RSW204_CNPUG1   CNPUGbits.CNPUG1
#define RSW204_CNPUG9   CNPUGbits.CNPUG9
//enable/disable changeNotification
#define RSW204_CNENG0   CNENGbits.CNIEG0
#define RSW204_CNENG1   CNENGbits.CNIEG1
#define RSW204_CNENG9   CNENGbits.CNIEG9

//sets the pin as input or output pin or if it should change state on pullup or pulldown
void pinMode(uint16_t pin, uint8_t value);


//reads the current value of the pin
uint8_t digitalRead(uint16_t pin); 

//writes to the latch
void digitalWrite(uint16_t pin, uint8_t value);

//enables/disables all onboard LEDs
void writeAllLED(uint8_t value); 

int8_t readRotaryEncPulse(void); 

#endif	/* XC_HEADER_TEMPLATE_H */

