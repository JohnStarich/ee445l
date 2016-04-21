#include "..//inc//tm4c123gh6pm.h"
#include <stdint.h>
#include <stdio.h>

#include "PLL.h"
#include "PWM.h"
#include "Tachometer.h"
#include "Buttons.h"
#include "ST7735.h"
#include "SysTick.h"

#define F16HZ (50000000/16)
#define F20KHZ (50000000/20000)

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
long StartCritical (void);    // previous I bit, disable interrupts
void EndCritical(long sr);    // restore I bit to previous value
void WaitForInterrupt(void);  // low power mode

uint32_t Target_Speed = 300;				// initial 30 rps

void Button0(void){
	//if(Target_Speed != 400){ Target_Speed += 50; }
};
void Button1(void){
	if(Target_Speed != 0){ Target_Speed -= 50; }
};
void Button2(void){
	if(Target_Speed != 400){ Target_Speed += 50; }
}

int main(void) {
	PLL_Init(Bus80MHz);             // bus clock at 50 MHz
  Tach_Init();										// initialize the Tach measureing input capture
	PWM0A_Init(40000, 30000); 			// 1000 Hz
	Buttons_Init();
	ST7735_InitR(INITR_REDTAB);
	SysTick_Init();

	EnableInterrupts();

	int32_t x = 0;
	ST7735_SetCursor(0,0);
	printf("Speed:\nTarget:");
	while(1) {
		ST7735_SetCursor(8, 0);
		int32_t speed = ST7735_TFTHEIGHT - 20 - Tach_GetSpeed() / 4;
		printf("%5d.%01d rps", speed / 10, speed % 10);
		ST7735_SetCursor(8, 1);
		printf("%5d.%01d rps", Target_Speed / 10, Target_Speed % 10);
		
		if(x == 0) ST7735_PlotClear(32, 159);

		while(! SysTick_ShouldDraw());
		ST7735_DrawPixel(x+1, speed+1, ST7735_RED);
		ST7735_DrawPixel(x+1, speed, ST7735_RED);
		ST7735_DrawPixel(x, speed+1, ST7735_RED);
		ST7735_DrawPixel(x, speed, ST7735_RED);
		x = (x + 1) % ST7735_TFTWIDTH;
		WaitForInterrupt();
	}
}
