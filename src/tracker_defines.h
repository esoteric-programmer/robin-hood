#ifndef TRACKER_INCLUDED
#define TRACKER_INCLUDED

#include <3ds.h>
#include <string.h>

#define REST -127

#define C3 -12
#define D3 -10
#define E3 -8
#define F3 -7
#define G3 -5
#define A3 -3
#define B3 -1
#define C4 0
#define D4 2
#define E4 4
#define F4 5
#define G4 7
#define A4 9
#define B4 11
#define C5 12
#define D5 14
#define E5 16
#define F5 17
#define G5 19
#define A5 21
#define B5 23
#define C6 24

#define WHOLE_NOTE 192
#define HALF_NOTE 96
#define QUARTER_NOTE 48
#define EIGHTH_NOTE 24
#define SIXTEENTH_NOTE 12
#define SILENCE_AT_END 4


typedef struct {
	s16 pitch;
	u16 value;
} Note;

typedef struct {
	u16 n_notes;
	Note* notes;
} Bar;

typedef struct {
	u16 n_bars;
	Bar* bars;
} Composition;

void clear_composition(Composition& c);
void copy_composition(Composition& dest, Composition src);
Composition telemann_sonata_f();

#endif

