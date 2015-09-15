#include "ButtonArray.h"

CButtonArray::CButtonArray(CTexture** button_textures, u16 number_of_button_textures) {
	this->button_array[0] = new CButton(0, button_textures, 0, number_of_button_textures, true);
	this->button_array[1] = new CButton(1, button_textures, 0, number_of_button_textures, true);
	this->button_array[2] = new CButton(2, button_textures, 0, number_of_button_textures, true);
	this->button_drawable[0] = false;
	this->button_drawable[1] = false;
	this->button_drawable[2] = false;
	this->active_button = 0;
	this->highlight_active_button = false;
	this->touch_down = false;
	this->a_inperrupted = false;
	this->a_down = false;
	this->active_touch_button = -1;
	this->last_touch_x = -1;
	this->last_touch_y = -1;
}

s16 CButtonArray::update(touchPosition touch, bool touch_hold, bool a_hold, bool up_pressed, bool down_pressed, s16 screen_offset_y) {
	if (!touch_hold && touch_down) {
		touch_down = false;
		if (active_touch_button < 0 || active_touch_button > 2) {
			active_touch_button = -1;
			return -1;
		}
		if (!button_drawable[active_touch_button]) {
			active_touch_button = -1;
			return -1;
		}
		active_button = active_touch_button;
		active_touch_button = -1;
		if (active_button >= 0 && active_button <= 2) {
			if (button_array[active_button] != 0) {
				button_array[active_button]->set_state(highlight_active_button?CButton::ButtonState::SELECTED:CButton::ButtonState::NORMAL);
				if (button_array[active_button]->is_at(this->last_touch_x, this->last_touch_y, screen_offset_y)) {
					return active_button;
				}
			}
		}
	} else if (touch_hold && !touch_down) {
		this->last_touch_x = touch.px;
		this->last_touch_y = touch.py;
		a_inperrupted = true;
		touch_down = true;
		active_touch_button = -1;
		for (s16 i=0; i<3; i++) {
			if (button_array[i] != 0 && button_drawable[i]) {
				if (button_array[i]->is_at(touch.px, touch.py, screen_offset_y)) {
					active_button = i;
					active_touch_button = i;
					button_array[active_button]->set_state(CButton::ButtonState::ACTIVE);
					break;
				}
			}
		}
	} else if (touch_hold && touch_down) {
		this->last_touch_x = touch.px;
		this->last_touch_y = touch.py;
		if (active_touch_button >= 0 && active_touch_button <= 2) {
			if (button_array[active_touch_button] != 0 && button_drawable[active_touch_button]) {
				if (button_array[active_touch_button]->is_at(touch.px, touch.py, screen_offset_y)) {
					button_array[active_touch_button]->set_state(CButton::ButtonState::ACTIVE);
				}else{
					button_array[active_touch_button]->set_state(highlight_active_button?CButton::ButtonState::SELECTED:CButton::ButtonState::NORMAL);
				}
			}
		}
	} else if (!a_hold && highlight_active_button) {
		if (!a_inperrupted && a_down) {
			// button_pressed!!!
			if (active_button >= 0 && active_button <= 2 && button_drawable[active_button]) {
				if (button_array[active_button] != 0) {
					button_array[active_button]->set_state(highlight_active_button?CButton::ButtonState::SELECTED:CButton::ButtonState::NORMAL);
					if (button_array[active_button]->is_at(touch.px, touch.py, screen_offset_y)) {
						a_down = false;
						a_inperrupted = false;
						return active_button;
					}
				}
			}
		}
		a_down = false;
		a_inperrupted = false;
	} else if (a_hold && !a_inperrupted && highlight_active_button) {
		a_down = true;
		if (active_button >= 0 && active_button <= 2 && button_drawable[active_button]) {
			if (button_array[active_button] != 0) {
				button_array[active_button]->set_state(CButton::ButtonState::ACTIVE);
			}
		}
	} else if (up_pressed && !down_pressed && highlight_active_button) {
		if (active_button >= 0 && active_button <= 2) {
			active_button += 2;
			active_button %= 3;
		}
	} else if (down_pressed && !up_pressed && highlight_active_button) {
		if (active_button >= 0 && active_button <= 2) {
			active_button += 1;
			active_button %= 3;
		}
	}
	return -1; // no button pressed.
}

void CButtonArray::set_button(s16 button_id, CTexture** text_textures, u16 number_of_text_textures) {
	if (button_id < 0 || button_id > 2)
		return;
	if (this->button_array[button_id] == 0)
		return;
	this->button_array[button_id]->set_text(text_textures, number_of_text_textures);
	if (text_textures == 0 || number_of_text_textures == 0) {
		button_drawable[button_id] = false;
	}else{
		button_drawable[button_id] = true;
	}
	if (!this->button_array[button_id]->is_enabled())
		this->button_array[button_id]->set_state(CButton::ButtonState::NORMAL);
}

void CButtonArray::set_enabled(s16 button_id, bool enabled) {
	if (button_id < 0 || button_id > 2)
		return;
	if (this->button_array[button_id] == 0)
		return;
	if (enabled && !this->button_array[button_id]->is_enabled())
		this->button_array[button_id]->set_state(CButton::ButtonState::NORMAL);
	else if (!enabled)
		this->button_array[button_id]->set_state(CButton::ButtonState::DISABLED);
}

void CButtonArray::draw(s16 screen_offset_y) {
	if (this->button_array[0] != 0) {
		this->button_array[0]->draw(0, screen_offset_y);
	}
	if (this->button_array[1] != 0) {
		this->button_array[1]->draw(0, screen_offset_y);
	}
	if (this->button_array[2] != 0) {
		this->button_array[2]->draw(0, screen_offset_y);
	}
}

CButtonArray::~CButtonArray() {
	if (this->button_array[0] != 0) {
		delete this->button_array[0];
	}
	if (this->button_array[1] != 0) {
		delete this->button_array[1];
	}
	if (this->button_array[2] != 0) {
		delete this->button_array[2];
	}
}

