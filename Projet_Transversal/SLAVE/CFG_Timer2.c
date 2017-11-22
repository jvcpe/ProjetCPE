//-------------------------------------------------------------------------------------
// CFG_Timer2.c
// Configuration et routine d'interruption du Timer2
//-------------------------------------------------------------------------------------
//AUTH: CASTELLO Maxime/MIOR Edouard
//DATE: 11/05/17
//
//
// Target: C8051F02x
// Tool chain: KEIL eval 'c'
//
// Objectifs : - Configuration du Timer 2
//						 - Routine d'interruption du Timer 2
//						 - Envoi d'une impulsion de largeur variable sur une sortie
//
//
// Documents utiles : Extraits de la Datasheet du C8051F020

//-----------------------------------------------------------------------------------------------------------
// Includes
//-----------------------------------------------------------------------------------------------------------
#include "c8051F020.h"
#include "Declarations_GPIO_BSE.h"
#include "CFG_Timer2.h"
#include <stdio.h>

void Config_Timer2()
{
        EA=0;                       // Désactivation des interruption
        CKCON &= 0xdf;  // MAZ bit6 - Tclk=SYSCLK/12
        TF2 = 0;            // RAZ drapeau TF2 - overflow (T2CON)
        EXF2=0;                 // RAZ flag EXF2 - drapeau externe du timer 2 (T2CON)
        EXEN2=0;                // Timer 2 enable (T2CON)
        CT2=0;                  // Mode Timer (T2CON)
        CPRL2=0;                // Mode autoreload (T2CON)
     
        // Valeur de préchargement 
        // Tick Time/Timer Period = 5ms/0.542us = 9225 -> (2409)H
        // RCAP = FFFF-2409 = DBF6 
        RCAP2L    = 0xF6;       
        RCAP2H    = 0xDB;
      //Chargement de la valeur de prechargement pour le premier cycle
        TL2       = 0xF6;
        TH2       = 0xDB;
         
        TR2=0;                  // Démarre le Timer (T2CON)
        PT2=1;                  // Priorité haute (IP)
        ET2=1;                  // Autorise les interruptions de Timer2 (IE)
     
        EA=1;                       // Autorise les interruptions (IE)	
	
}


