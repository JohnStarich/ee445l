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
#include "PLL.h"
#include "Timer1A.h"
#include "SysTick.h"
#include "Buttons.h"
#include "ADCSWTrigger.h"

#define PF1       (*((volatile uint32_t *)0x40025008))
#define PF2       (*((volatile uint32_t *)0x40025010))
#define PF3       (*((volatile uint32_t *)0x40025020))
#define LEDS      (*((volatile uint32_t *)0x40025038))
#define RED       0x02
#define BLUE      0x04
#define GREEN     0x08

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void PortF_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x20;				// activate port F
	while((SYSCTL_PRGPIO_R&0x0020) == 0){};// ready?
	GPIO_PORTF_DIR_R |= 0x0E;					// make PF3-1 output (PF3-1 built-in LEDs)
	GPIO_PORTF_AFSEL_R &= ~0x0E;			// disable alt funct on PF3-1
	GPIO_PORTF_DEN_R |= 0x0E;					// enable digital I/O on PF3-1
																		// configure PF3-1 as GPIO
	GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
	GPIO_PORTF_AMSEL_R = 0;						// disable analog functionality on PF
}

void PortE_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;        // activate port E
	while((SYSCTL_PRGPIO_R & 0x0010) == 0){}; // wait for clock on port
	GPIO_PORTE_DIR_R |= 0x01;         // set PE0 as output
	GPIO_PORTE_AFSEL_R &= ~0x01;      // disable alternate functions on PE0
	GPIO_PORTE_DEN_R |= 0x01;         // enable digital IO on PE0
	
	GPIO_PORTE_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFFFF0)+0x0;
	GPIO_PORTE_AMSEL_R = 0;           // disable analog functionality on PE
}

int main(void){ 
	DisableInterrupts();
  PLL_Init(Bus80MHz);								// bus clock at 50 MHz
	PortF_Init();
  LEDS = 0;													// turn all LEDs off
	Buttons_Init();
	SysTick_Init();
	//Timer0A_Init(&Song_PlayHandler, F20KHZ);	// initialize timer0A (20,000 Hz)
  //Timer0A_Init(&Song_PlayHandler, F16HZ);		// initialize timer0A (16 Hz)
	
	/*
	here we initialize our timers and our GPIO
	for PE0 PE3 (TEC toggler and temperature sensor, respectively)
	*/
	Buttons_Init();
	ADC0_InitSWTriggerSeq3_Ch0();
	PortE_Init();
	
  EnableInterrupts();
		
	while(1){
		/*
		We will read the ADC, check for input, and print to the screen
		*/
		for(int i = 0; i < 1000000; i += 1);
  }
}
