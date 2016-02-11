// Speaker.h
// Runs on LM4F120/TM4C123
// Software to control a speaker
// Jon Ambrose and John Starich
// Feb 10, 2016


// This function enables and disables speaker output
// Outputs: None
// Inputs: enable signal: 1 = on, 0 = off
// Assumes Timer0A Interrupt has been initialized.
void SpeakerEnable(uint32_t enable);