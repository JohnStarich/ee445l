// Speaker.h
// Runs on LM4F120/TM4C123
// Software to control a speaker
// Jon Ambrose and John Starich
// Feb 10, 2016


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"
#include "Bool.h"

// This function enables and disables speaker output
// Outputs: None
// Inputs: enable signal: 1 = on, 0 = off
// Assumes Timer0A Interrupt has been initialized.

void SpeakerEnable(bool enable) {
	// this effectively turns the speaker on and off
	if(enable)
		PWM0_ENABLE_R |= 0x01;
	else
		PWM0_ENABLE_R &= ~0x01;
}
