// PeriodicTimer0AInts.c
// Runs on LM4F120/TM4C123
// Use Timer0A in periodic mode to request interrupts at a particular
// period.
// Daniel Valvano
// September 11, 2013

/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015
  Program 7.5, example 7.6

 Copyright 2015 by Jonathan W. Valvano, valvano@mail.utexas.edu
    You may use, edit, run or distribute this file
    as long as the above copyright notice remains
 THIS SOFTWARE IS PROVIDED "AS IS".  NO WARRANTIES, WHETHER EXPRESS, IMPLIED
 OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF
 MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE.
 VALVANO SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL,
 OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.
 For more information about my classes, my research, and my books, see
 http://users.ece.utexas.edu/~valvano/
 */

// oscilloscope or LED connected to PF3-1 for period measurement
// When using the color wheel, the blue LED on PF2 is on for four
// consecutive interrupts then off for four consecutive interrupts.
// Blue is off for: dark, red, yellow, green
// Blue is on for: light blue, blue, purple, white
// Therefore, the frequency of the pulse measured on PF2 is 1/8 of
// the frequency of the Timer0A interrupts.

#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "PLL.h"
#include "Timer1A.h"
#include "SysTick.h"
#include "Buttons.h"
#include "ADCSWTrigger.h"
#include "ST7735.h"
#include "TEC.h"

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define LEDS      (*((volatile uint32_t *)0x40025038))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08

extern uint32_t ADC_Sample;
int32_t Current_Temp = 25;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void PortF_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x20;				// activate port F
	while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
	GPIO_PORTF_DIR_R &= ~0x07;					// make PF2-0 input (PF2-0 built-in LEDs)
	GPIO_PORTF_AFSEL_R &= ~0x07;			// disable alt funct on PF2-0
	GPIO_PORTF_DEN_R |= 0x07;					// enable digital I/O on PF2-0
																		// configure PF2-0 as GPIO
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF000)+0x00000000;
	GPIO_PORTF_AMSEL_R = 0;						// disable analog functionality on PF
}

int main(void){ 
	
	DisableInterrupts();
	PLL_Init(Bus10MHz);								// bus clock at 10 MHz
	PortF_Init();
	Buttons_Init();
	SysTick_Init();
	ST7735_InitR(INITR_REDTAB);
	TEC_Init();
	ADC0_InitSWTriggerSeq3_Ch0();
	EnableInterrupts();
		
	while(1) {

		/*
		convert ADC_sample to Current_Temp
		Get TEC_Temp
		Compare TEC_Temp with Current_Temp
		Turn off if less than/equal to
		
		Display "Critical Can Cooler V1.0"
		Display Current_Temp
		Display TEC_temp
		Display TEC_Status
		*/
	
		/*
		Temp scale:
		MAX 1740 mV or 2160 ADC measure = 25 C
		MIN 960  mV or 1192 ADC measure = 0 C
		
		2160* .806mV/adctic = temp in mV
		vo -480/15.6
		
		adc tics * .806mV/tic = sample in mV
		(mV - 960) /31.2 = T
		
		((adc *806) - 960000) / 31200 = T
		
		*/
		
		Current_Temp = ((ADC_Sample * 806) - 960000) / 31200;
		
		if(TEC_Get() >= Current_Temp) {
			TEC_Stop();
		}
		
		printf("Critical Can Cooler V1.0\nCurrent Temp: %d\nDesired Temp: %d\nTEC Status: ", Current_Temp, TEC_Get());
		if(TEC_Status()) {
			printf("ON\n");
		}
		else {
			printf("OFF\n");
		}
		
		WaitForInterrupt();
	}
}
