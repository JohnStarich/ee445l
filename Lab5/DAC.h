// DAC.h
// Runs on TM4C123
// DAC Driver
// John Starich and Jon Ambrose
// February 24, 2016

#include <stdint.h>

/**
 * Initialize the DAC, setting up any necessary ports and pins.
 */
void DAC_Init(void);

/**
 * Set the DAC output voltage to the specified value.
 * The output is limited to 12 bits so `outputVoltage` will be truncated to 12 bits before setting the output.
 */
void DAC_Output(uint16_t outputVoltage);
