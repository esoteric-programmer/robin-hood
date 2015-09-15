#include "Fallable.h"


CFallable::CFallable(s16 start_x, s16 start_y, CTexture* textures[], u16 number_of_textures, u16 time_per_frame, Rect bounding_box, float pixel_per_step, CLandscapeList* landscapelist, s16 landscape_width, s16 landscape_height, float g, bool ghost)
		: CMovable(start_x, start_y, textures, number_of_textures, time_per_frame, bounding_box, pixel_per_step, false, 0.0f, ghost?0:landscapelist, ghost?-1:landscape_width) {
	this->landscapelist = landscapelist;
	this->current_fallspeed = 0.0f;
	this->g = g;
	this->y_float = (float)this->get_y();
	this->staying_on_ground = false;
	this->landscape_height = landscape_height;
	this->fallen_down = false;
	this->ghost = ghost;
}

void CFallable::set_landscapelist(CLandscapeList* landscapelist) {
	this->landscapelist = landscapelist;
}

void CFallable::set_position(s16 x, s16 y) {
	CMovable::set_position(x,y);
	this->y_float = (float)y;
}

void CFallable::force_falling() {
	this->y_float++;
	this->add_to_position(0,1);
}

void CFallable::update(u16 time_steps) {
	if (fallen_down)
		return;
	CMovable::update(time_steps);
	// falling
	this->staying_on_ground = false;
	float new_y = (0.5f * this->g * (float)time_steps + this->current_fallspeed) * (float)time_steps + this->y_float;
	this->current_fallspeed += this->g * (float)time_steps;

	// collision detection
	bool collision = false;
	do {
		if (this->landscapelist==0)
			break;
		collision = false;
		Rect bb = this->get_bounding_box();
		IntVector vec = {this->get_x(), this->get_y()};
		CCollidable* collider = 0;
		if (new_y < this->y_float && !this->ghost) {
			// jumping...
			bb.y2 = bb.y1+1;
			bb.y1 += new_y - this->y_float;
			if (this->get_y() + bb.y1 < -this->landscape_height && this->landscape_height > 0) {
				// collision with top of level
				new_y += -bb.y1 - this->get_y() -this->landscape_height;
				collision = true;
				if (new_y >= this->y_float) {
					return;
				}
				continue;
			}
			if (this->landscapelist->collide(vec,bb,collider,CCollidable::ObjectArea::BOTTOM_EDGE,true)) {
				this->current_fallspeed = 0.0f;
				new_y = collider->get_bottom() - this->get_bounding_box().y1;
				collision = true;
				if (new_y >= this->y_float) {
					return;
				}
			}
			
		} else if (new_y > this->y_float) {
			// falling...
			bb.y1 = bb.y2-1;
			bb.y2 += new_y - this->y_float;
			if (this->landscapelist->collide(vec,bb,collider,CCollidable::ObjectArea::TOP_EDGE,false)) {
				this->current_fallspeed = 0.0f;
				new_y = collider->get_top() - this->get_bounding_box().y2 - 1;
				collision = true;
				this->staying_on_ground = true;
				if (new_y <= this->y_float) {
					return;
				}
			}
		}
	
	}while(collision);
	
	
	this->y_float = new_y;
	this->add_to_position(0,((s16)this->y_float) - this->get_y());
	
	if (this->get_y() > 0) {
		this->fallen_down = true;
	}
}

void CFallable::reset(s16 landscape_width, s16 landscape_height) {
	CMovable::reset(landscape_width);
	this->landscape_height = landscape_height;
	this->current_fallspeed = 0.0f;
	this->staying_on_ground = false;
	this->fallen_down = false;
	this->y_float = (float)this->get_y();
}

void CFallable::set_current_fallspeed(float speed) {
	this->current_fallspeed = speed;
}

bool CFallable::stays_on_ground() {
	return this->staying_on_ground;
}

bool CFallable::left_landscape(){
	return fallen_down;
}

CFallable::~CFallable() {
}

