///////////////////////////////
//CFG_UART1.c
///////////////////////////////

//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-M2
#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "CFG_UART1.h"

void config_uart1()
{
		
		T4CON|=0x30; //Le Timer 4 est utilisé pour la transmission et reception de l'UART1

		PCON	&= 0xF7;	// SSTAT1=0
		PCON	|= 0x10;	// Désactive la division par 2 du BAUDRATE
	
		SCON1 &= 0x7F;
		SCON1 |= 0x40;	// passe l'UART1 en mode 1
		SCON1 |= 0x20;	// pour vérifier qu'il y a un bit de stop
		
		SCON1 &= 0xFC;	// clear les 2 flags
		SCON1 |= 0x10;	// active l'uart1
	
		SCON1 |= 0x02;	// passe TI1 à 1
}
	