//------------------------------------------------------------------------------------
// Decodage_AR.c
//------------------------------------------------------------------------------------

// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Decodage des commandes de la centrale de commande
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------            
#include <c8051f020.h>   
#include "parseur.h"  
//------------------------------------------------------------------------------------
// parseur.c
//------------------------------------------------------------------------------------
//
// AUTH: Groupe C4
// Date: 04/04/17
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Decodage des commandes de la centrale de commande
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
                 // SFR declarations
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Putchar_Getchar.h"
#include "CMD_Servomoteur.h"
#include "Detec_Obstacle.h"
#include "CFG_Timer1.h"
#include "SPI_Master.h"
#include "detection.h"
#include "bsscanf.h"
#include "EncodageM2.h"
//------------------------------------------------------------------------------------
// Global Constants
//------------------------------------------------------------------------------------
char buffer[100];
char taille=0;
char encours=0;
unsigned char vitesseDefaut = 20;
struct COMMANDES Struct_commandes;
struct INFORMATIONS Struct_info;
int X =0,Y=0, Z=0, Angle=0;
//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
void init_struct(void)
{
    Struct_commandes.Etat_Mouvement=Mouvement_non;
    Struct_commandes.Etat_ACQ_Son=ACQ_non;
    Struct_commandes.Etat_DCT_Obst=DCT_non;
    Struct_commandes.Etat_Lumiere=Lumiere_non;
    Struct_commandes.Etat_Servo=Servo_non;
    Struct_commandes.Etat_Energie=Energie_non;
    Struct_commandes.Etat_Position=Position_non;
    Struct_commandes.Etat_Photo=Photo_non;
	return;
}


void reception_commande(void)
{
	char carac;
	char i=0;
	taille=0;
	do {
		carac = Getchar(0);
		*(buffer+i) = carac;
		i++;
		taille++;
	} while(carac != '\r');	// tant que la fin de la commande n'est pas arrivée
	
	*(buffer+i) = '\0';
	 actionCommande();
}

void actionCommande(void)
{	
	char i=0;
	if(taille>0)
		{
			switch(buffer[0]){				
				case 'D': // D: Debut epreuve
					debut_epreuve();
					retour(1);
					break;
				
				case 'Q': // Q: Arret d'urgence
					arret_urgence();
					break;
				
				case 'A': // A: Avancer
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						avancer();
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;
					
				case 'B':
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						reculer();
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;
				
				case 'E':// E: Fin de l epreuve 
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						fin_epreuve();
						retour(1);
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;
                 
				case 'T'://TV: Reglage vitesse de deplacement
				    if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
						{
							int vit=0;
							sscanf(buffer, "TV %u\r", &vit);
							if (vit<5 || vit>100)
							{
								Send_String(0,"La valeur de vitesse de déplacement n'est pas comprise entre 5 et 100");
								retour(0);
								break;
							}
							else
							{
								sscanf(buffer, "TV %u\r", &vitesseDefaut);
							}			
							retour(1);
						}
						else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
				    break;
									 
				case 'S': // S: STOP: Fin des commandes de déplacement A et B de la base roulante
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						stop();
						retour(1);
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;

				case 'R': //commandes commençant par R	
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						switch(buffer[1]){					
							case 'D': // RD: Rotation droite
								rotation_90droite();
								retour(1);
								break;
								
							case 'G': // RG: Rotation gauche
								rotation_90gauche();
								retour(1);
								break;
								
							case 'C': // RC [D/G]: rotation complete de 180° par la droite (par défau) ou par la gauche 
								if(taille == 5) //si y a parametre
								{
									if(buffer[3]=='D')// si parametre est D=0x44
									{
									rotation_180droite();
									}
									else if(buffer[3]=='G')// si parametre est G=0x47
									{
									rotation_180gauche();
									}							
								}
								else if(taille==3) //si pas de parametre
								{
									rotation_180droite();
								}
								retour(1);
								break;
							
							case 'A': //RA [D/G]:[0-180] :rotation de la base roulante d'un angle donné
								rotation_RA();
								retour(1);
								break;
								
							default:
								retour(0);
						}
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;
				
				case 'G': // G X:x Y:y A:angle : Deplacement de la base roulante avec coordonées
                            // x et y ? [-99;99] et angle ? [-180;180]
                    if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
                    {
                        deplacement_coord();
												
											//depl_coord_obs();
											//Send_String(0,"B");
											retour(1);
                    }
                    else{
										Send_String(0,"Pas d'epreuve selectionnee");
										retour(0);
										}
                    retour(1);
                    break;
					
				case 'C': // CS [H/V] [A:Angle]: Pilotage du servomoteur
					if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
					{
						servomoteur();
					}
					else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					break;
				
				case 'M':
						if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
						{
							MOB();
							retour(1);
						}
						else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
					  break;
						
				case 'L': 
          
						if(Struct_commandes.Etat_Epreuve>=1 && Struct_commandes.Etat_Epreuve<=8)
							{
								lumiere();
								retour(1);
							}
						else{Send_String(0,"Pas d'epreuve selectionnee"); retour(0);}
						
						break;
						
				case 'N':
					detect();
				retour(1);
				break;
				
				default:
					retour(0);
				
				
			}
			
			for(i=0;i<100;i++)
			{	
				buffer[i]=0x0d;
			}
		}
}

