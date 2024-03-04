/*
 * Driver_ADC.c
 *
 * Created: 18/08/2022 12:48:42
 *  Author: Eplimin.sac
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>

#include "Proyect_Defines.h"
#include "Driver_ADC.h"

void ADC_Driver_Initialize(){
	
	PCMSK0  |= ( 1 << PCINT0);
	
	/*	Disable the Digital Buffer on AI1, AI2, AI3 to save power */
	DIDR0	|= (1 << AI1)|(1 << AI2)|(1 << AI3);
	
	/*	Set ADC Pre-scaler, sample rate = 16MHz / 128 = 125KHz	 */    
	ADCSRA	|= (1 << ADPS2) | (1 << ADPS1) | (1 <<ADPS0);
	
	/*	Set ADC reference to AVCC */
	ADMUX	|= (1 << REFS0);
	 
	/*	Left adjust ADC result to allow easy 8-bit reading	*/
	ADMUX	|= (1 << ADLAR);
	
	/*	Set ADC to Free-Running Mode	*/
	ADCSRB	&= ~((1 << ADTS2) | (1 << ADTS1) | (1 << ADTS0));  
	
	/*	Enable ADC	*/
	ADCSRA	|= (1 << ADEN);   
	
	/*	Enable ADC Interrupt	*/
	//ADCSRA	|= (1 << ADIE);
	
	/*	Enable Global Interrupts	*/
	//sei();
		
	/*	Start A2D Conversions	*/
	ADCSRA	|= (1 << ADSC);  // 
	
}

uint8_t ADC_Driver_Read(uint8_t channel){
	
	/* Define the new ADC channel */
	ADMUX	=  ADMUX|(channel & 0x10); 
	
	/* Starts a new ADC conversion	*/ 
	ADCSRA	|= (1 << ADSC); 
	
	/* Wait until the conversion is done */
	while( ADCSRA & (1 << ADSC) ); 
	
	return ADCH;                        
}