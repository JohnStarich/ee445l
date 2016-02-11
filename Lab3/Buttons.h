// Buttons.h
// Runs on LM4F120/TM4C123
// Software to control a initialization and input from buttons.
// Jon Ambrose and John Starich
// Feb 10, 2016

#ifndef Buttons_h
#define Buttons_h 1

void Buttons_Init(void);

int32_t Buttons_Hours(void);
int32_t Buttons_Minutes(void);
int32_t Buttons_Seconds(void);

void Buttons_AddTime(bool hours, bool minutes, bool seconds);
void Buttons_ReadInput(void);

#endif
