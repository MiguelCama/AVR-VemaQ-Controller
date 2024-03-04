/*
 * Driver_GPIO.c
 *
 * Created: 18/08/2022 12:49:34
 *  Author: Eplimin.sac
 */ 

#include "Proyect_Defines.h"
#include "Driver_GPIO.h"


uint8_t  previous_state[4]	= { 0 , 0 , 0 , 0};
uint8_t  current_state[4]	= { 0 , 0 , 0 , 0};
uint8_t  state_button[4]	= { 0 , 0 , 0 , 0};


void GPIO_Driver_Initialize(void){
	/*	Initialize Digital outputs	*/
	/*	Set as output LED, RELAY_AUX, BUZZ */
	DDRB	|=	(1 << LED)|(1 << RELAY_AUX)|(1 << BUZZ);
	/*	Set the initial state of  LED, RELAY_AUX, BUZZ  to HIGH */
	PORTB	|=  (1 << LED);
	PORTB   &=  ~((1 << RELAY_AUX)|(1 << BUZZ));
	
	/*	Initialize Push-button inputs	*/
	/*	Set as input X1, X2, X3, X4 */
	DDRA	&=	~((1 << X1)|(1 << X2)|(1 << X3)|(1 << X4));
	
	/*	Initialize Sensor-digital inputs	*/
	/*	Set as input S_PRT, RUN, H_OIL, L_OIL */
	DDRD	&=	~((1 << S_PRT)|(1 << RUN)|(1 << H_OIL)|(1 << L_OIL));
}

void GPIO_Driver_outputON(uint8_t pin){
	/* pin --- ST , RUN , L_OIL, H_OIL */
	PORTB |=  ( 1 << pin );
	;
}

void GPIO_Driver_outputOFF(uint8_t pin){
	/* pin --- ST , RUN , L_OIL, H_OIL */
	PORTB &=  ~( 1 << pin );
	;
}

uint8_t  GPIO_Driver_sensorInput(uint8_t pin ){
	/* pin --- ST , RUN , L_OIL, H_OIL */
	uint8_t  state_pin = 0 ;
	if (PIND & (1 << pin)){
		state_pin = 1;
	}
	else{
		state_pin = 0;
	}
	return state_pin;
}


uint8_t  GPIO_Driver_buttonInput(uint8_t pin ){
	/* pin --- ST , RUN , L_OIL, H_OIL */
	uint8_t  state_pin = 0 ;
	if (PINB & (1 << pin)){
		state_pin = 1;
	}
	else{
		state_pin = 0;
	}
	return state_pin;
}


void GPIO_Driver_buttonState(uint8_t pin){
	/* pin --- X1 , X2 , X3, X4 */
	
	extern uint8_t  state_button[];
	extern uint8_t  previous_state[];
	extern uint8_t  current_state[];  
	
	uint8_t index = pin - 4 ; 
	 
	current_state[index] = GPIO_Driver_buttonInput(pin);
	
	if( (current_state[index] == 1) && (previous_state[index] == 0) ){
		state_button[index] = 1 - state_button[index];
		_delay_ms(50); 
	}
	previous_state[index] = current_state[index];
}
