/*
 * File:   melodies.c
 * Author: chrissi
 *
 * Created on January 28, 2018, 10:48 PM
 */


#include "melodies.h"
#include "music.h"
#include "../../drivers/digitalIO.h"
#include <time.h>
#include <stdlib.h>
#include <stdint.h>

/*********************************************************************
* Function: void playDAccord
*
* Overview: plays two notes, 2nd higher than first to signalize that system
 * realized input
 * because LEDs are broken we have to improvize
*
* PreCondition: none
*
* Input: - none -
*
* Output: - none -
*
********************************************************************/
void playDAccord(void){
        beep(200, NOTE_C3);
        beep(600, NOTE_G3);    
}

void playIncA(void){
        beep(200, NOTE_A3);
        beep(600, NOTE_B3);    
}
void playIncB(void){
        beep(200, NOTE_B3);
        beep(600, NOTE_D3);    
}
void playIncSw(void){
        beep(200, NOTE_E3);
        beep(600, NOTE_D3);    
}

/*********************************************************************
* Function: void playRandomMelody
*
* Overview: plays a really horrible melody by random numbers out of an array of 
* notes - these should really be changed to better ones
*
* PreCondition: none
*
* Input: - none -
*
* Output: - none -
*
********************************************************************/


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
