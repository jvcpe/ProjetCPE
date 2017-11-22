

//-------------------------------------------------------------------------------------
// CFG_Timer0.c
// Configuration et routine d'interruption du PCA0
//-------------------------------------------------------------------------------------
// AUTH: Mior Edouard
// DATE: 02/03/2017
//
// Target: C8051F02x
// Tool chain: KEIL eval 'c'
//
// Objectifs : - Configuration du PCA 0
//						 - Routine d'interruption du PCA 0
//						 - Envoi d'une impulsion de largeur variable sur une sortie
// 
// Broches utilisées : P1.0, P1.1
//
//
// Documents utiles : Extraits de la Datasheet du C8051F020




//-----------------------------------------------------------------------------------------------------------
// Variables globales
//-----------------------------------------------------------------------------------------------------------
 // Angle du servomoteur avant deplacement
 #include "c8051F020.h"
#include "Declarations_GPIO_BSE.h"
#include "CMD_Servomoteur.h"
#include <stdio.h>
#include <math.h>
 
char Angle_actuel_V=0;



unsigned char CMD_Servo_V (char Angle) //pour l’axe horizontal 
{
	long int Temps_angle, Temps_Estime;
	
	Temps_angle=600+(Angle+90)*10; // Temps en µs - Temps min : 600 µs - Temps max : 2400 µs
	
	// Calcul de la valeur de rechargement pour le PWM
	// Duty_cycle=Temps_angle/11851 avec 11851 le temps en ms d'une période
	// On multiplie par 100 pour le domaine du rapport cyclique
	// On multiplie par 65536 pour passer dans la base 16-bits
	// On divise par 100 pour avoir une valeur fidèle
	PCA0CPH0 = ((100-(Temps_angle*100))/11851)*65536/100>>8;
//	PCA0CPH1 = -(65536/11851)*temps_angle*1000>>8;
	
	// Calcul du temps estimé pour faire la rotation
	Temps_Estime=abs(Angle_actuel_V-Angle)*21/60; // cf datasheet 
	
	// Redéfinition de l'angle actuel
	Angle_actuel_V=Angle;
	
	return Temps_Estime;
}

