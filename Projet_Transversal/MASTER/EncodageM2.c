//------------------------------------------------------------------------------------
// EncodageM2.c
//------------------------------------------------------------------------------------
//
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Encodage des commandes à envoyer vers la serializer
//------------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------
#include <c8051f020.h>
#include "EncodageM2.h" 
#include <stdio.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include <string.h>
#include "Putchar_Getchar.h"

enum Commande derniereCommande;         

char* encode(struct COMMANDES_SERIALIZER c)
{
	char reponse[40];
	
	switch (c.Etat_Commande) 
	{
		case Reset:
			strcpy(reponse, "reset\r");
			break;
		
		case Getenc_1:
			strcpy(reponse, "getenc 1\r");
			break;
		case Getenc_2:
			strcpy(reponse, "getenc 2\r");
			break;
		case Getenc_1_2:
			strcpy(reponse, "getenc 1 2\r");
			break;
			
		case Clrenc_1:
			strcpy(reponse, "clrenc 1\r");
			break;
		case Clrenc_2:
			strcpy(reponse, "clrenc 2\r");
			break;
		case Clrenc_1_2:
			strcpy(reponse, "clrenc 1 2\r");
			break;
			
		case mogo_1:
			sprintf(reponse, "mogo 1:%d\r",(int) c.Vitesse_Mot1);
			break;
		case mogo_2:
			sprintf(reponse, "mogo 2:%d\r",(int) c.Vitesse_Mot1);
			break;
		case mogo_1_2:
			sprintf(reponse, "mogo 1:%d 2:%d \r\0", (int)c.Vitesse_Mot1,(int) c.Vitesse_Mot2);
			break;
			
		case Vpid_set:
			sprintf(reponse, "vpid %d:%d:%d:%d\r", (int)c.Set_P,(int)c.Set_I, (int)c.Set_D, (int)c.Set_L_A);
			break;
		
		case Vpid_read:
			strcpy(reponse, "vpid\r");
			break;
			
		case digo_1:
			sprintf(reponse, "digo 1:%d:%d\r", (int)c.Ticks_mot1,(int) c.Vitesse_Mot1);
			break;
		case digo_2:
			sprintf(reponse, "digo 2:%d:%d\r", (int)c.Ticks_mot2,(int) c.Vitesse_Mot2);
			break;
		case digo_1_2:
			sprintf(reponse, "digo 1:%d:%d 2:%d:%d\r",(int)c.Ticks_mot1, (int)c.Vitesse_Mot1,(int) c.Ticks_mot2,(int) c.Vitesse_Mot2);
			break;
			
		case Dpid_set:
			sprintf(reponse, "dpid %d:%d:%d:%d\r",(int) c.Set_P,(int) c.Set_I,(int) c.Set_D,(int) c.Set_L_A);
			break;
		
		case Dpid_read:
			strcpy(reponse, "dpid\r");
			break;
			
		case Rpid_Stinger:
			strcpy(reponse, "rpid s\r");
			break;
		
		case Pids:
			strcpy(reponse, "pids\r");
			break;
			
		case Stop:
			strcpy(reponse, "stop\r");
			break;
			
		case Vel:
			strcpy(reponse, "vel\r");
			break;
			
		case Restore:
			strcpy(reponse, "restore\r");
			break;
			
		default:	// pas normal
			break;
	}
	return reponse;
}

char* getReponse(void)
{
	char reponse[30];
	char carac;
	char i=0;
	
	do {
		carac = Getchar(1);	// attend la réponse de laserializer, UART1
		*(reponse+i) = carac;
		i++;
	} while(carac != '>');	// tant que la fin de la réponse n'est pas arrivée
	return reponse;
}

struct INFORMATIONS_SERIALIZER decode(char *reponse)
{
	struct INFORMATIONS_SERIALIZER info;
	
	switch (derniereCommande)
	{
		case Getenc_1:
			info.Etat_Response = Rep_getenc;
			sscanf(reponse, "%d %*s", (int*)&info.Read_Val_enc_1);
			break;
		case Getenc_2:
			info.Etat_Response = Rep_getenc;
			sscanf(reponse, "%d %*s", (int*)&info.Read_Val_enc_2);
			break;
		case Getenc_1_2:
			info.Etat_Response = Rep_getenc;
			sscanf(reponse, "%d %d %*s", (int*)&info.Read_Val_enc_1, (int*)&info.Read_Val_enc_2);
			break;
		
		case Vpid_read:
			info.Etat_Response = Rep_vpid;
			sscanf(reponse, "P:%d I:%d D:%d L:%d%*s", (int*)&info.Read_P, (int*)&info.Read_I, (int*)&info.Read_D, (int*)&info.Read_L_A);
			break;
			
		case Dpid_read:
			info.Etat_Response = Rep_dpid;
			sscanf(reponse, "P:%d I:%d D:%d A:%d%*s", (int*)&info.Read_P, (int*)&info.Read_I, (int*)&info.Read_D, (int*)&info.Read_L_A);
			break;
			
		case Pids:
			info.Etat_Response = Rep_pids;
			sscanf(reponse, "\r\n%c%*s", &info.Read_Pids);
			break;

		case Vel:
			info.Etat_Response = Rep_vel;
			sscanf(reponse, "%d %d %*s", (int*)&info.Read_Vitesse_mot1, (int*)&info.Read_Vitesse_mot2);
			break;			
	}
	return info;
}

