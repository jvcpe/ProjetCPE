//------------------------------------------------------------------------------------
// CFG_UART0.c
//------------------------------------------------------------------------------------
//
//AUTH: CASTELLO Maxime/MIOR Edouard
//DATE: 11/05/17
//
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Configuration de l'UART0
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>
#include <CFG_UART0.h>    
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void Config_UART0(void)
{
	//config de la clock
	RCLK0=0; //Le Timer 1 est utilisé pour la réception de l'UART0
	TCLK0=0; //Le Timer 1 est utilisé pour la transmission de l'UART0
	PCON|=0x80; //UART0 baud rate divide-by-two désactivé
	
	//config de l'UART0
	PCON&=0xbf; //SSTAT=0
	SCON0|=0x60; //UART0 en mode 8-Bit (avec bit de stop) avec Baud Rate variable.
	SCON0&=0x6C; //RAZ du flag de réception
	SCON0|=0x10; //On active l'UART0
	TI0=1;  //Mise a 1 du flag de transmission
}
