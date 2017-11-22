#ifndef STRUCT_H
#define STRUCT_H
		#include "STRUCT_COMMANDES_MASTER.h"
	
	#include "STRUCT_COMMANDES_SERIALIZER.h"



#endif



#ifndef PARSEUR_H
#define PARSEUR_H


//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void reception_commande(void);
void actionCommande(void);
void retour(char correct);
void debut_epreuve(void);
void arret_urgence(void);
void avancer(void);
void reculer(void);
void init_struct(void);
void reglage_vitesse(char* vit);
void fin_epreuve(void);
void stop(void);
void servomoteur(void);
void rotation_90droite(void);
void rotation_90gauche(void);
void rotation_180droite(void);
void rotation_180gauche(void);
void rotation_RA(void);
void MOB(void);
void resultat_obstacles(void);
void lumiere();
void deplacement_coord(void);
void detect(void);
void depl_coord_obs(void);
void choix_rotation(void);

#endif




