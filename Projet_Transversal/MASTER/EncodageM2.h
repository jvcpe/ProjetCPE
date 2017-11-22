//------------------------------------------------------------------------------------
// Encodage.h
//------------------------------------------------------------------------------------
//
// AUTH: 
// DATE: 
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------

#ifndef STRUCT_H
#define STRUCT_H
	
	#include "STRUCT_COMMANDES_MASTER.h"
	#include "STRUCT_COMMANDES_SERIALIZER.h"

	

#endif

#ifndef ENCODAGE_H
#define ENCODAGE_H
char* encode(struct COMMANDES_SERIALIZER c);	// transforme la struct en commande
char* getReponse(void); 	// attend la rÃ©ponse de la carte et la renvoie
struct INFORMATIONS_SERIALIZER decode(char *reponse);	// transforme la reponse ascii de la carte en struct
struct INFORMATIONS_SERIALIZER envoyerStruct(struct COMMANDES_SERIALIZER c);	// envoie la struct aprÃ¨s avoir appelÃ© encode, (puis send_string), rÃ©cupÃ¨re la rÃ©ponse

void mouvement(struct COMMANDES commande);	//techniquement fait partie de M5, Ã  appeler si commande.Etat_Mouvement != Mouvement_non
void pids (void);
#endif



