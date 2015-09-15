#include "ButtonsForwardsBackwards.h"


CButtonsForwardsBackwards::CButtonsForwardsBackwards(CTexture** button_textures, u16 number_of_button_textures, u16 distance_between) {
	this->button_array[0] = new CButton(0, button_textures, 0, number_of_button_textures, true, true, true);
	this->button_array[1] = new CButton(0, button_textures, 0, number_of_button_textures, true, true, false);
	this->touch_down = false;
	this->touch_down = false;
	this->distance_between = distance_between;
	this->last_touch_x = -1;
	this->last_touch_y = -1;
}

s16 CButtonsForwardsBackwards::map_x_to_button(s16 x, u16 btn_id) {
	if (btn_id < 0 || btn_id > 1)
		return x;
	return x+this->distance_between/2*(btn_id==0?1:-1);
}

s16 CButtonsForwardsBackwards::update(touchPosition touch, bool touch_hold, s16 screen_offset_y) {
	if (!touch_hold && touch_down) {
		touch_down = false;
		if (active_touch_button < 0 || active_touch_button > 1) {
			active_touch_button = -1;
			return -1;
		}
		
			if (button_array[active_touch_button] != 0) {
				button_array[active_touch_button]->set_state(CButton::ButtonState::NORMAL);
				if (button_array[active_touch_button]->is_at(map_x_to_button(this->last_touch_x,active_touch_button), this->last_touch_y, screen_offset_y)) {
					s16 tmp = active_touch_button;
					active_touch_button = -1;
					return tmp;
				}
			}
			active_touch_button = -1;
	} else if (touch_hold && !touch_down) {
		this->last_touch_x = touch.px;
		this->last_touch_y = touch.py;
		touch_down = true;
		active_touch_button = -1;
		for (s16 i=0; i<2; i++) {
			if (button_array[i] != 0) {
				if (button_array[i]->is_at(map_x_to_button(touch.px,i), touch.py, screen_offset_y)) {
					active_touch_button = i;
					button_array[active_touch_button]->set_state(CButton::ButtonState::ACTIVE);
					break;
				}
			}
		}
	} else if (touch_hold && touch_down) {
		this->last_touch_x = touch.px;
		this->last_touch_y = touch.py;
		if (active_touch_button >= 0 && active_touch_button <= 1) {
			if (button_array[active_touch_button] != 0) {
				if (button_array[active_touch_button]->is_at(map_x_to_button(touch.px,active_touch_button), touch.py, screen_offset_y)) {
					button_array[active_touch_button]->set_state(CButton::ButtonState::ACTIVE);
				}else{
					button_array[active_touch_button]->set_state(CButton::ButtonState::NORMAL);
				}
			}
		}
	}
	return -1; // no button pressed.
}

void CButtonsForwardsBackwards::draw(s16 screen_offset_y) {
	if (this->button_array[0] != 0) {
		this->button_array[0]->draw(this->distance_between/2, screen_offset_y);
	}
	if (this->button_array[1] != 0) {
		this->button_array[1]->draw(-this->distance_between/2, screen_offset_y);
	}
}

CButtonsForwardsBackwards::~CButtonsForwardsBackwards() {
	if (this->button_array[0] != 0) {
		delete this->button_array[0];
	}
	if (this->button_array[1] != 0) {
		delete this->button_array[1];
	}
}

void CButtonsForwardsBackwards::set_distance(s16 distance_between) {
	this->distance_between = distance_between;
}

