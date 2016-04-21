#include <stdint.h>
#include "PWM.h"
#include "..//inc//tm4c123gh6pm.h"

#define PC5 										(*((volatile uint32_t *)0x40006080))	// PC5 Direct address
#define STABILITY_COEFFICIENT 	3																			// Increase to make it more responsive, Decrease to make it more stable
#define PID_DELAY_VALUE 				10																		// Adjust to control how often the PID corrects speed

uint32_t Period;
int32_t Overflow;
int32_t Done;
uint32_t static Cnt;
extern uint32_t Target_Speed;
uint32_t Speed;      // motor speed in 0.1 rps
int32_t E = 0;           // speed error in 0.1 rps
int32_t U = 0;           // duty cycle 40 to 39960
uint32_t PID_delay = PID_DELAY_VALUE; // delay counter for PID control

void EnableInterrupts(void);  // Enable interrupts

void Tach_Init(void){

	SYSCTL_RCGC1_R |= SYSCTL_RCGC1_TIMER0;
	SYSCTL_RCGC2_R |= SYSCTL_RCGC2_GPIOC + SYSCTL_RCGC2_GPIOD;
	Period = 0;
	Overflow = 0;
	Done = 0;
	Cnt = 0;
	GPIO_PORTC_DIR_R |= 0X20;
	GPIO_PORTC_DEN_R |= 0X20;
	GPIO_PORTD_AFSEL_R |= 0X10;													// PD4 is the Tachometer input
	TIMER0_CTL_R &= ~(TIMER_CTL_TAEN|TIMER_CTL_TBEN);
	TIMER0_CFG_R = TIMER_CFG_16_BIT;
	
	//timer0a init
	TIMER0_TAMR_R = (TIMER_TAMR_TACMR|TIMER_TAMR_TAMR_CAP);
	TIMER0_CTL_R &= ~TIMER_CTL_TAEVENT_M;
	TIMER0_CTL_R += TIMER_CTL_TAEVENT_POS;
	TIMER0_TAILR_R = TIMER_TAILR_M;
	TIMER0_IMR_R |= TIMER_IMR_CAEIM;
	TIMER0_ICR_R = TIMER_ICR_CAECINT;
	
	//timer0b init
	TIMER0_TBMR_R = TIMER_TBMR_TBMR_PERIOD;
	TIMER0_TBILR_R = 6000;
	TIMER0_IMR_R |= TIMER_IMR_TBTOIM;
	TIMER0_ICR_R = TIMER_ICR_TBTOCINT;
	TIMER0_CTL_R |= TIMER_CTL_TBEN;
	
	//interrupt init
	NVIC_PRI4_R = (NVIC_PRI4_R & 0x00FFFFFF) | 0x40000000;
	NVIC_PRI5_R = (NVIC_PRI5_R & 0xFFFFFF00) | 0x00000040;
	NVIC_EN0_R = (1<<19 | 1<<20);
	EnableInterrupts();
}

void Timer0A_Handler(void){
	TIMER0_ICR_R = TIMER_ICR_CAECINT;
	
	if(Overflow){
		Period = 4294967295;
		Overflow = 0;
	}
	
	else{
		Period = Cnt;
	}
	Cnt = 0;
	Done = -1;
	
	TIMER0_CTL_R &= ~TIMER_CTL_TBEN;
	TIMER0_TBILR_R = 6000;
	TIMER0_ICR_R = TIMER_ICR_TBTOCINT;
	TIMER0_CTL_R |= TIMER_CTL_TBEN;
	
	if(PID_delay == 0){

		Speed = 200000000/Period; // 0.1 rps
		E = Target_Speed-Speed;   // 0.1 rps
		U = U+(STABILITY_COEFFICIENT*E)/64;  // discrete integral
		if(U < 100) U=100;        // Constrain output
		if(U>39900) U=39900;      // 100 to 39900
		PWM0A_Duty(U);            // output
		PID_delay = PID_DELAY_VALUE;
	}
	else {
		PID_delay -= 1;
	}
};

void Timer0B_Handler(void){

	PC5 = 0x20;
	TIMER0_ICR_R = TIMER_ICR_TBTOCINT;
	Cnt = Cnt + 1;
	if(Cnt == 0){
		Overflow = -1;
	}
	PC5 = 0x00;
};
