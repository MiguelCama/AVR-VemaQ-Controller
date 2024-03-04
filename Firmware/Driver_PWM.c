/*
 * Driver_PWM.c
 *
 * Created: 18/08/2022 12:49:08
 *  Author: Eplimin.sac
 */ 

#include "Driver_PWM.h"


void PWM1_Driver_Initialize(void){
	/*	Set OC2B as output	*/
	DDR_PWM	|= (1 << CH_PWM1);
	
	/*	Top Value of 255 */
	OCR1A = 255;	
	
	/*	Set Waveform Generation mode : PWM Phase Correct  :	
					TCCR1A --> WGM1[1:0]	= 0b01  
					TCCR1B --> WGM1[3:2]	= 0b10  */
	TCCR1A	|=	(1 << WGM10);					TCCR1B	&=  ~(1 << WGM11);
	TCCR1B	|=	(1 << WGM13);					TCCR1B	&=	~(1 << WGM12);	
	
	/*	Set Compare Output Mode for Channel B :	OC1B connected				
					TCCR1A --> COM1B[1:0]	= 0b10  */
	TCCR1A	|=	(1 << COM1B1);					TCCR1A	&=	~(1 << COM1B0);	
	
	/*	Set Clock Pre-scaler: Divisor by 256 						
					TCCR1B --> CS1[2:0]		= 0b110 */
	TCCR1B	|=	(1 << CS12);					TCCR1B	&=	~( (1 << CS11) );
	
}

void PWM1_Start(void){
	/*	Set Compare Output Mode for Channel B :				
					TCCR2A --> COM2B[1:0]	= 0b10  */
	TCCR1A	|=	(1 << COM1B1);	TCCR1A	&=	~(1 << COM1B0);	
}

void PWM1_Stop(void){
		
	/*	Set Compare Output Mode for Channel B : OC2B disconnected				
					TCC1A --> COM1B[1:0]	= 0b00  */
	TCCR1A	&= ~( (1 << COM1B1)|(1 << COM1B0) );
}

void PWM1_Update_Duty(float duty){
	
	uint8_t duty_hex =  (duty * 255)/100 ;
	OCR1B = duty_hex;
}

void PWM1_Update_Duty_Hex(uint8_t duty_hex){
	OCR1B = duty_hex;
}


void PWM2_Driver_Initialize(void){
	
	/*	Set OC2B as output	*/
	DDR_PWM	|= (1 << CH_PWM2);
	
	/*	Top Value of 255 */
	OCR2A = 255;
	
	/*	Set Waveform Generation mode : PWM Phase Correct  :	
					TCCR2A --> WGM2[1:0]	= 0b01  
					TCCR2B --> WGM2[2]		= 0b1  */
	TCCR2A	|=	(1 << WGM20);	TCCR2A	&=	~(1 << WGM21);
	TCCR2B	|=	(1 << WGM22);
	
	/*	Set Compare Output Mode for Channel B :	OC2B connected				
					TCCR2A --> COM2B[1:0]	= 0b10  */
	TCCR2A	|=	(1 << COM2B1);	TCCR2A	&=	~(1 << COM2B0);	
	
	/*	Set Clock Pre-scaler:								
					TCCR2B --> CS2[2:0]		= 0b110 */
	TCCR2B	|=	(1 << CS22) | (1 << CS21);	TCCR2B	&=	~( 1 << CS20 ) ;
}

void PWM2_Start(void){
	/*	Set Compare Output Mode for Channel B :				
					TCCR2A --> COM2B[1:0]	= 0b10  */
	TCCR2A	|=	(1 << COM2B1);	TCCR2A	&=	~(1 << COM2B0);	
}

void PWM2_Stop(void){
	
	/*	Set Compare Output Mode for Channel B : OC2B disconnected				
					TCCR2A --> COM2B[1:0]	= 0b00  */
	TCCR2A	&= ~( (1 << COM2B1)|(1 << COM2B0) );
}

void PWM2_Update_Duty(float duty){
	
	uint8_t duty_hex =  (duty * 255)/100;
	OCR2B = duty_hex;	
}

void PWM2_Update_Duty_Hex(uint8_t duty_hex){
	OCR2B = duty_hex;
}