

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

//#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
#include <stdio.h>

typedef enum {
            LED200,
            LED201,
            LED202,
            LED203,
            BTN200,
            BTN201,
            BTN202,
            BTN203
}PIN;



#define LED_COUNT 4
#define BTN_COUNT 4

//sets the pin as input or output pin or if it should change state on pullup or pulldown
void pinMode(PIN pin, uint8_t value);


//reads the current value of the pin
uint8_t digitalRead(PIN pin); 

//writes to the latch
void digitalWrite(PIN pin, uint8_t value);

//enables/disables all onboard LEDs
void writeAllLED(PIN value); 

#endif	/* XC_HEADER_TEMPLATE_H */

