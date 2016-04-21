#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include "PLL.h"
#include "PWM.h"
#include "Tachometer.h"
#include "Buttons.h"

#define F16HZ (50000000/16)
#define F20KHZ (50000000/20000)

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

uint32_t Target_Speed = 300;				// initial 30 rps

void Button0(void){
	if(Target_Speed != 400){ Target_Speed += 50; }
};
void Button1(void){
	if(Target_Speed != 0){ Target_Speed -= 50; }
};
void Button2(void){}; // no button 2 yet

int main(void) {
	PLL_Init(Bus80MHz);             // bus clock at 50 MHz
  Tach_Init();										// initialize the Tach measureing input capture
	PWM0A_Init(40000, 30000); 			// 1000 Hz
	Buttons_Init();
	EnableInterrupts();
}
