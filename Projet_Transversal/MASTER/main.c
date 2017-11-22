#include "c8051F020.h"
#include "CFG_UART0.h"
#include "CFG_GPIO.h"
#include "CFG_Timer3.h"
#include "parseur.h"
#include "Detec_Obstacle.h"
#include "detection.h"

#include "CFG_Timer1.h"
#include "CFG_SPI_master.h"
#include "SPI_Master.h"
#include "CMD_Servomoteur.h"

#include <string.h>

#include "CFG_UART1.h"
#include "CFG_TIMER4.h"
#include "Putchar_Getchar.h"

//#include "detection.h"


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
	Config_GPIO();
	Config_Timer1();
	Config_Timer3();
//	Config_Timer2();	
	config_timer4();
	//config_INT6();
	Config_UART0();
	Config_PCA0();
  FO_M4_init();
  Port_IO_Init();
  config_spi_master();
	config_uart1();

	init_struct();
    
}



void main(void)
{

	Init_Device();
    
	while(1)
	{
		 //envoi_trame(c,taille);
						//taille=strlen(c);
            //envoi_trame(c,taille);
        reception_commande();

	}
}
