#ifndef LIB_BSE_UART_H
#define LIB_BSE_UART_H


//#define TICK_CLK  200  // (en hertz)
void Config_Clock_UART0(void);
void Config_UART0(void);
char Putchar(char c, char csg_tempo);
char Send_String(char* ptr);
char Getchar();

#endif