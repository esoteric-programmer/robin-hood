#ifndef BUTTON_ARRAY_INCLUDED
#define BUTTON_ARRAY_INCLUDED

#include <3ds.h>
#include <sf2d.h>

#include "Button.h"

class CButtonArray{

private:
	CButton* button_array[3];
	bool button_drawable[3];
	s16 active_button;
	s16 active_touch_button;
	bool highlight_active_button;
	bool touch_down;
	bool a_inperrupted;
	bool a_down;
	s16 last_touch_x;
	s16 last_touch_y;

public:
	CButtonArray(CTexture** button_textures, u16 number_of_button_textures);
	s16 update(touchPosition touch, bool touch_hold, bool a_hold, bool up_pressed, bool down_pressed, s16 screen_offset_y);
	void set_button(s16 button_id, CTexture** text_textures, u16 number_of_text_textures);
	void set_enabled(s16 button_id, bool enabled);
	void draw(s16 screen_offset_y);
	~CButtonArray();

};

#endif

