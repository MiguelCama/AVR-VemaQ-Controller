/*
 * State_Machine.c
 *
 * Created: 10/09/2022 10:29:13
 *  Author: Eplimin.sac
 */ 

#include <stdio.h>
#include <util/delay.h>
#include "Driver_GPIO.h"
#include "HD44780.h"
#include "Driver_ADC.h"
#include "Driver_PWM.h"
#include "State_Machine.h"

extern eSystemEvent eNewEvent;
extern eSystemState eNextState;
extern eSystemState ePreviousState;

extern uint8_t ADC_lecture;
extern char ADC_lecture_char[3];

extern uint32_t counter;
extern uint8_t counterError;
extern uint8_t counterErrorMessage; 
extern uint8_t alarmBuzzer; 

uint8_t previousButton_RunAutoEdge = 1;
uint8_t currentButton_RunAutoEdge = 1;

uint8_t previousButton_RunManEdge = 1;
uint8_t currentButton_RunManEdge = 1;

uint8_t previousButton_StopEdge = 1;
uint8_t currentButton_StopEdge = 1;

uint8_t previousButton_ResetEdge = 1;
uint8_t currentButton_ResetEdge = 1;

uint8_t previousButton_AlarmEdge = 1;
uint8_t currentButton_AlarmEdge = 1;

uint8_t previousButton_AlarmReleasedEdge = 0;
uint8_t currentButton_AlarmReleasedEdge = 0;

uint8_t previousButton_StartEdge = 1;
uint8_t currentButton_StartEdge = 1;

uint8_t previousButton_StartEdgeRising = 0;
uint8_t currentButton_StartEdgeRising = 0;

float constateConversiontoPorcentage = 0.3937 ; 
float constantEscalerEnconder = 0.1 ; 

uint8_t AlarmEdge_H_OIL = 0;
uint8_t AlarmEdge_L_OIL = 0;
uint8_t AlarmEdge_S_PRT = 0;

