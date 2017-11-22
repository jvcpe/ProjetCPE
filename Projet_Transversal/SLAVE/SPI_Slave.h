///////////////////////////////
//SPI_Slave.h
///////////////////////////////
//AUTH: CASTELLO Maxime/MIOR Edouard
//DATE: 11/05/17
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1
 
#ifndef SPI_SLAVE_H__
#define SPI_SLAVE_H__
 







void fin_transfert();	// interruption levée à chaque fois que NSS passe à 0, donc fin de transfert d'un bit
void initialise_buffer();	// initialise le buffer
void ajout_caractere(unsigned char c); // ajoute un caractère au buffer
void servomoteur();
void actionCommande(void);
void lum_ON_OFF(void);


#endif