

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

