///////////////////////////////
//SPI_Master.h
///////////////////////////////
//AUTH: 
//DATE: 29/03/2016
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1
 
#ifndef SPI_MASTER_H
#define SPI_MASTER_H
 
#define carac_debut 0xBB
#define carac_fin 0xFF

unsigned char putchar_spi(unsigned char c);	// envoie un octet sur la liaison SPI
void envoi_trame(unsigned char *trame,int taille);	// envoie une trame sur la liaison SPI
#endif




/*
enum Lumiere {Lumiere_non, Allumer, Eteindre};

struct COMMANDES_POINTEUR 	// la structure à envoyer vers la carte slave, ne concerne que le pointeur lumineux (pour le moment ?)
{    
	enum  Lumiere Etat_Lumiere;     // Contient la commande d'allumage du pointeur lumineux "L" "LS"
                                   // Paramètres de la commande précédente:     
   BYTE  Lumiere_Intensite;        // Paramètre intensité lumineuse 							  
   BYTE  Lumiere_Duree;            // Paramètre durée d'allumage
   BYTE  Lumire_Extinction;        // Paramètre durée d'extinction
   BYTE  Lumiere_Nbre;             // Paramètre nombre de cycles d'allumage/extinction
};
*/
//unsigned char* serialize_struct(struct COMMANDES_POINTEUR c);	// transforme une struct en tableau de char

//void envoie_struct(struct COMMANDES_POINTEUR c); // appelle les fonctions précédentes pour envoyer une commande