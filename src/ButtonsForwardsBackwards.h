#ifndef BUTTONS_FORWARDS_BACKWARDS_INCLUDED
#define BUTTONS_FORWARDS_BACKWARDS_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Button.h"

class CButtonsForwardsBackwards{

private:
	CButton* button_array[2];
	s16 active_touch_button;
	bool touch_down;
	s16 last_touch_x;
	s16 last_touch_y;
	s16 distance_between;
	s16 map_x_to_button(s16 x, u16 btn_id);

public:
	CButtonsForwardsBackwards(CTexture** button_textures, u16 number_of_button_textures, u16 distance_between);
	s16 update(touchPosition touch, bool touch_hold, s16 screen_offset_y);
	void set_distance(s16 distance_between);
	void draw(s16 screen_offset_y);
	~CButtonsForwardsBackwards();

};

#endif

