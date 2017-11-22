//------------------------------------------------------------------------------------
// Function PROTOTYPES
//------------------------------------------------------------------------------------
#ifndef FO_M4
#define FO_M4
	
	void Reset_source_init();
	void FO_M4_init();
	void Oscillator_Init();
	void config_P3_FO_M4();
	void Timer2_Init_FO_M4();
	void Interrupt67_Init_FO_M4();
	void ISR__EXT_INT6_FO_M4();
	void ISR__EXT_INT7_FO_M4();
	unsigned int MES_Dist();
	void Pulse_P34();
	void delay_us(unsigned int us);
	
#endif
//------------------------------------------------------------------------------------
