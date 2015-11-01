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

	bool mouse_snap_to_grid;
	
	// SELECTION
	int selected_type;
	void* selected_object;
	
	CLevel level;
	
	// textures
	CTexture grass;
	CTexture grass_r;
	CTexture grass_l;
	CTexture grass_lr;
	CTexture finish;
	CTexture solid;
	CTexture robin;
	CTexture enemy;
	CTexture flower;
	CTexture stones;
	
	void process_mouse(CMouse* mouse, Vector display_pos, CTexture*& texture, int& x, int& y);

public:
	CLevelDisplay(Vector initial_size);
	void change_size(Vector size);
	void draw(SDL_Surface* screen, Vector position, CMouse* mouse);
	void click(CMouse* mouse, Vector lvldisplay_position);
	
	~CLevelDisplay();
};

#endif

