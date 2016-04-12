// Main.c
// Runs on LM4F120/TM4C123
// Temperature Data Acquisition System
// April 11, 2016

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

/**
 * Note: Three ways we could sample using an ADC conversion process:
 * 1. Successive approximation
 * 2. Sigma delta
 * 3. Flash
 *
 * To initiate an ADC conversion process, we could:
 * 1. Rising/falling edges or timer values
 * 2. Signal period trigger - Time difference between two edges of both rising or both falling edge
 * 3. Signal pulse trigger - Time difference between two edges of opposite edges
 *
 * We check to see if we've begun sampling by looking at the
 * CaptureA Event Raw Interrupt Status (CAERIS) interrupt flag.
 * This is triggered at every interrupt for sampling.
 *
 * To see if we've finished ADC conversion we check the ADC0_RIS_R memory address.
 */
#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "PLL.h"
#include "SysTick.h"
#include "ADCSWTrigger.h"
//#include "ST7735.h"

extern uint32_t ADC_Sample;

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

int main(void){ 
	DisableInterrupts();
	PLL_Init(Bus10MHz);	// bus clock at 10 MHz
	SysTick_Init();
	//ST7735_InitR(INITR_REDTAB);
	ADC0_InitSWTriggerSeq3_Ch0();
		
	EnableInterrupts();
	
	for(int i = 0; i < 100/2; i += 1) {
		printf("%d %d\n", ADC0_InSeq3(), ADC0_InSeq3());
	}
	
	while(1) {
	}
}
