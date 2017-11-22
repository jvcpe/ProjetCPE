
#include "CFG_UART0.h"
#include "CFG_GPIO.h"
#include "parseur.h"
#include "CFG_Timer1.h"
#include "CFG_SPI_master.h"
#include "SPI_Master.h"
#include <string.h>



void Reset_Init(void) //Initialisation des resets
{
	EA = 0; //D�sactivation des interruptions
	WDTCN = 0xDE; //D�sactivation du Watchdog;
	WDTCN = 0xAD;
	EA = 1; //On remet les interruptions;
}

void CFG_Sysclk(void) //Initialisation de l'horloge du systeme
{
	int i;
	OSCXCN = 0x67; //On a des quartz de fr�quence f>6.7Mhz
	for(i=0; i<3000; i++); //Attente d'une 1ms minimum
	while((OSCXCN & 0x80)==0); //Attente de la stabilisation du quartz
	OSCICN = 0x08; //On r�oriente l'horloge interne vers l'horloge exterxne.
}

void Port_IO_Init(void)  // Initialisation des ports d'entr�e sortie
{	
		P1MDOUT   = 0x07;
		XBR0      = 0x1E;
	 // XBR0      = 0x07;
		XBR1      = 0xAA;
		XBR2      = 0x4C;

}

void Init_Device (void) //Initialisation du microcontroleur
{
	Reset_Init();				// Appel des diff�rentes fonctions pour l'initialisation du microcontroleur
	
	CFG_Sysclk(); 							
	Config_GPIO();
	Config_Timer1();	
	//config_INT6();
	Config_UART0();
	Config_PCA0();
    FO_M4_init();
    Port_IO_Init();
    config_spi_master();
    
    
}



void main(void)
{
  char c[]="CS V A:-60";
	
	int taille;
	struct INFORMATIONS informations;
	struct COMMANDES commandes;
	Init_Device();
	init_struct();
	commandes.Etat_DCT_Obst=oui_180;
	commandes.DCT_Obst_Resolution=30;
	//informations=detection_obstacles(commandes);
   // taille=strlen(c);
    //envoi_trame(c,taille); 
    
   
    
	while(1)
	{
		 //envoi_trame(c,taille);
						//taille=strlen(c);
            //envoi_trame(c,taille);
        reception_commande();

	}
}