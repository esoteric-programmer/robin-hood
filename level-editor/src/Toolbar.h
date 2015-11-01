#ifndef TOOLBAR_INCLUDED
#define TOOLBAR_INCLUDED

#include <SDL2/SDL.h>

#include "Texture.h"
#include "Mouse.h"
#include "tools.h"

class CToolbar {
private:
	SDL_Surface* display;
	CMouse::MouseType selection;
	static const unsigned int width = 60;
	static const CMouse::MouseType elements[8];
	
	CTexture cursor;
	CTexture grass;
	CTexture solid;
	CTexture enemy;
	CTexture robin;
	CTexture finish;
	CTexture flower;
	CTexture stones;
	CTexture toolbox_selection;

public:
	CToolbar(unsigned int height);
	void draw(SDL_Surface* screen, Vector position, CMouse* mouse);
	void click(CMouse* mouse, Vector toolbar_position);
	~CToolbar();

};

#endif