eSystemEvent ReadEvent(void){
	eSystemEvent detectedEvent = None_Event; 
	uint8_t index = 0;
	
	/*************************************************************************/	
	/* Detect falling edge on RUN_AUTO  -- X1	*/ 
	currentButton_RunAutoEdge	=  PIN_X1 & (1 << X1);
	
	if (currentButton_RunAutoEdge!= previousButton_RunAutoEdge) {
		if (currentButton_RunAutoEdge == 0) {
			//falling edge, do something
			index = 1;
		}
		previousButton_RunAutoEdge = currentButton_RunAutoEdge;
	}
	/*************************************************************************/
	
	/* Detect falling edge on RUN_MANUAL  -- X2	*/
	currentButton_RunManEdge	=  PIN_X2 & (1 << X2);
	
	if (currentButton_RunManEdge!= previousButton_RunManEdge) {
		if (currentButton_RunManEdge == 0) {
			//falling edge, do something
			index = 2;
		}
		previousButton_RunManEdge = currentButton_RunManEdge;
	}
	/**************************************************************************/
	
	/* Detect falling edge on STOP  -- X3	*/
	currentButton_StopEdge	=  PIN_X3 & (1 << X3);
	
	if (currentButton_StopEdge!= previousButton_StopEdge) {
		if (currentButton_StopEdge == 0) {
			//falling edge, do something
			index = 6;
		}
		previousButton_StopEdge = currentButton_StopEdge;
	}
	/**************************************************************************/
	
	/* Detect falling edge on RESET  -- X4	*/
	currentButton_ResetEdge	=  PIN_X4 & (1 << X4);
	
	if (currentButton_ResetEdge!= previousButton_ResetEdge) {
		if (currentButton_ResetEdge == 0) {
			//falling edge, do something
			index = 7;
			ePreviousState = eNextState;
		}
		previousButton_ResetEdge = currentButton_ResetEdge;
	}
	/**************************************************************************/
/*	AlarmEdge_H_OIL = PIN_H_OIL & (1 << H_OIL);
	AlarmEdge_L_OIL = PIN_L_OIL & (1 << L_OIL);
	AlarmEdge_S_PRT = PIN_S_PRT & (1 << S_PRT);*/
	
	
	AlarmEdge_H_OIL = PIN_H_OIL & (1 << H_OIL);
	AlarmEdge_L_OIL = PIN_L_OIL & (1 << L_OIL);
	AlarmEdge_S_PRT = PIN_S_PRT & (1 << S_PRT);
	
	/*	Detect any alarm condition : S_PT , H_OIL, L_OW		*/
	currentButton_AlarmEdge	=  AlarmEdge_S_PRT || AlarmEdge_H_OIL || AlarmEdge_L_OIL ;
/*
	if (currentButton_AlarmEdge!= previousButton_AlarmEdge) {
		if (currentButton_AlarmEdge == 0) {
			//falling edge, do something
			index = 9;
		}
		previousButton_AlarmEdge = currentButton_AlarmEdge;
	}
*/

	if (currentButton_AlarmEdge) {
		index = 9 ;
	}
	/**************************************************************************/	
	
	/*	Detect alarm released condition : S_PT , H_OIL, L_OW		*/
	
	currentButton_AlarmReleasedEdge	=  (PIN_S_PRT & (1 << S_PRT)) || (PIN_L_OIL & (1 << L_OIL)) || (PIN_H_OIL & (1 << H_OIL)) ;
	
	if (currentButton_AlarmReleasedEdge!= previousButton_AlarmReleasedEdge) {
		if (currentButton_AlarmReleasedEdge == 0) {
			//falling edge, do something
			index = 10;
		}
		previousButton_AlarmReleasedEdge = currentButton_AlarmReleasedEdge;
	}
	/**************************************************************************/
	
	/*	Detect  */
		
	currentButton_StartEdge	=  PIN_RUN & (1 << RUN) ;
		
	if (currentButton_StartEdge!= previousButton_StartEdge) {
		if (currentButton_StartEdge == 0) {
			//rising edge, do something
			if (Automatic_Mode_Screen_State == ePreviousState){
				index = 3;
			}
			if (Manual_Mode_Screen_State == ePreviousState ){
				index = 4;
			}
			if (Automatic_Process_State == ePreviousState){
				index = 6;
			}
			if (Manual_Process_State == ePreviousState){
				index = 6;
			}
		}
		previousButton_StartEdge = currentButton_StartEdge;
	}	
		
	/**************************************************************************/
	
	/*	Detect alarm released condition : S_PT , H_OIL, L_OW		*/
	currentButton_StartEdgeRising	=  PIN_RUN & (1 << RUN) ;
	
	if (currentButton_StartEdgeRising!= previousButton_StartEdgeRising) {
		if (currentButton_StartEdgeRising > 0) {
			//rising edge, do something
			index = 5 ;
		}
		previousButton_StartEdgeRising = currentButton_StartEdgeRising;
	}
	/**************************************************************************/
	
	
	switch(index){
		case 0:
			detectedEvent = None_Event;
			break;
		
		case 1:
			detectedEvent = Run_Auto_Event;
			break;
		case 2:
			detectedEvent = Run_Manual_Event;
			break;
	
		case 3:
			detectedEvent = Pedal_Marcha_edge_Event;
			break;
		case 4:
			detectedEvent = Pedal_Marcha_high_Event;
			break;
		case 5:
			detectedEvent = Pedal_Marcha_low_Event;
			break;
	
		case 6:
			detectedEvent = Stop_Event;
			break;
			
		case 7:
			detectedEvent = Reset_Event;
			break;
		
		case 8:
			detectedEvent = Count_Reset_Success_Event;
			break;
		case 9:
			detectedEvent = Any_Alarm_Event;
			break;
			
		case 10:
			detectedEvent = No_Alarm_Event;
			break;
		
		default:
			break;
	}
	
	return detectedEvent;
}

//Prototype of eventhandlers
eSystemState	None_Handler(void){
	return Initial_Screen_State;
}


eSystemState	RunAuto_Handler(void){
	return Automatic_Mode_Screen_State;
}

eSystemState	RunManual_Handler(void){
	return Manual_Mode_Screen_State;
}

