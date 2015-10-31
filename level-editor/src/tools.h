#ifndef TOOLS_INCLUDED
#define TOOLS_INCLUDED

#include <SDL2/SDL.h>

typedef struct {
	int x;
	int y;
} Vector;

SDL_Surface* rgba_sf(unsigned int w, unsigned int h);

#endif

