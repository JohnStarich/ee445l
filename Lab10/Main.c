#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>

#include "PLL.h"
#include "PWM.h"
#include "Timer0A.h"

#define F16HZ (50000000/16)
#define F20KHZ (50000000/20000)

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

void UserTask(void){
	
}

void PortF_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;       // activate port E
	while((SYSCTL_PRGPIO_R&0x0010) == 0){};// ready?
  GPIO_PORTF_DIR_R = (GPIO_PORTF_DIR_R & ~0x08) | 0x04; // make PE2 output, PE3 input
  GPIO_PORTF_AFSEL_R &= ~0x0C;     // disable alt funct on PE2-3
  GPIO_PORTF_DEN_R |= 0x0C;        // enable digital I/O on PE2-3
                                   // configure PE2-3 as GPIO
  GPIO_PORTF_PCTL_R = (GPIO_PORTF_PCTL_R&0xFFFFF0FF)+0x00000000;
  GPIO_PORTF_AMSEL_R = 0;          // disable analog functionality on PF 
}

int main(void) {
	PLL_Init(Bus80MHz);              // bus clock at 50 MHz
  Timer0A_Init(&UserTask, F16HZ);  // initialize timer0A (16 Hz)
	EnableInterrupts();
}
