/*
 * State_Machine.h
 *
 * Created: 10/09/2022 10:26:22
 *  Author: eplim
 */ 


#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include <util/delay.h>

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_


//Different state of ATM machine
typedef enum
{
	Initial_Screen_State,
	Automatic_Mode_Screen_State,
	Manual_Mode_Screen_State,
	Automatic_Process_State,
	Manual_Process_State,
	Reset_Count_State,
	Sensors_Alarm_State
} eSystemState;
//Different type events
typedef enum
{
	None_Event,
	Run_Auto_Event,
	Run_Manual_Event,
	Pedal_Marcha_high_Event,
	Pedal_Marcha_low_Event,
	Pedal_Marcha_edge_Event,
	Stop_Event,
	Reset_Event,
	Count_Reset_Success_Event,
	Any_Alarm_Event,
	No_Alarm_Event
	
} eSystemEvent;


eSystemEvent ReadEvent(void);

//Prototype of eventhandlers
eSystemState	RunAuto_Handler(void);
eSystemState	RunManual_Handler(void);
eSystemState	PedalMarchaHigh_Handler(void);
eSystemState	PedalMarchaLow_Handler(void);
eSystemState	PedalMarchaEdge_Handler(void);
eSystemState	Stop_Handler(void);
eSystemState	Reset_Handler(void);
eSystemState	CountResetSuccess_Handler(void);
eSystemState	AnyAlarm_Handler(void);
eSystemState	NoAlarm_Handler(void);

// For Initial Screen State
void InitialScreenState_Actions(void);
void InitialScreenState_Transitions(void);

// For Automatic Mode Screen State
void AutomaticModeScreen_Actions(void);
void AutomaticModeScreen_Transitions(void);

// For Manual Mode Screen State
void ManualModeScreen_Actions(void);
void ManualModeScreen_Transitions(void);

// For Automatic Process State
void AutomaticProcessState_Actions(void);
void AutomaticProcessState_Transitions(void);

// For Manual Processs State
void ManualProcessState_Actions(void);
void ManualProcessState_Transitions(void);

// For Reset Count State
void ResetCountState_Actions(void);
void ResetCountState_Transitions(void);

// For Sensors Alarm State
void SensorsAlarmState_Actions(void);
void SensorsAlarmState_Transitions(void);


void LCD_AUX_Print3dig (uint8_t Value);
void LCD_AUX_Print5dig (uint32_t Value);

#endif /* STATE_MACHINE_H_ */