#include "c8051F020.h"
#include "Lumiere.h"
#include "Declarations_GPIO_BSE.h"
#include <stdio.h>


unsigned int etat_LED=0;
unsigned int cpt_cycles=0;
unsigned int RTC_5ms;
int Int;
int L_ON;
int L_OFF;
int L_Nbr;

void Lumiere(int Intensite, int Lum_ON, int Lum_OFF,int Lum_Nbr)
{
    RTC_5ms=0;
    Int=Intensite;
    L_ON=Lum_ON;
    L_OFF=Lum_OFF;
    L_Nbr=Lum_Nbr;
    PCA0CPM1=0xC2;// On lance le module 0 du PCA0
		TR2=1; // On lance le Timer2
}


void Lumiere_Stop(void)
{
	TR2=0; // On arrete le Timer2
	PCA0CPM1&=0x00;// On arrete le module 0 du PCA 0
	RTC_5ms=0;
}

void ISR_Timer2(void) interrupt 5
{
	long int valeur_intensite;
	// Compte le nombre d'incréments de RTC_5ms et réalise une RTC
	RTC_5ms++;
	
	if(cpt_cycles<L_Nbr) // Tant qu'on est inférieur au nombre de cycles
	{
		if(etat_LED==0) // Quand la LED est éteinte
		{
			if(RTC_5ms==20*L_OFF) //RTC_5ms compare avec une durée en dixieme de seconde (100 ms) -> Facteur 20 !
			{
				etat_LED=1; // On allume la LED
				PCA0CPM1=0xC2;// On lance le module 0 du PCA0 avec la bonne intensite
				valeur_intensite=(100-Int)*65536/100;
				PCA0CPH1 = valeur_intensite>>8;
				RTC_5ms=0; // On remet le compteur à 0 pour le comptage de l'état haut
			}
		}
		else
		{
			if(RTC_5ms==20*L_ON) //RTC_5ms compare avec une durée en dixieme de seconde (100 ms) -> Facteur 20 !
			{
				etat_LED=0; // On éteint la LED
				PCA0CPM1&=0x00;// On arrete le module 0 du PCA 0
				RTC_5ms=0; // On remet le compteur à 0 pour le comptage de l'état bas
				cpt_cycles++; // On compte un cycle
			}
			
		}
	}
	else
	{
		// On arrete le Timer, on atteint le bon nombre de cycles
		TR2=0;
		ET2=0; 
	}
	
	TF2=0;

}


