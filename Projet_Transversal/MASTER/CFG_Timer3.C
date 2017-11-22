//------------------------------------------------------------------------------------
// CFG_Timer3.c
//------------------------------------------------------------------------------------
//
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Configuration du Timer 3
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>
#include "CFG_Timer3.h"
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
//-----------------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------------------
unsigned char T3_5ms=0;

//-----------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------------

void Config_Timer3(void)
{
	TMR3CN&=0x78;
	
	TMR3RLL=0xF6;
	TMR3RLH=0xDB;
	TMR3H=TMR3RLH; // valeur de départ du timer
	TMR3L=TMR3RLL;

	EIP2&=0xFE; // interruption priorité basse
	EIE2|=0x01;	// interruption autorisée
	TMR3CN |= 0x04;	// on démarre le timer 3
}


void ISR_Timer3(void) interrupt 14
{
	// Compte le nombre d'incréments de T3_5ms
	T3_5ms++;
	
	TMR3CN&=0x7F;

}