eSystemState	PedalMarchaHigh_Handler(void){
	return Manual_Process_State;
}

eSystemState	PedalMarchaLow_Handler(void){
	return Manual_Mode_Screen_State;
}

eSystemState	PedalMarchaEdge_Handler(void){
	return Automatic_Process_State;
}

eSystemState	Stop_Handler(void){
	
	eSystemState next_state;
	
	if (eNextState == Automatic_Process_State)
	{	
		next_state = Automatic_Mode_Screen_State;
	}
	
	if (eNextState == Automatic_Mode_Screen_State)
	{
		next_state = Initial_Screen_State;
	}
	
	if (eNextState == Manual_Mode_Screen_State)
	{
		next_state = Initial_Screen_State;
	}
	
	return next_state;
	 //*********
}
eSystemState	Reset_Handler(void){
	return Reset_Count_State;
}
eSystemState	CountResetSuccess_Handler(void){
	
	eSystemState next_state;
	
	if (ePreviousState == Initial_Screen_State)
	{
		next_state = Initial_Screen_State;
	}
	if (ePreviousState == Automatic_Process_State)
	{
		return Automatic_Process_State;
	}
	
	if (ePreviousState == Automatic_Mode_Screen_State)
	{
		next_state = Automatic_Mode_Screen_State;
	}
	
	if (ePreviousState == Manual_Mode_Screen_State)
	{
		next_state = Manual_Mode_Screen_State;
	} 
	
	return next_state; //******
}
eSystemState	AnyAlarm_Handler(void){
	LCD_Clear();
	return Sensors_Alarm_State;
}
eSystemState	NoAlarm_Handler(void){
	LCD_Clear();
	return Initial_Screen_State;
}


/************************************************************************/
/*					   Initial Screen State                             */
/************************************************************************/

void InitialScreenState_Actions(void){

	//PORT_RELAY_AUX |= (1 << RELAY_AUX);
	PORT_RELAY_AUX &= ~(1 << RELAY_AUX);

	PWM1_Stop();
	PWM2_Stop();	
	
	alarmBuzzer = 0;
	AlarmEdge_H_OIL = 0;
	AlarmEdge_L_OIL = 0;
	AlarmEdge_S_PRT = 0;
	
	
	ADC_lecture = ADC_Driver_Read(CH_AI1);
	ADC_lecture = ADC_lecture* constateConversiontoPorcentage;

	LCD_GotoXY(0, 0);
	LCD_PrintString("Modo       CNT  VEL ");
	LCD_GotoXY(0, 1);
	LCD_PrintString("--- STOP ");
	LCD_GotoXY(10,1);
	LCD_AUX_Print5dig(counter*constantEscalerEnconder);
	LCD_GotoXY(16,1);
	LCD_AUX_Print3dig(ADC_lecture);
	
	ePreviousState = Initial_Screen_State;
}

void InitialScreenState_Transitions(void){
	
	if(Run_Manual_Event == eNewEvent)
	{
		eNextState = RunManual_Handler();
	}
	
	if(Run_Auto_Event == eNewEvent)
	{
		eNextState = RunAuto_Handler();
	}
	
	if(None_Event == eNewEvent)
	{
		eNextState = None_Handler();
	}
	
	if(Any_Alarm_Event == eNewEvent)
	{
		eNextState = AnyAlarm_Handler();
	}
	if(Reset_Event == eNewEvent)
	{
		eNextState = Reset_Handler();
	}
}
/************************************************************************/
/*             Automatic Mode Screen State                              */
/************************************************************************/

