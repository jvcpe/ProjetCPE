///////////////////////////////
//SPI_Master.c
///////////////////////////////
//AUTH: 
//DATE: 29/04/2017
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1
 #include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include <string.h>
#include "SPI_Master.h"
#include "Putchar_Getchar.h"
/*
unsigned char* serialize_struct(struct COMMANDES_POINTEUR c)
{
	unsigned char *data;
    data = (unsigned char*) malloc(sizeof(c));
    memcpy(data, &c1, sizeof(c));
	
	return data;
}
*/
unsigned char putchar_spi(unsigned char c)
{
	int i = 0;
	while (!SPIF);		// on attend la fin du dernier transfert
	SPIF = 0; // on remet le flag à 0	
	
	P3__5 = 0; // NSS			
	_nop_();
	_nop_();	// 2 sysclk avant le début du transfert

	SPI0DAT = c;	// on met les donnees
	while (TXBSY);	// attend la fin du transfert	
	
	if (WCOL)
		c = 0;	//collision, renverra 0
	
	P3__5 = 1; // fin du transfert, NSS repasse en HIGH
	for(i=0;i<2000;i++);	// tempo à affiner
	return c;
}

void envoi_trame(unsigned char *trame,int taille)
{
	int i=0;

	//envoi caractère début
	putchar_spi(carac_debut);
	putchar_spi(carac_debut);
	
	while (i < taille)
	{
		while (!putchar_spi(*trame));
		i++;		
		trame++;
	}
    
    // caractères fin
	putchar_spi(carac_fin);
	putchar_spi(carac_fin);
	
	
}
/*
void envoie_struct(struct COMMANDES_POINTEUR c)
{
	unsigned char *data = serialize_struct(c);
	
	envoie_trame(data);
	
	free(data);
}
*/
