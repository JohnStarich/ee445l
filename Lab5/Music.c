
#include "DAC.h"
#include "Music.h"

const unsigned short Wave[64] = {
	2048,2224,2399,2571,2737,2897,3048,3190,3321,3439,3545,3635,3711,3770,3813,3839,3848,3839,3813,3770,
	3711,3635,3545,3439,3321,3190,3048,2897,2737,2571,2399,2224,2048,1872,1697,1525,1359,1199,1048,906,775,
	657,551,461,385,326,283,257,248,257,283,326,385,461,551,657,775,906,1048,1199,1359,1525,1697,1872
};

const unsigned short oboe[64] = {
	2126,2164,2238,2550,3356,3496,2550,1510,1322,1322,1406,1462,1538,1690,2078,2268,2418,2664,2930,
	3090,2854,3176,2740,2172,1416,1038,896,980,1132,1368,1604,1984,2126,2164,2238,2550,3356,3496,2550,
	1510,1322,1322,1406,1462,1538,1690,2078,2268,2418,2664,2930,3090,2854,3176,2740,2172,1416,1038,
	896,980,1132,1368,1604,1984
};

const unsigned short trumpet[64] = {
	2014,2176,2312,2388,2134,1578,606,198,1578,3020,2952,2346,2134,2074,2168,2124,2022,2030,2090,2124,
	2022,2022,2116,2226,2168,2150,2158,2210,2176,2098,2030,2090,2014,2176,2312,2388,2134,1578,606,198,
	1578,3020,2952,2346,2134,2074,2168,2124,2022,2030,2090,2124,2022,2022,2116,2226,2168,2150,2158,
	2210,2176,2098,2030,2090
};

const unsigned short flute[64] = {
	2014,2504,2748,3096,3396,3594,3650,3594,3350,3124,2766,2438,2184,2014,1826,1780,1666,1694,1620,1554,
	1488,1348,1196,1102,1018,952,990,1066,1178,1318,1516,1752,2014,2504,2748,3096,3396,3594,3650,3594,
	3350,3124,2766,2438,2184,2014,1826,1780,1666,1694,1620,1554,1488,1348,1196,1102,1018,952,990,1066,
	1178,1318,1516,1752
};

const unsigned short bassoon[64] = {
	2136,2338,2350,2322,2260,2226,2204,2152,2064,1970,1926,1974,2164,2686,3474,3726,3150,2062,1076,618,
	660,944,1252,1614,2076,2540,2840,2922,2750,2402,2010,1638,1316,1064,992,1188,1608,2110,2496,2646,
	2466,2098,1790,1652,1652,1700,1724,1722,1798,1922,2012,2046,2092,2184,2354,2448,2372,2266,2196,
	2204,2218,2152,2054,2006
};

/**
 * Get the current pitch for an instrument with the specified voice index.
 */
uint16_t Instrument_CurrentVoltage(uint32_t voiceIndex) {
	Instrument currentVoice = Song_CurrentNote()->voice;
	switch(currentVoice) {
		case Flute: return flute[voiceIndex % 64];
		case Bassoon: return bassoon[voiceIndex % 64];
		case Oboe: return oboe[voiceIndex % 64];
		case Trumpet: return trumpet[voiceIndex % 64];
	}
	return Wave[voiceIndex % 64];
}

uint16_t Instrument_EnvelopeMultiplier(uint32_t timeIndex) {
	int64_t x = timeIndex * ENVELOPE_SCALE;
	x = 1 - x / 100 + x * x / 20000 - x / 6000 * x / 1000 * x;
	//return x > 0 ? x : 0;
	return (uint16_t)ENVELOPE_SCALE;
}

uint32_t noteIndex = 0;
uint32_t beatIndex = 0;
Song currentSong;

void Song_PlayInit(Song song) {
	currentSong = song;
	noteIndex = 0;
	beatIndex = 0;
}

/**
 * Get the current output voltage for the specified beat index for this song.
 * The beat index is the index of which note in the song to find a pitch for.
 */
Note* Song_CurrentNote() {
	return &currentSong.notes[noteIndex];
}

void Song_PlayHandler(void){
	Note currentNote = *Song_CurrentNote();
	beatIndex += 1;
	if(beatIndex >= currentNote.duration * 2) {
		noteIndex += 1;
		beatIndex = 0;
	}
}

Note ff7_pre[] = {				// Final Fantasy 7 Prelude, 128 notes total
{ B3 , Eighth , Trumpet } ,
{ C3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ A6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ C3 , Eighth , Trumpet } ,
{ G3 , Eighth , Trumpet } ,
{ A3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ G3 , Eighth , Trumpet } ,
{ A3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ G4 , Eighth , Trumpet } ,
{ A4 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ G5 , Eighth , Trumpet } ,
{ A5 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ A6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ C3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ A6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ C3 , Eighth , Trumpet } ,
{ G3 , Eighth , Trumpet } ,
{ A3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,
{ G3 , Eighth , Trumpet } ,
{ A3 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ G4 , Eighth , Trumpet } ,
{ A4 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ G5 , Eighth , Trumpet } ,
{ A5 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ A6 , Eighth , Trumpet } ,
{ E6 , Eighth , Trumpet } ,
{ D6 , Eighth , Trumpet } ,
{ C6 , Eighth , Trumpet } ,
{ B5 , Eighth , Trumpet } ,
{ F5 , Eighth , Trumpet } ,
{ D5 , Eighth , Trumpet } ,
{ C5 , Eighth , Trumpet } ,
{ B4 , Eighth , Trumpet } ,
{ F4 , Eighth , Trumpet } ,
{ D4 , Eighth , Trumpet } ,
{ C4 , Eighth , Trumpet } ,
{ B3 , Eighth , Trumpet } ,
{ F3 , Eighth , Trumpet } ,
{ D3 , Eighth , Trumpet } ,

{0, Whole, Flute}
};
Note mary_lamb[] = {
	//1 BAGABBBAAABDD
	//  1111112112112
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Half, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Half, Flute},
	{B, Quarter, Flute},
	{D, Quarter, Flute},
	{D, Half, Flute},
	
	//2 BAGABBBBAABAG
	//  1111111111114
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Whole, Flute},
	
	//1 BAGABBBAAABDD
	//  1111112112112
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Half, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Half, Flute},
	{B, Quarter, Flute},
	{D, Quarter, Flute},
	{D, Half, Flute},
	
	//3 BAGABBBBAABAGD
	//  11111111111131
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{D, Quarter, Flute},

	//1 BAGABBBAAABDD
	//  1111112112112
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Half, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Half, Flute},
	{B, Quarter, Flute},
	{D, Quarter, Flute},
	{D, Half, Flute},
	
	//3 BAGABBBBAABAGD
	//  11111111111131
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{D, Quarter, Flute},

	//1 BAGABBBAAABDD
	//  1111112112112
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Half, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Half, Flute},
	{B, Quarter, Flute},
	{D, Quarter, Flute},
	{D, Half, Flute},

	//2 BAGABBBBAABAG
	//  1111111111114
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{A, Quarter, Flute},
	{B, Quarter, Flute},
	{A, Quarter, Flute},
	{G, Whole, Flute},
	
	{0, Whole, Flute}
};
