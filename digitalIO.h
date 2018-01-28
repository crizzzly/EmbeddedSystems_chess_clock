

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
#include "digitalIO.c"

//sets the pin as input or output pin or if it should change state on pullup or pulldown
void pinMode(uint16_t pin, uint8_t mode);


//reads the current value of the pin
uint8_t digitalRead(uint16_t pin); 

//writes to the latch
void digitalWrite(uint16_t pin, uint8_t value);

//enables/disables all onboard LEDs
void writeAllLED(uint16_t value); 

#endif	/* XC_HEADER_TEMPLATE_H */

