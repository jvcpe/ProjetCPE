///////////////////////////////
//CFG_SPI_master.c
///////////////////////////////
//AUTH: 
//DATE: 29/03/2016
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1
 #include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#include "CFG_SPI_master.h"
 
void config_spi_master()
{
  SPI0CFG &= 0x3F;	// data sampled on first edge of clk, clk line idle low
	SPI0CFG |= 0x07;	// envoie 8 bits par 8 bits
	MSTEN = 1;			//fonctionne en Master
	SPIF=1;					// met le flag à 1
	SPI0CKR = 0xFF;	// règle la sclk
	P3__5 = 1; // NSS à 1 
	
	SPIEN = 1; 	// active le SPI
}
    