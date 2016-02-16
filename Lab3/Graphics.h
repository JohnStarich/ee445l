// Graphics.h
// Runs on LM4F120/TM4C123
// Software to control a initialization and output to the display.
// Jon Ambrose and John Starich
// Feb 10, 2016

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

// Define the hour positions of the hour hand
#define HOUR_1 79,24
#define HOUR_2 90,35
#define HOUR_3 94,50
#define HOUR_4 90,65
#define HOUR_5 79,76
#define HOUR_6 64,80
#define HOUR_7 49,76
#define HOUR_8 38,65
#define HOUR_9 34,50
#define HOUR_10 38,35
#define HOUR_11 49,24
#define HOUR_12 64,20

// Define the minute positions of the minute hand
#define MIN_0 64,10
#define MIN_1 68,10
#define MIN_2 72,11
#define MIN_3 76,12
#define MIN_4 80,13
#define MIN_5 84,15
#define MIN_6 88,18
#define MIN_7 91,20
#define MIN_8 94,23
#define MIN_9 96,26
#define MIN_10 99,30
#define MIN_11 101,34
#define MIN_12 102,38
#define MIN_13 103,42
#define MIN_14 104,46
#define MIN_15 104,50
#define MIN_16 104,54
#define MIN_17 103,58
#define MIN_18 102,62
#define MIN_19 101,66
#define MIN_20 99,70
#define MIN_21 96,74
#define MIN_22 94,77
#define MIN_23 91,80
#define MIN_24 88,82
#define MIN_25 84,85
#define MIN_26 80,87
#define MIN_27 76,88
#define MIN_28 72,89
#define MIN_29 68,90
#define MIN_30 64,90
#define MIN_31 60,90
#define MIN_32 56,89
#define MIN_33 52,88
#define MIN_34 48,87
#define MIN_35 44,85
#define MIN_36 40,82
#define MIN_37 37,80
#define MIN_38 34,77
#define MIN_39 32,74
#define MIN_40 29,70
#define MIN_41 27,66
#define MIN_42 26,62
#define MIN_43 25,58
#define MIN_44 24,54
#define MIN_45 24,50
#define MIN_46 24,46
#define MIN_47 25,42
#define MIN_48 26,38
#define MIN_49 27,34
#define MIN_50 29,30
#define MIN_51 32,26
#define MIN_52 34,23
#define MIN_53 37,20
#define MIN_54 40,18
#define MIN_55 44,15
#define MIN_56 48,13
#define MIN_57 52,12
#define MIN_58 56,11
#define MIN_59 60,10

void Alarm_clock_Graphics_Init(void);
void ST7735_DrawCircle(int x0, int y0, int radius, int color);
void ST7735_DrawLine(int x0, int y0, int x1, int y1, int color);
