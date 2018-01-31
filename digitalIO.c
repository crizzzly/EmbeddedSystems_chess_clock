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






//enabled change registers for buttons
void pinMode(uint16_t pin, uint8_t value){
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
             LED202_ANSEL = 0;
            LED202_TRIS = value ;
            LED202_CNEN = 0;
            LED202_CNPU = 0;
            LED202_CNPD = 0;
            break;
            
        case LED203:
             LED203_ANSEL = 0;
            LED203_TRIS = value ;
            LED203_CNEN = 0;
            LED203_CNPU = 0;
            LED203_CNPD = 0;
            break;
            
        case PZ200:
               //Piezo Output
            PIEZ_ANS = 0;   //analogSelect to digital
            PIEZ_TRIS = 0;  //I/O select as output
            PIEZ_CNEN = 0;  //no interrupt
            break; 


        case BTN200:
            BTN200_LAT  = 0;
            BTN200_TRIS = value;
            BTN200_CNEN = 1;
            BTN200_CNPU = 1;
            BTN200_CNPD = 0;
            
            IPC4bits.CNIP = 4;     //set interrupt priority 
            IEC1bits.CNIE = 1; 		// Enable CN interrupts
            IFS1bits.CNIF = 0; 		// Reset CN interrupt flag
            
            break;
            
        case BTN201:
            BTN201_TRIS = value;
            BTN201_CNEN = 1;
            BTN201_CNPU = 1;
            BTN201_CNPD = 0;
            BTN201_LAT  = 0;
            break;

            
        case BTN202:
            BTN202_TRIS = value;
            BTN202_CNEN = 1;
            BTN202_CNPU = 1;
            BTN202_CNPD = 0;
            BTN201_LAT  = 0;
            break;

            
        case BTN203:
            BTN203_TRIS = value;
            BTN203_CNEN = 1;
            BTN203_CNPU = 1;
            BTN203_CNPD = 0;
            BTN203_LAT  = 0;
            break;
            
            
               /*Input Capture 3, Vec: 45, IRQ: 37, IVT Adr: 0x00005E 	
            //flag at:IFS2<5>, enable at:IEC2<5>, prio:IPC9<6:4>            
            
            IC1  IFS0<1> 	IEC0<1>         IPC0<6:4>
            IFS0bits.IC1IF  IEC0bits.IC1IE  IC1IP

            IC7 IFS1<6>		IEC1<6>         IPC5<10:8>
            IFS1bits.IC7IF  IEC1bits.IC7IE  IC7IP
            IC8	IFS1<7> 	IEC1<7> 	IPC5<14:12>
            */
        case RSW204:
            RSW204_TRIS0 = 1;
            RSW204_CNPUG0 = 1;
            RSW204_CNENG0 =1;

            
            RSW204_TRIS1 = 1;
            RSW204_CNPUG1 = 1;
            RSW204_CNENG1 =1;
            
            RSW204_CNPUG9 = 1;
            RSW204_TRIS9 = 1;
            RSW204_ANS  = 0; 
            RSW204_CNENG9 =1;
           
            


        default:
  //          printf("this pin is not configured");
            break;
            
        }
                    
    }

    
uint8_t digitalRead(uint16_t pin){
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
            return ((BTN200_PORT == HIGH) ? false : true );

        case BTN201:
            return ((BTN201_PORT == HIGH) ? false : true );

        case BTN202:
            return ((BTN202_PORT == HIGH) ? false : true );

        case BTN203:
            return ((BTN203_PORT == HIGH) ? false : true );
        case INC_A:
            return((RSW204_INC_A == HIGH) ? true : false);
        case INC_B:
            return((RSW204_INC_B == HIGH) ? true : false);
            
        case INC_SW:
            return((RSW204_INC_SW == HIGH) ? true : false);
//        case RSW204:
//            return 
        default:
            //printf("this pin is not configured as input");
            break; 
    }
    return 0;
}
/*********************************************************************
* Function: int8_t readRotaryEncPulse();
*
* Overview: checks weather the val of inc_a has changed and if an 
 * direction switch has occured. if not returns 0
 * 
*
*
* Input: None
*
* Output: value: "  -1"  if direction is backwards 
 *        value:    1      if direction is forward
 *        value:    0       if nothing happened
*
********************************************************************/

int8_t readRotaryEncPulse(){
    bool inc_a = digitalRead(INC_A);
    while (inc_a == digitalRead(INC_A)){
        if(!digitalRead(INC_SW)){
            return 0; 
        }
    }
        
    //Returns -1 if rotating backwards and 1 if forwards
    if(!inc_a == digitalRead(INC_B)){
        return -1; 
    }
    else{
        return 1; 
    }
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
void digitalWrite(uint16_t pin, uint8_t value){
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
            //printf("this pin is not configured as output");
            break;
    }
}

void writeAllLED(uint8_t value){
    LATB &= 0xF0FF; // clear all four LEDs
    LATB |= (value << 8); // set bits again
}

/****************************************************
 Function:
 void initPiezo( void )

  Summary:
    Initializes Piezo     
  Description:
    Initializes the pins of piezo 
 *      ANSEL - analogSelect 0 = digital
 *      TRIS -  I/O select 0 = output
 *      CNEN -  enable interrupt 0 = no interrupts

  Precondition:
    The Timer peripheral must have been initialized for Timer 3.

  Parameters:
    None.

  Returns:
    None.

  Remarks:
    None
 
 **********************************************************************/    
//void initPiezo() {
    //Piezo Output
    //PIEZ_ANS = 0;   //analogSelect to digital
    //PIEZ_TRIS = 0;  //I/O select as output
    //PIEZ_CNEN = 0;  //no interrupt
//}


