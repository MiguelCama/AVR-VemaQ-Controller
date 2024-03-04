/*
 * Driver_Encoder.c
 *
 * Created: 09/09/2022 14:39:02
 *  Author: Eplimin.sac
 */

 #include <avr/io.h>
 #include <avr/interrupt.h>

 #include "Driver_Encoder.h"
 
 void Interrupt_Initialize(void){
	 /* The rising edge of INT0 generates an interrupt request*/
	 EICRA |=  ( 1 << ISC00 ) | ( 1 << ISC01 );	

	 /* External Interrupt Request 0 and 1 Enable  */
	 EIMSK |= ( 1 << INT0);
 }
 
 
 void Encoder_Driver_Initialize(void){
	/*	Top Value of 7811 */
	OCR3A = 7811;	
	
	/*	Set Waveform Generation mode : CTC Mode  :	
					TCCR3A --> WGM3[1:0]	= 0b00  
					TCCR3B --> WGM3[3:2]	= 0b01  */
												TCCR3A	&=  ~( (1 << WGM31) | (1 << WGM30) );
	TCCR3B	|=	(1 << WGM32);					TCCR3B	&=	~(1 << WGM33);	
	
	/*	Set Compare Output Mode for Channel B :	OC3B/A  disconnected				
					TCCR1A --> COM1B[1:0]	= 0b00  */
												TCCR3A	&=	~( (1 << COM3B0) | (1 << COM3B1));	
	
	/*	Set Clock Pre-scaler: Divisor by 1024 						
					TCCR1B --> CS1[2:0]		= 0b101 */
	TCCR3B	|=	(1 << CS32)|(1 << CS30);					TCCR3B	&=	~( (1 << CS31) );
	
	/* Enable timer1 overflow interrupt (TOIE3)  */
	TIMSK3 = (1 << OCIE3A) ;   
	  	 
}


