/*
 * Driver_PWM.h
 *
 * Created: 18/08/2022 12:47:22
 *  Author: Eplimin.sac
 */ 
#include <avr/io.h>

#ifndef DRIVER_PWM_H_
#define DRIVER_PWM_H_

#define PORT_PWM	PORTD
#define DDR_PWM		DDRD
#define PIN_PWM		PIND

#define CH_PWM1		4
#define CH_PWM2		6

uint8_t duty_hex; 

void PWM1_Driver_Initialize(void);
void PWM2_Driver_Initialize(void);
void PWM1_Start(void);
void PWM2_Start(void);
void PWM1_Stop(void);
void PWM2_Stop(void);
void PWM1_Update_Duty(float duty);
void PWM2_Update_Duty(float duty);
void PWM1_Update_Duty_Hex(uint8_t duty_hex);
void PWM2_Update_Duty_Hex(uint8_t duty_hex);

#endif /* DRIVER_PWM_H_ */