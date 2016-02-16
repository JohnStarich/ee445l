// Graphics.h
// Runs on LM4F120/TM4C123
// Software to control a initialization and output to the display.
// Jon Ambrose and John Starich
// Feb 10, 2016

#ifndef Graphics
#define Graphics

#define CLOCK_CENTER	64,50		
#define CLOCK_RADIUS	40

struct clock_hand_pos {
	uint32_t x;
	uint32_t y;
};

struct clock_hand_pos Hour_hand[12] = { {64,20},{79,24},{90,35},{94,50},{90,65},{79,76},{64,80},{49,76},{38,65},{34,50},{38,35},{49,24} };
struct clock_hand_pos Min_hand[60] = {
{64,10},
{68,10},
{72,11},
{76,12},
{80,13},
{84,15},
{88,18},
{91,20},
{94,23},
{96,26},
{99,30},
{101,34},
{102,38},
{103,42},
{104,46},
{104,50},
{104,54},
{103,58},
{102,62},
{101,66},
{99,70},
{96,74},
{94,77},
{91,80},
{88,82},
{84,85},
{80,87},
{76,88},
{72,89},
{68,90},
{64,90},
{60,90},
{56,89},
{52,88},
{48,87},
{44,85},
{40,82},
{37,80},
{34,77},
{32,74},
{29,70},
{27,66},
{26,62},
{25,58},
{24,54},
{24,50},
{24,46},
{25,42},
{26,38},
{27,34},
{29,30},
{32,26},
{34,23},
{37,20},
{40,18},
{44,15},
{48,13},
{52,12},
{56,11},
{60,10},
};


void Alarm_clock_Graphics_Init(void);
void Graphics_DrawCircle(int x0, int y0, int radius, int color);
void Graphics_DrawLine(int x0, int y0, int x1, int y1, int color);

#endif
