#include "Button.h"
#include "defines.h"

CButton::CButton(s16 button_pos, CTexture** button_textures, CTexture** text_textures, u16 number_of_textures_each, bool enabled, bool arrow_button, bool mirrored)
		: CDrawable((TOUCH_SCREEN_WIDTH - button_textures[0]->get_width()) / 2, ((5*button_pos+1)*button_textures[0]->get_height()) / 4) {
	this->button_textures = button_textures;
	this->text_textures = text_textures;
	this->number_of_text_textures = number_of_textures_each;
	this->number_of_button_textures = number_of_textures_each;
	this->state = (enabled?ButtonState::NORMAL:ButtonState::DISABLED);
	this->arrow_button = arrow_button;
	this->mirrored = mirrored;
}

u16 CButton::get_texture_index() {
	switch (this->state) {
		case ButtonState::NORMAL:
			return 0;
		case ButtonState::SELECTED:
			if (this->number_of_button_textures > 1 && this->number_of_text_textures > 1)
				return 1;
			else
				return 0;
		case ButtonState::ACTIVE:
			if (this->number_of_button_textures > 2 && this->number_of_text_textures > 2)
				return 2;
			else if (this->number_of_button_textures > 1 && this->number_of_text_textures > 1)
				return 1;
			else
				return 0;
		case ButtonState::DISABLED:
			if (this->number_of_button_textures > 3 && this->number_of_text_textures > 3)
				return 4;
			else
				return 0;
		default:
			return 0;
	}
}


void CButton::set_text(CTexture** text_textures, u16 number_of_textures) {
	this->text_textures = text_textures;
	this->number_of_text_textures = number_of_textures;
}

void CButton::set_state(ButtonState state) {
	this->state = state;
}

bool CButton::is_enabled() {
	return (this->state != ButtonState::DISABLED);
}

CButton::ButtonState CButton:: get_state() {
	return this->state;
}

bool CButton::is_at(u16 x, u16 y, s16 screen_offset_y) {

	if (this->button_textures == 0)
		return false;
	if (this->button_textures[this->get_texture_index()] == 0)
		return false;

/*	
	u32 pixel;
	pixel = this->button_textures[this->get_texture_index()]->pixel_at(x - this->get_x(), y - (this->get_y() - screen_offset_y));
	if (pixel != 0) {
		return true;
	}
	return false;
*/

	x -= this->get_x();
	y -= this->get_y() - screen_offset_y;
	s16 width = this->button_textures[this->get_texture_index()]->get_width();
	s16 height = this->button_textures[this->get_texture_index()]->get_height();
	
	if (x>=0 && y>= 0 && x < width && y < height && x+y >= height/2 && x-y+height/2 >= 0 && width-x+y >= height/2 && width-x-y+height/2 >= 0)
		return true;
		
	if (arrow_button && x>= 0 && y>= 0 && x < width && y < height && !this->mirrored && width-x+y >= height/2 && width-x-y+height/2 >= 0)
		return true;
	if (arrow_button && x>= 0 && y>= 0 && x < width && y < height && this->mirrored && x+y >= height/2 && x-y+height/2 >= 0)
		return true;
	return false;


}

void CButton::draw(s16 screen_offset_x, s16 screen_offset_y) {
	if (this->button_textures != 0) {
		if (this->button_textures[this->get_texture_index()]) {
			if (this->arrow_button || this->text_textures != 0) {
				this->button_textures[this->get_texture_index()]->draw(this->get_x()-screen_offset_x, this->get_y()-screen_offset_y, this->mirrored);
			}
			if (this->text_textures != 0) {
				if (this->text_textures[this->get_texture_index()] != 0) {
					s16 text_offset_x = ((s16)this->button_textures[this->get_texture_index()]->get_width() - (s16)this->text_textures[this->get_texture_index()]->get_width()) / 2;
					s16 text_offset_y = ((s16)this->button_textures[this->get_texture_index()]->get_height() - (s16)this->text_textures[this->get_texture_index()]->get_height()) / 2 + 2;
					this->text_textures[this->get_texture_index()]->draw(this->get_x()+text_offset_x-screen_offset_x, this->get_y()+text_offset_y-screen_offset_y, this->mirrored);
				}
			}
		}
	}
}

void CButton::update(u16 time_steps) {
}

CButton::~CButton() {
}

