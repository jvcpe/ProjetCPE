
//Target: C8051F02x
//Tool chain: KEIL Eval 'c'
//
//Sous-ensemble FO-M2
/*
#ifndef INCLUDES
#define INCLUDES

#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h>
#endif

char putchar (char choix_uart, char c);
char getchar(char choix_uart);
*/
//------------------------------------------------------------------------------------
// LIB_BSE_UART.h
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
#ifndef PUT_GET_H_
#define  PUT_GET_H_


char Putchar (char choix_uart, char c);
void Send_String(char choix_uart, char* char_ptr);
char Getchar(char choix_uart);
#endif
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
