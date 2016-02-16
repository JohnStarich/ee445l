#include <stdint.h>
#include "Bool.h"
#include "../inc/tm4c123gh6pm.h"

#define PF1             (*((volatile uint32_t *)0x40025008))
	
extern uint32_t Secs_current, Mins_current, Hours_current, Secs_old, Mins_old, Hours_old, Timer_one_sec, Timer_one_min, Timer_one_hour;

void Timer0A_Init(uint32_t period){
  volatile uint32_t delay;
  // **** general initialization ****
  SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  delay = SYSCTL_RCGCTIMER_R;      // allow time to finish activating
  TIMER0_CTL_R &= ~TIMER_CTL_TAEN; // disable timer0A during setup
  TIMER0_CFG_R = 0;                // configure for 32-bit timer mode
  // **** timer0A initialization ****
                                   // configure for periodic mode
  TIMER0_TAMR_R = TIMER_TAMR_TAMR_PERIOD;
  TIMER0_TAILR_R = period;         // start value
  TIMER0_IMR_R |= TIMER_IMR_TATOIM;// enable timeout (rollover) interrupt
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;// clear timer0A timeout flag
  TIMER0_CTL_R |= TIMER_CTL_TAEN;  // enable timer0A 32-b, periodic, interrupts
  // **** interrupt initialization ****
                                   // Timer0A=priority 1
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x20000000; // top 3 bits
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
}

void Timer0A_Handler(void){
  TIMER0_ICR_R = TIMER_ICR_TATOCINT;    // acknowledge timer0A timeout
	
	PF1 ^= 0x02;
	Secs_old = Secs_current;
	Secs_current += 1;
	Timer_one_sec = true;
	
	if(Secs_current >= 60) {
		Secs_current = 0;
		Mins_old = Mins_current;
		Mins_current += 1;
		Timer_one_min = true;
	}
	if(Mins_current >= 60) {
		Mins_current = 0;
		Hours_old = Hours_current;
		Hours_current += 1;
		Timer_one_hour = true;
	}
	if(Hours_current >= 12) {
		Hours_current = 0;	
	}
	PF1 ^= 0x02;
}
