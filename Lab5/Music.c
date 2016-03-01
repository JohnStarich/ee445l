
#include "DAC.h"
#include "Music.h"

const unsigned short Wave[64] = {
	2048,2224,2399,2571,2737,2897,3048,3190,3321,3439,3545,3635,3711,3770,3813,3839,3848,3839,3813,3770,
	3711,3635,3545,3439,3321,3190,3048,2897,2737,2571,2399,2224,2048,1872,1697,1525,1359,1199,1048,906,775,
	657,551,461,385,326,283,257,248,257,283,326,385,461,551,657,775,906,1048,1199,1359,1525,1697,1872
};

/**
 * Get the current pitch for an instrument with the specified voice index.
 */
uint16_t Instrument_CurrentVoltage(uint32_t voiceIndex) {
	//Instrument currentVoice = currentNote.voice;
	return Wave[voiceIndex % 64];
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
Note Song_CurrentNote() {
	return currentSong.notes[noteIndex];
}

void Song_PlayHandler(void){
	Note currentNote = Song_CurrentNote();
	beatIndex += 1;
	if(beatIndex >= currentNote.duration) {
		noteIndex += 1;
		beatIndex = 0;
	}
}

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
	{G, Whole, Flute}
};
