///////////////////////////////
//CFG_TIMER4.c
///////////////////////////////

//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-M2
#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "CFG_TIMER4.h"

void config_timer4()
{
		CKCON |= 0x40;
	
		T4CON |= 0x30; // on passe les bits 4 et 5 à 1 pour fonctionner en baud generator
		T4CON &= 0x7F;	// clear le flag d'overflow du timer 4
		EIE2 &= 0xFB;		// désactive les interruptions de T4
	
		RCAP4H = 0xff;	// valeur de rechargement pour baudrate=19200
		RCAP4L = 0xdc;	// on met 36 parce qu'il faut faire 65500 coups d'horloge
		
		T4CON |= 0x04;	// active le timer
}
