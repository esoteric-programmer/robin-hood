#ifndef LEVELDISPLAY_INCLUDED
#define LEVELDISPLAY_INCLUDED

#include <SDL2/SDL.h>

#include "Level.h"
#include "Texture.h"
#include "Mouse.h"
#include "List.h"
#include "tools.h"

// TODO: Scrolling / Scrolling-Offset??

class CLevelDisplay {
private:
	int x_offset;
	int y_offset;
	CTexture* background;
	SDL_Surface* display;
	bool scrollbar_x;
	bool scrollbar_y;

	// SELECTION
	int selected_type;
	void* selected_object;
	
	CLevel level;
	
	// textures
	CTexture robin;
	CTexture grass;
	CTexture grass_r;
	CTexture grass_l;
	CTexture grass_lr;
	CTexture finish;
	CTexture solid;
	CTexture enemy;
	CTexture flower;
	CTexture stones;

public:
	CLevelDisplay(Vector initial_size);
	void change_size(Vector size);
	void draw(SDL_Surface* screen, Vector position, CMouse* mouse);
	void click(CMouse* mouse, Vector lvldisplay_position);
	
	~CLevelDisplay();

};

#endif

