//-----------------------------------------------------------------------------------------------------------
// Main.c
//-----------------------------------------------------------------------------------------------------------
//
// AUTH: Edouard Mior
// DATE: 02/03/2017
//
// Target: C8051F02x
// Tool chain: KEIL eval 'c'

//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include "C8051F020.h"
#include "Declarations_GPIO_BSE.h"
#include "CMD_Servomoteur.h"
#include <stdio.h>
#include "intrins.h"
#include "CFG_Globale.h"
#include <math.h>
#include "LIB_BSE_UART.h"
int temps_dep_servomoteur_h;


void main(void)
{
 
	Reset_Sources_Init();
		
	Sysclk_Init();
	Config_PCA0();
	Port_IO_Init();
	
	
  temps_dep_servomoteur_h=CMD_Servo_H (-90); // Sortie sur port 1.1
	while(1)
	{
	
	}
}
