/*
 * File:   time.c
 * Author: chrissi
 *
 * Created on January 28, 2018, 3:37 PM
 */

#include "time.h"
#include "../drivers/digitalIO.h"

void delay_s(uint16_t s){
}


void delay_us(uint16_t us) {
    __delay_us(us);
}

// void delay_ms(uint16_t u16milliseconds){
//     uint16_t ui16_i=0;
//     while(u16milliseconds){
//         for (ui16_i=0;ui16_i<331;ui16_i++){    //1 ms delay loop
//             __asm__ volatile("nop \n\t"
//                              "nop \n\t"
//                              "nop \n\t");
//         }//for
//         u16milliseconds--;
//     }//while
//
// }

void beep(uint16_t ms, uint16_t freq) {
    ms /= 10; // Only 10ms duration steps for higher freq resolution
    uint16_t freq_loop = freq/100; // 1/100 second to do in each loop
    uint32_t cycles = (FCY/freq)/2;
    
    while (ms) {
        for (int i = 0; i < freq_loop; i++) {
            __delay32(cycles);
            PIEZ_LAT = 1;
            __delay32(cycles);
            PIEZ_LAT = 0;
        }
        ms--;
    }
}