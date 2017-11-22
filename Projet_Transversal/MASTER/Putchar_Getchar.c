//------------------------------------------------------------------------------------
// Putchar_Getchar.c
//------------------------------------------------------------------------------------
//
// AUTH: Groupe C4
// DATE: 04/04/17
// Target: C8051F02x
//
// Tool chain: KEIL PK51
//
//OBJECTIF: Ecriture des fonctions getchar, putchar ...
//-----------------------------------------------------------------------------------
// Includes
//------------------------------------------------------------------------------------                
#include <c8051f020.h>
#include "Declarations_GPIO_BSE.h"
#include <intrins.h> 
#include "Putchar_Getchar.h"
//-----------------------------------------------------------------------------
// Function PROTOTYPES
//-----------------------------------------------------------------------------
void Send_String(char choix_uart, char* char_ptr)
{
	while(*char_ptr != '\0')
	{
		Putchar(choix_uart,*char_ptr);
		char_ptr=char_ptr+1;
	}
	return;
}

char Getchar(char choix_uart)
{
    char carac;
    if(choix_uart==0)
    {
			while(!RI0);
			carac=SBUF0;
      RI0=0;
			Putchar(0,carac);
      return carac;
    }
    else
    {
        while(!(SCON1 & 0x01));
        carac=SBUF1;
        SCON1 &= 0xFE;
        return carac;
    }
}

char Putchar (char choix_uart, char c)  {
     
    if(choix_uart==0)
    {
        if (c == '\n')  {   // si le caractère est un retour à la ligne :
            while (!TI0);   
            TI0 = 0;
            SBUF0 = 0x0d;                         /* output CR  */
        }
        while (!TI0);
        TI0 = 0;
        SBUF0=c;
        return 0;
    }
    else
    {
        if (c == '\n')  {
            while (!(SCON1 & 0x02));       
            SCON1 &= 0xFD;
            SBUF1 = 0x0d;                         /* output CR  */
        }
        while (!(SCON1 & 0x02));
				//Putchar(0,c);
        SCON1 &= 0xFD;
        SBUF1=c;
        return 0;
    }
}
