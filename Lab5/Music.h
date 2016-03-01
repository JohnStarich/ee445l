// Song.h
// Runs on TM4C123
// Song data structure
// John Starich and Jon Ambrose
// February 24, 2016

#ifndef MUSIC_H
#define MUSIC_H 1

#include <stdint.h>

// if desired interrupt frequency is f, Timer0A_Init parameter is busfrequency/f
#define F16HZ (80000000/16)
#define F20KHZ (80000000/20000)
#define F64HZ	(80000000/64)
#define ENVELOPE_SCALE 100000

#define A 440
#define B 494
//#define D 294
#define D 588
#define G 392

#define C3 131
#define D3 147
#define E3 156//normal:165
#define F3 175
#define G3 196
#define A3 220
#define B3 233//normal:247
#define C4 262
#define D4 294
#define E4 311//normal:330
#define F4 349
#define G4 392
#define A4 440
#define B4 466//494
#define C5 523
#define D5 587
#define E5 622//659
#define F5 698
#define G5 784
#define A5 880
#define B5 932//988
#define C6 1047
#define D6 1175
#define E6 1244//1319
#define F6 1397
#define G6 1568
#define A6 1760
#define B6 1865//1976
#define C7 2093

#define Whole 16
#define Half 8
#define Quarter 4
#define Eighth 2
#define Sixteenth 1

/** Represents the voice/shape of a note's sound. */
typedef enum {
	Oboe,
	Trumpet,
	Bassoon,
	Flute
} Instrument;

/** Represents all data about a note that will be played. */
typedef struct {
	uint16_t pitch;    //frequency for note
	uint16_t duration; //number of beats for note
	Instrument voice;  //sound of note
} Note;

/** Represents a song that will be played. */
typedef struct {
	uint16_t tempo;    //beats per minute
	Note *notes;       //all of the notes in the song
} Song;

/**
 * Get the current output voltage for the specified beat index for this song.
 * The beat index is the index of which beat (or quarter-note beat) in the song to find a voltage for.
 */
Note* Song_CurrentNote(void);

/**
 * Get the current pitch for an instrument with the specified voice index.
 */
uint16_t Instrument_CurrentVoltage(uint32_t voiceIndex);

uint16_t Instrument_EnvelopeMultiplier(uint32_t timeIndex);

void Song_PlayInit(Song song);
void Song_PlayHandler(void);

extern Note mary_lamb[];
extern Note ff7_pre[];

#endif
