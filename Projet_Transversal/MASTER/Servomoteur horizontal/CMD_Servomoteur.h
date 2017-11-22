
//-------------------------------------------------------------------------------------
// CFG_Timer0.h
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
// Broches utilisées : P1.4, P1.5
//
//
// Documents utiles : Extraits de la Datasheet du C8051F020

void tempo_servo(unsigned char temps);
#ifndef CFG_PCA0
#define CFG_PCA0

void Config_PCA0(void);
unsigned char CMD_Servo_H (char Angle);
unsigned char CMD_Servo_V (char Angle);


#endif