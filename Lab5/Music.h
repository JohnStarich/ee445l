// Song.h
// Runs on TM4C123
// Song data structure
// John Starich and Jon Ambrose
// February 24, 2016

#ifndef MUSIC_H
#define MUSIC_H 1

#include <stdint.h>

#define A 440
#define B 494
#define D 294
#define G 415

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
Note Song_CurrentNote(Song song, uint32_t beatIndex);

/**
 * Get the current pitch for an instrument with the specified voice index.
 */
uint16_t Instrument_CurrentVoltage(Instrument voice, uint32_t voiceIndex);

void Song_PlayInit(Song song);
void Song_PlayHandler(void);

extern Note mary_lamb[];

#endif
