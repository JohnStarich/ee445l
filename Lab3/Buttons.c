
#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Bool.h"
#include "Buttons.h"
#include "Timers.h"

void Buttons_Init(void) {
	SYSCTL_RCGCGPIO_R |= 0x10;        // 1) activate clock for Port E
  while((SYSCTL_PRGPIO_R&0x10)==0); // allow time for clock to start
                                    // 2) no need to unlock PE0-3
  GPIO_PORTE_PCTL_R &= ~0x000F0F00; // 3) regular GPIO
  GPIO_PORTE_AMSEL_R &= ~0x0F;      // 4) disable analog function on PE0-3
                                    // 5) no pullup for external switches
  GPIO_PORTE_DIR_R &= ~0x0F;        // 5) set direction to output
  GPIO_PORTE_AFSEL_R &= ~0x0F;      // 6) regular port function
  GPIO_PORTE_DEN_R |= 0x0F;         // 7) enable digital port
	
	Timer1_Init();
}

// 0-23 hours
int32_t hours = 0;
// 0-59 minutes
int32_t minutes = 0;
bool set_alarm = false;

// bool debounce[4] = { hours, minutes, arm_alarm, set_alarm };
bool debounce[4];

int32_t Buttons_Hours(void) {return hours;}
int32_t Buttons_Minutes(void) {return minutes;}
bool Buttons_SetAlarmMode(void) {return set_alarm;}

void Buttons_ReadInput(void) {
	int32_t data = GPIO_PORTE_DATA_R;
	if(! debounce[0])
		debounce[0] += (data & 0x01)*2;
	if(! debounce[1])
		debounce[1] += ((data & 0x2) >> 1)*2;
	if(! debounce[2])
		debounce[2] += ((data & 0x4) >> 2)*2;
	if(! debounce[3])
		debounce[3] += ((data & 0x8) >> 3)*2;
}

void Buttons_Pressed(uint32_t button) {
	if(button == 0)
		hours = (hours + 1) % 24;
	else if(button == 1)
		minutes = (minutes + 1) % 60;
	else if(button == 2)
		Alarm_active = ! Alarm_active;
	else if(button == 3)
		set_alarm = ! set_alarm;
}

void Buttons_10ms_Handler(void) {
	Buttons_ReadInput();
	for(uint32_t i = 0; i < 4; i += 1) {
		if(debounce[i] > 0) {
			debounce[i] -= 1;
			if(debounce[i] == 0) {
				Buttons_Pressed(i);
			}
		}
	}
}
