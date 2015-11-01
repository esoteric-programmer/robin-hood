#include "LevelDisplay.h"

extern const RawImage ROBIN_RIGHT;
extern const RawImage GRASS;
extern const RawImage GRASS_LEFT;
extern const RawImage GRASS_RIGHT;
extern const RawImage GRASS_LEFT_RIGHT;
extern const RawImage SOLID_BLOCK;
extern const RawImage FINISH;
extern const RawImage ROBIN_RIGHT;
extern const RawImage ENEMY_RIGHT;
extern const RawImage FLOWER1_1;
extern const RawImage STONES;

CLevelDisplay::CLevelDisplay(Vector initial_size) :
		grass(GRASS), grass_r(GRASS_RIGHT),
		grass_l(GRASS_LEFT), grass_lr(GRASS_LEFT_RIGHT),
		finish(FINISH),
		solid(SOLID_BLOCK),
		robin(ROBIN_RIGHT), enemy(ENEMY_RIGHT),
		flower(FLOWER1_1), stones(STONES) {

	this->display = rgba_sf(initial_size.x, initial_size.y);
	this->mouse_snap_to_grid = true;

	RawImage BACKGROUND;
	BACKGROUND.width=1;
	BACKGROUND.height=256;
	BACKGROUND.bytes_per_pixel = 4;
	char* data = new char[256*4];
	for (int i=0; i<BACKGROUND.height; i++) {
		for (int j=0; j<BACKGROUND.width; j++) {
			data[(i*BACKGROUND.width + j)*4] = 0;
			data[(i*BACKGROUND.width + j)*4+1] = (255*i)/(BACKGROUND.height-1);
			data[(i*BACKGROUND.width + j)*4+2] = 255;
			data[(i*BACKGROUND.width + j)*4+3] = 255;
		}
	}
	BACKGROUND.pixel_data = data;
	background = new CTexture(BACKGROUND);
	delete data;

	x_offset = 0; // scrolling
	y_offset = 0;  // scrolling
	selected_type = -1; // no selection
	selected_object = 0; // no selection
}

void CLevelDisplay::change_size(Vector size) {
	if (this->display != 0) {
		SDL_FreeSurface(this->display);
	}
	this->display = rgba_sf(size.x, size.y);
}

void CLevelDisplay::draw(SDL_Surface* screen, Vector position, CMouse* mouse) {

	if (screen == 0 || this->display == 0 || this->background == 0) {
		return;
	}

	SDL_Rect dsp = {0,0,this->display->w,this->display->h};
	SDL_FillRect(this->display, 0, SDL_MapRGB(this->display->format,0x7F,0x7F,0x7F));
	this->background->draw_scaled(dsp,this->display,true);
	

	CLevel::Landscape* it = this->level.get_landscape_list()->first();
	while (it != 0) {
		switch (it->type) {
			case 0:
				// GRASS
				if (it->left == 0 && it->x != 0) {
					if (it->right == 0 && it->x + grass.get_width() != this->level.get_width()) {
						grass_lr.draw(it->x, it->y,this->display);
					}else{
						grass_l.draw(it->x, it->y,this->display);
					}
				}else{
					if (it->right == 0 && it->x + grass.get_width() != this->level.get_width()) {
						grass_r.draw(it->x, it->y,this->display);
					}else{
						grass.draw(it->x, it->y,this->display);
					}
				}
				break;
			case 1:
				// SOLID
				solid.draw(it->x, it->y,this->display);
				break;
			default:
				// UNKNOWN
				break;
		}
		it = this->level.get_landscape_list()->next();
	}
	// TODO: enemies, nature, ...
	finish.draw(this->level.get_finish_pos().x,this->level.get_finish_pos().y,this->display);
	robin.draw(this->level.get_start_pos().x,this->level.get_start_pos().y,this->display);
	
	int x = 0;
	int y = 0;
	CTexture* draw_mouse = 0;
	process_mouse(mouse, position, draw_mouse, x, y);
	if (draw_mouse != 0) {
		draw_mouse->draw(x, y, this->display);
	}

	
	SDL_Rect pos = {position.x,position.y,this->display->w,this->display->h};
	SDL_BlitSurface(this->display, 0, screen, &pos);
	
}

void CLevelDisplay::click(CMouse* mouse, Vector lvldisplay_position) {
	int x = 0;
	int y = 0;
	CTexture* draw_mouse = 0;
	process_mouse(mouse, lvldisplay_position, draw_mouse, x, y);
	if (draw_mouse != 0) {
		switch (mouse->get_type()) {
			case CMouse::GRASS:
				{
					CLevel::Landscape grass = {x, y, 0, 0, 0};
					this->level.add_landscape(grass);
					break;
				}
			case CMouse::SOLID:
				{
					CLevel::Landscape solid = {x, y, 1, 0, 0};
					this->level.add_landscape(solid);
					break;
				}
			case CMouse::ROBIN:
				{
					Vector pos = {x, y};
					this->level.set_start_pos(pos);
					break;
				}
			case CMouse::FINISH:
				{
					Vector pos = {x, y};
					this->level.set_finish_pos(pos);
					break;
				}
			default:
				// TODO: more cases
				break;
		}
	}
}

void CLevelDisplay::process_mouse(CMouse* mouse, Vector display_pos, CTexture*& draw_mouse, int& x, int& y) {
	draw_mouse = 0;
	x = 0;
	y = 0;
	if (mouse != 0) {
		Vector mp = mouse->get_coordinates();
		mp.x -= display_pos.x;
		mp.y -= display_pos.y;
		mp.y = this->display->h - mp.y;
		if (mp.x >= 0 && mp.x < this->display->w && mp.y >= 0 && mp.y < this->display->h) {
			bool snap_to_grid_x = false;
			bool snap_to_grid_y = false;
			if (this->mouse_snap_to_grid) {
				if (mouse->get_type() == CMouse::GRASS || mouse->get_type() == CMouse::SOLID) {
					mp.x -= mp.x % 32;
					snap_to_grid_x = true;
				}
				mp.y -= mp.y % 32;
				snap_to_grid_y = true;
			}
			// draw mouse!
			switch (mouse->get_type()) {
				case CMouse::GRASS:
					draw_mouse = &grass;
					break;
				case CMouse::SOLID:
					draw_mouse = &solid;
					break;
				case CMouse::ROBIN:
					draw_mouse = &robin;
					break;
				case CMouse::ENEMY:
					draw_mouse = &enemy;
					break;
				case CMouse::FINISH:
					draw_mouse = &finish;
					break;
				case CMouse::FLOWER:
					draw_mouse = &flower;
					break;
				case CMouse::STONE:
					draw_mouse = &stones;
					break;
				default:
					break;
			}
			if (draw_mouse!=0) {
				x = mp.x - (snap_to_grid_x?0:draw_mouse->get_width()/2);
				y = mp.y - (snap_to_grid_y?0:draw_mouse->get_height()/2);
			}
		}
	}
}

CLevelDisplay::~CLevelDisplay() {
	// TODO: tidy up
	if (this->display != 0) {
		SDL_FreeSurface(this->display);
	}
}


