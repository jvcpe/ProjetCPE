//------------------------------------------------------------------------------------
// CFG_Timer1.c
//------------------------------------------------------------------------------------
//
// AUTH: MAZOYER Thomas, THIRION Olivier
// DATE: 15/03
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Configuration du Timer 1
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>

#include <intrins.h>
#include <CFG_Timer1.h>

//-----------------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------------------


//-----------------------------------------------------------------------------------
// Functions
//------------------------------------------------------------------------------------

void Config_Timer1(void)
{
	CKCON&=0xef; //Timer 1 utilise SYSCLK/12
	
	TF1=0; //RAZ du flag d'overflow du Timer 1
	TMOD&=0x2f; //Timer 1 en mode timer et actif même si /INT1=0
	TMOD|=0x20; //Timer 1 en mode timer 8 bits avec auto-reload
	
	TH1=0xfa; //Valeur de reload pour avoir Baud Rate = 19200 (voir Datasheet)
	TL1=TH1; //On intitialise le timer 1 pour qu'il commence au bon endroit
	
	ET1=0; //Invalidation interruption du Timer 1
	TR1=1; //Activation Timer 1
}

