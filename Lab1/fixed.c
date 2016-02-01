/* ******** fixed.h ************** 
 * Jon Ambrose and John Starich
 * 01-30-2016
 * Fixed point display functions and plot functions.
 * Lab 1
 * Mahesh
 * 01-31-2016
 */

#include "ST7735.h"
#include "stdio.h"
#include <stdlib.h>

/****************ST7735_sDecOut3***************
 converts fixed point number to LCD
 format signed 32-bit with resolution 0.001
 range -9.999 to +9.999
 Inputs:  signed 32-bit integer part of fixed-point number
 Outputs: none
 send exactly 6 characters to the LCD 
*/
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

/**
 * Convert binary fixed point to decimal fixed point.
 * n the number to convert from binary fixed point
 * returns the decimal fixed point representation
 */
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


/**************ST7735_uBinOut8***************
 unsigned 32-bit binary fixed-point with a resolution of 1/256. 
 The full-scale range is from 0 to 999.99. 
 If the integer part is larger than 256000, it signifies an error. 
 The ST7735_uBinOut8 function takes an unsigned 32-bit integer part 
 of the binary fixed-point number and outputs the fixed-point value on the LCD
 Inputs:  unsigned 32-bit integer part of binary fixed-point number
 Outputs: none
 send exactly 6 characters to the LCD 
*/
void ST7735_uBinOut8(uint32_t n) {
	if(n >= 256000) {
		printf("***.**");
		return;
	}
	n = toBinFix(n);
	printf("%3u.%02u", n / 100, n % 100);
}

int32_t gminX, gmaxX, gminY, gmaxY;

/**************ST7735_XYplotInit***************
 Specify the X and Y axes for an x-y scatter plot
 Draw the title and clear the plot area
 Inputs:  title  ASCII string to label the plot, null-termination
          minX   smallest X data value allowed, resolution= 0.001
          maxX   largest X data value allowed, resolution= 0.001
          minY   smallest Y data value allowed, resolution= 0.001
          maxY   largest Y data value allowed, resolution= 0.001
 Outputs: none
 assumes minX < maxX, and miny < maxY
*/
void ST7735_XYplotInit(char *title, int32_t minX, int32_t maxX, int32_t minY, int32_t maxY) {
	ST7735_FillScreen(0);  // set screen to black
  ST7735_SetCursor(0,0);
	printf("%s\n", title);
	gminX = minX;
	gmaxX = maxX;
	gminY = minY;
	gmaxY = maxY;
}

/**************ST7735_XYplot***************
 Plot an array of (x,y) data
 Inputs:  num    number of data points in the two arrays
          bufX   array of 32-bit fixed-point data, resolution= 0.001
          bufY   array of 32-bit fixed-point data, resolution= 0.001
 Outputs: none
 assumes ST7735_XYplotInit has been previously called
 neglect any points outside the minX maxY minY maxY bounds
*/
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