void debut_epreuve()
{
	char msg[20]="Invite de commande ";
	int c_variable;
	int numEpreuve=0;
	sscanf(buffer,"D %d", &numEpreuve);
	Struct_commandes.Etat_Epreuve=numEpreuve;
	
	Struct_info.Etat_Invite=Invite_oui;
	Struct_info.MSG_Invit=msg;
	Struct_info.Tab_Val_Obst=&c_variable;
	Send_String(0,Struct_info.MSG_Invit);
	
	sprintf(msg, "%d", (int)Struct_commandes.Etat_Epreuve);
	Send_String(0, msg);
	return;
}

void avancer()
{

	int vitesse  = 0; 	// par défaut 

	Struct_commandes.Etat_Mouvement=Avancer;
	sscanf(buffer, "A %d\r", &vitesse);
	
	
	if (vitesse>=0 && vitesse <=100)
	{
		if (vitesse < 5)
		{
			Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
		}		
		else
		{
			Struct_commandes.Vitesse = (unsigned char)vitesse;
		}
		mouvement(Struct_commandes);
		retour(1);
	}
	else
	{
		retour(0);
	}
	
	
	return;
}

void reculer()
{
	int vitesse=0; 	// par défaut 

	Struct_commandes.Etat_Mouvement=Reculer;
	sscanf(buffer, "B %d\r", &vitesse);
	if (vitesse>=0 && vitesse <=100)
	{
		if (vitesse < 5)
		{
			Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
		}
		else
		{
			Struct_commandes.Vitesse = (unsigned char)vitesse;
		}
		mouvement(Struct_commandes);
		retour(1);
	}
	else
	{
		retour(0);
	}
	
	
	return;
}

void arret_urgence()
{

	stop();
	RSTSRC=0x10;
	return;
}

void fin_epreuve()
{
    Struct_commandes.Etat_Epreuve=Fin_Epreuve;
		Struct_info.Etat_Invite=Invite_non;
		Send_String(0,"Fin epreuve");
    return;
}
 
void stop()
{
    Struct_commandes.Etat_Mouvement=Stopper;
		mouvement(Struct_commandes);
    return;
}

void retour(char correct)
{
	if(correct==0)					//envoi du message de retour en fonction de la compréhension ou non de la commande
	{
		Putchar(0,0x0d);
		Putchar(0,0x0a);
		Putchar(0,0x23);
	}
	else
	{
		Putchar(0,0x0d);
		Putchar(0,0x0a);
		Putchar(0,0x3e);
	}
	return;
}

void rotation_90droite()
{
	Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
	Struct_commandes.Etat_Mouvement=Rot_90D;
	mouvement(Struct_commandes);
	return;
}
void rotation_90gauche()
{
	Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
	Struct_commandes.Etat_Mouvement=Rot_90G;
	mouvement(Struct_commandes);
	return;
}

void rotation_180droite()
{
	Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
	Struct_commandes.Etat_Mouvement=Rot_180D;
	mouvement(Struct_commandes);
	return;
}
void rotation_180gauche()
{
	Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
	Struct_commandes.Etat_Mouvement=Rot_180G;
	mouvement(Struct_commandes);
	return;
}

