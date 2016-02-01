// filename ******** fixed.h ************** 
// possible header file for Lab 1 
// feel free to change the specific syntax of your system
// put your name here
// put the date here

#include "ST7735.h"
#include "stdio.h"
#include <stdlib.h>

void ST7735_sDecOut3(int32_t n) {
	if(n > 9999 || n < -9999) {
		printf(" *.***");
		return;
	}
	if(n >= 0) {
		printf(" ");
	}
	else {
		printf("-");
	}
	printf("%d.%03d", abs(n / 1000), abs(n % 1000));
}

uint32_t toBinFix(uint32_t n) {
	//n = n * 1000 / 256;
	//n = n * 125 / 32;
	n = (n * 125) >> 5;
	// remove this if statement to remove rounding
	if (n % 10 >= 5) {
		n += 10;
	}
	n /= 10;
	return n;
}

void ST7735_uBinOut8(uint32_t n) {
	if(n >= 256000) {
		printf("***.**");
		return;
	}
	n = toBinFix(n);
	printf("%3u.%02u", n / 100, n % 100);
}

int32_t gminX, gmaxX, gminY, gmaxY;

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY) {
	ST7735_FillScreen(0);  // set screen to black
  ST7735_SetCursor(0,0);
	printf("%s\n", title);
	gminX = minX;
	gmaxX = maxX;
	gminY = minY;
	gmaxY = maxY;
}

void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]) {
	uint32_t i, mappedX, mappedY;
	for(i = 0; i < num; i += 1) {
		if (bufX[i] > gmaxX || bufX[i] < gminX || bufY[i] > gmaxY || bufY[i] < gminY) {
			continue;
		}
		mappedX = (127*(bufX[i]-gminX))/(gmaxX-gminX);
		mappedY = 32+(127*(gmaxY-bufY[i]))/(gmaxY-gminY);
		ST7735_DrawPixel(mappedX, mappedY, ST7735_BLUE);
	}
}