void AutomaticModeScreen_Actions(void){

	PWM1_Stop();
	PWM2_Stop();
	
	ADC_lecture = ADC_Driver_Read(CH_AI1);
	ADC_lecture = ADC_lecture* constateConversiontoPorcentage;
	
	LCD_GotoXY(0, 0);
	LCD_PrintString("Modo       CNT  VEL ");
	LCD_GotoXY(0, 1);
	LCD_PrintString("AUT-STOP ");
	LCD_GotoXY(10,1);
	LCD_AUX_Print5dig(counter*constantEscalerEnconder);
	LCD_GotoXY(16,1);
	LCD_AUX_Print3dig(ADC_lecture);
	
	ePreviousState = Automatic_Mode_Screen_State;

}
void AutomaticModeScreen_Transitions(void){
	
	if(Run_Manual_Event == eNewEvent)
	{
		eNextState = RunManual_Handler();
	}
	if(Stop_Event == eNewEvent)
	{
		eNextState = Stop_Handler();
	}
	
	if(Any_Alarm_Event == eNewEvent)
	{
		eNextState = AnyAlarm_Handler();
	}
	
	if(Reset_Event == eNewEvent)
	{
		eNextState = Reset_Handler();
	}
	
	if(Pedal_Marcha_edge_Event == eNewEvent)
	{
		eNextState = PedalMarchaEdge_Handler();
	}
}


/************************************************************************/
/*                 Manual Mode Screen State                             */
/************************************************************************/
 
void ManualModeScreen_Actions(void){
	PWM1_Stop();
	PWM2_Stop();
	
	ADC_lecture = ADC_Driver_Read(CH_AI1);
	ADC_lecture = ADC_lecture* constateConversiontoPorcentage;
	
	LCD_GotoXY(0, 0);
	LCD_PrintString("Modo       CNT  VEL ");
	LCD_GotoXY(0, 1);
	LCD_PrintString("MAN-STOP ");
	LCD_GotoXY(10,1);
	LCD_AUX_Print5dig(counter*constantEscalerEnconder);
	LCD_GotoXY(16,1);
	LCD_AUX_Print3dig(ADC_lecture);
	
	ePreviousState = Manual_Mode_Screen_State;
	
}
void ManualModeScreen_Transitions(void){
	
	if(Run_Auto_Event == eNewEvent)
	{
		eNextState = RunAuto_Handler();
	}
	
	if(Stop_Event == eNewEvent)
	{
		eNextState = Stop_Handler();
	}
	
	if(Any_Alarm_Event == eNewEvent)
	{
		eNextState = AnyAlarm_Handler();
	}
	
	if(Reset_Event == eNewEvent)
	{
		eNextState = Reset_Handler();
	}
	
	if(Pedal_Marcha_high_Event == eNewEvent)
	{
		eNextState = PedalMarchaHigh_Handler();
	}
	
}
/************************************************************************/
/*                     Automatic Process State                          */
/************************************************************************/

void AutomaticProcessState_Actions(void){

	ADC_lecture = ADC_Driver_Read(CH_AI1);
	ADC_lecture = ADC_lecture* constateConversiontoPorcentage;
	
	//PWM1_Update_Duty(50);
	PWM2_Update_Duty( 37 + ADC_lecture * 0.2);
	
	PWM1_Start();
	PWM2_Start();

	LCD_GotoXY(0, 0);
	LCD_PrintString("Modo       CNT  VEL ");
	LCD_GotoXY(0, 1);
	LCD_PrintString("AUT-RUN ");
	LCD_GotoXY(10,1);
	LCD_AUX_Print5dig(counter*constantEscalerEnconder);
	LCD_GotoXY(16,1);
	LCD_AUX_Print3dig(ADC_lecture);
	
}
void AutomaticProcessState_Transitions(void){
	if(Stop_Event == eNewEvent)
	{
		eNextState = Stop_Handler();
	}
	
	if(Any_Alarm_Event == eNewEvent)
	{
		eNextState = AnyAlarm_Handler();
	}
	
	if(Reset_Event == eNewEvent)
	{
		eNextState = Reset_Handler();
	}
}

/************************************************************************/
/*                          Manual Processs State                       */
/************************************************************************/

