/*
 * Driver_Encoder.h
 *
 * Created: 09/09/2022 14:31:57
 *  Author: eplim
 */ 
#include <avr/io.h>
#include <stdbool.h>

#ifndef DRIVER_ENCODER_H_
#define DRIVER_ENCODER_H_

/*	Push-button inputs	*/
/*
	ENC_A ---> 
	ENC_B--> 

*/

#define PORT_ENC_A		PORTD
#define DDR_ENC_A		DDRD
#define PIN_ENC_A		PIND
#define ENC_A			2

#define PORT_ENC_B		PORTD
#define DDR_ENC_B		DDRD
#define PIN_ENC_B		PIND
#define ENC_B			3

 void Encoder_Driver_Initialize(void);
 void Interrupt_Initialize(void);


#endif /* DRIVER_ENCODER_H_ */