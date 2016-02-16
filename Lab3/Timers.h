/**
 * Set up timers.
 */

#ifndef __TIMERSINTS_H__ // do not include more than once
#define __TIMERSINTS_H__

void Timer0A_Init(uint32_t period);

// ***************** Timer1_Init ****************
// Activate Timer1 interrupts to run user task periodically
// Inputs:  task is a pointer to a user function
//          period in units (1/clockfreq)
// Outputs: none
void Timer1_Init(void);

#endif // __TIMERSINTS_H__
