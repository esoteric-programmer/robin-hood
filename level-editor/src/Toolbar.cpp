#include "Toolbar.h"

const CMouse::MouseType CToolbar::elements[8] = {
			CMouse::CURSOR,
			CMouse::GRASS,
			CMouse::SOLID,
			CMouse::ENEMY,
			CMouse::ROBIN,
			CMouse::FINISH,
			CMouse::FLOWER,
			CMouse::STONE};

extern const RawImage CURSOR;
extern const RawImage ROBIN_TOOLBOX;
extern const RawImage GRASS;
extern const RawImage FINISH;
extern const RawImage SOLID_BLOCK;
extern const RawImage ENEMY_RIGHT;
extern const RawImage FLOWER1_1;
extern const RawImage STONES;
extern const RawImage TOOLBOX_SELECTION;


CToolbar::CToolbar(unsigned int height) :
		cursor(CURSOR),
		grass(GRASS), solid(SOLID_BLOCK),
		enemy(ENEMY_RIGHT), robin(ROBIN_TOOLBOX),
		finish(FINISH),
		flower(FLOWER1_1), stones(STONES),
		toolbox_selection (TOOLBOX_SELECTION) {

	this->display = rgba_sf(this->width, height);

	selection = CMouse::CURSOR;
}

void CToolbar::draw(SDL_Surface* screen, Vector position, CMouse* mouse) {
	if (screen == 0 || this->display == 0) {
		return;
	}
	
	if (mouse != 0) {
		this->selection = mouse->get_type();
	}

	SDL_FillRect(this->display, 0, SDL_MapRGB(this->display->format,0x7F,0x7F,0x7F));
	
	for (int i=0;i<8;i++) {
		if (this->elements[i] == this->selection) {
			toolbox_selection.draw(0,i*48,display,false,true);
		}
	}

	cursor.draw(14,8,display,false,true);
	grass.draw(14,1*48+8,display,false,true);
	solid.draw(14,2*48+8,display,false,true);
	enemy.draw((60-ENEMY_RIGHT.width)/2,3*48+8+(32-ENEMY_RIGHT.height)/2,display,false,true);
	SDL_Rect robin_dest_rect = {(60-42)/2,4*48+8+(32-42)/2,42,42};
	robin.draw_scaled(robin_dest_rect,display,true);
	finish.draw(14,5*48+8,display,false,true);
	flower.draw((60-FLOWER1_1.width)/2,6*48+8+(32-FLOWER1_1.height)/2,display,false,true);
	stones.draw((60-STONES.width)/2,7*48+8+(32-STONES.height)/2,display,false,true);
	
	SDL_Rect pos = {position.x,position.y,this->display->w,this->display->h};
	SDL_BlitSurface(this->display, 0, screen, &pos);
	
}

void CToolbar::click(CMouse* mouse, Vector toolbar_position) {
	if (mouse != 0) {
		Vector mp = mouse->get_coordinates();
		mp.x -= toolbar_position.x;
		mp.y -= toolbar_position.y;
		if (mp.x >= 0 && mp.x < this->display->w && mp.y >= 0 && mp.y < this->display->h) {
			// GET ELEMENT AT POSITION
			int element = mp.y/48;
			if (element < 8) {
				this->selection = this->elements[element];
				mouse->set_type(this->selection);
			}
		}
	}
}

CToolbar::~CToolbar() {
	// TODO: tidy up
	if (this->display != 0) {
		SDL_FreeSurface(this->display);
	}
}


