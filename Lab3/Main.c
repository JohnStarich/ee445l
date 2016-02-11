// Main.c
// Runs on TM4C123


/* This example accompanies the book
   "Embedded Systems: Real Time Interfacing to Arm Cortex M Microcontrollers",
   ISBN: 978-1463590154, Jonathan Valvano, copyright (c) 2015

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


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "PLL.h"
#include "ST7735.h"
#include <stdio.h>
#include "Bool.h"
#include "Buttons.h"
#include "Graphics.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

/***** GLOBAL VARIABLES *****/
uint32_t Systick_one_sec = false;				// semaphore for one second intervals updated by the Systick Timer.
/****************************/

int32_t hourXLocations[24] = {0, 20};
int32_t hourYLocations[24] = {0, 20};
int32_t minuteXLocations[24] = {0, 20};
int32_t minuteYLocations[24] = {0, 20};

int main(void){
	DisableInterrupts();									// disable interrupts while configuring
  PLL_Init(Bus80MHz);                   // 80 MHz
  SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F
  GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x06;          // disable alt funct on PF2, PF1
  GPIO_PORTF_DEN_R |= 0x06;             // enable digital I/O on PF2, PF1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
  PF2 = 0;                              // turn off LED
	ST7735_InitR(INITR_REDTAB);
	EnableInterrupts();

	Buttons_Init();
	while (1) {
		Systick_one_sec = true;						// acknowledge the systick semaphore

		Buttons_ReadInput();
		Graphics_DrawCircle();
		//TODO: offset to center later
		//draw hour hand
		Graphics_DrawLine(0, 0, hourXLocations[Buttons_Hours()], hourYLocations[Buttons_Hours()]);
		//draw minute hand
		Graphics_DrawLine(0, 0, minuteXLocations[Buttons_Hours()], minuteYLocations[Buttons_Hours()]);

		while(Systick_one_sec == false);		// wait for systick timer then run main loop
	}
}
// End of Main
