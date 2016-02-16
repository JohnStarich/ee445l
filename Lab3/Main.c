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
#include "Timers.h"
#include "Speaker.h"

#define PF2             (*((volatile uint32_t *)0x40025010))
#define PF1             (*((volatile uint32_t *)0x40025008))

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

/***** GLOBAL VARIABLES *****/
uint32_t Timer_one_sec = false;				// semaphore for one second intervals updated by Timer0A.
uint32_t Timer_one_min = false;				// semaphore for one minute intervals updated by Timer0A.
uint32_t Timer_one_hour = false;			// semaphore for one hour intervals updated by Timer0A.
uint32_t Hours_current = 0;						// holds the current hour
uint32_t Mins_current = 0;						// holds the current minute
uint32_t Secs_current = 0;						// holds the current second
uint32_t Hours_old;										// keeps track of the previous hour time (used for graphics)
uint32_t Mins_old;										// keeps track of the previous min time (used for graphics)
uint32_t Secs_old;										// keeps track of the previous sec time (used for graphics)
uint32_t Hours_alarm = 0;							// holds the alarm hour time
uint32_t Mins_alarm = 0;							// holds the alarm min time
uint32_t Alarm_active = false;				// flag for arming and disarming the alarm.
/****************************/

int main(void){
	volatile uint32_t delay;
	DisableInterrupts();									// disable interrupts while configuring
  PLL_Init(Bus80MHz);                   // 80 MHz
	SYSCTL_RCGCGPIO_R |= 0x20;            // activate port F
  delay = SYSCTL_RCGCGPIO_R;						// delay for port activation
	GPIO_PORTF_DIR_R |= 0x06;             // make PF2, PF1 out (built-in LED)
  GPIO_PORTF_AFSEL_R &= ~0x06;          // disable alt funct on PF2, PF1
  GPIO_PORTF_DEN_R |= 0x06;             // enable digital I/O on PF2, PF1
                                        // configure PF2 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF00F)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;               // disable analog functionality on PF
  PF1 = 0;                              // turn off LED
  PF2 = 0;                              // turn off LED
	ST7735_InitR(INITR_REDTAB);
	Timer0A_Init(80000000);									// initialize timer0A for one second interupts @80MHz
	EnableInterrupts();
	//Buttons_Init();
	
Alarm_clock_Graphics_Init();																																						// draw inital clock face
			
	while(1){
		PF2 ^= 0x02;
		if(Timer_one_hour == true){																																					// if the hour rolled over,
		ST7735_DrawLine(CLOCK_CENTER,Hour_hand[Hours_old].x,Hour_hand[Hours_old].y,ST7735_BLACK); 					// erase the old hour hand
		Timer_one_hour = false;																																							// clear hour hand flag
		}
		if(Timer_one_min == true){																																					// if min hand rolled over,
		ST7735_DrawLine(CLOCK_CENTER,Min_hand[Mins_old].x,Min_hand[Mins_old].y,ST7735_BLACK);								// erase the old min hand
		Timer_one_min = false;																																							// clear flag
		}
		if(Timer_one_sec == true){																																					// if the sec hand rolled over,
																																																				// and it will ever update of Timer0A,
			ST7735_DrawLine(CLOCK_CENTER,Min_hand[Secs_old].x,Min_hand[Secs_old].y,ST7735_BLACK);							// erase old sec hand
			ST7735_DrawLine(CLOCK_CENTER,Hour_hand[Hours_current].x,Hour_hand[Hours_current].y,ST7735_BLUE);	// draw new hour hand
			ST7735_DrawLine(CLOCK_CENTER,Min_hand[Mins_current].x,Min_hand[Mins_current].y,ST7735_BLUE);			// draw new min hand
			ST7735_DrawLine(CLOCK_CENTER,Min_hand[Secs_current].x,Min_hand[Secs_current].y,ST7735_RED);				// draw new sec hand
			Timer_one_sec = false;																																						// clear flag
			ST7735_SetCursor(7,12);																																						// 
			printf("%0d:%02d:%02d",Hours_current,Mins_current,Secs_current);																	// print digital time
		}
		if (Alarm_active) {																																									// if Alarm is on
			if(Hours_current == Hours_alarm && Mins_current == Mins_alarm){																		// and time matches
				SpeakerEnable(1);																																								// activate speaker
				Alarm_active = false;
			}
		}
	PF2 ^= 0x02;
	}																																																			// repeat for all time
}
// End of Main


/**** Initialize the Clock face ****/
void Alarm_clock_Graphics_Init(void){
	ST7735_FillScreen(ST7735_BLACK);
	printf("Lab3");
	ST7735_DrawCircle(CLOCK_CENTER,CLOCK_RADIUS+2,ST7735_WHITE);																					// initial draw of clock face
	
	ST7735_DrawChar(60, 1, 0x31, ST7735_WHITE, ST7735_BLACK, 1); 																					// label clock face
	ST7735_DrawChar(65, 1, 0x32, ST7735_WHITE, ST7735_BLACK, 1); 																					//
	ST7735_DrawChar(87, 7, 0x31, ST7735_WHITE, ST7735_BLACK, 1); 																					//
	ST7735_DrawChar(103, 24, 0x32, ST7735_WHITE, ST7735_BLACK, 1);																				//
	ST7735_DrawChar(109, 48, 0x33, ST7735_WHITE, ST7735_BLACK, 1);																				//
	ST7735_DrawChar(103, 70, 0x34, ST7735_WHITE, ST7735_BLACK, 1);																				//
	ST7735_DrawChar(86, 89, 0x35, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(62, 95, 0x36, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(39, 89, 0x37, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(21, 71, 0x38, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(14, 47, 0x39, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(16, 23, 0x31, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(21, 23, 0x30, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(34, 5, 0x31, ST7735_WHITE, ST7735_BLACK, 1);																					//
	ST7735_DrawChar(39, 5, 0x31, ST7735_WHITE, ST7735_BLACK, 1);																					//
	
	ST7735_DrawLine(CLOCK_CENTER,Hour_hand[Hours_current].x,Hour_hand[Hours_current].y,ST7735_BLUE);			// draw starting time
	ST7735_DrawLine(CLOCK_CENTER,Min_hand[Mins_current].x,Min_hand[Mins_current].y,ST7735_BLUE);					//
	ST7735_DrawLine(CLOCK_CENTER,Min_hand[Secs_current].x,Min_hand[Secs_current].y,ST7735_RED);						//
	
	ST7735_SetCursor(7,12);																																								// print starting time
	printf("%0d:%02d:%02d",Hours_current,Mins_current,Secs_current);																			//
}
