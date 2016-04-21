#include <stdint.h>
#include "PWM.h"
#include "..//inc//tm4c123gh6pm.h"



extern uint32_t Target_Speed;
extern uint32_t Period;     // 24-bit, 12.5 ns units
uint32_t Speed;      // motor speed in 0.1 rps
int32_t E;           // speed error in 0.1 rps
int32_t U;           // duty cycle 40 to 39960

void Timer2A_Handler(void){
	
	TIMER2_ICR_R = 0x01;      // acknowledge timer2A
  Speed = 200000000/Period; // 0.1 rps
  E = Target_Speed-Speed;          // 0.1 rps
  U = U+(3*E)/64;           // discrete integral
  if(U < 100) U=100;        // Constrain output
  if(U>39900) U=39900;      // 100 to 39900
  PWM0A_Duty(U);            // output
}