void rotation_RA()
{
	void * tab[40];
	int angle = 0;

	char GD = 'a';
	tab[0]=(void*)&GD;
	tab[1]=(void*)&angle;
	sscanf(buffer, "RA %c:%d", &GD, &angle);
	Struct_commandes.Vitesse = (unsigned char)vitesseDefaut;
	if (GD=='G')
		Struct_commandes.Etat_Mouvement=Rot_AngG;
	else
		Struct_commandes.Etat_Mouvement=Rot_AngD;

	Struct_commandes.Angle=angle;	

	mouvement(Struct_commandes);
	return;
}

void servomoteur()
{
	char HV='B';
	int angle=-90;
	char chaineCar[10];
	int i=0, temps_estime;	// pour attendre
	
	sscanf(buffer, "CS %c A:%d\n",&HV, &angle);
    //sscanf(buffer, "C%d", &angle);
	Struct_commandes.Servo_Angle = angle;	
	if (HV=='H')
		temps_estime=CMD_Servo_H(Struct_commandes.Servo_Angle);
       
	if(HV=='V')
    {
		envoi_trame(buffer,taille);
        
		//temps_estime=CMD_Servo_V(Struct_commandes.Servo_Angle);
    }
    
	else
	{
		Send_String(0,"Probleme etat_servo");
		return;
	}
	
    //char angle=-90;

	for (i=0; i<(16*temps_estime*10000);i++)
	{
		_nop_();
	}
	retour();
	sprintf(chaineCar,"AS %c", HV);
	Send_String(0,chaineCar);
    retour();
	return;
}

void MOB(void)
{
	int reso_angle = 30;
	char D='0';
	sscanf(buffer, "MOB %c A:%d", &D, &reso_angle);
	if (D=='D')
	{
		Struct_commandes.Etat_DCT_Obst = oui_180;
	}
	else
	{
		sscanf(buffer, "MOB A:%d", &reso_angle);
		Struct_commandes.Etat_DCT_Obst = oui_360;
	}
	
	Struct_commandes.DCT_Obst_Resolution = reso_angle;

	Struct_info = detection_obstacles(Struct_info,Struct_commandes);
	
	resultat_obstacles();
}

void detect(void)	
{
	char test[40];
	unsigned int Distance_AV=MES_Dist_AV ();
	sprintf(test, "Distance : %d\n", Distance_AV);
	
	Send_String(0, test);
}

void resultat_obstacles(void)
{
	char resultat[720];
	int pas = Struct_commandes.DCT_Obst_Resolution;
	int i = 0;
	int angle=0;
	int val=0;
	
	sprintf(resultat, "%s", "KOB");
	
	if (Struct_commandes.Etat_DCT_Obst == oui_180)
	{
		angle=-90;
		for (i=0; i<Struct_info.Nbre_Val_obst; i++)
		{
			sprintf(resultat, "%s %d:%u", resultat, angle+i*pas, *(Struct_info.Tab_Val_Obst+i));
		}
	}
	else if (Struct_commandes.Etat_DCT_Obst == oui_360)
	{
		angle=90;
		while(val>=-180)
		{
			val=angle-pas;
			if(val>=-180)
				angle=val;
		}
		for (i=0; i<Struct_info.Nbre_Val_obst; i++)
		{
			if(angle+i*pas<=180)
				sprintf(resultat, "%s %d:%u", resultat, angle+i*pas, *(Struct_info.Tab_Val_Obst+i));
		}
	}
	sprintf(resultat, "%s \n", resultat);
	
	Send_String(0, resultat);
}

void deplacement_coord()
{
    int X =0,Y=0,Angle=0;
    sscanf(buffer, "G X:%d Y:%d A:%d", &X,&Y, &Angle);
    //on avance ou recule
    if(Y >0) 
    {
        Struct_commandes.Coord_X=Y;
        Struct_commandes.Etat_Mouvement = Depl_Coord;
        mouvement(Struct_commandes);
    }
    else if(Y<0)
    {
			
			  Angle=Angle+180;
        Struct_commandes.Etat_Mouvement = Rot_180D;   
        mouvement(Struct_commandes);
			
			  pids();
			
        Struct_commandes.Coord_X=-Y;
        Struct_commandes.Etat_Mouvement = Depl_Coord;   
        mouvement(Struct_commandes);
    }
     
    //On attend la fin de déplacement
    pids();
     
    //on fait une rotation droite ou gauche
    if(X >0)
    {
        Angle=Angle+90;
        Struct_commandes.Etat_Mouvement = Rot_90D;
        mouvement(Struct_commandes);
    }
    else if(X<0)
    {
        Angle=Angle-90;
				X=-X;
        Struct_commandes.Etat_Mouvement = Rot_90G;  
        mouvement(Struct_commandes);
    }
     
    //On attend la fin de rotation
    pids();
     
    //on avance si nécessaire
    if(X!=0)
    {
        Struct_commandes.Coord_X=X;
        Struct_commandes.Etat_Mouvement = Depl_Coord;
        mouvement(Struct_commandes);
    }
     
    //On attend la fin de déplacement
    pids();
     
    //on fait une rotation droite ou gauche d'un angle donné
    if(Angle<0)
    {
        Angle=-Angle;
        Struct_commandes.Angle=Angle;
        Struct_commandes.Etat_Mouvement = Rot_AngD; 
        mouvement(Struct_commandes);
    }
    else if(Angle>0)
    {
        Struct_commandes.Angle=Angle;
        Struct_commandes.Etat_Mouvement = Rot_AngG;
        mouvement(Struct_commandes);    
    }
     
    //On attend la fin de rotation
    pids();
		
    //Struct_info.Etat_BUT_Mouvement=BUT_Atteint_oui;
    Send_String(0,"B\n");
     
}

