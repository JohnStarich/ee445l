#include <stdint.h>
#include "PWM.h"
#include "..//inc//tm4c123gh6pm.h"

#define PC5 										(*((volatile uint32_t *)0x40006080))	// PC5 Direct address
#define STABILITY_COEFFICIENT 	3																			// Increase to make it more responsive, Decrease to make it more stable
#define PID_DELAY_VALUE 				10																		// Adjust to control how often the PID corrects speed

uint32_t Period;
int32_t Overflow;
uint32_t static First;        // Timer0A first edge, 12.5 ns units
int32_t Done;
extern uint32_t Target_Speed;
uint32_t Speed;      // motor speed in 0.1 rps
int32_t E = 0;           // speed error in 0.1 rps
int32_t U = 0;           // duty cycle 40 to 39960
uint32_t PID_delay = PID_DELAY_VALUE; // delay counter for PID control

void EnableInterrupts(void);  // Enable interrupts

void Tach_Init(void){

	SYSCTL_RCGCTIMER_R |= 0x01;      // activate timer0
  SYSCTL_RCGCGPIO_R |= 0x02;       // activate port B
  First = 0;                       // first will be wrong
  Done = 0;                        // set on subsequent
  GPIO_PORTB_DIR_R &= ~0x40;       // make PB6 input
  GPIO_PORTB_AFSEL_R |= 0x40;      // enable alt funct on PB6
  GPIO_PORTB_DEN_R |= 0x40;        // configure PB6 as T0CCP0
  GPIO_PORTB_PCTL_R = (GPIO_PORTB_PCTL_R&0xF0FFFFFF)+0x07000000;
  TIMER0_CTL_R &= ~0x00000001;     // disable timer0A during setup
  TIMER0_CFG_R = 0x00000004;       // configure for 16-bit capture mode
  TIMER0_TAMR_R = 0x00000007;      // configure for rising edge event
  TIMER0_CTL_R &= ~0x0000000C;     // rising edge
  TIMER0_TAILR_R = 0x0000FFFF;     // start value
  TIMER0_TAPR_R = 0xFF;            // activate prescale, creating 24-bit 
  TIMER0_IMR_R |= 0x00000004;      // enable capture match interrupt
  TIMER0_ICR_R = 0x00000004;       // clear timer0A capture match flag
  TIMER0_CTL_R |= 0x00000001;      // timer0A 24-b, +edge, interrupts
  NVIC_PRI4_R = (NVIC_PRI4_R&0x00FFFFFF)|0x40000000; //Timer0A=priority 2
  NVIC_EN0_R = 1<<19;              // enable interrupt 19 in NVIC
  EnableInterrupts();

}

void Timer0A_Handler(void){
	TIMER0_ICR_R = 0x00000004;       // acknowledge timer0A
	
	GPIO_PORTF_DATA_R ^= 0x08;			// heartbeat
	
  Period = (First - TIMER0_TAR_R)&0x00FFFFFF; 
// 24-bit, 12.5ns resolution
  First = TIMER0_TAR_R;            // setup for next
  Done = 1;                        // set semaphore
	
	Speed = 200000000/Period; // 0.1 rps
	
	if(PID_delay == 0){
		E = Target_Speed-Speed;   // 0.1 rps
		U = U+(STABILITY_COEFFICIENT*E)/64;  // discrete integral
		if(U < 100) U=100;        // Constrain output
		if(U>39900) U=39900;      // 100 to 39900
		PWM0B_Duty(U);            // output
		PID_delay = PID_DELAY_VALUE;
	}
	else {
		PID_delay -= 1;
	}
	
	//GPIO_PORTF_DATA_R &= ~0x08;			// heartbeat
	
};

uint32_t Tach_GetPeriod(void) {
	return Period;
}

uint32_t Tach_GetSpeed(void) {
	return Speed;
}
