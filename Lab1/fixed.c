// filename ******** fixed.h ************** 
// possible header file for Lab 1 
// feel free to change the specific syntax of your system
// put your name here
// put the date here

#include "ST7735.h"
#include "stdio.h"

int fputc(int ch, FILE *f){ // Print a character to ST7735 LCD
	ST7735_OutChar(ch);
	return 1;
}

void ST7735_sDecOut3(int32_t n) {
	if(n > 9999 || n < -9999) {
		printf(" *.***");
		return;
	}
	if(n < 0) {
		printf("-");
	}
	else {
		printf(" ");
	}
	printf("%d.%d\n", n / 1000, n % 1000);
}

uint32_t toBinFix(uint32_t n) {
	//n = n * 1000 / 256;
	//n = n * 125 / 32;
	n = (n * 125) >> 5;
	if (n % 10 >= 5) {
		n += 10;
	}
	n /= 10;
	return n;
}

void ST7735_uBinOut8(uint32_t n) {
	if(n > 256000) {
		printf("***.**");
		return;
	}
	n = toBinFix(n);
	//99999 / 10000 = 9
	if(n / 10000 == 0) {
		printf(" ");
	}
	if(n / 1000 == 0) {
		printf(" ");
	}
	printf("%d.%d\n", n / 100, n % 100);
}

int32_t gminX, int32_t gmaxX, int32_t gminY, int32_t gmaxY;

void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY) {
	ST7735_InitR(INITR_REDTAB);
  ST7735_FillScreen(0);  // set screen to black
  ST7735_SetCursor(0,0);
	printf("%s\n", title);
	gminX = minX;
	gmaxX = maxX;
	gminY = minY;
	gmaxY = maxY;
}

void ST7735_XYplot(uint32_t num, int32_t bufX[], int32_t bufY[]) {
	uint32_t i, x, y;
	uint32_t currentX = 0;
	for(i = 0; i < num; i += 1) {
		if (bufX[i] > gmaxX || bufX[i] < gminX || bufY[i] > gmaxY || bufY[i] < gminY) {
			continue;
		}
		while(currentX != bufX[i]) {
			ST7735_PlotNext();
			currentX = (currentX + 1) % gmaxX;
		}
		ST7735_PlotPoint(bufY[i]);
	}
}
