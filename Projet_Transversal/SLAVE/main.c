#include "c8051F020.h"
#include "CFG_SPI_Slave.h"
#include "CMD_Servomoteur.h"
#include "SPI_Slave.h"
#include "CFG_UART0.h"
#include "Putchar_Getchar.h"
#include "CFG_Timer1.h"
#include "CFG_PCA0.h"
#include "CFG_Timer2.h"
#include "Lumiere.h"


void Reset_Init(void) //Initialisation des resets
{
	EA = 0; //Désactivation des interruptions
	WDTCN = 0xDE; //Désactivation du Watchdog;
	WDTCN = 0xAD;
	EA = 1; //On remet les interruptions;
}

void CFG_Sysclk(void) //Initialisation de l'horloge du systeme
{
	int i;
	OSCXCN = 0x67; //On a des quartz de fréquence f>6.7Mhz
	for(i=0; i<3000; i++); //Attente d'une 1ms minimum
	while((OSCXCN & 0x80)==0); //Attente de la stabilisation du quartz
	OSCICN = 0x08; //On réoriente l'horloge interne vers l'horloge exterxne.
}

void Port_IO_Init(void)  // Initialisation des ports d'entrée sortie
{	
		P1MDOUT   = 0x07;
		XBR0      = 0x1E;
	 
		XBR1      = 0xAA;
		XBR2      = 0x4C;

}

void Init_Device (void) //Initialisation du microcontroleur
{
		Reset_Init();				// Appel des différentes fonctions pour l'initialisation du microcontroleur
		CFG_Sysclk();
    Port_IO_Init();
    Config_Timer1();
    Config_PCA0();
    Config_UART0();
    config_spi();
    initialise_buffer();
    Config_Timer2();
	
}



void main(void)
{
    Init_Device();
    
    while(1)
    {
        
    }
        
}