struct INFORMATIONS_SERIALIZER envoyerStruct(struct COMMANDES_SERIALIZER c)
{
	char reponse[30];
	int i=0;
	struct INFORMATIONS_SERIALIZER info;
	derniereCommande = c.Etat_Commande; // pour savoir a quelle reponse s'attendre
	Send_String(1, encode(c));
	
	strcpy(reponse, getReponse());
	if (strcmp(reponse, "\r\nNACK\r\n>") != 0) 
	{
		info = decode(reponse);
	}
	else
	{
		Send_String(0,"NACK"); 
	}
	
	return info;
}

void pids()
{
    //char test[40];
    struct COMMANDES_SERIALIZER commandeSerializer;
    struct INFORMATIONS_SERIALIZER info;
     
    
    commandeSerializer.Etat_Commande = Pids;
    info = envoyerStruct(commandeSerializer);
    //sprintf(test,"Read_Pids : %d\n", (int)info.Read_Pids); // renvoie 29 = unit separator??
    //Send_String(0,test);
     
    while(info.Read_Pids!='0')
    {
        info = envoyerStruct(commandeSerializer);
        //sprintf(test,"Read_Pids : %d\n", info.Read_Pids);
        //Send_String(0,test);
    }
    
}

void mouvement(struct COMMANDES commande)	
{
	struct INFORMATIONS_SERIALIZER info; // pour examiner la réponse
	struct COMMANDES_SERIALIZER commandeSerializer;	// struct à envoyer à M2
	
	switch(commande.Etat_Mouvement)
	{
		
		case Avancer:
			commandeSerializer.Etat_Commande = mogo_1_2;	// on fait tourner les moteurs
			commandeSerializer.Vitesse_Mot1 = commande.Vitesse;	
			commandeSerializer.Vitesse_Mot2 = commande.Vitesse;		
			break;
		case Reculer:
			commandeSerializer.Etat_Commande = mogo_1_2;	// on fait tourner les moteurs
			commandeSerializer.Vitesse_Mot1 = -commande.Vitesse;	
			commandeSerializer.Vitesse_Mot2 = -commande.Vitesse;
			break;
			
		case Stopper:
			commandeSerializer.Etat_Commande = Stop;
			break;
			
		case Rot_90D:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = -500; 
			commandeSerializer.Ticks_mot2 = 500; 
			break;
		case Rot_90G:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = 500; 
			commandeSerializer.Ticks_mot2 = -500; 
			break;
			
		case Rot_180D:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = -1000; 
			commandeSerializer.Ticks_mot2 = 1000; 
			break;
		case Rot_180G:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = 1000; 
			commandeSerializer.Ticks_mot2 = -1000; 
			break;
			
		case Rot_AngD:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = -commande.Angle*5.5; // à tester, j'en sais rien
			commandeSerializer.Ticks_mot2 = commande.Angle*5.5; // à tester, j'en sais rien
			break;
		case Rot_AngG:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = 10; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = 10; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = commande.Angle*5.5; 
			commandeSerializer.Ticks_mot2 = -commande.Angle*5.5; 
			break;
			
		case Depl_Coord:
			commandeSerializer.Etat_Commande = digo_1_2;	// on fait tourner les 2 moteurs sur une certaine distance pour obtenir une rotation
			commandeSerializer.Vitesse_Mot1 = commande.Vitesse; //commande.Vitesse;	//le moteur 1 (gauche ?) tourne vers l'avant
			commandeSerializer.Vitesse_Mot2 = commande.Vitesse; //commande.Vitesse; // l'autre vers l'arrière
			commandeSerializer.Ticks_mot1 = commande.Coord_X*335; 
			commandeSerializer.Ticks_mot2 = commande.Coord_X*335; 
			break;
			
		default:	// pas normal
			break;
	}
	
	info = envoyerStruct(commandeSerializer);
}