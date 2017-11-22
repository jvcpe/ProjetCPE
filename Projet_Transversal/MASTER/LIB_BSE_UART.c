#include <c8051F020.h>
#include <stdio.h>
#include <intrins.h>
#include "LIB_BSE_UART.h"
#include "CFG_GLOBALE.h"
void Config_Clock_UART0()
{
	//Timer1 disabled
	TR1 = 0;
	//Timer1 uses Sysclk 
	CKCON |= 0x10;
	//Timer1 enabled when TR1=1
	//Timer1 incremented clock defined by T1M
	//Timer1 mode 2 : 8-bit counter with auto-reload
	TMOD |= 0x20;
	TMOD &= ~(0xD0);
	//Clear Timer1 overflow flag
	TF1 = 0;
	TH1 = -(SYSCLK/BAUDRATE/16);//sysclk/baudrate/16
	//Enable Timer1 interrupt
	ET1 = 0;
	//Timer1 enabled
	TR1 = 1;
}

void Config_UART0()
{
	//Mode 1 : 8 bit UART, variable baud rate
	//RI0 will only be activated if stop bit = 1
	//UART0 reception enabled
	SCON0 |= 0x70;
	SCON0 &= ~(0x83);
	//Timer 1 overflows used for receive clock
	RCLK0 = 0;
	//Timer 1 overflows used for transmit clock
	TCLK0 = 0;
	//UART0 baud rate /2 disabled
	PCON |= 0x80;
	//Reads/writes of SM20-SM00 access the SM20-SM00 UART0 mode setting
	PCON &= ~(0x40);
	//Clear transmit interrupt flag
	TI0 = 1;
}

char Putchar(char c, char csg_tempo)
{
	while (!TI0)
	{
		int i;
		for(i=0;i<2200;i++)_nop_();//2200->100µs
		_nop_();
		_nop_();
		csg_tempo--;
		if(csg_tempo == 0) 
		{
			return 0;
		}
	}
	
	SBUF0 = c;
	TI0=0;
	return c;
}

char Send_String(char* ptr)
{
	char c;
	int compteur=0;
	while(*ptr != 0x00)
	{
		c = Putchar(*ptr,100);
		if (c != 0)
		{
			ptr++;
			compteur++;
			//TI0=1;
		}
		else
		{
			return 0;
		}
	}
	return compteur;
		
}

char Getchar()
{
	char c;
	if(RI0 == 0) 
	{
		return 0;//if no data received-->return 0
	}
	c = SBUF0;
	RI0 = 0;
	return c;
}

void Test_main()
{
	/*char c;
	char* ptr = &c;
	TI0 = 1;
	while (1)
	{
		c = Getchar();
		Send_String(ptr);
	}*/
	int i=0;
	char packet=0 ;
	char mot[] = "Phrase de test contenant de la ponctuation ,?;.:/" ;
	Send_String(mot);

	for(i=0;i<10;i++)
	{
	while(packet==0)
	{
	packet = Getchar();		// reçoit le caractère et le stocke
	if(packet != 0x00)
		{   // si le packet est non vide
			Putchar(packet,100);		// alors on l'envoie
		}
	}
		packet=0;
	}
}
	