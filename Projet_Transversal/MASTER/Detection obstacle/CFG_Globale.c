#include <c8051f020.h>
#include "CFG_Globale.h"
//sbit BP = P3^7;  


void Reset_Sources_Init()  // désactivation du watch dog et activation des interruptions
{
	EA=0; //Disable all interrupts
	WDTCN=0xDE; //disable software watchdog timer
	WDTCN=0xAD; 
}

void Sysclk_Init(void)   // initialisation de l'horloge systeme
{
	
	int i;
	//OSCICN=0x08; //CLKSL=1 uses exit oscillator as syst clck
	
      OSCXCN    = 0x67;
    for (i = 0; i < 3000; i++);  // Wait 1ms for initialization
    while ((OSCXCN & 0x80) == 0);
    //OSCICN    = 0x08;
		OSCICN    = 0x0C;

	
}

void Port_IO_Init(void)  // Initialisation des ports d'entrée sortie
{
		P0MDOUT   =  0x01;
	  XBR0      = 0x04;
    XBR2      = 0x44;

    XBR2      = 0x44; // 44 si on veut UART1 enabled 40 sinon
	  P3        = 0xFF;

		XBR0      = 0x0E;
    XBR2      = 0x44;
    P3MDOUT   = 0x30;
		P1MDOUT   = 0x01;
	
	
	

}

void Init_Device(void)   //Cette fonction fait appelle aux autres fonctions d'initialisation du microcontroleur
{
	
	Reset_Sources_Init(); //Desactivation du Watchodog
	Sysclk_Init(); //Config de l'horloge systeme
	Port_IO_Init(); //Affectation des broches aux periphériques internes et config de ces broches
}		 



