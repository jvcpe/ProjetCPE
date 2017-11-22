#include "c8051F020.h"
#include "CFG_PCA0.h"
#include "Declarations_GPIO_BSE.h"
#include <stdio.h>


void Config_PCA0(void)
{
		long int Temps_angle;
		// Choix de l'horloge - SYSCLK pour un cycle de 11,852 ms
		PCA0MD |= 0x02;  
		PCA0MD &= ~0x0C;
		
	
		// Mode PWM 16-bit
	  PCA0CPM0=0xC2;
		PCA0CPM1=0xC2;
	
	
		// Rapport cyclique
		Temps_angle=1500;
		PCA0CPH0 = ((100-(Temps_angle*100))/11851)*65536/100>>8; // Sortie sur port 1.0
		PCA0CPH1 = ((100-(Temps_angle*100))/11851)*65536/100>>8; // Sortie sur port 1.1

		// Lance le comptage du PCA0
		PCA0CN |= 0x40;
}