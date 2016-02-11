// Speaker.h
// Runs on LM4F120/TM4C123
// Software to control a speaker
// Jon Ambrose and John Starich
// Feb 10, 2016


#include <stdint.h>
#include "../inc/tm4c123gh6pm.h"

// This function enables and disables speaker output
// Outputs: None
// Inputs: enable signal: 1 = on, 0 = off
// Assumes Timer0A Interrupt has been initialized.

void SpeakerEnable(uint32_t enable) {
	NVIC_EN0_R = enable<<19;              // enable/disable interrupt 19 in NVIC
																				// this effectively turns the speaker on and off
}