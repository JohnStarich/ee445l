#include <stdbool.h>
#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>

int16_t TEC_Temp = 25;

void TEC_Init(void) {
	
	SYSCTL_RCGCGPIO_R |= 0x10;        // activate port E
	while((SYSCTL_PRGPIO_R & 0x0010) == 0){}; // wait for clock on port
	GPIO_PORTE_DIR_R |= 0x01;         // set PE0 as output
	GPIO_PORTE_AFSEL_R &= ~0x01;      // disable alternate functions on PE0
	GPIO_PORTE_DEN_R |= 0x01;         // enable digital IO on PE0
	
	GPIO_PORTE_PCTL_R = (GPIO_PORTF_PCTL_R & 0xFFFFFFF0)+0x0;
}

void TEC_Start(void){
	GPIO_PORTE_DATA_R |= 0x01;
}

void TEC_Stop(void){
	GPIO_PORTE_DATA_R &= ~0x01;
}

bool TEC_Status(void){
 return GPIO_PORTE_DATA_R & 0x01;
}

void TEC_Temp_Up(void){
	TEC_Temp += 1;
}
	
void TEC_Temp_Down(void){
	TEC_Temp -= 1;
}

int16_t TEC_Get(void){
	return TEC_Temp;
}

