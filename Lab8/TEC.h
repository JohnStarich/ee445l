// TEC.h
// Runs on LM4F120/TM4C123
// Software to control the Thermoelectric Cooling (TEC) plates
// Jon Ambrose and John Starich
// April 6, 2016

#include <stdbool.h>
#include <stdint.h>

/**
 * Initialize the Thermoelectric Cooling plates
 */
void TEC_Init(void);

/**
 * Start running the TEC plates
 */
void TEC_Start(void);

/**
 * Stop running the TEC plates
 */
void TEC_Stop(void);

/**
 * Get the current on/off status of the TEC plates
 */
bool TEC_Status(void);

/**
 * Increase the desired temperature
 */
void TEC_Temp_Up(void);

/**
 * Decrease the desired temperature
 */
void TEC_Temp_Down(void);

/**
 * Get the current desired temperature
 */
int16_t TEC_Get(void);

