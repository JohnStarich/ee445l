#include "stdint.h"
#include "ST7735.h"


void Draw_Line(int16_t startX, int16_t startY, int16_t endX, int16_t endY) {
	
	for(int16_t x = startX; x < endX; x += 1) {
		ST7735_DrawPixel(x, startY, ST7735_BLUE);
	}
	
	for(int16_t y = startY; y < endY; y += 1) {
		ST7735_DrawPixel(startX, y, ST7735_BLUE);
	}
	
}