void depl_coord_obs (void)
{
	int Xobs=0,Yobs=0;
	int dist_detec=10; //en dm
	int dist_secu=2.5; // en dm
	int reso_angle=30;
	
	char test[40];
	
	X=0,Y=0,Z=0,Angle=0;
	
	
	sscanf(buffer, "G X:%d Y:%d A:%d", &X,&Y, &Angle);
	Send_String(0,"DEBUT\n");
	while(X!=0 || Y!=0)
		
		{
						
			if(Y<0) //si Y<0 on fait un demi-tour
			{	
				//Send_String(0,"0\n");
				Y=-Y;	
				X=-X;
				Angle=Angle+180;
        Struct_commandes.Etat_Mouvement = Rot_180D;   
        mouvement(Struct_commandes);		
			  pids();
			}
			
			//Detection des Obstacles:
			Struct_commandes.Etat_DCT_Obst = oui_180;
			Struct_commandes.DCT_Obst_Resolution = reso_angle;
			Struct_info = detection_obstacles(Struct_info,Struct_commandes);
			 
			Yobs=*(Struct_info.Tab_Val_Obst+3)*0.1;
			sprintf(test,"Capteur 1 : %d\n",*(Struct_info.Tab_Val_Obst+2));
			Send_String(0,test);
			sprintf(test,"Capteur 2 : %d\n",*(Struct_info.Tab_Val_Obst+3));
			Send_String(0,test);
			sprintf(test,"Capteur 3 : %d\n",*(Struct_info.Tab_Val_Obst+4));
			Send_String(0,test);
			
			
			
			
			//gestion des déplacements

			if(*(Struct_info.Tab_Val_Obst+3)>(dist_detec*10)) //MES_Dist_AV()
			{
				Send_String(0,"obs>1m\n");
				if(Y>=dist_detec) //si Y superieur ou  égale à la distance de détection maximale du capteur, On deplace le robot de la distance maximale de detection
				{	
					Send_String(0,"Y>1m\n");
					Struct_commandes.Coord_X=dist_detec;
					Struct_commandes.Etat_Mouvement=Depl_Coord;
					Y=Y-dist_detec;
					mouvement(Struct_commandes);
					pids();
					
					
				}
				else				// si Y est inférieur à la distance de détection maximale du capteur, on deplace le robot de la distance Y, puis on tourne si nécessaire
				{
					Send_String(0,"y<1m\n");
					Struct_commandes.Coord_X=/*(unsigned char)*/Y;
					Struct_commandes.Etat_Mouvement=Depl_Coord;
					Y=0;
					mouvement(Struct_commandes);
					pids();
					choix_rotation(); //on tourne
									
				}
			}
			else
			{
				Send_String(0,"obs<1m\n");
				if ( Y>=(Yobs))//-dist_secu) ) //si Y (le point d'arrivée) est derriere l'obstacle, on avance jusqu'a l'obstacle, puis on tourne si nécessaire
				{
					Send_String(0,"algo evitement\n");
					if(X==0)
					{
						Send_String(0,"3\n");
					  Yobs=Yobs-dist_secu;
					  Struct_commandes.Coord_X=Yobs;
					  Struct_commandes.Etat_Mouvement=Depl_Coord;
					  Y=Y-Yobs;
					  mouvement(Struct_commandes);
					  pids();
					
					  Angle=Angle+90;
						Struct_commandes.Etat_Mouvement=Rot_90D;
						mouvement(Struct_commandes);
						pids();			
						Z=X; // on switch X et Y car on a tourné et qu'on fait les if uniquement sur Y (lorsqu'on avance)
						X=-Y;
						Y=Z;
						
						Struct_commandes.Coord_X=4;
					  Struct_commandes.Etat_Mouvement=Depl_Coord;
					  mouvement(Struct_commandes);
					  pids();
						
						
						Angle=Angle-90;
						Struct_commandes.Etat_Mouvement=Rot_90G;
						mouvement(Struct_commandes);
						pids();
						Z=X;
						X=Y;
						Y=-Z;
												
							
						Struct_commandes.Coord_X=8;
					  Struct_commandes.Etat_Mouvement=Depl_Coord;
					  Y=Y-8;
					  mouvement(Struct_commandes);
					  pids();
						
						Angle=Angle-90;
						Struct_commandes.Etat_Mouvement=Rot_90G;
						mouvement(Struct_commandes);
						pids();
						Z=X;
						X=Y;
						Y=-Z;
										
						Struct_commandes.Coord_X=4;
					  Struct_commandes.Etat_Mouvement=Depl_Coord;
					  mouvement(Struct_commandes);
					  pids();
						
						Angle=Angle+90;
						Struct_commandes.Etat_Mouvement=Rot_90D;
						mouvement(Struct_commandes);
						pids();			
						Z=X; // on switch X et Y car on a tourné et qu'on fait les if uniquement sur Y (lorsqu'on avance)
						X=-Y;
						Y=Z;
						
						
						
					}
					else
					{
						//Send_String(0,"3bis\n");
						Yobs=Yobs-dist_secu;
						Struct_commandes.Coord_X=Yobs;
						
					
						Struct_commandes.Etat_Mouvement=Depl_Coord;
						Y=Y-Yobs;
						mouvement(Struct_commandes);
						pids();
					
					  choix_rotation(); //on tourne
					}
					
				}
				else   //si Y (le point d'arrivée) est devant l'obstacle, on avance puis on tourne si nécessaire
				{
					Send_String(0,"pas evitement\n");
					//Send_String(0,"4\n");
					Struct_commandes.Coord_X=Y;
					Struct_commandes.Etat_Mouvement=Depl_Coord;
					Y=0;
					mouvement(Struct_commandes);
					pids();
					choix_rotation(); //on tourne

				}
			}			
		}
		
		choix_rotation();
		Send_String(0,"B\n");
}

