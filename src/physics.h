#ifndef PHYSICS_INCLUDED
#define PHYSICS_INCLUDED

#include <3ds.h>

// point or vector
typedef struct {
	float x;
	float y;
} Vector;

typedef struct {
	s32 x;
	s32 y;
} IntVector;

typedef struct {
	s32 x1, y1, x2, y2;
} Rect;

// horizontal or vertical line
typedef struct {
	float position;
	bool vertical;
} Line;

// an object starting at start_point with speed start_speed beeing accelerated.
typedef struct {
	Vector start_point;
	Vector start_speed;
	Vector accelerate;
} Parabel;

Vector getPosition(Parabel p, float time);
Parabel getParabel(Parabel p, float time);
bool intersects(Parabel p, Line l, bool get_second_intersection, float& time);

#endif

