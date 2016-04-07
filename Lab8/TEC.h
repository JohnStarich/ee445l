#include <stdbool.h>
#include <stdint.h>

void TEC_Init(void);
void TEC_Start(void);
void TEC_Stop(void);
bool TEC_Status(void);
void TEC_Temp_Up(void);
void TEC_Temp_Down(void);
int16_t TEC_Get(void);
