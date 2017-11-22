// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
// GROUPE C4
//
// Date de modification: 25/04/2017
//
// Projet: Projet Transversal
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>                    // SFR declarations
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "Detec_Obstacle.h"


// Variables globales
int isHigh=0;
unsigned int High_Level_Time;
static unsigned int interruption=0; //passe a 1 pendant la duree de l'interruption
static unsigned int front=0; //quand front=0, INT6/INT7 se declenche sur front montant, quand front=1, sur front descendant

//------------------------------------------------------------------------------------
//Initilisation generale du sous-module
//------------------------------------------------------------------------------------
void FO_M4_init()
{
    //config_P3_FO_M4();
    Timer2_Init_FO_M4();
    Interrupt67_Init_FO_M4();
}

//------------------------------------------------------------------------------------
//Configuration des ports P3.4 et P3.6
//------------------------------------------------------------------------------------
void config_P3_FO_M4()
{
    // P3.3  -  Unassigned,  Push-Pull,  Digital, telemetre Trigger
    // P3.6  -  Unassigned,  Open-Drain, Digital, telemetre echo
    // P3.4  -  Unassigned,  Push-Pull,  Digital, telemetre Trigger
    // P3.7  -  Unassigned,  Open-Drain, Digital, telemetre echo
    
    XBR2      = 0x40;
    
}
//------------------------------------------------------------------------------------
//Configuration du Timer 2
//------------------------------------------------------------------------------------

void Timer2_Init_FO_M4()
{
    TL2       = 0x00;	//pour un premier cycle
    TH2       = 0x00;	//de bonne duree
}
//------------------------------------------------------------------------------------
//Configuration de l'interruptions 6
//------------------------------------------------------------------------------------
// Configure l'interruption 6/7 sur front montant de P3.6/P3.7 et l'autorise.
void Interrupt67_Init_FO_M4()
{
    P3IF     |= 0x0C; //les interruptions 6 et 7 se declenchent sur front montant de P3.6 et P3.7
    EIP2      = 0x10;
    P3IF     &= 0x3F;
    EIE2     |= 0x30; //enable external interrupt 6
}

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
        
        High_Level_Time=0xFF*TH2+TL2;
        TH2=0x00; //remise a 0 des valeurs
        TL2=0x00; //du timer
        
        P3IF |= 0x04; //l'interruption se declenche sur front montant
        front=0;
        isHigh=0;
    }
    interruption=0;
    P3IF &= 0xBF;
}

void ISR__EXT_INT7_FO_M4() interrupt 19
{
    if(front==0 && interruption==0)
    {
        interruption=1;
        TR2=1; //demarrage du timer2
        P3IF &= 0xF7; //l'interruption de declenche maintenant sur front descendant
        front=1;
    }
    
    if(front==1 && interruption==0)
    {
        interruption=1;
        TR2=0; //arret du timer
        
        High_Level_Time=0xFF*TH2+TL2;
        TH2=0x00; //remise a 0 des valeurs
        TL2=0x00; //du timer
        
        P3IF |= 0x08; //l'interruption se declenche sur front montant
        front=0;
        isHigh=0;
    }
    interruption=0;
    P3IF &= 0x7F;
}

unsigned int MES_Dist_AV (void) //pour le télémètre Avant
{
	unsigned int Distance=0;
	int i=0;
	// Déclenchement du télémètre : impulsion de 10µs sur P3.4
    Pulse_P33();
	
	// Attente pour tre sur que l'on rŽcupre la bonne valeur de High_Level_Time
	while(isHigh==1);
	
	Distance=High_Level_Time*0.542f*(0.000001)*34000.0f/2.0f;
	if (Distance >100) // Pas de detection d'objet ˆ plus de 100 cm
	{
		Distance=0;
	}
	return Distance;
}

unsigned int MES_Dist_AR (void) //pour le télémètre Avant
{
	unsigned int Distance=0;
	int i=0;
	// Déclenchement du télémètre : impulsion de 10µs sur P3.5
    Pulse_P34();
	
	// Attente pour tre sur que l'on rŽcupre la bonne valeur de High_Level_Time
	while(isHigh==1);
	
	Distance=High_Level_Time*0.542f*(0.000001)*34000.0f/2.0f;
	if (Distance >100) // Pas de detection d'objet ˆ plus de 100 cm
	{
		Distance=0;
	}
	return Distance;
}


void Pulse_P33()
{
    int i=0;
    P3__3=1;
    
    for(i=0;i<15;i++)
        _nop_();
    
    P3__3=0;
    isHigh=1;
}

void Pulse_P34()
{
    int i=0;
    P3__4=1;
    
    for(i=0;i<15;i++)
        _nop_();
    
    P3__4=0;
    isHigh=1;
}

	

