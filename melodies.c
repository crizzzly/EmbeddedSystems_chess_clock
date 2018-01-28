/*
 * File:   melodies.c
 * Author: chrissi
 *
 * Created on January 28, 2018, 10:48 PM
 */


#include "melodies.h"
#include "music.h"
#include "digitalIO.h"
#include <time.h>
#include <stdlib.h>
#include <stdint.h>





void playRandomMelody(void){
    srand(time(NULL)); //initialize random generator; 
    //d e g a h d e
    
    uint16_t tones[] = { NOTE_D3, NOTE_E3, NOTE_G3, NOTE_A3, NOTE_B4};
        uint16_t max =30;

        uint16_t i =0;
    for(i = 0; i < max; i++){
        uint16_t r = rand()%sizeof(tones); 
        beep(500, tones[r]);
    }
}
