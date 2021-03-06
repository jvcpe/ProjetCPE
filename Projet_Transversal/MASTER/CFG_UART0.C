//------------------------------------------------------------------------------------
// CFG_UART0.c
//------------------------------------------------------------------------------------
//
// AUTH: 
// DATE: 
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Configuration de l'UART0
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include <CFG_UART0.h>                 
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------

void Config_UART0(void)
{
	//config de la clock
	RCLK0=0; //Le Timer 1 est utilis� pour la r�ception de l'UART0
	TCLK0=0; //Le Timer 1 est utilis� pour la transmission de l'UART0
	PCON|=0x80; //UART0 baud rate divide-by-two d�sactiv�
	
	//config de l'UART0
	PCON&=0xbf; //SSTAT=0
	SCON0|=0x60; //UART0 en mode 8-Bit (avec bit de stop) avec Baud Rate variable.
	SCON0&=0x6C; //RAZ du flag de r�ception
	SCON0|=0x10; //On active l'UART0
	TI0=1;  //Mise a 1 du flag de transmission
}
