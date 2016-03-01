// Song.h
// Runs on TM4C123
// Song data structure
// John Starich and Jon Ambrose
// February 24, 2016

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

/** Constructor for Song */
Song Song_Create(uint16_t tempo, Note *notes);

/** Constructor for Note */
Note Note_Create(uint16_t pitch, uint16_t duration, Instrument voice);

/**
 * Get the current output voltage for the specified beat index for this song.
 * The beat index is the index of which beat (or quarter-note beat) in the song to find a voltage for.
 */
uint16_t Song_CurrentOutput(Song song, uint32_t beatIndex);

/**
 * Get the current pitch for an instrument with the specified beat index.
 */
uint16_t Instrument_CurrentPitch(Instrument voice, uint32_t beatIndex);

extern Note mary_lamb[] = {
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
