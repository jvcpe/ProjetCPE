///////////////////////////////
//SPI_Slave.c
///////////////////////////////
//AUTH: CASTELLO Maxime/MIOR Edouard
//DATE: 11/05/17
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1

#include "c8051F020.h"
#include "SPI_Slave.h"
#include "Declarations_GPIO_BSE.h"
#include "CMD_Servomoteur.h"
#include <intrins.h> 
#include "Putchar_Getchar.h"
#include "Lumiere.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Variables globales
int taille_buffer=50;
char buffer[50];	// stocke les caractères reçus au fur et à mesure
int i_buffer=0;	// position dans le buffer
int cas=0;

int Intensite=0;
int Intensite_defaut=100; 
int Lum_ON=0;
int Lum_ON_defaut=99;
int Lum_OFF=0;
int Lum_OFF_defaut=0;
int Lum_Nbr=0;
int Lum_Nbr_defaut=1;

void fin_transfert() interrupt 6
{	
	char c;	
	// mise à zéro des flags
	SPIF=0;
	WCOL=0;
	MODF=0;

	RXOVRN=0;
		// on récupère le caractère dans le buffer de SPI 
	
	
	
    
    if(SPI0DAT!=0xFF && SPI0DAT!=0xBB )
		{
			c=SPI0DAT;
      ajout_caractere(c);
            
		}
	if(SPI0DAT==0xFF)
    {
        actionCommande();  
        initialise_buffer();
    }
		
}

void initialise_buffer()
{
	int i=0;
	for (i=0;i<taille_buffer;i++)
	{	
		buffer[i] =' ';
	}
	i_buffer=0;
}

void ajout_caractere(unsigned char c)
{	
	buffer[i_buffer] = c;	// on ajoute le caractère dans le buffer
	i_buffer++;	// on incrémente la position du pointeur
	
}


void actionCommande(void)
{	
	char i=0;
	int k=0;
	if(taille_buffer>0)
		{
      if(sscanf(buffer, "L I:%d D:%d E:%d N:%d\r",&Intensite, &Lum_ON, &Lum_OFF, &Lum_Nbr)==0);
			{
			Lumiere( Intensite_defaut, Lum_ON_defaut, Lum_OFF_defaut,Lum_Nbr_defaut);
			}         
			switch(buffer[0])
			{				
				case 'C':
					servomoteur();
					break;
				
				case 'L':
					switch(buffer[1])
					{	
						case 'S':
							Lumiere_Stop();
						break;
						
						case ' ':
							switch(buffer[2])
						  {												
								case 'D':
									cas=1;
									lum_ON_OFF();
								break;
								
								case 'I':
									cas=2;
									lum_ON_OFF();
								break;
								
							default:
								cas=0;
							}
							
						break;
					default:
						cas=0;
					}
				break;
				default:
					cas=0;
				}
			
    }   
}
    
void servomoteur()
{
	char HV='B';
	int angle=-90;
	char chaineCar[10];
	int i=0, temps_estime;	// pour attendre
 	if(sscanf(buffer, "CS %c A:%d",&HV, &angle)==2)
	{
		if(HV=='V')
			temps_estime=CMD_Servo_V((int)angle);
	}
	
		
	else
	{
		Send_String(0,"Probleme etat_servo");
		return;
	}
    
	for (i=0; i<(16*temps_estime*10000);i++)
	{
		_nop_();
	}
	sprintf(chaineCar,"AS %c", HV);

	return;
}

void lum_ON_OFF()
{
    Intensite=0;
		 
    Lum_ON=0;
		
    Lum_OFF=0;
		
    Lum_Nbr=0;
		
   
	if (cas==1){		
			if(sscanf(buffer, "L D:%d E:%d N:%d\r",&Lum_ON, &Lum_OFF, &Lum_Nbr)==3)
			{
				Lumiere( Intensite_defaut, Lum_ON, Lum_OFF,Lum_Nbr);
			}
		}

	else if (cas==2){
			
		if(sscanf(buffer, "L I:%d D:%d E:%d N:%d\r",&Intensite, &Lum_ON, &Lum_OFF, &Lum_Nbr)==4)
			{
				Lumiere( Intensite, Lum_ON, Lum_OFF,Lum_Nbr);
			}
		}
		return;
}
