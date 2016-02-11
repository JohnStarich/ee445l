
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Bool.h"
#include "Buttons.h"

void Buttons_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x04;        // 1) activate clock for Port C
  while((SYSCTL_PRGPIO_R&0x20)==0); // allow time for clock to start
                                    // 2) no need to unlock PC0-2
  GPIO_PORTC_PCTL_R &= ~0x000F0F00; // 3) regular GPIO
  GPIO_PORTC_AMSEL_R &= ~0x07;      // 4) disable analog function on PC0-2
                                    // 5) no pullup for external switches
  GPIO_PORTC_DIR_R |= 0x07;         // 5) set direction to output
  GPIO_PORTC_AFSEL_R &= ~0x07;      // 6) regular port function
  GPIO_PORTC_DEN_R |= 0x07;         // 7) enable digital port
}

//    0-23 hours, 0-59 minutes, 0-59 seconds
int32_t hours = 0, minutes = 0, seconds = 0;

int32_t Buttons_Hours(void) {return hours;}
int32_t Buttons_Minutes(void) {return minutes;}
int32_t Buttons_Seconds(void) {return seconds;}

void Buttons_ReadInput(void) {
	bool hours, minutes, seconds;
	hours = GPIO_PORTC_DATA_R & 0x01;
	minutes = (GPIO_PORTC_DATA_R & 0x2) >> 1;
	seconds = (GPIO_PORTC_DATA_R & 0x4) >> 2;
	Buttons_AddTime(hours, minutes, seconds);
}

void Buttons_AddTime(bool hoursPressed, bool minutesPressed, bool secondsPressed) {
	if(hoursPressed) {
		hours = (hours + 1) % 24;
	}
	if(minutesPressed) {
		minutes = (minutes + 1) % 60;
	}
	if(secondsPressed) {
		seconds = (seconds + 1) % 60;
	}
}

