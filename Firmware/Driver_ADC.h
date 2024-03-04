/*
 * Driver_ADC.h
 *
 * Created: 18/08/2022 12:46:52
 *  Author: eplim
 */ 

#include <avr/io.h>

#ifndef DRIVER_ADC_H_
#define DRIVER_ADC_H_


/*	Analog inputs	*/
#define PORT_AI1	PORTA
#define DDR_AI1		DDRA
#define PIN_AI1		PINA
#define AI1			0
#define CH_AI1		0

#define PORT_AI2	PORTA
#define DDR_AI2		DDRA
#define PIN_AI2		PINA
#define AI2			1
#define CH_AI2		1

#define PORT_AI3	PORTA
#define DDR_AI3		DDRA
#define PIN_AI3		PINA
#define AI3			2
#define CH_AI3		2

void	ADC_Driver_Initialize(void);
uint8_t	ADC_Driver_Read(uint8_t channel);







#endif /* DRIVER_ADC_H_ */