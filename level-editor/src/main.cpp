#include <SDL2/SDL.h>
#include <stdio.h>

#include "tools.h"
#include "Texture.h"
#include "LevelDisplay.h"

extern const RawImage CURSOR;
extern const RawImage ROBIN_RIGHT;
extern const RawImage GRASS;
extern const RawImage GRASS_LEFT;
extern const RawImage GRASS_RIGHT;
extern const RawImage GRASS_LEFT_RIGHT;
extern const RawImage FINISH;
extern const RawImage ENEMY_RIGHT;
extern const RawImage SOLID_BLOCK;
extern const RawImage FLOWER1_1;
extern const RawImage TREE;
extern const RawImage STONES;
extern const RawImage CLOUD_1;
extern const RawImage CLOUD_2;
extern const RawImage CLOUD_3;

extern const RawImage TOOLBOX_SELECTION;

bool redraw_in_queue = false;

bool redraw(Uint32 window_id) {
	if (!redraw_in_queue) {
		redraw_in_queue = true;
		SDL_Event sdlevent;
		sdlevent.type = SDL_WINDOWEVENT;
		sdlevent.window.type = SDL_WINDOWEVENT;
		sdlevent.window.event = SDL_WINDOWEVENT_EXPOSED;
		sdlevent.window.windowID = window_id;
		sdlevent.window.data1 = -2;
		sdlevent.window.data2 = -2;
		SDL_PushEvent(&sdlevent);
	}
}

int main(int argc, char* argv[]) {
	if (SDL_Init(SDL_INIT_VIDEO) == -1) {
		printf("Could not initialize SDL: %s\n", SDL_GetError());
		return -1;
	}
	
	SDL_Window* window = SDL_CreateWindow("Level Editor for Robin Hood's Platform Game",SDL_WINDOWPOS_UNDEFINED,SDL_WINDOWPOS_UNDEFINED,800, 600,SDL_WINDOW_SHOWN);
	
	if (!window) {
		printf("Could not create main window: %s\n", SDL_GetError());
		return -1;
	}
	SDL_Surface* screen = SDL_GetWindowSurface(window);
	if (!screen) {
		printf("Could not get surface of main window: %s\n", SDL_GetError());
		return -1;
	}
	SDL_FillRect(screen, 0, SDL_MapRGB(screen->format,0xA0,0xA0,0xA0));
	
	Vector mouse_pos = {100,100};
	CMouse mouse(mouse_pos, CMouse::CURSOR);
	
	SDL_Surface* level_screen = rgba_sf(screen->w-64-16, screen->h-32-16);

	CTexture robin(ROBIN_RIGHT);
	CTexture grass(GRASS);
	CTexture finish(FINISH);
	

	SDL_Surface* toolbox_screen = rgba_sf(60, screen->h);
	SDL_FillRect(toolbox_screen, 0, SDL_MapRGB(toolbox_screen->format,0x7F,0x7F,0x7F));
	CTexture toolbox_selection(TOOLBOX_SELECTION);
	toolbox_selection.draw(0,0,toolbox_screen,false,true);
	CTexture cursor(CURSOR);
	cursor.draw(14,8,toolbox_screen,false,true);
	grass.draw(14,1*48+8,toolbox_screen,false,true);
	CTexture solid(SOLID_BLOCK);
	solid.draw(14,2*48+8,toolbox_screen,false,true);
	CTexture enemy(ENEMY_RIGHT);
	enemy.draw((60-ENEMY_RIGHT.width)/2,3*48+8+(32-ENEMY_RIGHT.height)/2,toolbox_screen,false,true);
	robin.draw((60-ROBIN_RIGHT.width)/2,4*48+8+(32-ROBIN_RIGHT.height)/2,toolbox_screen,false,true);
	finish.draw(14,5*48+8,toolbox_screen,false,true);
	CTexture flower(FLOWER1_1);
	flower.draw((60-FLOWER1_1.width)/2,6*48+8+(32-FLOWER1_1.height)/2,toolbox_screen,false,true);
	CTexture stones(STONES);
	stones.draw((60-STONES.width)/2,7*48+8+(32-STONES.height)/2,toolbox_screen,false,true);
	
	SDL_Rect pos;
	pos.x = 0;
	pos.y = 0;
	SDL_BlitSurface(toolbox_screen, 0, screen, &pos);
	

	Vector ld_size = {screen->w-64-16, screen->h-32-16};
	CLevelDisplay ld(ld_size);
	Vector ld_pos = {64, 32};
	ld.draw(screen,ld_pos,&mouse);

	
	bool exit = false;
	mouse.set_type(CMouse::GRASS);
	SDL_Event event;
	redraw(SDL_GetWindowID(window));
	while(!exit && SDL_WaitEvent(&event)) {
		switch(event.type) {
			case SDL_QUIT:
				exit = true;
				break;
			case SDL_WINDOWEVENT:
				if (event.window.event == SDL_WINDOWEVENT_EXPOSED) {
					SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
					mouse.set_coordinates(mouse_pos);
					ld.draw(screen,ld_pos,&mouse);
					SDL_UpdateWindowSurface(window);
					if (event.window.data1 == -2 && event.window.data2 == -2) {
						redraw_in_queue = false;
					}
				} else {
					// redraw(SDL_GetWindowID(window));
				}
				break;
			case SDL_MOUSEMOTION:
				{
					redraw(SDL_GetWindowID(window));
				}
			default:
				break;
		}
	};
	SDL_FreeSurface(level_screen);
	SDL_FreeSurface(toolbox_screen);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

