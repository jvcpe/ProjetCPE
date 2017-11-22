#ifndef DETEC_OBSTACLES_H
#define DETEC_OBSTACLES_H

void FO_M4_init();
void Oscillator_Init();
void config_P3_FO_M4();
void Timer2_Init_FO_M4();
void Interrupt67_Init_FO_M4();
void ISR__EXT_INT6_FO_M4();
void Pulse_P33();
void Pulse_P34();
unsigned int MES_Dist_AV (void);
unsigned int MES_Dist_AR (void);

#endif

