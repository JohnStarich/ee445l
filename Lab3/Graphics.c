#include "stdint.h"
#include "ST7735.h"

void Graphics_DrawCircle(void) {
}

void Graphics_DrawLine(int32_t x1, int32_t y1, int32_t x2, int32_t y2) {
	for(int16_t x = x1; x < x2; x += 1) {
		ST7735_DrawPixel(x, y1, ST7735_BLUE);
	}

	for(int16_t y = y1; y < y2; y += 1) {
		ST7735_DrawPixel(x1, y, ST7735_BLUE);
	}
}
