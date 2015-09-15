#include "Movable.h"


CMovable::CMovable(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, bool mirrored, float start_moving_percentage, CLandscapeList* landscapelist, s16 landscape_width)
		: CCollidable(start_x, start_y, textures, number_of_textures, time_per_frame, bounding_box, mirrored) {
	this->pixel_per_step = pixel_per_step;
	this->moving_percentage = start_moving_percentage;
	this->x_change_residue = 0.0f;
	this->landscapelist = landscapelist;
	this->landscape_width = landscape_width;
}

void CMovable::set_moving(float percentage) {
	//-1.0: move left; 0.0: stop; 1.0: move right; values between: move slow
	this->moving_percentage = percentage;
	if (percentage > 0.0f) {
		this->set_mirrored(false);
	}else if (percentage < 0.0f) {
		this->set_mirrored(true);
	}
}

void CMovable::update(u16 time_steps) {
	CAnimated::update(time_steps);
	float moving = (pixel_per_step * moving_percentage * (float)time_steps) + x_change_residue ;
	

	// collision detection
	bool collision = false;
	do {
		if (this->landscapelist==0)
			break;
		collision = false;
		Rect bb = this->get_bounding_box();
		bb.y1++;
		bb.y2--;
		IntVector vec = {this->get_x(), this->get_y()};
		CCollidable* collider = 0;
		if (moving < 0) {
			// moving left...
			bb.x2 = bb.x1;
			bb.x1 += (s16)moving;
			if (this->get_x() + bb.x1 < 0 && this->landscape_width > 0) {
				moving += -bb.x1 - this->get_x();
				collision = true;
				if (moving >= 0) {
					return;
				}
				continue;
			}
			if (this->landscapelist->collide(vec,bb,collider,CCollidable::ObjectArea::RIGHT_EDGE,true)) {
				s16 new_x = collider->get_right() - this->get_bounding_box().x1 + 1;
				moving = new_x - this->get_x();
				collision = true;
				if (moving >= 0) {
					return;
				}
			}
			
		} else if (moving > 0) {
			// moving right...
			bb.x1 = bb.x2;
			bb.x2 += (s16)moving;
			if (this->get_x() + bb.x2 > this->landscape_width && this->landscape_width > 0) {
				moving += this->landscape_width-bb.x2 - this->get_x();
				collision = true;
				if (moving <= 0) {
					return;
				}
				continue;
			}
			if (this->landscapelist->collide(vec,bb,collider,CCollidable::ObjectArea::LEFT_EDGE,true)) {
				s16 new_x = collider->get_left() - this->get_bounding_box().x2 - 1;
				moving = new_x - this->get_x();
				collision = true;
				if (moving <= 0) {
					return;
				}
			}
		}
	
	}while(collision);
	
	
	s16 x_change = (s16)moving;
	moving -= (float)x_change;
	this->add_to_position(x_change, 0);
	this->x_change_residue = moving;
}

void CMovable::set_position(s16 x, s16 y) {
	CCollidable::set_position(x,y);
	this->x_change_residue = 0.0f;
}

CMovable::~CMovable() {
}

void CMovable::reset(s16 landscape_width) {
	this->landscape_width = landscape_width;
	this->moving_percentage = 0.0f;
	this->x_change_residue = 0.0f;
}

