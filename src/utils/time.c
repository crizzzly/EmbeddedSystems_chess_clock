/*
 * File:   time.c
 * Author: chrissi
 *
 * Created on January 28, 2018, 3:37 PM
 */

#include "../time.h"

void delay_s(uint16_t s){
}


void delay_us(uint16_t us) {
    __delay_us(us);
}

void beep(uint16_t ms, uint16_t freq) {
    ms /= 10; // Only 10ms duration steps for higher freq resolution
    uint16_t freq_loop = freq/100; // 1/100 second to do in each loop
    uint32_t cycles = (FCY/freq)/2;
    
    while (ms) {
        int i;
        for (i = 0; i < freq_loop; i++) { 
            __delay32(cycles);
            LATGbits.LATG8 = 1;
            __delay32(cycles);
            LATGbits.LATG8 = 0;
        }
        ms--;
    }

}