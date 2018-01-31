/* 
 * File:    melodies.h   
 * Author:  c.rost
 * Comments:  headerfile for melodies.c with basic functions on what kind of melodies are given
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef MELODIES_H
#define	MELODIES_H


// Comment a function and leverage automatic documentation with slash star star
/**
    <p><b>Function prototype:</b></p>
  
    <p><b>Summary:</b></p>

    <p><b>Description:</b></p>

    <p><b>Precondition:</b></p>

    <p><b>Parameters:</b></p>

    <p><b>Returns:</b></p>

    <p><b>Example:</b></p>
    <code>
 
    </code>

    <p><b>Remarks:</b></p>
 */
// TODO Insert declarations or function prototypes (right here) to leverage 
// live documentation

#ifdef	__cplusplus
extern "C" {
#endif /* __cplusplus */
    
void playIncA(void);
void playIncB(void);
void playIncSw(void);
    
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
void playDAccord(void);

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
void  playRandomMelody( void );



#endif	/* MELODIES_H */

