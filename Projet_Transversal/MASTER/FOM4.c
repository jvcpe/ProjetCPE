
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>
#include "FOM4.h"
#include "intrins.h"

sbit P3__4 = P3^4;
sbit P3__6 = P3^6;	


//------------------------------------------------------------------------------------
// Variables globales
//------------------------------------------------------------------------------------
static unsigned int temps=0;	//valeur du temps de l'echo pulse
static unsigned int interruption=0; //passe a 1 pendant la duree de l'interruption
static unsigned int front=0; //quand front=0, INT6 se declenche sur front montant, quand front=1, sur front descendant
unsigned int Mesure=0; //quand mesure=1, la mesure est en cours, sinon il n'y a pas de mesure

//------------------------------------------------------------------------------------
//Initilisation generale du sous-module
//------------------------------------------------------------------------------------
void FO_M4_init()
{
    config_P3_FO_M4();
    Timer2_Init_FO_M4();
    Interrupt67_Init_FO_M4();
}

//------------------------------------------------------------------------------------
//Configuration des ports P3.4, P3.5, P3.6 et P3.7
//------------------------------------------------------------------------------------
void config_P3_FO_M4()
{    
  // P3.4  -  Unassigned,  Push-Pull,  Digital, telemetre Trigger
  // P3.6  -  Unassigned,  Open-Drain, Digital, telemetre echo

		P3MDOUT   = 0x10;
		XBR2      = 0x40;
	
}
//------------------------------------------------------------------------------------
//Configuration du Timer 2
//------------------------------------------------------------------------------------
/* Le Timer utilise le systeme de clock divise par 12, de telle sorte qu'il n'atteigne
 * jamais sa valeur de reload avant la fin du signal d'Echo Pulse. En effet, le timer 
 * se remet a zero au maximum au bout de 35.8ms, pour nous, le temps maximum que nous 
 * mesurons est de 25ms.
*/
void Timer2_Init_FO_M4()
{
  TL2       = 0x00;	//pour un premier cycle
  TH2       = 0x00;	//de bonne duree
}
//------------------------------------------------------------------------------------
//Configuration de l'interruptions 6
//------------------------------------------------------------------------------------
// Configure l'interruption 6 sur front montant de P3.6 et l'autorise.
void Interrupt67_Init_FO_M4()
{
    P3IF		 |= 0x04; //l'interruption 6 se declenche sur front montant de P3.6
	EIP2      = 0x10;
	P3IF &= 0xBF;
	EIE2      |= 0x10; //enable external interrupt 6
}
//------------------------------------------------------------------------------------
//Routine de l'interruption 6
//------------------------------------------------------------------------------------
/* Lorsque l'interruption se declenche sur front montant, elle se reconfigure pour se 
 * declencher sur front descendant et demarre le timer2. Lorsqu'elle se declenche sur
 * front descendant, elle se reconfigure sur front montant, recupere la valeur du timer,
 * l'arrete et le remet a zero.
*/
void ISR__EXT_INT6_FO_M4() interrupt 18
{
	if(front==0 && interruption==0)
	{
		interruption=1;
		TR2=1; //demarrage du timer2
		P3IF &= 0xFB; //l'interruption de declenche maintenant sur front descendant
		front=1;
	}
	
	if(front==1 && interruption==0)
	{
		interruption=1;
		TR2=0; //arret du timer
		
		temps=0xFF*TH2+TL2;
		TH2=0x00; //remise a 0 des valeurs 
		TL2=0x00; //du timer
		
		P3IF |= 0x04; //l'interruption se declenche sur front montant
		front=0;
	}
	interruption=0;
	P3IF &= 0xBF;
}

//------------------------------------------------------------------------------------
//Fonction qui se charge de la mesure avec le telemetre a l'avant
//------------------------------------------------------------------------------------
/*
*/

unsigned int MES_Dist(void)
{
	switch (Mesure){
	case 0:
		Pulse_P34();
		Mesure=1;
		return 60;

	case 1:
		Mesure=0;
		return temps*0.542f*(0.000001)*34000.0f/2.0f; //retourne la distance en centimetre
		
	default:
		return 0;
	}       
    
}

//------------------------------------------------------------------------------------
//Fonction qui declenche la mesure avec le telemetre
//------------------------------------------------------------------------------------
/* Envoie une pulsation de 10us sur la sortie P3.4 pour declencher une mesure de
 * distance du telemtre avant.
*/
void Pulse_P34()
{
	int i=0;
	P3__4=1;
	
	for(i=0;i<250;i++)
		_nop_();
	
	P3__4=0;
}