void ManualProcessState_Actions(void){

	ADC_lecture = ADC_Driver_Read(CH_AI1);
	ADC_lecture = ADC_lecture* constateConversiontoPorcentage;
	
	//PWM1_Update_Duty(50);
	PWM2_Update_Duty( 37 + ADC_lecture * 0.2);
	
	PWM1_Start();
	PWM2_Start();
	
	LCD_GotoXY(0, 0);
	LCD_PrintString("Modo       CNT  VEL ");
	LCD_GotoXY(0, 1);
	LCD_PrintString("MAN-RUN ");
	LCD_GotoXY(10,1);
	LCD_AUX_Print5dig(counter*constantEscalerEnconder);
	LCD_GotoXY(16,1);
	LCD_AUX_Print3dig(ADC_lecture);

}
void ManualProcessState_Transitions(void){
	if(Any_Alarm_Event == eNewEvent)
	{
		eNextState = AnyAlarm_Handler();
	}
	
	if(Reset_Event == eNewEvent)
	{
		eNextState = Reset_Handler();
	}
	
	if(Pedal_Marcha_low_Event == eNewEvent)
	{
		eNextState = PedalMarchaLow_Handler();
	}
	
}

/************************************************************************/
/*                            Reset Count State                         */
/************************************************************************/

void ResetCountState_Actions(void){
	
	counter = 0; 
	
	eNewEvent = Count_Reset_Success_Event;
}
void ResetCountState_Transitions(void){
	
	if(Count_Reset_Success_Event == eNewEvent)
	{
		eNextState = CountResetSuccess_Handler();
	}
}
/************************************************************************/
/*                            Sensors Alarm State                       */
/************************************************************************/

void SensorsAlarmState_Actions(void){
	alarmBuzzer = 1;
	
	PWM1_Stop();
	PWM2_Stop();
	
	//PORT_RELAY_AUX &= ~(1 << RELAY_AUX);
	PORT_RELAY_AUX |= (1 << RELAY_AUX);
	
	LCD_GotoXY(0, 0);
	LCD_PrintString("    !PRECAUCION!    ");

	
	if (counterError == 1) {
		LCD_GotoXY(0, 1);
		LCD_PrintString("Revisar los sensores");
	}
	
	if (counterError == 2 ) {
		;
	}
	
	if (counterError == 3 ){
		if (AlarmEdge_H_OIL && (counterErrorMessage == 1)){
			LCD_GotoXY(0, 1);
			LCD_PrintString("     Aceite Alto    ");
			if (AlarmEdge_L_OIL && AlarmEdge_S_PRT){
				counterErrorMessage = 0;
			}
		}
	
		if (AlarmEdge_L_OIL && (counterErrorMessage == 2)){
			LCD_GotoXY(0, 1);
			LCD_PrintString("     Aceite Bajo    ");
			if (AlarmEdge_H_OIL && AlarmEdge_S_PRT){
				counterErrorMessage = 0;
			}
		}
		
		if (AlarmEdge_S_PRT && (counterErrorMessage == 3)){
			LCD_GotoXY(0, 1);
			LCD_PrintString("Sensor de Proteccion");
			counterErrorMessage = 0;
		}
	}

	if (counterError == 4){
		;
	}
	
}
void SensorsAlarmState_Transitions(void){
	if(No_Alarm_Event == eNewEvent)
	{
		eNextState = NoAlarm_Handler();
	}
}



void LCD_AUX_Print3dig (uint8_t Value){
	if (Value > 99)
	{
		LCD_PrintInteger(Value);
	}
	else if (Value > 9 && Value < 100)
	{
		LCD_PrintString(" ");
		LCD_PrintInteger(Value);
	}
	else{
		LCD_PrintString("  ");
		LCD_PrintInteger(Value);
	}
}

void LCD_AUX_Print5dig (uint32_t Value){
	if (Value > 9999)
	{
		LCD_PrintInteger(Value);
	}
	else if (Value > 999 && Value < 10000)
	{
		LCD_PrintString(" ");
		LCD_PrintInteger(Value);
	}
	else if (Value > 99 && Value < 1000)
	{
		LCD_PrintString("  ");
		LCD_PrintInteger(Value);
	}
	else if (Value > 9 && Value < 100)
	{
		LCD_PrintString("   ");
		LCD_PrintInteger(Value);
	}
	else{
		LCD_PrintString("    ");
		LCD_PrintInteger(Value);
	}
}