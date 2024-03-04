/*
 * Driver_GPIO.h
 *
 * Created: 18/08/2022 12:48:13
 *  Author: Eplimin.sac
 */ 
#include <avr/io.h>
#include <stdbool.h>

#ifndef DRIVER_GPIO_H_
#define DRIVER_GPIO_H_

/*	Push-button inputs	*/
/*
	X1 ---> RESET
	X2 ---> STOP
	X3 ---> RUN_AUTO
	X4 ---> RUN_MAN 
*/

#define PORT_X1		PORTA
#define DDR_X1		DDRA
#define PIN_X1		PINA
#define X1			6

#define PORT_X2		PORTA
#define DDR_X2		DDRA
#define PIN_X2		PINA
#define X2			7

#define PORT_X3		PORTA
#define DDR_X3		DDRA
#define PIN_X3		PINA
#define X3			5

#define PORT_X4		PORTA
#define DDR_X4		DDRA
#define PIN_X4		PINA
#define X4			4

/*	Sensor-digital inputs */
/*
	S_PRT	---> Protection sensor, normaly closed
	RUN		---> Run the system
	H_OIL   ---> High oil alarm
	L_OIL   ---> Low oil alarm
*/

#define PORT_S_PRT		PORTD
#define DDR_S_PRT		DDRD
#define PIN_S_PRT		PIND
#define S_PRT			0

#define PORT_RUN		PORTD
#define DDR_RUN			DDRD
#define PIN_RUN			PIND
#define RUN				1

#define PORT_H_OIL		PORTD
#define DDR_H_OIL		DDRD
#define PIN_H_OIL		PIND
#define H_OIL			7

#define PORT_L_OIL		PORTD
#define DDR_L_OIL		DDRD
#define PIN_L_OIL		PIND
#define L_OIL			5

/*	Digital outputs */
/*
	LED			---> Pilot indicador on the external panel
	RELAY_AUX	---> Relay auxiliar 
	BUZZ		---> Buzzer
*/

#define PORT_LED		PORTB
#define DDR_LED			DDRB
#define PIN_LED			PINB
#define LED				2

#define PORT_RELAY_AUX	PORTB
#define DDR_RELAY_AUX	DDRB
#define PIN_RELAY_AUX	PINB
#define RELAY_AUX		3

#define PORT_BUZZ		PORTB
#define DDR_BUZZ		DDRB
#define PIN_BUZZ		PINB
#define BUZZ			4

	

/*	GPIO Driver Functions */

void GPIO_Driver_Initialize(void);
void GPIO_Driver_outputON(uint8_t pin);
void GPIO_Driver_outputOFF(uint8_t pin);
uint8_t GPIO_Driver_sensorInput(uint8_t pin);

uint8_t GPIO_Driver_buttonInput(uint8_t pin);
void GPIO_Driver_buttonState(uint8_t pin);

#endif /* DRIVER_GPIO_H_ */