void choix_rotation()
{
	Send_String(0,"DEBUT ROTATION\n");
	if(X>0)         //si X>0 on tourne 90D
	{
		//Send_String(0,"5\n");
		Angle=Angle+90;
		Struct_commandes.Etat_Mouvement=Rot_90D;
		mouvement(Struct_commandes);
		pids();
		
		
		Z=X; // on switch X et Y car on a tourné et qu'on fait les if uniquement sur Y (lorsqu'on avance)
		X=-Y;
		Y=Z;
	}
	else if(X<0)   //si X<0 on tourne 90G
	{
		//Send_String(0,"6\n");
		Angle=Angle-90;
		Struct_commandes.Etat_Mouvement=Rot_90G;
		mouvement(Struct_commandes);
		pids();
		Z=X;
		X=Y;
		Y=-Z;
	}
	else if(X==0) // si X=0 on met le robot à l'angle demandé en commande
	{
		//Send_String(0,"7\n");
		if(Angle>0)
		{
		Struct_commandes.Angle=Angle;
		Struct_commandes.Etat_Mouvement=Rot_AngG;
		mouvement(Struct_commandes);
		pids();			
				Angle=0;
		}
		else if(Angle<0)
		{
		Angle=-Angle;
		Struct_commandes.Angle=Angle;
		Struct_commandes.Etat_Mouvement=Rot_AngD;
		mouvement(Struct_commandes);
		pids();	
			Angle=0;
		}
	}
}

void lumiere()
{
    char Int=0;
    char L_ON=0;
    char L_OFF=0;
    char L_Nbr=0;
    
    
    sscanf(buffer, "L I:%d D:%d E:%d N:%d",&Int, &L_ON, &L_OFF, &L_Nbr);
    
    envoi_trame(buffer,taille);
    retour();
}
