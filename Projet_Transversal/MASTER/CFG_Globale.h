 /*---------------------------------------------------------------------------
;
;

;
;---------------------------------------------------------------------------*/

                                                        // 
#ifndef CFG_GLOBALE_H
#define CFG_GLOBALE_H

#define BAUDRATE 19200
#define SYSCLK 22118400        // Baud rate of UART in bps
//#define TICK_CLK  200  // (en hertz)
void Sysclk_Init(void);
void Reset_Sources_Init(void);
void Port_IO_Init(void);
void Init_Device(void); 

#endif