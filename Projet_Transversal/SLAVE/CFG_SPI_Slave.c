///////////////////////////////
//CFG_SPI_slave.c
///////////////////////////////
//AUTH: 
//DATE: 
//
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-MS1
 #include <c8051f020.h>
#include "CFG_SPI_Slave.h"

#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
 
void config_spi()
{
    SPI0CFG &= 0x3F;	// data sampled on first edge of clk, clk line idle low
	SPI0CFG |= 0x07;	// envoie 8 bits par 8 bits
	MSTEN = 0;			//fonctionne en Slave
	SPIF=0;
	SPI0CKR = 0x04;	// règle la sclk
	
	SPIEN = 1; 	// active le SPI
	
	EIE1 |=0x01;
}
    